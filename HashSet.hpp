#include <cstddef>
#include <vector>
#include <list>
#include <functional>

template<typename T>
class HashSet {
  public:
    HashSet() : buckets(10), sz(0) {}
    ~HashSet() {}
    HashSet(const HashSet& other) : buckets(other.buckets), sz(other.sz) {}
    HashSet& operator=(const HashSet& other) {
        if (this == &other) return *this;
        buckets = other.buckets;
        sz = other.sz;
        return *this;
    }
    void insert(const T& value) {
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
    void erase(const T& value) {
        std::size_t idx = hash(value);
         for (auto it = buckets[idx].begin(); it != buckets[idx].end(); ++it) {
            if (*it == value) {
                buckets[idx].erase(it);
                sz--;
                return;
            }
        }
    }
    std::size_t count(const T& value) const {
        std::size_t idx = hash(value);

        for (const T& x : buckets[idx]) {
            if (x == value) return 1;
        }

        return 0;
    }
    void clear() {
        for (auto& bucket : buckets) {
            bucket.clear();
        }
        sz = 0;
    }
    bool empty() const {
        return sz == 0;
    }

  private:
    std::vector<std::list<T>> buckets;
    std::size_t sz;

    std::size_t hash(const T& value) const {
        return std::hash<T>{}(value) % buckets.size();
    }

    void rehash(std::size_t newBucketCount) {
        std::vector<std::list<T>> newBuckets(newBucketCount);

        for (const auto& bucket : buckets) {
            for (const T& value : bucket) {
                std::size_t newIndex = std::hash<T>{}(value) % newBucketCount;
                newBuckets[newIndex].push_back(value);
            }
        }

        buckets = newBuckets;
    }
};