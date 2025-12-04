#include "evaluator.h"

#include "d01.h"
#include "d02.h"
#include "d03.h"
#include "d04.h"
#include "d05.h"

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <string>

namespace advent {
void evaluate(uint8_t day, const std::string& inFilename, bool verbose) {
    auto [partOne, partTwo] = getDay(day);

    if (verbose) {
        std::cout << "Starting part one.\n";
    }

    auto [partOneResult, partOneTime] = executePart(partOne, inFilename);

    if (verbose) {
        std::cout << "Part One: '" << partOneResult << "' in "
                  << formatTime(partOneTime) << "\n";
        std::cout << "Starting part two.\n";
    } else {
        std::cout << "p1: '" << partOneResult << "'\n";
    }

    auto [partTwoResult, partTwoTime] = executePart(partTwo, inFilename);

    if (verbose) {
        std::cout << "Part Two: '" << partTwoResult << "' in "
                  << formatTime(partTwoTime) << "\n";
    } else {
        std::cout << "p2: '" << partTwoResult << "'\n";
    }
}

std::pair<adventFunctor, adventFunctor> getDay(uint8_t day) {
    switch (day) {
    case 1:
        return d01::getParts();
    case 2:
        return d02::getParts();
    case 3:
        return d03::getParts();
	case 4:
		return d04::getParts();
	case 5:
		return d05::getParts();
    }

    throw std::invalid_argument("Encountered unparseable year");
}

std::pair<std::string, uint64_t> executePart(const adventFunctor& functor,
                                             const std::string& inFilename) {
    auto before = std::chrono::high_resolution_clock::now();

    auto result = functor(inFilename);

    auto after = std::chrono::high_resolution_clock::now();

    uint64_t duration =
        std::chrono::duration_cast<std::chrono::nanoseconds>(after - before)
            .count();

    return std::make_pair(result, duration);
}

std::string formatTime(uint64_t nanoSeconds) {
    uint64_t microSeconds = nanoSeconds / 1000;
    uint64_t milliSeconds = microSeconds / 1000;
    uint64_t seconds = milliSeconds / 1000;

    uint64_t integer = 0;
    uint64_t fractional = 0;
    std::string units{""};

    if (seconds > 0) {
        integer = seconds;
        fractional = (milliSeconds - (seconds * 1000)) / 10;
        units = "s";
    } else if (milliSeconds > 0) {
        integer = milliSeconds;
        fractional = (microSeconds - (milliSeconds * 1000)) / 10;
        units = "ms";
    } else if (microSeconds > 0) {
        integer = microSeconds;
        fractional = (nanoSeconds - (microSeconds * 1000)) / 10;
        units = "us";
    } else {
        integer = nanoSeconds;
        units = "ns";
    }
    return std::to_string(integer) + "." + std::to_string(fractional) + units;
}

} // namespace advent
