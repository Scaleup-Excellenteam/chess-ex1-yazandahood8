#pragma once
#include <iostream>
#include <mutex>
#include <stdexcept>

// Thread-safe singly-linked priority queue
// Comparator should return >0 if first argument has higher priority

template <typename T, typename Comparator>
class PriorityQueue {
private:
    Node* head;
    Comparator comp;
    struct Node {
        T value;
        Node* next;
        Node(const T& val) : value(val), next(nullptr) {}
    };
    Node* head;
    Comparator comp;
    mutable std::mutex pqMutex;


public:
    PriorityQueue()
        : head(nullptr), comp(Comparator()) {}

    ~PriorityQueue() {
        std::lock_guard<std::mutex> lock(pqMutex);
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Push a new value into the queue
    void push(const T& value) {
        Node* newNode = new Node(value);
        std::lock_guard<std::mutex> lock(pqMutex);
        if (!head || comp(value, head->value) > 0) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next && comp(value, current->next->value) <= 0) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // Retrieve and remove the highest-priority element
    T poll() {
        std::lock_guard<std::mutex> lock(pqMutex);
        if (!head) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        Node* temp = head;
        T value = temp->value;
        head = head->next;
        delete temp;
        return value;
    }

    // Check if the queue is empty
    bool isEmpty() const {
        std::lock_guard<std::mutex> lock(pqMutex);
        return head == nullptr;
    }

    // Print top 3 elements without modifying the queue
    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue& pq) {
        std::lock_guard<std::mutex> lock(pq.pqMutex);
        Node* current = pq.head;
        int count = 0;
        while (current && count < 3) {
            os << current->value << std::endl;
            current = current->next;
            ++count;
        }
        return os;
    }
};
