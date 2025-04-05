//
// Created by pbarbeira on 23-03-2025.
//

#include <gtest/gtest.h>
#include "../src/HuffmanTree.h"
#include <unordered_map>

using ull = unsigned long long;

TEST(HuffmanTreeTest, BuildsTreeProperly){
    const std::unordered_map<char, ull> map = {
        { 'c', 32},
        { 'd', 42},
        { 'e', 120},
        { 'k', 7},
        { 'l', 42},
        { 'm', 24},
        { 'u', 37},
        { 'z', 2},
    };

    const auto root = HuffmanTree::buildTree(map);

    std::vector<int> ids;

    std::queue<HuffmanNode*> queue;
    queue.push(root.get());
    while (!queue.empty()) {
        const auto node = queue.front();
        queue.pop();

        ids.push_back(node->id);

        if (node->left != nullptr) {
            queue.push(node->left.get());
        }
        if (node->right != nullptr) {
            queue.push(node->right.get());
        }
    }

    const std::vector expected = {15, 6, 14, 12, 13, 1, 7, 4, 11, 8, 10, 9, 3, 2, 5};

    EXPECT_EQ(expected, ids);
    HuffmanTree::resetId();
}

TEST(HuffmanTreeTest, EncodesFrequencyProperly) {
    const std::unordered_map<char, ull> map = {
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

    auto result = HuffmanTree::encodeFrequency(tree.get());
    std::vector expected = {306, 120, 186, 79, 107, 37, 42, 42, 65, 32, 33, 9, 24, 2, 7};

    EXPECT_EQ(expected, result);
    HuffmanTree::resetId();
}

TEST(HuffmanTreeTest, EncodesHeaderProperly) {
    std::unordered_map<char, ull> map = {
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

    auto result = HuffmanTree::encodeHeader(tree.get());
    std::string expected = "15,6,14|6,e|14,12,13|12,1,7|13,4,11|1,u|7,d|4,l|11,8,10|8,c|10,9,3|9,2,5|3,m|2,z|5,k|=";

    EXPECT_EQ(expected, result);
    HuffmanTree::resetId();
}