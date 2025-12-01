#include "combinatorics.h"

namespace advent::utility::combinatorics {
/// Heaps algorithm
std::vector<std::vector<std::size_t>> permutations(std::size_t length) {
    std::vector<std::vector<std::size_t>> result;

    std::vector<std::size_t> row;

    for (std::size_t i = 0; i < length; i++)
        row.push_back(i);

    result.push_back(row);

    std::vector<std::size_t> state(length, 0);

    std::size_t i = 1;
    std::size_t temp = 0;

    while (i < length) {
        if (state[i] < i) {
            if (i % 2 == 0) {
                temp = row[0];
                row[0] = row[i];
                row[i] = temp;
            } else {
                temp = row[state[i]];
                row[state[i]] = row[i];
                row[i] = temp;
            }
            result.push_back(row);

            state[i] += 1;
            i = 1;
        } else {
            state[i] = 0;
            i++;
        }
    }

    return result;
}
} // namespace advent::utility::combinatorics
