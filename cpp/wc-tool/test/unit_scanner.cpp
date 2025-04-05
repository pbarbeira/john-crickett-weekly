//
// Created by pbarbeira on 06-04-2025.
//

#ifndef UNIT_SCANNER_H
#define UNIT_SCANNER_H

#include <gtest/gtest.h>
#include "../src/Scanner.h"

TEST(ScannerTest, CanCountBytes) {
    constexpr int EXPECTED = 24;
    const std::string input = "This should be 24 bytes.";

    const auto options = std::make_unique<Options>();
    options->options[Option::BYTE] = true;

    auto scanner = Scanner(options.get());
    const  auto result = scanner.getWcCounts(input);
    EXPECT_EQ(result.at(Option::BYTE), EXPECTED);
}

TEST(ScannerTest, CanScanLines) {
    constexpr int EXPECTED = 3;
    const std::string input = "This should be \n3\nlines in total.";

    const auto options = std::make_unique<Options>();
    options->options[Option::LINE] = true;

    auto scanner = Scanner(options.get());
    const auto result = scanner.getWcCounts(input);
    EXPECT_EQ(result.at(Option::LINE), EXPECTED);
}

TEST(ScannerTest, CanCountWords) {
    constexpr int EXPECTED = 7;
    const std::string input = "This should be \n7\nwords in total.";

    const auto options = std::make_unique<Options>();
    options->options[Option::WORD] = true;

    auto scanner = Scanner(options.get());
    const auto result = scanner.getWcCounts(input);
    EXPECT_EQ(result.at(Option::WORD), EXPECTED);
}

TEST(ScannerTest, CanScanChars) {
    constexpr int EXPECTED = 24;
    const std::string input = "This should be 24 chars.";

    const auto options = std::make_unique<Options>();
    options->options[Option::CHAR] = true;

    auto scanner = Scanner(options.get());
    const  auto result = scanner.getWcCounts(input);
    EXPECT_EQ(result.at(Option::CHAR), EXPECTED);
}

TEST(ScannerTest, CanScanMultiple) {
    constexpr int EXPECTED_BYTE = 33;
    constexpr int EXPECTED_LINE = 3;
    constexpr int EXPECTED_WORD = 7;
    constexpr int EXPECTED_CHAR = 33;
    const std::string input = "This should be \n7\nwords in total.";

    const auto options = std::make_unique<Options>();
    options->options[Option::BYTE] = true;
    options->options[Option::LINE] = true;
    options->options[Option::WORD] = true;
    options->options[Option::CHAR] = true;

    auto scanner = Scanner(options.get());
    const  auto result = scanner.getWcCounts(input);
    EXPECT_EQ(result.at(Option::BYTE), EXPECTED_BYTE);
    EXPECT_EQ(result.at(Option::LINE), EXPECTED_LINE);
    EXPECT_EQ(result.at(Option::WORD), EXPECTED_WORD);
    EXPECT_EQ(result.at(Option::CHAR), EXPECTED_CHAR);
}


#endif //UNIT_SCANNER_H
