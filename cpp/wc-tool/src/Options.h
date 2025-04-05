//
// Created by pbarbeira on 05-04-2025.
//

#ifndef OPTIONPARSER_H
#define OPTIONPARSER_H

#include <unordered_map>
#include <regex>
#include <memory>

enum class Option {
    BYTE, LINE, WORD, CHAR, STDIN
};

const std::regex pattern(R"(.+?\.txt)");

struct Options {
    std::unordered_map<Option, bool> options = {
        { Option::BYTE, false },
        { Option::LINE, false },
        { Option::WORD, false },
        { Option::CHAR, false },
        { Option::STDIN, true },
    };
    std::string filename;

    static std::unique_ptr<Options> defaultInstance() {
        auto options = std::make_unique<Options>();

        options->options[Option::BYTE] = true;
        options->options[Option::WORD] = true;
        options->options[Option::LINE] = true;

        return std::move(options);
    }
};

class OptionsParser {
    public:
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
