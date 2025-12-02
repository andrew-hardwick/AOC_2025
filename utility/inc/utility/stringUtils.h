#ifndef ADVENT_STRING_UTILS_H
#define ADVENT_STRING_UTILS_H

#include <string>
#include <vector>

namespace advent::utility::string {
std::vector<std::string> split(std::string source,
                               const std::string& delimiter);

std::vector<std::string> split(const std::string& source, char delimiter);

std::vector<std::string> equalSubStrsOfLength(const std::string& source,
                                              std::size_t length,
                                              std::size_t subLength);

std::vector<int> convertToIntArray(const std::vector<std::string>& source);

std::vector<int> parseToIntArray(const std::string& source,
                                 const std::string& delimiter);

bool leadCharMatches(const std::string& target, char c, std::size_t count);

std::string replace(const std::string& source, const std::string& target,
                    const std::string& replacement);

std::string replace(const std::string& source,
                    const std::vector<std::string>& targets,
                    const std::vector<std::string>& replacements);
} // namespace advent::utility::string

#endif
