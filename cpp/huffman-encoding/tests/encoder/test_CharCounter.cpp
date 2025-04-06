//
// Created by pbarbeira on 23-03-2025.
//

#include <codecvt>
#include <gtest/gtest.h>
#include "../../src/encoder/CharCounter.h"
#include <fstream>

#include "../../src/utils/Reader.h"

TEST(CharCounterTest, CanHandleEmptyString) {
    std::wstring testStr;
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 0);
}

TEST(CharCounterTest, CanCountSingleChar) {
    std::wstring testStr = L"aaaaaa";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
}

TEST(CharCounterTest, CanCountMultipleChar) {
    std::wstring testStr = L"aaaaaabbbcccc";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
    EXPECT_EQ(counts['b'], 3);
    EXPECT_EQ(counts['c'], 4);
}

TEST(CharCounterTest, CanDistinguishUpperAndLower) {
    std::wstring testStr = L"aaaaaaAAAAA";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
    EXPECT_EQ(counts['A'], 5);
}

TEST(CharCounterTest, CanHandleMixedChars) {
    std::wstring testStr = L"aAbaAacbcAacbbAacAa";
    auto counts = CharCounter::countChars(testStr);
    EXPECT_EQ(counts['a'], 6);
    EXPECT_EQ(counts['A'], 5);
    EXPECT_EQ(counts['b'], 4);
    EXPECT_EQ(counts['c'], 4);
}

TEST(CharCounterTest, CanHandleLargeInputs) {
    const std::string input = HmcReader::readAsString("tests/input/test.txt");

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wText = converter.from_bytes(input);

    auto counts = CharCounter::countChars(wText);
    EXPECT_EQ(counts['X'], 333);
    EXPECT_EQ(counts['t'], 223000);
}