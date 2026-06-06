#ifndef MAXHEAP_HPP
#define MAXHEAP_HPP

#include <cstddef>
#include <stdexcept>
#include "Vector.hpp"

template<typename T>
class MaxHeap{
  public:
    MaxHeap();
    ~MaxHeap();
    MaxHeap(const MaxHeap<T>& other);
    MaxHeap<T>& operator=(const MaxHeap<T>& other);
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
MaxHeap<T>::MaxHeap() {}

template<typename T>
MaxHeap<T>::~MaxHeap() {}

template<typename T>
MaxHeap<T>::MaxHeap(const MaxHeap<T>& other) : data(other.data) {}

template<typename T>
MaxHeap<T>& MaxHeap<T>::operator=(const MaxHeap<T>& other) {
  if (this == &other) return *this;
  data = other.data;
  return *this;
}

template<typename T>
void MaxHeap<T>::push(const T& value) {
  data.push_back(value);
  heapifyUp(data.size()-1);
}

template<typename T>
void MaxHeap<T>::pop() {
  if (empty()) {
    throw std::out_of_range("Heap Empty\n");
  }

  data[0] = data[size()-1];
  data.pop_back();
  if (!empty()) heapifyDown(0);
}

template<typename T>
T& MaxHeap<T>::top() {
  if (empty()) {
    throw std::out_of_range("Heap Empty\n");
  }
  return data[0];
}

template<typename T>
const T& MaxHeap<T>::top() const {
  if (empty()) {
    throw std::out_of_range("Heap Empty\n");
  }
  return data[0];
}

template<typename T>
bool MaxHeap<T>::empty() const {
  return data.empty();
}

template<typename T>
std::size_t MaxHeap<T>::size() const {
  return data.size();
}

template<typename T>
void MaxHeap<T>::clear() {
  data.clear();
}

template<typename T>
void MaxHeap<T>::heapifyUp(std::size_t index) {
  while (index > 0) {
        std::size_t parent = (index - 1) / 2;

        if (data[parent] >= data[index]) break;
        T temp = data[parent];
        data[parent] = data[index];
        data[index] = temp;

        index = parent;
    }
}

template<typename T>
void MaxHeap<T>::heapifyDown(std::size_t index) {
  std::size_t n = size();
  while (index < n) {
        std::size_t left = index*2 + 1;
        std::size_t right = index*2 + 2;
        std::size_t largest = index;
        
        if (left < n && data[left] > data[largest]) largest = left;
        if (right < n && data[right] > data[largest]) largest = right;
        if (largest == index) break;

        T temp = data[index];
        data[index] = data[largest];
        data[largest] = temp;

        index = largest;
    }
} 

#endif // MAXHEAP_HPP