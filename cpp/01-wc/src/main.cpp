#include <codecvt>
#include <iostream>

#include "Options.h"
#include "Reader.h"
#include "Scanner.h"

/**
 * The main loop of the program. Parses options from command line
 * arguments. Reads text from input and runs it through Scanner.
 * Uses Options to determine the information to be shown to the
 * user according to the command line flags.
 * @param argc the number of command line arguments.
 * @param argv the command line arguments.
 * @return 0 if success, 1 otherwise.
 */
int main(const int argc, char *argv[]) {
    try {
        const auto options = OptionsParser::parse(argc, argv);

        const std::string text = options->options.at(Option::STDIN)
            ? Reader::readStdIn()
            : Reader::readFile(options->filename);


        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        const std::wstring wideStr = converter.from_bytes(text);

        auto counts = Scanner::getWcCounts(wideStr);
        counts[Option::BYTE] = text.length();

        const std::vector printOrder = {
            Option::LINE,
            Option::WORD,
            Option::CHAR,
            Option::BYTE
        };
        for (const auto& option : printOrder) {
            if (options->options.at(option)) {
                std:: cout << counts.at(option);
                std::cout << "  ";
            }
        }
        std::cout << options->filename << std::endl;
    }catch (const std::range_error &e) {
        std::cerr << "Encoding error: " << e.what() << std::endl;
        return 1;
    }
    catch (std::exception &e) {
        std::cerr << "Runtime error: " << e.what() << std::endl;
        std::cerr << "Usage: ccwc [-c|-l|-w|-m] [filepath]\n";
        return 1;
    }

    return 0;
}
