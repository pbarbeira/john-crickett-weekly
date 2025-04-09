//
// Created by pbarbeira on 05-04-2025.
//
#include <gtest/gtest.h>
#include "../src/Options.h"

const int OPTIONS_TOTAL = 5;

TEST(OptionParserTest, CanParseOptionBYTEOption) {
    char* argv[2] = { "main", "-c"};
    const auto result = OptionsParser::parse(2, argv);

    const auto map = result->options;
    EXPECT_EQ(map.size(), OPTIONS_TOTAL);
    EXPECT_EQ(map.at(Option::BYTE), true);
    EXPECT_EQ(map.at(Option::LINE), false);
    EXPECT_EQ(map.at(Option::WORD), false);
    EXPECT_EQ(map.at(Option::CHAR), false);
    EXPECT_EQ(map.at(Option::STDIN), true);
    EXPECT_EQ(result->filename, "");
}

TEST(OptionParserTest, CanParseOptionLINEOption) {
    char* argv[2] = { "main", "-l" };
    const auto result = OptionsParser::parse(2, argv);

    const auto map = result->options;
    EXPECT_EQ(map.size(), OPTIONS_TOTAL);
    EXPECT_EQ(map.at(Option::BYTE), false);
    EXPECT_EQ(map.at(Option::LINE), true);
    EXPECT_EQ(map.at(Option::WORD), false);
    EXPECT_EQ(map.at(Option::CHAR), false);
    EXPECT_EQ(map.at(Option::STDIN), true);
    EXPECT_EQ(result->filename, "");
}

TEST(OptionParserTest, CanParseOptionWORDOption) {
    char* argv[2] = { "main", "-w" };
    const auto result = OptionsParser::parse(2, argv);

    const auto map = result->options;
    EXPECT_EQ(map.size(), OPTIONS_TOTAL);
    EXPECT_EQ(map.at(Option::BYTE), false);
    EXPECT_EQ(map.at(Option::LINE), false);
    EXPECT_EQ(map.at(Option::WORD), true);
    EXPECT_EQ(map.at(Option::CHAR), false);
    EXPECT_EQ(map.at(Option::STDIN), true);
    EXPECT_EQ(result->filename, "");
}

TEST(OptionParserTest, CanParseCharOption) {
    char* argv[2] = { "main", "-m" };
    const auto result = OptionsParser::parse(2, argv);

    const auto map = result->options;
    EXPECT_EQ(map.size(), OPTIONS_TOTAL);
    EXPECT_EQ(map.at(Option::BYTE), false);
    EXPECT_EQ(map.at(Option::LINE), false);
    EXPECT_EQ(map.at(Option::WORD), false);
    EXPECT_EQ(map.at(Option::CHAR), true);
    EXPECT_EQ(map.at(Option::STDIN), true);
    EXPECT_EQ(result->filename, "");
}

TEST(OptionParserTest, CanParseMultiOption) {
    char* argv[4] = { "main", "-m", "-c", "-w" };
    const auto result = OptionsParser::parse(4, argv);

    const auto map = result->options;
    EXPECT_EQ(map.size(), OPTIONS_TOTAL);
    EXPECT_EQ(map.at(Option::BYTE), true);
    EXPECT_EQ(map.at(Option::LINE), false);
    EXPECT_EQ(map.at(Option::WORD), true);
    EXPECT_EQ(map.at(Option::CHAR), true);
    EXPECT_EQ(map.at(Option::STDIN), true);
    EXPECT_EQ(result->filename, "");
}

TEST(OptionParserTest, CanParseFile) {
    char* argv[4] = { "main", "-m", "file.txt" };
    const auto result = OptionsParser::parse(3, argv);

    const auto map = result->options;
    EXPECT_EQ(map.size(), OPTIONS_TOTAL);
    EXPECT_EQ(map.at(Option::BYTE), false);
    EXPECT_EQ(map.at(Option::LINE), false);
    EXPECT_EQ(map.at(Option::WORD), false);
    EXPECT_EQ(map.at(Option::CHAR), true);
    EXPECT_EQ(map.at(Option::STDIN), false);
    EXPECT_EQ(result->filename, "file.txt");
}

TEST(OptionParserTest, ThrowsOnBadInput) {
    try {
        char* argv[4] = { "main", "-x" };
        const auto result = OptionsParser::parse(3, argv);
    }catch (const std::exception& e) {
        EXPECT_EQ(true, true);
        return;
    }
    EXPECT_EQ(true, false);
}