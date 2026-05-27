#include <cstddef>

class InsertionSort {
  public:
    template<typename T>
    void sort(T& nums) {
        std::size_t n = nums.size();
        
        for (std::size_t i = 1; i < n; i++) {
            auto key = nums[i];
            std::size_t j = i;
            while (j > 0 && nums[j-1] > key) {
                nums[j] = nums[j-1];
                j--;
            }
            nums[j] = key;
        }
    }
};