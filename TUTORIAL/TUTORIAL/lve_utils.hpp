#pragma once

namespace lve {
    template <typename T, typename... Rest>
    void hashCombine(size_t& seed, const T& value, const Rest&... rest) {
        std::hash<T> hasher;
        seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        (hashCombine(seed, rest), ...);
    }   
}