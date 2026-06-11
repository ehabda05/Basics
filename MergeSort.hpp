#ifndef MERGE_SORT_HPP
#define MERGE_SORT_HPP

#include <cstddef>
#include "Vector.hpp"

template<typename T>
class MergeSort {
  public:
    void sort(Vector<T>& v);
};

template<typename T>
void MergeSort<T>::sort(Vector<T>& v) {
    if (v.size() <= 1) return;

    std::size_t mid = v.size() / 2;
    Vector<T> left(mid);
    Vector<T> right(v.size() - mid);

    for (std::size_t i = 0; i < mid; ++i) {
        left[i] = v[i];
    }
    for (std::size_t i = mid; i < v.size(); ++i) {
        right[i - mid] = v[i];
    }

    sort(left);
    sort(right);

    std::size_t i = 0, j = 0, k = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            v[k++] = left[i++];
        } else {
            v[k++] = right[j++];
        }
    }
    while (i < left.size()) {
        v[k++] = left[i++];
    }
    while (j < right.size()) {
        v[k++] = right[j++];
    }
}
#endif // MERGE_SORT_HPP