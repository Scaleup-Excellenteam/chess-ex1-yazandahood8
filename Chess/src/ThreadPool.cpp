#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads)
{
    isStopping = false;
    activeTaskCount = 0;

    for (size_t i = 0; i < numThreads; ++i)
    {
        workerThreads.emplace_back(&ThreadPool::workerLoop, this);
    }
}

ThreadPool::~ThreadPool()
{
    shutdown();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    {
        std::lock_guard<std::mutex> guard(taskQueueMutex);
        taskQueue.push(std::move(task));
    }

    taskAvailable.notify_one();
}

void ThreadPool::workerLoop()
{
    while (true)
    {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(taskQueueMutex);

            taskAvailable.wait(lock, [this]()
            {
                std::lock_guard<std::mutex> stopGuard(stopMutex);
                return isStopping || !taskQueue.empty();
            });

            if (isStopping && taskQueue.empty())
            {
                return;
            }

            task = std::move(taskQueue.front());
            taskQueue.pop();
        }

        {
            std::lock_guard<std::mutex> activeLock(activeMutex);
            ++activeTaskCount;
        }

        // Execute the task
        task();

        {
            std::lock_guard<std::mutex> activeLock(activeMutex);
            --activeTaskCount;
        }

        // Notify in case wait_for_all is waiting
        idleCondition.notify_all();
    }
}

void ThreadPool::wait_for_all()
{
    std::unique_lock<std::mutex> lock(activeMutex);

    idleCondition.wait(lock, [this]()
    {
        std::lock_guard<std::mutex> queueGuard(taskQueueMutex);
        return taskQueue.empty() && activeTaskCount == 0;
    });
}

void ThreadPool::shutdown()
{
    {
        std::lock_guard<std::mutex> queueLock(taskQueueMutex);
        std::lock_guard<std::mutex> stopLock(stopMutex);
        isStopping = true;
    }

    taskAvailable.notify_all();

    for (auto& thread : workerThreads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }

    workerThreads.clear();
}
