//
// Created by pbarbeira on 23-03-2025.
//

#include <gtest/gtest.h>
#include "../../src/encoder/CharCounter.h"
#include <fstream>

TEST(CharCounterTest, CanHandleEmptyString) {
    std::string testStr;
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 0);
}

TEST(CharCounterTest, CanCountSingleChar) {
    std::string testStr = "aaaaaa";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
}

TEST(CharCounterTest, CanCountMultipleChar) {
    std::string testStr = "aaaaaabbbcccc";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
    EXPECT_EQ(counts['b'], 3);
    EXPECT_EQ(counts['c'], 4);
}

TEST(CharCounterTest, CanDistinguishUpperAndLower) {
    std::string testStr = "aaaaaaAAAAA";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
    EXPECT_EQ(counts['A'], 5);
}

TEST(CharCounterTest, CanHandleMixedChars) {
    std::string testStr = "aAbaAacbcAacbbAacAa";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
    EXPECT_EQ(counts['A'], 5);
    EXPECT_EQ(counts['b'], 4);
    EXPECT_EQ(counts['c'], 4);
}

TEST(CharCounterTest, CanHandleLargeInputs) {
    std::ifstream file("/home/pbarbeira/dev/code/john-crickett-weekly/cpp/huffman-encoding/test.txt");
    std::string line;
    std::string testStr;
    while (std::getline(file, line)) {
        testStr.append(line);
    }

    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['X'], 333);
    EXPECT_EQ(counts['t'], 223000);
}