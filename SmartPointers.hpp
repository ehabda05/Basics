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
class WeakPtr;

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
    struct ControlBlock {
        std::size_t strong_count;
        std::size_t weak_count;

        ControlBlock() : strong_count(1), weak_count(0) {}
    };

    T* ptr;
    ControlBlock* control;
    void release();
    friend class WeakPtr<T>;
};

template<typename T>
class WeakPtr {
  public:
    WeakPtr();
    WeakPtr(const SharedPtr<T>& shared);
    ~WeakPtr();

    WeakPtr(const WeakPtr<T>& other);
    WeakPtr<T>& operator=(const WeakPtr<T>& other);

    WeakPtr(WeakPtr<T>&& other) noexcept;
    WeakPtr<T>& operator=(WeakPtr<T>&& other) noexcept;

    SharedPtr<T> lock() const;

    bool expired() const;
    std::size_t use_count() const;

    void reset();

  private:
    T* ptr;
    typename SharedPtr<T>::ControlBlock* control;
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
SharedPtr<T>::SharedPtr() : ptr(nullptr), control(nullptr) {}

template<typename T>
SharedPtr<T>::SharedPtr(T* p) : ptr(p), control(nullptr) {
    if (p) control = new ControlBlock();
}

template<typename T>
SharedPtr<T>::~SharedPtr() {
    release();
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : ptr(other.ptr), control(other.control) {
    if (control) control->strong_count++;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other) {
    if (this == &other) return *this;

    release();

    ptr = other.ptr;
    control = other.control;
    if (control) control->strong_count++;

    return *this;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) noexcept : ptr(other.ptr), control(other.control) {
    other.ptr = nullptr;
    other.control = nullptr;
}

template<typename T>
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T>&& other) noexcept {
    if (this == &other) return *this;

    release();

    ptr = other.ptr;
    control = other.control;

    other.ptr = nullptr;
    other.control = nullptr;

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
    return control ? control->strong_count : 0;
}

template<typename T>
void SharedPtr<T>::reset(T* newPtr) {
    if (ptr == newPtr) return;

    release();

    ptr = newPtr;
    control = nullptr;

    if (newPtr) control = new ControlBlock();
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return ptr != nullptr;
}

template<typename T>
void SharedPtr<T>::release() {
    if (!control) {
        ptr = nullptr;
        return;
    }

    control->strong_count--;

    if (control->strong_count == 0) {
        delete ptr;
        ptr = nullptr;

        if (control->weak_count == 0) {
            delete control;
        }
    }

    ptr = nullptr;
    control = nullptr;
}

template<typename T>
WeakPtr<T>::WeakPtr() : ptr(nullptr), control(nullptr) {}

template<typename T>
WeakPtr<T>::WeakPtr(const SharedPtr<T>& shared) : ptr(shared.ptr), control(shared.control) {
    if (control) control->weak_count++;
}

template<typename T>
WeakPtr<T>::~WeakPtr() {
    release();
}

template<typename T>
WeakPtr<T>::WeakPtr(const WeakPtr<T>& other) : ptr(other.ptr), control(other.control) {
    if (control) control->weak_count++;
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(const WeakPtr<T>& other) {
    if (this == &other) return *this;

    release();

    ptr = other.ptr;
    control = other.control;
    if (control) control->weak_count++;

    return *this;
}

template<typename T>
WeakPtr<T>::WeakPtr(WeakPtr<T>&& other) noexcept : ptr(other.ptr), control(other.control) {
    other.ptr = nullptr;
    other.control = nullptr;
}

template<typename T>
WeakPtr<T>& WeakPtr<T>::operator=(WeakPtr<T>&& other) noexcept {
    if (this == &other) return *this;

    release();

    ptr = other.ptr;
    control = other.control;
    other.ptr = nullptr;
    other.control = nullptr;

    return *this;
}

template<typename T>
SharedPtr<T> WeakPtr<T>::lock() const {
    SharedPtr<T> result;

    if (control != nullptr && control->strong_count > 0) {
        result.ptr = ptr;
        result.control = control;
        control->strong_count++;
    }

    return result;
}

template<typename T>
bool WeakPtr<T>::expired() const {
    return control == nullptr || control->strong_count == 0;
}

template<typename T>
std::size_t WeakPtr<T>::use_count() const {
    return control ? control->strong_count : 0;
}

template<typename T>
void WeakPtr<T>::reset() {
    release();
}

template<typename T>
void WeakPtr<T>::release() {
    if (control == nullptr) return;

    control->weak_count--;

    if (control->strong_count == 0 && control->weak_count == 0) {
        delete control;
    }

    ptr = nullptr;
    control = nullptr;
}

#endif // SMARTPOINTERS_HPP