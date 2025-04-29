#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <list>
#include <stdexcept>

template<typename T, typename Comparator>
class PriorityQueue {
    std::list<T> data;
    Comparator comp;

public:
    void push(const T& item) {
        auto it = data.begin();
        while (it != data.end() && comp(*it, item) < 0)
            ++it;
        data.insert(it, item);
        if (data.size() > 5)
            data.pop_back();
    }

    T poll() {
        if (data.empty())
            throw std::runtime_error("Polling from empty queue");
        T top = data.front();
        data.pop_front();
        return top;
    }

    bool empty() const { return data.empty(); }

    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }
};

#endif
