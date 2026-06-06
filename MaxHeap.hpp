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

#endif // MAXHEAP_HPP