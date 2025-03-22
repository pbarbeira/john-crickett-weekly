#include <iostream>
#include "Lexer.h"
#include <vector>

int main() {
    std::string str = "{}[]:,truefalsenull\"test\"12.3";
    Lexer lexer = Lexer(str);
    std::vector<std::unique_ptr<Token>> v;
    while (lexer.hasNextToken()) {
        v.push_back(std::move(lexer.nextToken()));
    }
    for (int i = 0; i < v.size(); i++) {
        std::cout << v[i]->token << std::endl;
    }
    return 0;
}