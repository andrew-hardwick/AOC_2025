#include "adventTypedef.h"

#include <fileOps.h>

#include <algorithm>
#include <cstdint>
#include <string>

namespace advent::d01 {
int16_t convert(const std::string& source) {
    auto dir = source[0];

    auto numSource = source.substr(1);

    auto result = std::stoi(numSource);

    if (dir == 'L')
        result = -result;

    return result;
}

std::vector<int16_t> loadAndParse(const std::string& inFilename) {
    auto source = utility::fileOps::readFileToLines(inFilename);

    std::vector<int16_t> result(source.size());

    std::transform(source.cbegin(), source.cend(), result.begin(), convert);

    return result;
}

std::string p1(const std::string& inFilename) {
    auto moves = loadAndParse(inFilename);

    int32_t currentValue = 50;
    uint16_t numberOfZeroInstances = 0;

    for (const auto& delta : moves) {
        currentValue += delta;

        if (currentValue % 100 == 0)
            numberOfZeroInstances++;
    }

    return std::to_string(numberOfZeroInstances);
}

std::string p2(const std::string& inFilename) {
    auto moves = loadAndParse(inFilename);

    int32_t currentValue = 50;
    uint16_t numberOfZeroInstances = 0;

    for (auto delta : moves) {
        if (currentValue == 0 && delta < 0)
            numberOfZeroInstances--;

        currentValue += delta;

        while (currentValue < 0) {
            currentValue += 100;
            numberOfZeroInstances++;
        }

        while (currentValue > 100) {
            currentValue -= 100;
            numberOfZeroInstances++;
        }

        if (currentValue == 100) {
            currentValue = 0;
        }

        if (currentValue % 100 == 0)
            numberOfZeroInstances++;
    }

    return std::to_string(numberOfZeroInstances);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d01
