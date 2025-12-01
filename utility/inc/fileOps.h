#ifndef ADVENT_FILE_OPS_H
#define ADVENT_FILE_OPS_H

#include <string>
#include <vector>

namespace advent::utility::fileOps {
std::string readFileRaw(const std::string& inFilename);

std::vector<char> readFileToChars(const std::string& inFilename);

std::vector<std::string> readFileToLines(const std::string& inFilename);
} // namespace advent::utility::fileOps

#endif
