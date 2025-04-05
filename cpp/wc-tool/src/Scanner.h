//
// Created by pbarbeira on 05-04-2025.
//

#ifndef SCANNER_H
#define SCANNER_H

#include "Options.h"

using ull = unsigned long long;

class Scanner {
    const Options* _options;
    std::unordered_map<Option, ull> _counts = {
        { Option::BYTE, 0},
        { Option::LINE, 1},
        { Option::WORD, 0},
        { Option::CHAR, 0},
    };

    public:
        explicit Scanner(const Options* options):
             _options(options) {}

        std::unordered_map<Option, ull> getWcCounts(const std::string& input){
            for (const auto& c : input) {
                if (_options->options.at(Option::BYTE)) {
                    _counts[Option::BYTE]++;
                }
                if (_options->options.at(Option::CHAR)) {
                    _counts[Option::CHAR]++;
                }
                if (isspace(c)) {
                    if (c == '\n' && _options->options.at(Option::LINE)) {
                        _counts[Option::LINE]++;
                    }
                    if (_options->options.at(Option::WORD)) {
                        _counts[Option::WORD]++;
                    }
                }

            }
            return _counts;
        }
};

#endif //SCANNER_H
