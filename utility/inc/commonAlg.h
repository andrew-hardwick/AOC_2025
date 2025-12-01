#ifndef ADVENT_COMMON_ALG_H
#define ADVENT_COMMON_ALG_H

#include <functional>
#include <vector>

namespace advent::utility::commonAlg {
template <class T>
T selectBest(const std::vector<T> source,
             std::function<std::size_t(T)> fitness) {
    T result = source.at(0);
    auto best = fitness(result);

    for (const auto& entry : source) {
        auto entryFitness = fitness(entry);
        if (entryFitness > best) {
            best = entryFitness;

            result = entry;
        }
    }

    return result;
}

std::vector<std::size_t>
greedyBackpack(std::vector<std::pair<std::size_t, std::size_t>> source,
               std::function<std::vector<std::size_t>(std::size_t)> filter);
} // namespace advent::utility::commonAlg

#endif
