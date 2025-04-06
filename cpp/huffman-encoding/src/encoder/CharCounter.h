//
// Created by pbarbeira on 23-03-2025.
//

#ifndef CHARCOUNTER_H
#define CHARCOUNTER_H

#include <unordered_map>
#include <string>
#include <algorithm>

using ull = unsigned long long;

/**
 * Encapsulates the character counting logic required to build the frequency
 * table.
 */
class CharCounter{
    public:
    /**
     * Counts how many times each character in a given string appears in it.
     * @param str the input string.
     * @return a map containing the character frequencies.
     */
    static std::unordered_map<wchar_t, ull> countChars(const std::wstring& str){
            std::unordered_map<wchar_t, ull> charCounts;
            std::ranges::for_each(str, [&charCounts](const wchar_t& c){
                if(!charCounts.contains(c)){
                    charCounts[c] = 0;
                }
                charCounts[c]++;
            });
            return charCounts;
        }
};

#endif //CHARCOUNTER_H
