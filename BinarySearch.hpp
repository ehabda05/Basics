#include <cstddef>

class BinarySearch {
  public:
    template<typename T, typename U>
    bool search(const T& data, const U& key) {
        std::size_t l = 0;
        std::size_t r = data.size();

        while (l < r) {
            std::size_t m = l + ((r-l)/2);
            if (data[m] == key) return true;
            else if (data[m] < key) l = m+1;
            else r = m;
        }

        return false;
    }
};