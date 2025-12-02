#include "point.h"

#include "stringUtils.h"

#include <string>

namespace advent {
namespace utility {
Point Point::from(const std::string& source) {
    auto split = string::split(source, ',');

    return {std::stoi(split[0]), std::stoi(split[1])};
}

Point rotateRight(const Point& source) {
    return {-source.y, source.x};
}

bool operator==(const Point& a, const Point& b) {
    if (a.x != b.x)
        return false;
    if (a.y != b.y)
        return false;

    return true;
}

bool operator!=(const Point& a, const Point& b) {
    return !(a == b);
}

bool operator<(const Point& a, const Point& b) {
    if (a.x != b.x)
        return a.x < b.x;
    return a.y < b.y;
}

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "{ " << p.x << ", " << p.y << " }";

    return os;
}

Point operator+(const Point& a, const Point& b) {
    return {a.x + b.x, a.y + b.y};
}

Point operator+=(Point& self, const Point& other) {
    return self + other;
}

Point operator*(const Point& a, int b) {
    return {a.x * b, a.y * b};
}
} // namespace utility
} // namespace advent
