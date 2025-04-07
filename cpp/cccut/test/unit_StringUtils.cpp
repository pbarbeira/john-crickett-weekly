//
// Created by pbarbeira on 07-04-2025.
//

#include <gtest/gtest.h>
#include "../src/StringUtils.h"

TEST(StringUtilsTest, SplitEmptyString) {
    const std::string INPUT = "";
    constexpr std::vector<std::string> EXPECTED;
    constexpr char DELIM = ',';

    const auto result = StringUtils::split(INPUT, DELIM);

    ASSERT_EQ(result, EXPECTED);
}

TEST(StringUtilsTest, SplitStringDelim) {
    const std::string INPUT = "token1,token2,token3";
    const std::vector<std::string> EXPECTED = { "token1", "token2", "token3" };
    constexpr char DELIM = ',';

    const auto result = StringUtils::split(INPUT, DELIM);

    ASSERT_EQ(result, EXPECTED);
}