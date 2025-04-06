//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../../src/utils//StringUtils.h"

TEST(StringUtilsTest, TokenizeComma) {
    const std::vector<std::wstring> EXPECTED = { L"12", L"13"};
    const std::wstring input = L"12,13";

    const auto result = StringUtils::split(input, ',');

    ASSERT_EQ(result, EXPECTED);
}

TEST(StrinGutilsTest, TokenizeBar) {
    const std::vector<std::wstring> EXPECTED = { L"12,13,14", L"13,a", L"14,b"};
    const std::wstring input = L"12,13,14|13,a|14,b|";

    const auto result = StringUtils::split(input, '|');

    ASSERT_EQ(result, EXPECTED);
}