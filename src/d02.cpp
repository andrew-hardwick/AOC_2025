#include "adventTypedef.h"

#include <fileOps.h>
#include <stringUtils.h>

#include <algorithm>
#include <cstdint>
#include <string>

namespace advent::d02 {
std::pair<uint64_t, uint64_t> parseEntry(const std::string& source) {
    auto split = utility::string::split(source, "-");

    return {std::stoul(split[0]), std::stoul(split[1])};
}

std::vector<std::pair<uint64_t, uint64_t>>
loadAndParse(const std::string& inFilename) {
    auto source = utility::fileOps::readFileToLines(inFilename)[0];

    auto split = utility::string::split(source, ",");

    std::vector<std::pair<uint64_t, uint64_t>> result(split.size());

    std::transform(split.cbegin(), split.cend(), result.begin(), parseEntry);

    return result;
}

bool isMatchingSubstringsOfLength(const uint64_t& target, std::size_t length,
                                  std::size_t subLength) {
    static uint64_t pow10[] = {1,
                               10,
                               100,
                               1000,
                               10000,
                               100000,
                               1000000,
                               10000000,
                               100000000,
                               1000000000,
                               10000000000,
                               100000000000,
                               1000000000000,
                               10000000000000,
                               100000000000000,
                               1000000000000000};

    auto shiftWidth = length - subLength;

    auto first = target / pow10[shiftWidth];

    auto count = length / subLength;

    auto modMask = pow10[subLength];

    for (std::size_t i = 1; i < count; ++i) {
        auto ordReduction = pow10[subLength * (i - 1)];
        auto other = (target / ordReduction) % modMask;

        if (first != other) {

            return false;
        }
    }

    return true;
}

uint64_t lengthOfNum(uint64_t target) {
    uint64_t length = 0;

    while (target != 0) {
        target /= 10;
        ++length;
    }

    return length;
}

bool isInvalidIdP1(uint64_t id) {

    auto length = lengthOfNum(id);

    if (length == 1)
        return false;

    if (length % 2 != 0)
        return false;

    auto halfLength = length / 2;

    return isMatchingSubstringsOfLength(id, length, halfLength);
}

bool isInvalidIdP2(uint64_t id) {
    auto length = lengthOfNum(id);

    if (length == 1)
        return false;

    for (std::size_t subLength = 1; subLength <= length / 2; ++subLength) {
        if (length % subLength != 0)
            continue;

        if (isMatchingSubstringsOfLength(id, length, subLength))
            return true;
    }

    return false;
}

uint64_t checkRange(uint64_t begin, uint64_t end,
                    std::function<bool(uint64_t)> isInvalidId) {
    uint64_t result = 0;
    for (uint64_t i = begin; i <= end; ++i) {
        if (isInvalidId(i)) {
            result += i;
        }
    }
    return result;
}

std::string genericExecution(const std::string& inFilename,
                             std::function<bool(uint64_t)> isInvalidId) {
    auto data = loadAndParse(inFilename);

    uint64_t total = 0;

    for (const auto& [begin, end] : data) {
        total += checkRange(begin, end, isInvalidId);
    }

    return std::to_string(total);
}

std::string p1(const std::string& inFilename) {
    return genericExecution(inFilename, isInvalidIdP1);
}

std::string p2(const std::string& inFilename) {
    return genericExecution(inFilename, isInvalidIdP2);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d02
