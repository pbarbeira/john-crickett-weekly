//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../../src/encoder/Encoder.h"

std::unique_ptr<HuffmanNode> _buildTestTree() {
    const std::unordered_map<char, unsigned long long> map = {
        { 'c', 32},
        { 'd', 42},
        { 'e', 120},
        { 'k', 7},
        { 'l', 42},
        { 'm', 24},
        { 'u', 37},
        { 'z', 2},
    };

    //We already tested this, no point building the tree manually
    return HuffmanTree::buildTree(map);
}

TEST(EncoderTest, CanBuildMap) {
    const auto root = _buildTestTree();

    const Encoder encoder(root.get());
    const auto encoded = encoder.getPrefixTable();

    EXPECT_EQ(encoded.size(), 8);
    EXPECT_EQ(encoded.at('e'), "0");
    EXPECT_EQ(encoded.at('u'), "100");
    EXPECT_EQ(encoded.at('d'), "101");
    EXPECT_EQ(encoded.at('l'), "110");
    EXPECT_EQ(encoded.at('c'), "1110");
    EXPECT_EQ(encoded.at('m'), "11111");
    EXPECT_EQ(encoded.at('z'), "111100");
    EXPECT_EQ(encoded.at('k'), "111101");

    HuffmanTree::resetId();
}

TEST(EncoderTest, CanEncodeText) {
    std::string TO_ENCODE = "edulzmkc";
    std::string EXPECTED = "0101100110111100111111111011110";

    const auto root = _buildTestTree();

    const Encoder encoder(root.get());
    const auto result = encoder.encode(TO_ENCODE);

    EXPECT_EQ(EXPECTED, result);

    HuffmanTree::resetId();
}
