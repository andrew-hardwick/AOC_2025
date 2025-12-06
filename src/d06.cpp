#include "adventTypedef.h"
#include "fileOps.h"
#include "stringUtils.h"

#include <algorithm>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <map>
#include <string>

namespace fileOps = advent::utility::fileOps;
namespace string = advent::utility::string;

namespace advent::d06 {
enum class op_t { MUL, ADD, UNK };

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

std::tuple<std::vector<uint64_t>, uint16_t, uint16_t, std::vector<op_t>>
loadAndParsePart1(const std::string& inFilename) {
    auto source = fileOps::readFileToLines(inFilename);

    std::vector<uint64_t> numbers;
    std::vector<op_t> ops;

    uint16_t rowLength = 0;
    uint16_t rowCount = 0;

    std::vector<std::string> cleanupTargets{" ", "  ", "   "};
    std::vector<std::string> cleanupReplacements{" ", " ", " "};

    for (const auto& line : source) {
        auto cleaned =
            string::replace(line, cleanupTargets, cleanupReplacements);

        auto split = string::split(cleaned, " ", false, false);

        if (split[0] == "+" || split[0] == "*") {
            ops.resize(split.size());

            std::transform(split.cbegin(), split.cend(), ops.begin(), parseOp);

            continue;
        }

        ++rowCount;

        if (rowLength == 0)
            rowLength = split.size();

        numbers.reserve(numbers.size() + rowLength);

        for (auto e : split)
            numbers.push_back(std::stol(e));
    }

    return {numbers, rowLength, rowCount, ops};
}

uint64_t calculateColumnPartOne(const std::vector<uint64_t> numbers,
                                uint16_t rowCount, uint64_t rowLength,
                                uint64_t col, op_t op) {

    uint64_t result = op == op_t::ADD ? 0 : 1;

    for (uint64_t row = 0; row < rowCount; ++row) {
        uint64_t index = row * rowLength + col;
        uint64_t e = numbers[index];

        result = opMap[op](result, e);
    }

    return result;
}

std::string p1(const std::string& inFilename) {
    auto [numbers, rowLength, rowCount, ops] = loadAndParsePart1(inFilename);

    uint64_t total = 0;

    for (uint64_t col = 0; col < ops.size(); ++col) {
        auto e =
            calculateColumnPartOne(numbers, rowCount, rowLength, col, ops[col]);

        total += e;
    }

    return std::to_string(total);
}

uint64_t computePartTwo(const std::vector<uint64_t>& nums, op_t op) {
    uint64_t result = op == op_t::ADD ? 0 : 1;

    auto opF = opMap[op];

    for (const auto& n : nums) {
        result = opF(result, n);
    }

    return result;
}

std::tuple<bool, uint64_t>
parseNumPartTwo(const std::vector<std::string>& source, std::size_t index) {
    bool allBlank = true;
    uint64_t result = 0;
    for (const auto& line : source) {
        auto c = line[index];

        if (c != ' ') {
            allBlank = false;

            result *= 10;
            result += (uint64_t)(c - '0');
        }
    }

    return {allBlank, result};
}

std::string p2(const std::string& inFilename) {
    auto source = fileOps::readFileToLines(inFilename);

    std::vector<std::string> numbersSource(source.begin(), source.end() - 1);
    std::string opSource{*(source.end() - 1)};

    std::vector<uint64_t> groupNums;
    op_t op = op_t::UNK;

    uint64_t total = 0;

	groupNums.reserve(10);

    for (std::size_t c = 0; c < opSource.size(); ++c) {
        auto opC = opSource[c];

        if (opC != ' ') {
            if (op != op_t::UNK)
                total += computePartTwo(groupNums, op);

            groupNums.clear();
            op = opC == '+' ? op_t::ADD : op_t::MUL;
        }

        auto [allBlank, num] = parseNumPartTwo(numbersSource, c);

		if (!allBlank)
			groupNums.push_back(num);
    }

	total += computePartTwo(groupNums,  op);

	return std::to_string(total);
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::d06
