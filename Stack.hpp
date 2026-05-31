#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class Stack {
  public:
    Stack();
    ~Stack();
    Stack(const Stack<T>& other);
    Stack<T>& operator=(const Stack<T>& other);
    const T& top() const;
    void push(const T& value);
    void pop();
    bool empty() const;
    std::size_t size() const;

  private:
    T* data;
    std::size_t sz;
    std::size_t cap;

    void grow();
};

template<typename T>
Stack<T>::Stack() : data(nullptr), sz(0), cap(0) {}

template<typename T>
Stack<T>::~Stack() {
    delete[] data;
}

template<typename T>
Stack<T>::Stack(const Stack<T>& other) : data(nullptr), sz(other.sz), cap(other.cap) {
    data = new T[cap];
    for (std::size_t i = 0; i < sz; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other) {
    if (this == &other) return *this;

    T* newData = new T[other.cap];
    for (std::size_t i = 0; i < other.sz; i++) {
        newData[i] = other.data[i];
    }
    delete[] data;
    data = newData;
    sz = other.sz;
    cap = other.cap;
    return *this;
}

template<typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::out_of_range("Stack empty\n");
    }
    return data[sz-1];
}

template<typename T>
void Stack<T>::push(const T& value) {
    if (sz >= cap) grow();
    data[sz] = value;
    sz++;
}

template<typename T>
void Stack<T>::pop() {
    if (!empty()) sz--;
}

template<typename T>
bool Stack<T>::empty() const {
    return (sz == 0);
}

template<typename T>
void Stack<T>::grow() {
    std::size_t newCap;
    if (cap == 0) newCap = 1;
    else newCap = cap * 2;

    T* newData = new T[newCap];
    for (std::size_t i = 0; i < sz; i++) {
        newData[i] = data[i];
    }
    delete[] data;

    data = newData;
    cap = newCap;
}

template<typename T>
std::size_t Stack<T>::size() const {
    return sz;
}

#endif // STACK_HPP