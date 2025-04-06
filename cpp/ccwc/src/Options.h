//
// Created by pbarbeira on 05-04-2025.
//

#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include <unordered_map>
#include <regex>
#include <memory>

/**
 * Enum class containing the possible command line options, as
 * well as an indicator if the input should be read from stdin.
 */
enum class Option {
    BYTE, LINE, WORD, CHAR, STDIN
};

/**
 * Used to match .txt files.
 */
const std::regex pattern(R"(.+?\.txt)");

/**
 * Options class. stores command line options so the program can
 * use them.
 */
struct Options {
    /**
     * Stores information regarding which flags were used.
     */
    std::unordered_map<Option, bool> options = {
        { Option::BYTE, false },
        { Option::LINE, false },
        { Option::WORD, false },
        { Option::CHAR, false },
        { Option::STDIN, true },
    };
    /**
     * The name of the file, if STDIN is not to be used.
     */
    std::string filename;

    /**
     * Default options instance. Used to ensure default program
     * behavior when the user does not enter any option.
     * @return the default options instance.
     */
    static std::unique_ptr<Options> defaultInstance() {
        auto options = std::make_unique<Options>();

        options->options[Option::BYTE] = true;
        options->options[Option::WORD] = true;
        options->options[Option::LINE] = true;

        return std::move(options);
    }
};

/**
 * Parses the command line arguments to fill the Options class.
 */
class OptionsParser {
    public:
        /**
         * Main method. Analyses argc to determine if any command
         * line options were passed. If not, returns default Option.
         * If there were command line options passed, iterates
         * through them and fills the Options object accordingly.
         * @param argc the number of commandl line arguments.
         * @param argv the command line arguments.
         * @return unique pointer to the parsed options object.
         */
        static std::unique_ptr<Options> parse(int argc, char* argv[]) {
            if (argc == 1) {
                return Options::defaultInstance();
            }

            auto options = std::make_unique<Options>();
            
            for (int i = 1; i < argc; i++) {
                std::string arg(argv[i]);
                if (arg == "-c") {
                    options->options[Option::BYTE] = true;
                }
                else if (arg == "-l") {
                    options->options[Option::LINE] = true;
                }
                else if (arg == "-w") {
                    options->options[Option::WORD] = true;
                }
                else if (arg == "-m") {
                    options->options[Option::CHAR] = true;
                }
                else if (std::regex_match(arg, pattern)) {
                    options->options[Option::STDIN] = false;
                    options->filename = arg;
                }else {
                    throw std::runtime_error("Unknown option: " + std::string(argv[i]));
                }
            }
            return std::move(options);
        }
};

#endif //OPTIONPARSER_H
