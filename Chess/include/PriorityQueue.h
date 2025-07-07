#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <list>
#include <algorithm>
#include <mutex>
#include <vector>

// Comparator for priority queue elements.
// Compares based on the 'first' element of the pair (for min/max priority behavior).
template<typename T>
struct MyComparator {
    bool operator()(const T& a, const T& b) const {
        return a.first < b.first;
    }
};

// Thread-safe, fixed-size priority queue (max size = 5 by default).
// Stores elements ordered by priority; supports concurrent access.
template<typename T, typename Comparator = MyComparator<T>>
class PriorityQueue {
    std::list<T> queue;          // Underlying container for elements.
    Comparator comp;             // Comparison functor (default: MyComparator).
    mutable std::mutex safetyThread;  // Mutex for thread-safety.
    static const size_t MAX_SIZE = 5; // Maximum allowed queue size.

public:
    // Insert an element into the queue in priority order.
    // If the queue exceeds MAX_SIZE, removes the lowest priority item.
    void push(const T& value) {
        std::lock_guard<std::mutex> lockMutex(safetyThread);
        auto it = queue.begin();
        while (it != queue.end() && comp(*it, value)) {
            ++it;
        }
        queue.insert(it, value);
        if (queue.size() > MAX_SIZE) {
            queue.pop_back();
        }
    }

    // Returns the element with the highest priority (front of the queue).
    // (Assumes queue is not empty)
    T top() const {
        std::lock_guard<std::mutex> lockMutex(safetyThread);
        return queue.front();
    }

    // Removes the element with the highest priority.
    void pop() {
        std::lock_guard<std::mutex> lockMutex(safetyThread);
        if (!queue.empty()) {
            queue.pop_front();
        }
    }

    // Checks if the queue is empty.
    bool empty() const {
        std::lock_guard<std::mutex> lockMutex(safetyThread);
        return queue.empty();
    }

    // Returns the current number of elements in the queue.
    size_t size() const {
        std::lock_guard<std::mutex> lockMutex(safetyThread);
        return queue.size();
    }

    // Returns a vector containing all elements in priority order.
    std::vector<T> QueueToVector() const {
        std::lock_guard<std::mutex> lockMutex(safetyThread);
        return std::vector<T>(queue.begin(), queue.end());
    }
};

#endif // PRIORITYQUEUE_H
