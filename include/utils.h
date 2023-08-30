#ifndef _UTILS_H_
#define _UTILS_H_

#include <array>

namespace _dirty {
template <std::size_t N, typename T>
const std::array<std::byte, N>& arraySubBytes(const T& arr, std::size_t index) {
    return reinterpret_cast<const std::array<std::byte, N>&>(arr[index]);
}
} // namespace _dirty

// using namespace _dirty;

#endif
