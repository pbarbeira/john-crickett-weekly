#include <iostream>
#include "HuffmanTree.h"

int main() {
    std::unordered_map<char, int> map = {
        { 'c', 32},
        { 'd', 42},
        { 'e', 120},
        { 'k', 7},
        { 'l', 42},
        { 'm', 24},
        { 'u', 37},
        { 'z', 2},
    };
    auto n = HuffmanTree::buildTree(map);
    std::cout << n->freq;
    return 0;
}