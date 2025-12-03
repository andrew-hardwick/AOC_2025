#include "adventTypedef.h"
#include "utility/inc/utility/fileOps.h"

#include <algorithm>
#include <cstdint>
#include <iterator>
#include <string>

namespace advent::d03 {
uint8_t parseEntry(char source) {
    return (uint8_t)(source - '0');
}

std::vector<std::vector<uint8_t>> loadAndParse(const std::string& inFilename) {
    auto source = utility::fileOps::readFileToLines(inFilename);

    std::vector<std::vector<uint8_t>> result;

    for (const auto& line : source) {
        std::vector<uint8_t> resultEntry(line.size());

        std::transform(line.cbegin(), line.cend(), resultEntry.begin(),
                       parseEntry);

        result.push_back(resultEntry);
    }

    return result;
}

std::pair<uint8_t, uint64_t>
findHighestValueInSubset(const std::vector<uint8_t>& bank, uint64_t lOffset,
                         uint64_t rOffset) {
    auto maxIt =
        std::max_element(bank.cbegin() + lOffset, bank.cend() - rOffset);

    return {*maxIt, std::distance(bank.cbegin(), maxIt)};
}

uint64_t findHighestJoltage(const std::vector<uint8_t>& bank, int16_t numBats) {
    uint64_t joltage = 0;

    uint8_t digit = 0;
    int16_t lOffset = -1;

    for (int16_t rOffset = numBats - 1; rOffset >= 0; --rOffset) {
        std::tie(digit, lOffset) =
            findHighestValueInSubset(bank, lOffset + 1, rOffset);
        joltage *= 10;
        joltage += digit;
    }

    return joltage;
}

std::string genericExecution(const std::string& inFilename, int16_t numBats) {
    auto banks = loadAndParse(inFilename);

    uint64_t total = 0;

    for (const auto& bank : banks) {
        auto joltage = findHighestJoltage(bank, numBats);

        total += joltage;
    }

    return std::to_string(total);
}

std::string p1(const std::string& inFilename) {
    return genericExecution(inFilename, 2);
}

std::string p2(const std::string& inFilename) {
    return genericExecution(inFilename, 12);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d03
