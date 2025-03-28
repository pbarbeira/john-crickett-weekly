//
// Created by pbarbeira on 23-03-2025.
//

#ifndef CHARCOUNTER_H
#define CHARCOUNTER_H

#include <unordered_map>
#include <string>
#include <algorithm>

using ull = unsigned long long;

class CharCounter{
    public:
        static std::unordered_map<char, ull> countChars(const std::string& str){
            std::unordered_map<char, ull> charCounts;
            std::ranges::for_each(str, [&charCounts](const char& c){
                if(!charCounts.contains(c)){
                    charCounts[c] = 0;
                }
                charCounts[c]++;
            });
            return charCounts;
        }
};

#endif //CHARCOUNTER_H
