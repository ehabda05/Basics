#include <cstddef>
#include <stdexcept>

template<typename T>
class Vector {
  public:
    Vector() : data(nullptr), n(0), capacity(0) {}

    ~Vector() {delete[] data;}

    Vector(const Vector& other) : data(nullptr), n(other.n), capacity(other.capacity) {
        data = new T[capacity];
        for (std::size_t i = 0; i < n; i++) {
            data[i] = other.data[i];
        }
    }
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        capacity = other.capacity;
        n = other.n;

        T* newData = new T[capacity];
        for (std::size_t i = 0; i < n; i++) {
            newData[i] = other.data[i];
        }
        delete[] data;
        data = newData;
        return *this;
    }

    void push_back(const T& value) {
        if (n >= capacity) grow();
        data[n] = value;
        n++;
    }

    void pop_back() {
        if (n > 0) n--;
    }

    T& back() {
        if (empty()) {
            throw std::out_of_range("Vector is empty\n");
        }
        return data[n-1];
    }

    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Vector is empty\n");
        }
        return data[n-1];
    }

    std::size_t size() const {
        return n;
    }

    T& operator[](std::size_t index) {
        if (index >= n) {
            throw std::out_of_range("Index out of range\n");
        }
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        if (index >= n) {
            throw std::out_of_range("Index out of range\n");
        }
        return data[index];
    }

    T& at(std::size_t index) {
        if (index >= n) {
            throw std::out_of_range("Index out of range\n");
        }
        return data[index];
    }

    const T& at(std::size_t index) const {
        if (index >= n) {
            throw std::out_of_range("Index out of range\n");
        }
        return data[index];
    }

    bool empty() const {
        return (n == 0);
    }

    void clear() {
        n = 0;
    }
  private:
    T* data;
    std::size_t n;
    std::size_t capacity;
    void grow() {
        std::size_t newCapacity;

        if (n==0) {
            newCapacity = 1;
        } else {
            newCapacity = capacity * 2;
        }

        T* newData = new T[newCapacity];

        for (std::size_t i = 0; i < n; i++) {
            newData[i] = data[i];
        }
        delete[] data;

        capacity = newCapacity;
        data = newData;
    }
};