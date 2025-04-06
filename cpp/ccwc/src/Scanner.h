//
// Created by pbarbeira on 05-04-2025.
//

#ifndef SCANNER_H
#define SCANNER_H

#include "Options.h"

using ull = unsigned long long;

/**
 * Scans the input in order to extract the counts.
 */
class Scanner {
    public:
        /**
         * Receives a wide string and iterates through it. Counts
         * the number of words and lines. Stores the length of the
         * string as the number of characters.
         * @param input the input string.
         * @return the input string metadata.
         */
        static std::unordered_map<Option, ull> getWcCounts(const std::wstring& input){
            std::unordered_map<Option, ull> counts = {
                { Option::BYTE, 0},
                { Option::LINE, 1},
                { Option::WORD, 0},
                { Option::CHAR, 0},
            };
            counts[Option::CHAR] = input.length();

            for (int i = 0; i < input.length(); i++) {
                if (const wchar_t c = input[i]; isspace(c) || i == input.length() - 1) {
                    if (c == '\n') {
                        counts[Option::LINE]++;
                    }
                    if (!isspace(input[i - 1])) {
                        counts[Option::WORD]++;
                    }
                }


            }
            return counts;
        }
};

#endif //SCANNER_H
