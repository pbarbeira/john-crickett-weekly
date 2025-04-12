//
// Created by pbarbeira on 06-04-2025.
//

#ifndef OPTIONS_H
#define OPTIONS_H

#include <regex>
#include "Logger.h"
#include "StringUtils.h"

struct Options{
    std::string filename;
    char delimiter = '\t';
    std::vector<unsigned int> fields;
    bool stdin = false;
};

inline std::regex pattern(R"(.*?\.(csv|tsv))");
inline std::regex csv_pattern(R"(-f\d*(,\d*)*)");
inline std::regex ssv_pattern(R"(-f"\d*(\s\d*)*")");

class OptionsParser{
    static void _handleFieldInput(Options* options, const std::string& arg, Logger* logger, bool ssv = false) {
        char delim = ssv ? ' ' : ',';
        //if ssv we remove -f" and final ", otherwise only -f
        std::string input = arg.substr(ssv ? 3 : 2, arg.size() - (ssv ? 4 : 2));
        const auto tokens = StringUtils::split(input, delim);
        for (const auto& token : tokens) {
            const int field = std::stoi(token);
            if (field == 0) {
                logger->log(INFO, "-f option must be positive integer");
                throw std::invalid_argument("Invalid value [-f]");
            }
            options->fields.push_back(field);
        }
    }

    static void _handleField(Options* options, const std::string& arg, Logger* logger){
        if(arg.size() < 3){
            logger->log(INFO, "-f option must have at least one target field");
            throw std::invalid_argument("Unspecified value [-f]");
        }
        if (std::regex_match(arg, csv_pattern)) {
            _handleFieldInput(options, arg, logger);
            return;
        }
        if (std::regex_match(arg, ssv_pattern)) {
            _handleFieldInput(options, arg, logger, true);
            return;
        }
        throw std::invalid_argument("Invalid value [-f]");
    }

    static void _handleDelimiter(Options* options, const std::string& arg, Logger* logger){
        if(arg.size() != 3){
            logger->log(INFO, "-d option must have one delimiting character");
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
                   << "\tcccut [-f]<fields> [-d]<delimitir> <filename>";
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
                if (arg[0] != '-') {
                    if(std::regex_match(arg, pattern)){
                        options->filename = arg;
                        continue;
                    }
                    throw std::invalid_argument("Invalid file name");
                }
            }
            if (options->filename.empty()) {
                options->stdin = true;
            }
            return std::move(options);
        };
};

#endif //OPTIONS_H
