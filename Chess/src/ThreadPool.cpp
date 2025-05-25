#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads)
{
    stopFlag = false;

    for (size_t i = 0; i < numThreads; ++i) {
        std::thread worker;
        worker = std::thread(&ThreadPool::workerLoop, this);
        workers.push_back(std::move(worker));
    }
}

ThreadPool::~ThreadPool()
{
    shutdown();
}

void ThreadPool::enqueue(std::function<void()> task)
{
    std::lock_guard<std::mutex> lock(queueMutex);
    tasks.push(std::move(task));
    cv.notify_one();
}

void ThreadPool::workerLoop()
{
    while (true) {
        std::function<void()> task;

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            cv.wait(lock, [this] {
                bool shouldWake = false;

                {
                    std::lock_guard<std::mutex> stopLock(stopMutex);
                    if (stopFlag || !tasks.empty()) {
                        shouldWake = true;
                    }
                }

                return shouldWake;
            });

            bool shouldExit = false;

            {
                std::lock_guard<std::mutex> stopLock(stopMutex);
                if (stopFlag && tasks.empty()) {
                    shouldExit = true;
                }
            }

            if (shouldExit) {
                return;
            }

            task = std::move(tasks.front());
            tasks.pop();
        }

        task();
    }
}

void ThreadPool::shutdown()
{
    {
        std::lock_guard<std::mutex> lock1(queueMutex);
        std::lock_guard<std::mutex> lock2(stopMutex);
        stopFlag = true;
    }

    cv.notify_all();

    for (size_t i = 0; i < workers.size(); ++i) {
        std::thread& t = workers[i];

        if (t.joinable()) {
            t.join();
        }
    }

    workers.clear();
}
