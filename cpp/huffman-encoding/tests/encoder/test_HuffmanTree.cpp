//
// Created by pbarbeira on 23-03-2025.
//

#include <gtest/gtest.h>
#include "../../src/encoder/HuffmanTree.h"
#include <unordered_map>

using ull = unsigned long long;

TEST(HuffmanTreeTest, BuildsTreeProperly){
    const std::vector EXPECTED = {15, 6, 14, 12, 13, 1, 7, 4, 11, 8, 10, 9, 3, 2, 5};
    const std::unordered_map<wchar_t, ull> map = {
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


    EXPECT_EQ(EXPECTED, ids);
    HuffmanTree::resetId();
}

TEST(HuffmanTreeTest, EncodesFrequencyProperly) {
    std::vector EXPECTED = {306, 120, 186, 79, 107, 37, 42, 42, 65, 32, 33, 9, 24, 2, 7};
    const std::unordered_map<wchar_t, ull> map = {
        { 'c', 32},
        { 'd', 42},
        { 'e', 120},
        { 'k', 7},
        { 'l', 42},
        { 'm', 24},
        { 'u', 37},
        { 'z', 2},
    };

    const auto tree = HuffmanTree::buildTree(map);

    const auto result = HuffmanTree::encodeFrequency(tree.get());

    EXPECT_EQ(EXPECTED, result);
    HuffmanTree::resetId();
}

TEST(HuffmanTreeTest, EncodesHeaderProperly) {
    std::wstring EXPECTED = L"15,6,14|6,e|14,12,13|12,1,7|13,4,11|1,u|7,d|4,l|11,8,10|8,c|10,9,3|9,2,5|3,m|2,z|5,k|=";
    std::unordered_map<wchar_t, ull> map = {
        { 'c', 32},
        { 'd', 42},
        { 'e', 120},
        { 'k', 7},
        { 'l', 42},
        { 'm', 24},
        { 'u', 37},
        { 'z', 2},
    };

    const auto tree = HuffmanTree::buildTree(map);

    const auto result = HuffmanTree::encodeHeader(tree.get());

    EXPECT_EQ(EXPECTED, result);
    HuffmanTree::resetId();
}

// TEST(HuffmanTreeTest, BuildFromEncodedHeader) {
//     const std::wstring EXPECTED = L"15,6,14|6,e|14,12,13|12,1,7|13,4,11|1,u|7,d|4,l|11,8,10|8,c|10,9,3|9,2,5|3,m|2,z|5,k|=";
//
//     const auto root = HuffmanTree::buildTree(EXPECTED);
//
//     const auto result = HuffmanTree::encodeHeader(root.get());
//
//     EXPECT_EQ(EXPECTED, result);
// }