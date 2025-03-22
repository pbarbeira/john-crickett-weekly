//
// Created by pbarbeira on 21-03-2025.
//

#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType{
  LEFT_CURLY, RIGHT_CURLY,
  LEFT_SQUARE, RIGHT_SQUARE,
  COMMA, COLON,
  TRUE, FALSE, NIL,
  STRING, NUMBER
};

struct Token{
    std::string token;
    TokenType type;

    Token(const std::string& token, const TokenType& type) : token(token), type(type) {}
};

#endif //TOKEN_H
