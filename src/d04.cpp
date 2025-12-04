#include "adventTypedef.h"

#include <fileOps.h>
#include <point.h>

#include <cstdint>
#include <string>

using Point = advent::utility::point::Point;

namespace advent::d04 {
uint8_t rollPresent(int64_t r, int64_t c, const std::vector<std::string>& map) {
    if (r < 0 || r >= (int64_t)map.size())
        return 0;

    if (c < 0 || c >= (int64_t)map[0].size())
        return 0;

    return map[r][c] == '@' ? 1 : 0;
}

bool checkAccessible(int64_t r, int64_t c,
                     const std::vector<std::string>& map) {
    if (map[r][c] != '@')
        return false;

    uint8_t neighborCount = 0;

    neighborCount += rollPresent(r - 1, c - 1, map);
    neighborCount += rollPresent(r - 1, c, map);
    neighborCount += rollPresent(r - 1, c + 1, map);

    neighborCount += rollPresent(r, c - 1, map);
    neighborCount += rollPresent(r, c + 1, map);

    neighborCount += rollPresent(r + 1, c - 1, map);
    neighborCount += rollPresent(r + 1, c, map);
    neighborCount += rollPresent(r + 1, c + 1, map);

    return neighborCount < 4;
}

std::vector<Point> getAccessibleRolls(const std::vector<std::string>& map) {
    std::vector<utility::point::Point> result;

    auto height = (int64_t)map.size();
    auto width = (int64_t)map[0].size();

    for (int64_t r = 0; r < height; r++) {
        for (int64_t c = 0; c < width; c++) {
            if (checkAccessible(r, c, map)) {
                result.push_back({(int)r, (int)c});
            }
        }
    }

    return result;
}

void removeRolls(const std::vector<Point>& rollsToRemove,
                 std::vector<std::string>& map) {
    for (const auto& p : rollsToRemove) {
        map[p.x][p.y] = '.';
    }
}

std::string p1(const std::string& inFilename) {
    auto map = utility::fileOps::readFileToLines(inFilename);

    uint64_t accessibleCount = getAccessibleRolls(map).size();

    return std::to_string(accessibleCount);
}

std::string p2(const std::string& inFilename) {
    auto map = utility::fileOps::readFileToLines(inFilename);

    std::vector<Point> accessiblePoints;

    uint64_t removedCount = 0;

    do {
        accessiblePoints = getAccessibleRolls(map);

        removedCount += accessiblePoints.size();

        removeRolls(accessiblePoints, map);
    } while (accessiblePoints.size() > 0);

    return std::to_string(removedCount);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d04
