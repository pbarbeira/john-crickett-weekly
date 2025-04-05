//
// Created by pbarbeira on 05-04-2025.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

/**
 * Static string utility class to encapsulate some common operations. While
 * this could've been done procedurally, using a static class allows us
 * another dimension of communication of intent within the code.
 */
class StringUtils {
    public:
    /**
     * Splits a string in a list of tokens using delim as a delimiter character.
     * @param s the string to be split.
     * @param delim the delimiter character.
     * @return the list of split tokens
     */
    static std::vector<std::string> split(const std::string& s, const char delim) {
            std::vector<std::string> out;
            int last = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == delim) {
                    out.push_back(s.substr(last, i - last));
                    last = i + 1;
                }
                if (i == s.length() - 1 && last <= i) {
                    out.push_back(s.substr(last));
                }
            }
            return out;
        }
};

#endif //STRINGUTILS_H
