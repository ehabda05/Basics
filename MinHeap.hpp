#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include <cstddef>
#include <stdexcept>
#include "Vector.hpp"

template<typename T>
class MinHeap{
  public:
    MinHeap();
    ~MinHeap();
    MinHeap(const MinHeap<T>& other);
    MinHeap<T>& operator=(const MinHeap<T>& other);
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;
    bool empty() const;
    std::size_t size() const;
    void clear();

  private:
    Vector<T> data;
    void heapifyUp(std::size_t index);
    void heapifyDown(std::size_t index);    
};

template<typename T> 
MinHeap<T>::MinHeap() {}

template<typename T>
MinHeap<T>::~MinHeap() {}

template<typename T>
MinHeap<T>::MinHeap(const MinHeap<T>& other) : data(other.data) {}

template<typename T>
MinHeap<T>& MinHeap<T>::operator=(const MinHeap<T>& other) {
  if (this == &other) return *this;
  data = other.data;
  return *this;
}

template<typename T>
void MinHeap<T>::push(const T& value) {
  data.push_back(value);
  heapifyUp(data.size()-1);
}

template<typename T>
void MinHeap<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Heap Empty\n");
  }

  data[0] = data[size()-1];
  data.pop_back();
  if (!empty()) heapifyDown(0);
}

template<typename T>
T& MinHeap<T>::top() {
  if (empty()) {
    throw std::out_of_range("Heap Empty\n");
  }
  return data[0];
}

template<typename T>
const T& MinHeap<T>::top() const {
  if (empty()) {
    throw std::out_of_range("Heap Empty\n");
  }
  return data[0];
}

template<typename T>
bool MinHeap<T>::empty() const {
  return data.empty();
}

template<typename T>
std::size_t MinHeap<T>::size() const {
  return data.size();
}

template<typename T>
void MinHeap<T>::clear() {
  data.clear();
}

template<typename T>
void MinHeap<T>::heapifyUp(std::size_t index) {
  while (index > 0) {
        std::size_t parent = (index - 1) / 2;

        if (data[parent] <= data[index]) break;
        T temp = data[parent];
        data[parent] = data[index];
        data[index] = temp;

        index = parent;
    }
}

template<typename T>
void MinHeap<T>::heapifyDown(std::size_t index) {
  std::size_t n = size();
  while (index < n) {
        std::size_t left = index*2 + 1;
        std::size_t right = index*2 + 2;
        std::size_t smallest = index;
        
        if (left < n && data[left] < data[smallest ]) smallest = left;
        if (right < n && data[right] < data[smallest ]) smallest = right;
        if (smallest == index) break;

        T temp = data[index];
        data[index] = data[smallest];
        data[smallest ] = temp;

        index = smallest;
    }
} 

#endif // MINHEAP_HPP