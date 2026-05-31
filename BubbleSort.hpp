#ifndef BUBBLESORT_HPP
#define BUBBLESORT_HPP

#include <cstddef>
#include <utility>

class BubbleSort {
  public:
    template<typename T>
    void sort(T& nums);
};

template<typename T>
void BubbleSort::sort(T& nums) {
    std::size_t n = nums.size();
    bool isSorted = false;

    while (!isSorted && n > 1) {
        isSorted = true;
        for (std::size_t i = 1; i < n; i++) {
            if (nums[i] < nums[i-1]) {
                isSorted = false;
                std::swap(nums[i],nums[i-1]);
            }
        }
        n--;
    }
}

#endif // BUBBLESORT_HPP