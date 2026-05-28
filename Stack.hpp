#include <cstddef>
#include <stdexcept>

template<typename T>
class Stack {
  public:
    Stack() : data(nullptr), sz(0), cap(0) {}

    ~Stack() {
        delete[] data;
    }

    Stack(const Stack& other) : data(nullptr), sz(other.sz), cap(other.cap) {
        data = new T[cap];
        for (std::size_t i = 0; i < sz; i++) {
            data[i] = other.data[i];
        }
    }

    Stack& operator=(const Stack& other) {
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

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Stack empty\n");
        }
        return data[sz-1];
    }

    void push(const T& value) {
        if (sz >= cap) grow();
        data[sz] = value;
        sz++;
    }

    void pop() {
        if (!empty()) sz--;
    }

    bool empty() const {
        return (sz == 0);
    }

  private:
    T* data;
    std::size_t sz;
    std::size_t cap;

    void grow() {
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
};