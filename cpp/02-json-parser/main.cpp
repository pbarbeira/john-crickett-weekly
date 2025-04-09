#include <iostream>
#include "Parser.h"

int main() {
    std::string jsonStr = R"(
    {
      "N": 0,
      "M": 0,
      "nodes": {
        "entryNode": {
          "xPos": 0,
          "yPos": 0
        },
        "1": {
          "xPos": 0,
          "yPos": 0
        },
        "2": {
          "xPos": 0,
          "yPos": 0
        }
      }
    })";
    auto node = Parser::parse(jsonStr);
    node->print();
    return 0;
}