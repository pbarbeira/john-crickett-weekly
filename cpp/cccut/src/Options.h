//
// Created by pbarbeira on 06-04-2025.
//

#ifndef OPTIONS_H
#define OPTIONS_H

#include <regex>
#include "Logger.h"

struct Options{
    std::string filename;
    char delimiter = '\t';
    unsigned int field{};
};

inline std::regex pattern(R"(.*?\.(csv|tsv))");

class OptionsParser{
    static void _handleField(Options* options, const std::string& arg, Logger* logger){
        if(arg.size() < 3){
            logger->log(LogLevel::ERROR, "-f option must have at least one target field");
            throw std::invalid_argument("Unspecified value [-f]");
        }
        options->field = std::stoi(arg.substr(2, arg.size() - 2));
    }

    static void _handleDelimiter(Options* options, const std::string& arg, Logger* logger){
        if(arg.size() != 3){
            logger->log(LogLevel::ERROR, "-d option must have one delimiting character");
            throw std::invalid_argument("Unspecified value [-d]");
        }
        options->delimiter = arg[2];
    }
    public:
        static std::unique_ptr<Options> parse(const int argc, char* argv[], Logger* logger){
            if(argc < 3){
                std::stringstream ss;
                ss << "\n\tUsage:\n\t"
                   << "\tcccut [-f]<fields> <filename>\n\t"
                   << "\tcccut [-f]<fields> [-d]<delimitir> <filename>\n\t"
                   << std::endl;
                logger->log(INFO, ss.str());
                throw std::runtime_error("Invalid usage");
            }
            auto options = std::make_unique<Options>();
            for(int i = 1; i < argc; i++) {
                std::string arg(argv[i]);
                if(arg.contains("-f")){
                    _handleField(options.get(), arg, logger);
                }
                if(arg.contains("-d")){
                    _handleDelimiter(options.get(), arg, logger);
                }
                if(std::regex_match(arg, pattern)){
                    options->filename = arg;
                }
            }
            if (options->filename.empty()) {
                throw std::invalid_argument("Filename not specified");
            }
            return std::move(options);
        };
};

#endif //OPTIONS_H
