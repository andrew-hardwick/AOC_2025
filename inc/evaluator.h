#ifndef ADVENT_EVALUATOR_H
#define ADVENT_EVALUATOR_H

#include "adventTypedef.h"

#include <cstdint>
#include <string>

namespace advent {
void evaluate(uint8_t day, const std::string& inFilename, bool verbose);

std::pair<adventFunctor, adventFunctor> getDay(uint8_t day);

std::pair<std::string, std::size_t> executePart(const adventFunctor& functor,
                                                const std::string& inFilename);
} // namespace advent

#endif
