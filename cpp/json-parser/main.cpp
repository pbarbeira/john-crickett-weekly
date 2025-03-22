#include <iostream>
#include "Parser.h"

int main() {
    std::string jsonStr = R"({"key":["list1","list2","list3"]})";
    auto node = Parser::parse(jsonStr);
    node->print();
    return 0;
}