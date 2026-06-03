#ifndef HASHSET_HPP
#define HASHSET_HPP

#include <cstddef>
#include "Vector.hpp"
#include "List.hpp"
#include <functional>

template<typename T>
class HashSet {
  public:
    HashSet();
    ~HashSet();
    HashSet(const HashSet<T>& other);
    HashSet<T>& operator=(const HashSet<T>& other);
    void insert(const T& value);
    void erase(const T& value);
    std::size_t count(const T& value) const;
    void clear();
    bool empty() const;
    std::size_t size() const;
  private:
    Vector<List<T>> buckets;
    std::size_t sz;

    std::size_t hash(const T& value) const;
    void rehash(std::size_t newBucketCount);
};

template<typename T>
HashSet<T>::HashSet() : buckets(10), sz(0) {}

template<typename T>
HashSet<T>::~HashSet() {
    clear();
}

template<typename T>
HashSet<T>::HashSet(const HashSet<T>& other) : buckets(other.buckets), sz(other.sz) {}

template<typename T>
HashSet<T>& HashSet<T>::operator=(const HashSet<T>& other) {
    if (this == &other) return *this;
    buckets = other.buckets;
    sz = other.sz;
    return *this;
}

template<typename T>
void HashSet<T>::insert(const T& value) {
    std::size_t idx = hash(value);

    for (const T& x : buckets[idx]) {
        if (x == value) return;
    }
    
    if (sz >= buckets.size()) {
        rehash(buckets.size() * 2);
        idx = hash(value);
    }


    buckets[idx].push_back(value);
    sz++;
}

template<typename T>
void HashSet<T>::erase(const T& value) {
    std::size_t idx = hash(value);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
        if (*it == value) {
            buckets[idx].erase(it);
            sz--;
            return;
        }
    }
}

template<typename T>
std::size_t HashSet<T>::count(const T& value) const {
    std::size_t idx = hash(value);

    for (const T& x : buckets[idx]) {
        if (x == value) return 1;
    }

    return 0;
}

template<typename T>
void HashSet<T>::clear() {
    for (auto& bucket : buckets) {
        bucket.clear();
    }
    sz = 0;
}

template<typename T>
bool HashSet<T>::empty() const {
    return sz == 0;
}

template<typename T>
std::size_t HashSet<T>::size() const {
    return sz;
}

template<typename T>
std::size_t HashSet<T>::hash(const T& value) const {
    return std::hash<T>{}(value) % buckets.size();
}

template<typename T>
void HashSet<T>::rehash(std::size_t newBucketCount) {
    Vector<List<T>> newBuckets(newBucketCount);

    for (const auto& bucket : buckets) {
        for (const T& value : bucket) {
            std::size_t newIndex = std::hash<T>{}(value) % newBucketCount;
            newBuckets[newIndex].push_back(value);
        }
    }

    buckets = newBuckets;
}

#endif // HASHSET_HPP