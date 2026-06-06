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

#endif // MINHEAP_HPP