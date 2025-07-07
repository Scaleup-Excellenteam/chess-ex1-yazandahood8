#include "ThreadPool.h"

// Constructor: launches worker threads and starts the pool.
// Each thread waits for tasks and executes them as they arrive.
ThreadPool::ThreadPool(size_t Threadsnum) : isStopped(false)
{
    for (size_t i = 0; i < Threadsnum; ++i)
    {
        workers.emplace_back([this]
                             {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(this->queueM);
                    // Wait for a task or shutdown signal.
                    this->cond.wait(lock, [this]{
                         return this->isStopped || !this->tasks.empty(); 
                        });
                    // Exit if shutdown and all tasks have been processed.
                    if (this->isStopped && this->tasks.empty())
                        return;
                    // Pop a task from the queue.
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                // Execute the retrieved task outside the lock.
                task();
            } });
    }
}

// Destructor: signals all threads to isStopped and waits for their completion.
// Ensures clean shutdown (no tasks left hanging, no deadlocks).
ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queueM);
        isStopped = true; // Set the flag to notify all workers to exit
    }
    cond.notify_all(); // Wake up all threads (so they see 'isStopped' is true)
    for (std::thread &worker : workers)
        worker.join(); // Wait for each worker thread to finish
}
