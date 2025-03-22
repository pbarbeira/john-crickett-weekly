//
// Created by pbarbeira on 21-03-2025.
//

#ifndef PARSER_H
#define PARSER_H

#include "JsonNode.h"
#include "Lexer.h"

class Parser {
    public:
      Parser();

      static JsonNode parse(const std::string& input);
};

#endif //PARSER_H
