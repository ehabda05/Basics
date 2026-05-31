#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class Queue {
  public:
    Queue();
    ~Queue();
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    const T& front() const;
    void push(const T& value);
    void pop();
    bool empty() const;
    void clear();
    std::size_t size() const;

  private:
    struct Node {
        T val;
        Node* next;
        Node(const T&v) : val(v), next(nullptr) {}
    };
    Node* first;
    Node* last;
    std::size_t sz;
};

template<typename T>
Queue<T>::Queue() : first(nullptr), last(nullptr),sz(0) {}

template<typename T>
Queue<T>::~Queue() {
    clear();
}

template<typename T>
Queue<T>::Queue(const Queue<T>& other) : first(nullptr), last(nullptr), sz(0) {
    Node* cur = other.first;
    while (cur != nullptr) {
        push(cur->val);
        cur = cur->next;
    }
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other) {
    if (this == &other) return *this;

    clear();
    Node* cur = other.first;
    while (cur != nullptr) {
        push(cur->val);
        cur = cur->next;
    }

    return *this;
}

template<typename T>
const T& Queue<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Queue empty\n");
    }
    return first->val;
}

template<typename T>
void Queue<T>::push(const T& value) {
    Node* newNode = new Node(value);
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        last->next = newNode;
        last = last->next;
    }
    sz++;
}

template<typename T>
void Queue<T>::pop() {
    if (empty()) return;
    Node* oldFirst = first;
    first = first->next;
    delete oldFirst;
    sz--;
    if (sz == 0) last = nullptr;
}

template<typename T>
bool Queue<T>::empty() const {
    return (sz == 0);
}

template<typename T>
void Queue<T>::clear() {
    while (!empty()) pop();
}

template<typename T>
std::size_t Queue<T>::size() const {
    return sz;
}

#endif // QUEUE_HPP