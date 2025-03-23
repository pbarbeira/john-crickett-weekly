//
// Created by pbarbeira on 23-03-2025.
//

#include <gtest/gtest.h>
#include "../src/HuffmanTree.h"
#include <unordered_map>

TEST(HuffmanTreeTest, BuildsTreeProperly){
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

    auto tree = HuffmanTree::buildTree(map);
    auto result = HuffmanTree::encode(tree.get());
    std::vector<int> expected = {306, 120, 186, 79, 107, 37, 42, 42, 65, 32, 33, 9, 24, 2, 7};

    EXPECT_EQ(expected, result);
}