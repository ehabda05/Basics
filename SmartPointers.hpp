#ifndef SMARTPOINTERS_HPP
#define SMARTPOINTERS_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class UniquePtr {
  public:
    UniquePtr();
    explicit UniquePtr(T* p);
    ~UniquePtr();

    UniquePtr(const UniquePtr<T>& other) = delete;
    UniquePtr<T>& operator=(const UniquePtr<T>& other) = delete;

    UniquePtr(UniquePtr<T>&& other) noexcept;
    UniquePtr<T>& operator=(UniquePtr<T>&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;

    T* release();
    void reset(T* newPtr = nullptr);

    explicit operator bool() const;

  private:
    T* ptr;
};

template<typename T>
class SharedPtr {
  public:
    SharedPtr();
    explicit SharedPtr(T* p);
    ~SharedPtr();

    SharedPtr(const SharedPtr<T>& other);
    SharedPtr<T>& operator=(const SharedPtr<T>& other);

    SharedPtr(SharedPtr<T>&& other) noexcept;
    SharedPtr<T>& operator=(SharedPtr<T>&& other) noexcept;

    T& operator*() const;
    T* operator->() const;
    T* get() const;

    std::size_t use_count() const;
    void reset(T* newPtr = nullptr);

    explicit operator bool() const;

  private:
    T* ptr;
    std::size_t* count;
    void release();
};

template<typename T>
UniquePtr<T>::UniquePtr() : ptr(nullptr) {}

template<typename T>
UniquePtr<T>::UniquePtr(T* p) : ptr(p){}

template<typename T>
UniquePtr<T>::~UniquePtr() {
    delete ptr;
}

template<typename T>
UniquePtr<T>::UniquePtr(UniquePtr<T>&& other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
}

template<typename T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T>&& other) noexcept {
    if (this == &other) return *this;

    delete ptr;
    ptr = other.ptr;
    other.ptr = nullptr;

    return *this;
}

template<typename T>
T& UniquePtr<T>::operator*() const {
    if (!ptr) throw std::runtime_error("Dereferencing null UniquePtr");
    return *ptr;
}

template<typename T>
T* UniquePtr<T>::operator->() const {
    if (!ptr) throw std::runtime_error("Dereferencing null UniquePtr");
    return ptr;
}

template<typename T>
T* UniquePtr<T>::get() const {
    return ptr;
}

template<typename T>
T* UniquePtr<T>::release() {
    T* temp = ptr;
    ptr = nullptr;
    return temp;
}

template<typename T>
void UniquePtr<T>::reset(T* newPtr) {
    if (ptr != newPtr) {
        delete ptr;
        ptr = newPtr;
    }
}

template<typename T>
UniquePtr<T>::operator bool() const {
    return ptr != nullptr;
}

template<typename T>
SharedPtr<T>::SharedPtr() : ptr(nullptr), count(nullptr) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* p) : ptr(p) {
    if (p) count = new std::size_t(1);
    else count = nullptr;
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    release();
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : ptr(other.ptr), count(other.count) {
    if (count) ++(*count);
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if (this == &other) return *this;

    release();

    ptr = other.ptr;
    count = other.count;
    if (count) ++(*count);

    return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept : ptr(other.ptr), count(other.count) {
    other.ptr = nullptr;
    other.count = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
    if (this == &other) return *this;

    release();

    ptr = other.ptr;
    count = other.count;

    other.ptr = nullptr;
    other.count = nullptr;

    return *this;
}

template<typename T>
T& SharedPtr<T>::operator*() const {
    if (!ptr) throw std::runtime_error("Dereferencing null SharedPtr");
    return *ptr;
}

template<typename T>
T* SharedPtr<T>::operator->() const {
    if (!ptr) throw std::runtime_error("Dereferencing null SharedPtr");
    return ptr;
}

template<typename T>
T* SharedPtr<T>::get() const {
    return ptr;
}

template<typename T>
std::size_t SharedPtr<T>::use_count() const {
    return count ? *count : 0;
}

template<typename T>
void SharedPtr<T>::reset(T* newPtr) {
    if (ptr == newPtr) return;

    release();

    ptr = newPtr;
    if (newPtr) count = new std::size_t(1);
    else count = nullptr;
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return ptr != nullptr;
}

template<typename T>
void SharedPtr<T>::release() {
    if (!count) {
        ptr = nullptr;
        return;
    }

    --(*count);

    if (*count == 0) {
        delete ptr;
        delete count;
    }

    ptr = nullptr;
    count = nullptr;
}

#endif // SMARTPOINTERS_HPP