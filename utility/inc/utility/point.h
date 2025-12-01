#ifndef ADVENT_POINT_H
#define ADVENT_POINT_H

#include <ostream>

namespace advent::utility {
struct Point {
    int x;
    int y;

    static Point from(const std::string& source);
};

Point rotateRight(const Point& source);

bool operator==(const Point& a, const Point& b);

bool operator!=(const Point& a, const Point& b);

bool operator<(const Point& a, const Point& b);

std::ostream& operator<<(std::ostream& os, const Point& p);

Point operator+(const Point& a, const Point& b);

Point operator+=(Point& self, const Point& other);

Point operator*(const Point& a, int b);
} // namespace advent::utility

#endif
