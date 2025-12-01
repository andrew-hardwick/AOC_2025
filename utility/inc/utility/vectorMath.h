#ifndef ADVENT_VECTOR_MATH_H
#define ADVENT_VECTOR_MATH_H

#include <stdexcept>
#include <vector>

namespace advent::utility::vectorMath {
template <class T>
std::vector<T> add(const std::vector<T>& a, const std::vector<T>& b) {
    std::vector<T> result;

    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "vectorMath::add: vector lengths must match");
    }

    for (std::size_t i = 0; i < a.size(); i++) {
        result.push_back(a[i] + b[i]);
    }

    return result;
}

template <class T>
std::vector<T> piecewiseMultiply(const std::vector<T>& a,
                                 const std::vector<T>& b) {
    std::vector<T> result;

    if (a.size() != b.size()) {
        throw std::invalid_argument(
            "vectorMath::piecewiseMultiply: vector lengths must match");
    }

    for (std::size_t i = 0; i < a.size(); i++) {
        result.push_back(a[i] * b[i]);
    }

    return result;
}

template <class T1, class T2>
std::vector<T1> multiplyByScalar(const std::vector<T1>& a, T2 b) {
    std::vector<T1> result;

    for (const auto& e : a) {
        result.push_back(e * b);
    }

    return result;
}

template <class T> T sum(const std::vector<T>& a) {
    T result = 0;

    for (const auto& e : a) {
        result += e;
    }

    return result;
}
} // namespace advent::utility::vectorMath

#endif
