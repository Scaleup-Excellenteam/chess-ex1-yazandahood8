#pragma once
#include <condition_variable>
#include <functional>
#include <future>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>


// ThreadPool: a simple fixed-size thread pool for concurrent task execution.
class ThreadPool {
public:
    // Constructs a thread pool with the specified number of worker threads.
    explicit ThreadPool(size_t Threadsnum);

    // Destructor: joins all threads and cleans up.
    ~ThreadPool();

    // Adds a new task to the thread pool.
    // Accepts any callable object and its arguments.
    // Returns a std::future for retrieving the result asynchronously.
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type>;

private:
    std::vector<std::thread> workers;                     // Worker threads
    std::queue<std::function<void()>> tasks;           // Task queue
    std::mutex queueM;                            // Mutex for task queue
    std::condition_variable cond;                 // For worker notification
    bool isStopped = false;                                 // Stop flag for shutdown
};

// Enqueues a new task into the thread pool for execution.
//   F      - callable type (function, lambda, functor, etc.)
//   Args   - arguments to pass to F
// Returns: std::future<ReturnType> for getting the result.
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using return_type = typename std::result_of<F(Args...)>::type;

    // Wrap the callable and its arguments in a packaged_task.
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queueM);
        if (isStopped)
            throw std::runtime_error("stopped ThreadPool");
        // Add the packaged task to the queue as a void() lambda.
        tasks.emplace([task]() { (*task)(); });
    }
    // Notify one waiting worker thread.
    cond.notify_one();
    return res;
}
