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

        std::unordered_map<Option, ull> getWcCounts(const std::wstring& input){
            _counts[Option::CHAR] = input.length();

            for (int i = 0; i < input.length(); i++) {
                if (const wchar_t c = input[i]; isspace(c)) {
                    if (c == '\n') {
                        _counts[Option::LINE]++;
                    }
                    if (!isspace(input[i - 1])) {
                        _counts[Option::WORD]++;
                    }
                }


            }
            return _counts;
        }
};

#endif //SCANNER_H
