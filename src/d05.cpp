#include "adventTypedef.h"
#include "fileOps.h"
#include "stringUtils.h"

#include <algorithm>
#include <cstdint>
#include <string>

namespace advent::d05 {
struct freshRange {
    int64_t start;
    int64_t end;

    bool inRange(uint64_t val) const {
        return val >= start && val <= end;
    }

    bool operator<(const freshRange& other) {
        if (this->start == other.start)
            return this->end < other.end;

        return this->start < other.start;
    }
};

freshRange parseRange(const std::string& line) {
    auto splitLine = utility::string::split(line, "-");

    return {std::stol(splitLine[0]), std::stol(splitLine[1])};
}

std::pair<std::vector<freshRange>, std::vector<uint64_t>>
loadAndParse(const std::string& inFilename) {
    auto source = utility::fileOps::readFileToLines(inFilename);

    std::vector<freshRange> ranges;
    std::vector<uint64_t> ingredients;
    bool pastRanges = false;

    for (const auto& line : source) {
        if (line == "") {
            pastRanges = true;
            continue;
        }

        if (!pastRanges) {
            ranges.push_back(parseRange(line));
        } else {
            ingredients.push_back(std::stoul(line));
        }
    }

    return {ranges, ingredients};
}

std::string p1(const std::string& inFilename) {
    auto [freshRanges, ingredients] = loadAndParse(inFilename);

    uint64_t count = 0;

    for (const auto& ingredient : ingredients) {
        for (const auto& fr : freshRanges) {
            if (fr.inRange(ingredient)) {
                ++count;
                break;
            }
        }
    }

    return std::to_string(count);
}

std::string p2(const std::string& inFilename) {
    auto [freshRanges, _] = loadAndParse(inFilename);

    std::sort(freshRanges.begin(), freshRanges.end());

    int64_t count = 0;
    int64_t lastEdge = 0;

    for (const auto& [start, end] : freshRanges) {
        if (end <= lastEdge)
            continue;

        uint64_t thisRangeWidth = end - start + 1;

        if (start <= lastEdge) {
            thisRangeWidth -= (lastEdge - start) + 1;
        }
        lastEdge = end;

        count += thisRangeWidth;
    }

    return std::to_string(count);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d05
