#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class Deque {
  public:
    Deque();
    ~Deque();
    Deque(const Deque<T>& other);
    Deque<T>& operator=(const Deque<T>& other);
    const T& front() const;
    const T& back() const;
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    bool empty() const;
    void clear();

  private:
    struct Node {
        T val;
        Node* next;
        Node* prev;

        Node(const T&v) : val(v), next(nullptr), prev(nullptr) {}
    };
    Node* first;
    Node* last;
    std::size_t sz;
};

template<typename T>
Deque<T>::Deque() : first(nullptr), last(nullptr),sz(0) {}

template<typename T>
Deque<T>::~Deque() {
    clear();
}

template<typename T>
Deque<T>::Deque(const Deque<T>& other) : first(nullptr), last(nullptr), sz(0) {
    Node* cur = other.first;
    while (cur != nullptr) {
        push_back(cur->val);
        cur = cur->next;
    }
}

template<typename T>
Deque<T>& Deque<T>::operator=(const Deque<T>& other) {
    if (this == &other) return *this;

    clear();
    Node* cur = other.first;
    while (cur != nullptr) {
        push_back(cur->val);
        cur = cur->next;
    }

    return *this;
}

template<typename T>
const T& Deque<T>::front() const {
    if (empty()) {
        throw std::out_of_range("Deque empty\n");
    }
    return first->val;
}

template<typename T>
const T& Deque<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Deque empty\n");
    }
    return last->val;
}

template<typename T>
void Deque<T>::push_front(const T& value) {
    Node* newNode = new Node(value);
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        first->prev = newNode;
        newNode->next = first;
        first = newNode;
    }
    sz++;
}

template<typename T>
void Deque<T>::push_back(const T& value) {
    Node* newNode = new Node(value);
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        newNode->prev = last;
        last->next = newNode;
        last = last->next;
    }
    sz++;
}

template<typename T>
void Deque<T>::pop_front() {
    if (empty()) return;
    Node* oldFirst = first;
    first = first->next;
    if (first != nullptr) first->prev = nullptr;
    delete oldFirst;
    sz--;
    if (sz == 0) last = nullptr;
}

template<typename T>
void Deque<T>::pop_back() {
    if (empty()) return;
    Node* oldLast = last;
    last = last->prev;
    if (last != nullptr) last->next = nullptr;
    delete oldLast;
    sz--;
    if (sz == 0) first = nullptr;
}

template<typename T>
bool Deque<T>::empty() const {
    return (sz == 0);
}

template<typename T>
void Deque<T>::clear() {
    while (!empty()) pop_front();
}

#endif // DEQUE_HPP