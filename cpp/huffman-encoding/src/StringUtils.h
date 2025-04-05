//
// Created by pbarbeira on 05-04-2025.
//

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <vector>
#include <string>

class StringUtils {
    public:
        static std::vector<std::string> split(const std::string& s, const char delim) {
            std::vector<std::string> out;
            int last = 0;
            for (int i = 0; i < s.length(); i++) {
                if (s[i] == delim) {
                    out.push_back(s.substr(last, i - last));
                    last = i + 1;
                }
                if (i == s.length() - 1 && last < i) {
                    out.push_back(s.substr(last));
                }
            }
            return out;
        }
};

#endif //STRINGUTILS_H
