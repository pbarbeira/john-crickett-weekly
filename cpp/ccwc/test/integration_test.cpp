//
// Created by pbarbeira on 06-04-2025.
//

#include <codecvt>
#include <gtest/gtest.h>
#include "../src/Reader.h"
#include "../src/Scanner.h"

TEST(IntegrationTest, ReadsFullBook) {
    constexpr int EXPECTED_BYTE = 342190;
    constexpr int EXPECTED_CHAR = 339292;
    constexpr int EXPECTED_WORD = 58164;
    constexpr int EXPECTED_LINE = 7146;

    const std::string filepath = "test/input/test.txt";
    const std::string text = Reader::readFile(filepath);

    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    const std::wstring wideStr = converter.from_bytes(text);

    auto result = Scanner::getWcCounts(wideStr);
    result[Option::BYTE] = text.length();

    EXPECT_EQ(result.at(Option::BYTE), EXPECTED_BYTE);
    EXPECT_EQ(result.at(Option::CHAR), EXPECTED_CHAR);
    EXPECT_EQ(result.at(Option::WORD), EXPECTED_WORD);
    EXPECT_EQ(result.at(Option::LINE), EXPECTED_LINE);
}
