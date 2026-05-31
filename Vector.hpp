#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <stdexcept>

template<typename T>
class Vector {
  public:
    Vector();
    ~Vector();
    Vector(const Vector<T>& other);
    Vector<T>& operator=(const Vector<T>& other);
    void push_back(const T& value);
    void pop_back();
    T& back();
    const T& back() const;
    std::size_t size() const;
    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;
    T& at(std::size_t index);
    const T& at(std::size_t index) const;
    bool empty() const;
    void clear();
  private:
    T* data;
    std::size_t sz;
    std::size_t capacity;
    void grow();
};

template<typename T>
Vector<T>::Vector() : data(nullptr), sz(0), capacity(0) {}

template<typename T>
Vector<T>::~Vector() {delete[] data;}

template<typename T>
Vector<T>::Vector(const Vector<T>& other) : data(nullptr), sz(other.sz), capacity(other.capacity) {
    data = new T[capacity];
    for (std::size_t i = 0; i < sz; i++) {
        data[i] = other.data[i];
    }
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
    if (this == &other) return *this;

    T* newData = new T[other.capacity];

    for (std::size_t i = 0; i < other.sz; i++) {
        newData[i] = other.data[i];
    }
    delete[] data;

    data = newData;
    capacity = other.capacity;
    sz = other.sz;

    return *this;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (sz >= capacity) grow();
    data[sz] = value;
    sz++;
}

template<typename T>
void Vector<T>::pop_back() {
    if (sz > 0) sz--;
}

template<typename T>
T& Vector<T>::back() {
    if (empty()) {
        throw std::out_of_range("Vector is empty\n");
    }
    return data[sz-1];
}

template<typename T>
const T& Vector<T>::back() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty\n");
    }
    return data[sz-1];
}

template<typename T>
std::size_t Vector<T>::size() const {
    return sz;
}

template<typename T>
T& Vector<T>::operator[](std::size_t index) {
    if (index >= sz) {
        throw std::out_of_range("Index out of range\n");
    }
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](std::size_t index) const {
    if (index >= sz) {
        throw std::out_of_range("Index out of range\n");
    }
    return data[index];
}

template<typename T>
T& Vector<T>::at(std::size_t index) {
    if (index >= sz) {
        throw std::out_of_range("Index out of range\n");
    }
    return data[index];
}

template<typename T>
const T& Vector<T>::at(std::size_t index) const {
    if (index >= sz) {
        throw std::out_of_range("Index out of range\n");
    }
    return data[index];
}

template<typename T>
bool Vector<T>::empty() const {
    return (sz == 0);
}

template<typename T>
void Vector<T>::clear() {
    sz = 0;
}

template<typename T>
void Vector<T>::grow() {
    std::size_t newCapacity;

    if (capacity==0) {
        newCapacity = 1;
    } else {
        newCapacity = capacity * 2;
    }

    T* newData = new T[newCapacity];

    for (std::size_t i = 0; i < sz; i++) {
        newData[i] = data[i];
    }
    delete[] data;

    capacity = newCapacity;
    data = newData;
}

#endif // VECTOR_HPP