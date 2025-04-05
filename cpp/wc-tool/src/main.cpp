#include <iostream>

#include "Options.h"
#include "Reader.h"
#include "Scanner.h"

int main(int argc, char *argv[]) {
    try {
        auto options = OptionsParser::parse(argc, argv);
        std::string text = options->options.at(Option::STDIN)
            ? Reader::readStdIn()
            : Reader::readFile(options->filename);

        auto scanner = Scanner(options.get());
        auto counts = scanner.getWcCounts(text);

        const std::vector printOrder = { Option::LINE, Option::WORD, Option::CHAR, Option::BYTE };
        for (const auto& option : printOrder) {
            if (options->options.at(option)) {
                std:: cout << counts.at(option);
                std::cout << "  ";
            }
        }
        std::cout << options->filename << std::endl;
    }catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Usage: ccwc [-c|-l|-w|-m] [filepath]\n";
    }

    return 0;
}
