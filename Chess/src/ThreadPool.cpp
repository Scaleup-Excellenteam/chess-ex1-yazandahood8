#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads)
    : stopFlag(false)
{
    for (size_t i = 0; i < numThreads; ++i)
        workers.emplace_back(&ThreadPool::workerLoop, this);
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
    }
    cv.notify_one();
}

void ThreadPool::workerLoop() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            cv.wait(lock, [this]{ return stopFlag || !tasks.empty(); });
            if (stopFlag && tasks.empty()) return;
            task = std::move(tasks.front());
            tasks.pop();
        }
        task();
    }
}

void ThreadPool::shutdown() {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        stopFlag = true;
    }
    cv.notify_all();
    for (auto &t : workers)
        if (t.joinable()) t.join();
    workers.clear();
}
