#pragma once
#include <iostream>

template <typename T, typename Comparator>
class PriorityQueue {
private:
    Node* head;
    Comparator comp;
    struct Node {
        T value;
        Node* next;
        Node(T val) : value(val), next(nullptr) {}
    };
public:
    PriorityQueue() : head(nullptr) {}
    ~PriorityQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
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

    T poll() {
        if (!head) {
            throw std::out_of_range("PriorityQueue is empty");
        }
        Node* temp = head;
        T value = temp->value;
        head = head->next;
        delete temp;
        return value;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const PriorityQueue& pq) {
        Node* current = pq.head;
        int count = 0;
        while (current && count < 3) { // Print top 3 moves
            os << current->value << std::endl;
            current = current->next;
            count++;
        }
        return os;
    }
};
