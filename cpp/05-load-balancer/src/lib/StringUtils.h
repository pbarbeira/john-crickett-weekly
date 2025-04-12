//
// Created by pbarbeira on 07-04-2025.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>
#include <sstream>

class StringUtils {
public:
    static std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

#endif //STRINGUTILS_H
