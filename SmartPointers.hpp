#ifndef SMARTPOINTERS_HPP
#define SMARTPOINTERS_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

template<typename T>
class UniquePtr {
  public:
    UniquePtr();
    explicit UniquePtr(T* ptr);
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
    T* data;
};

template<typename T>
class SharedPtr {
  public:
    SharedPtr();
    explicit SharedPtr(T* ptr);
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
    T* data;
    std::size_t* count;
    void release();
};

#endif // SMARTPOINTERS_HPP