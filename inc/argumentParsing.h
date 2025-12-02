#ifndef ADVENT_ARGUMENT_PARSING_H
#define ADVENT_ARGUMENT_PARSING_H

#include <argp.h>

#include <cstdint>
#include <string>
#include <tuple>

namespace advent::argumentParsing {
error_t parse_opt(int key, char* arg, struct argp_state* state);

std::tuple<uint8_t, std::string, bool> parseArguments(int argc, char** argv);
} // namespace advent::argumentParsing

#endif
