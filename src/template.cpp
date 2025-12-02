#include "adventTypedef.h"

#include <cstdlib>

namespace advent::templ {
std::string p1(const std::string& inFilename) {
    return "nonimpl";
}

std::string p2(const std::string& inFilename) {
    return "nonimpl";
}

std::pair<adventFunctor, adventFunctor> getParts() {
    return {p1, p2};
}
} // namespace advent::templ
