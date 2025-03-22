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
    std::string value;
    TokenType type;

    Token(const std::string& value, const TokenType& type) : value(value), type(type) {}
};

#endif //TOKEN_H
