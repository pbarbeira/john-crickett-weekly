#include <iostream>
#include "HuffmanFactory.h"

const std::string EXT = ".hmc";

/**
 * Usage:
 *  - henc [-e|-d] <filepath> (<outputpath>)?
 * Flags:
 *  - -e used to encode filepath.
 *  - -d used to decode filepath
 *  Both options can receive an optional output path. Otherwise, they default
 *  to encode.hme and decode.hme, respectively.
 * @param argv number of arguments
 * @param argc argument flags
 * @return 0 if success, 1 otherwise
 */
int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage:\n\thenc [-e|-d] <filepath>\n\thenc [-e|-d] <filepath> <outputpath>" << std::endl;
        exit(1);
    }

    const bool encode = "-e" == argv[1];
    const std::string filepath(argv[2]);

    std::string outputpath = argc == 4 ? std::string(argv[3]) : encode ? "./encode.hmc" : "./decode.hmc";

    if (!filepath.contains(EXT)) {
        std::cerr << "Input file extension not supported\nExpected .hmc file" << std::endl;
        exit(1);
    }

    if (!outputpath.contains(EXT)) {
        std::cerr << "Output file extension not supported\nExpected .hmc file" << std::endl;
        exit(1);
    }

    auto huffmanEngine = HuffmanFactory::build(encode);

    try {
        huffmanEngine->run(filepath, outputpath);
    }catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    return 0;
}