#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <cstddef>
#include <functional>
#include <stdexcept>
#include "Vector.hpp"
#include "List.hpp"

template<typename T, typename U>
class HashMap {
  public:
    HashMap();
    ~HashMap();
    HashMap(const HashMap<T,U>& other);
    HashMap<T,U>& operator=(const HashMap<T,U>& other);
    U& operator[](const T& key) ;
    void insert(const T& key, const U& value);
    void erase(const T& key);
    std::size_t count(const T& key) const;
    void clear();
    bool empty() const;
    std::size_t size() const;
  private:
    struct Pair {
        T key;
        U value;
    };
    Vector<List<Pair>> buckets;
    std::size_t sz;

    std::size_t hash(const T& value) const;
    void rehash(std::size_t newBucketCount);
};

template<typename T, typename U>
HashMap<T,U>::HashMap() : buckets(10), sz(0) {}

template<typename T, typename U>
HashMap<T,U>::~HashMap() {}

template<typename T, typename U>
HashMap<T,U>::HashMap(const HashMap<T,U>& other) : buckets(other.buckets), sz(other.sz) {}

template<typename T, typename U>
HashMap<T,U>& HashMap<T,U>::operator=(const HashMap<T,U>& other) {
    if (this == &other) return *this;
    buckets = other.buckets;
    sz = other.sz;
    return *this;
}

template<typename T, typename U>
U& HashMap<T,U>::operator[](const T& key) {
    std::size_t idx = hash(key);
    for (auto& pair : buckets[idx]) {
        if (pair.key == key) {
            return pair.value;
        }
    }
    insert(key, U{});
    idx = hash(key);
    for (auto& pair : buckets[idx]) {
        if (pair.key == key) {
            return pair.value;
        }
    }

    throw std::out_of_range("Key not found");
}

template<typename T, typename U>
void HashMap<T,U>::insert(const T& key, const U& value) {
    std::size_t idx = hash(key);

    for (const Pair& x : buckets[idx]) {
        if (x.key == key) return;
    }
    
    if (sz >= buckets.size()) {
        rehash(buckets.size() * 2);
        idx = hash(key);
    }

    Pair newPair{key, value};
    buckets[idx].push_back(newPair);
    sz++;
}

template<typename T, typename U>
void HashMap<T,U>::erase(const T& key) {
    std::size_t idx = hash(key);
        for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
        if ((*it).key == key) {
            buckets[idx].erase(it);
            sz--;
            return;
        }
    }
}

template<typename T, typename U>
std::size_t HashMap<T,U>::count(const T& key) const {
    std::size_t idx = hash(key);

    for (const Pair& pair : buckets[idx]) {
        if (pair.key == key) {
            return 1;
        }
    }

    return 0;
}

template<typename T, typename U>
void HashMap<T,U>::clear() {
    for (auto& bucket : buckets) {
        bucket.clear();
    }
    sz = 0;
}

template<typename T, typename U>
bool HashMap<T,U>::empty() const {
    return sz == 0;
}

template<typename T, typename U>
std::size_t HashMap<T,U>::size() const {
    return sz;
}

template<typename T, typename U>
std::size_t HashMap<T,U>::hash(const T& value) const {
    return std::hash<T>{}(value) % buckets.size();
}

template<typename T, typename U>
void HashMap<T,U>::rehash(std::size_t newBucketCount) {
    Vector<List<Pair>> newBuckets(newBucketCount);

    for (const auto& bucket : buckets) {
        for (const Pair& pair : bucket) {
            std::size_t newIndex = std::hash<T>{}(pair.key) % newBucketCount;
            newBuckets[newIndex].push_back(pair);
        }
    }

    buckets = newBuckets;
}

#endif // HASHMAP_HPP