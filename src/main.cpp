#include "argumentParsing.h"
#include "evaluator.h"

int main(int argc, char** argv) {
    auto [day, inFile, verbose] =
        advent::argumentParsing::parseArguments(argc, argv);

    advent::evaluate(day, inFile, verbose);
}
