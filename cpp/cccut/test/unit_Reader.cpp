//
// Created by pbarbeira on 06-04-2025.
//

#include <gtest/gtest.h>
#include "../src/Reader.h"

TEST(ReaderTest, CanReadLinesTsv) {
    int EXPECTED = 6;
    const auto lines = Reader::readFile("test/input/sample.tsv");

    EXPECT_EQ(lines.size(), EXPECTED);
}

TEST(ReaderTest, CanReadLinesCsv) {
    int EXPECTED = 156;
    const auto lines = Reader::readFile("test/input/fourchords.csv");

    EXPECT_EQ(lines.size(), EXPECTED);
}