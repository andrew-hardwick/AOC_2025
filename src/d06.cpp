#include "adventTypedef.h"
#include "fileOps.h"

#include <cstdint>
#include <ctime>
#include <functional>
#include <map>
#include <string>

namespace fileOps = advent::utility::fileOps;

namespace advent::d06 {
enum class op_t { MUL, ADD, UNK };

op_t from(const char& c) {
    switch (c) {
    case '+':
        return op_t::ADD;
    case '*':
        return op_t::MUL;
    default:
        return op_t::UNK;
    }
}

op_t parseOp(const std::string& source) {
    if (source == "+")
        return op_t::ADD;
    else if (source == "*")
        return op_t::MUL;
    return op_t::UNK;
}

std::map<op_t, std::function<uint64_t(uint64_t, uint64_t)>> opMap{
    {op_t::ADD, std::plus()},
    {op_t::MUL, std::multiplies()},
};

uint64_t foldOp(const std::vector<uint64_t>& nums, op_t op) {
    uint64_t result = op == op_t::ADD ? 0 : 1;

    auto opF = opMap[op];

    for (const auto& n : nums) {
        result = opF(result, n);
    }

    return result;
}

std::tuple<std::vector<std::size_t>, std::vector<op_t>>
identifyOpColumns(const std::string& opLine) {
    std::vector<std::size_t> resultIndices;
    std::vector<op_t> resultOps;

    char previousC = opLine[0];

    for (std::size_t i = 1; i < opLine.size(); i++) {
        auto c = opLine[i];
        if (c != ' ') {
            resultIndices.push_back(i - 1);
            resultOps.push_back(from(previousC));
            previousC = c;
        }
    }

    resultIndices.push_back(opLine.size());
    resultOps.push_back(from(previousC));

    return {resultIndices, resultOps};
}

std::tuple<std::vector<std::string>, std::string>
loadSource(const std::string& inFilename) {
    auto source = fileOps::readFileToLines(inFilename);

    std::vector<std::string> numbersSource(source.begin(), source.end() - 1);
    std::string opSource{*(source.end() - 1)};

    return {numbersSource, opSource};
}

std::vector<uint64_t>
parseNumberGroupPartOne(const std::vector<std::string>& numbersSource,
                        std::size_t groupSize, std::size_t groupStart,
                        std::size_t groupLength) {
    std::vector<uint64_t> group(groupSize);

    for (std::size_t j = 0; j < groupSize; ++j) {
        auto numSource = numbersSource[j].substr(groupStart, groupLength);

        group[j] = std::stol(numSource);
    }

    return group;
}

std::vector<uint64_t>
parseNumberGroupPartTwo(const std::vector<std::string>& numbersSource,
                        std::size_t groupSize, std::size_t groupStart,
                        std::size_t groupLength) {
    std::vector<uint64_t> group(groupLength, 0);

    for (std::size_t i = 0; i < groupSize; ++i) {
        for (std::size_t j = 0; j < groupLength; ++j) {
            auto c = numbersSource[i][groupStart + j];
            if (c != ' ') {
                group[j] *= 10;
                group[j] += (c - '0');
            }
        }
    }

    return group;
}

using parseNumberGroup_t = std::function<std::vector<uint64_t>(
    const std::vector<std::string>&, std::size_t, std::size_t, std::size_t)>;

std::vector<std::vector<uint64_t>>
identifyNumberGroups(const std::vector<std::string>& numbersSource,
                     const std::vector<std::size_t>& opColumns,
                     parseNumberGroup_t parseNumberGroup) {
    std::vector<std::vector<uint64_t>> result;

    auto groupSize = numbersSource.size();
    std::size_t groupStart = 0;

    for (const auto& groupEnd : opColumns) {
        std::size_t groupLength = groupEnd - groupStart;

        auto group =
            parseNumberGroup(numbersSource, groupSize, groupStart, groupLength);

        result.push_back(group);

        groupStart = groupEnd + 1;
    }

    return result;
}

std::string genericExecution(const std::string& inFilename,
                             parseNumberGroup_t parseNumberGroup) {
    auto [numbersSource, opSource] = loadSource(inFilename);

    auto [opColumns, ops] = identifyOpColumns(opSource);

    auto numberGroups =
        identifyNumberGroups(numbersSource, opColumns, parseNumberGroup);

    uint64_t total = 0;

    for (std::size_t i = 0; i < opColumns.size(); i++)
        total += foldOp(numberGroups[i], ops[i]);

    return std::to_string(total);
}

std::string p1(const std::string& inFilename) {
    return genericExecution(inFilename, parseNumberGroupPartOne);
}

std::string p2(const std::string& inFilename) {
    return genericExecution(inFilename, parseNumberGroupPartTwo);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d06
