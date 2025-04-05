//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../src/Reader.h"

const std::string EXPECTED_BASE = "This is some input data to use in basic tests.";
const std::string EXPECTED_MULTILINE = "This is some input data to use in basic tests.\n\nIt has multiple lines.";
const std::string EXPECTED_SPECIAL = "This is some input data to use in basic tests.\n\nIt uses weird porutugese characters.\n\nAssunção é uma coisa bela!";


TEST(ReaderTest, CanReadFile_BASE) {
    std::string filepath = "../test/input/reader.txt";

    std::ofstream file(filepath);
    if (file.is_open()) {
        file << EXPECTED_BASE;
    }
    file.close();

    auto result = Reader::readFile(filepath);

    EXPECT_EQ(result, EXPECTED_BASE);
}

TEST(ReaderTest, CanReadFile_MultiLine) {
    std::string filepath = "../test/input/reader.txt";

    std::ofstream file(filepath);
    if (file.is_open()) {
        file << EXPECTED_MULTILINE;
    }
    file.close();

    auto result = Reader::readFile(filepath);

    EXPECT_EQ(result, EXPECTED_MULTILINE);
}

TEST(ReaderTest, CanReadFile_Special) {
    std::string filepath = "../test/input/reader.txt";

    std::ofstream file(filepath);
    if (file.is_open()) {
        file << EXPECTED_SPECIAL;
    }
    file.close();

    auto result = Reader::readFile(filepath);

    EXPECT_EQ(result, EXPECTED_SPECIAL);
}

TEST(ReaderTest, CanReadSTDIN_BASE) {
    std::istringstream input(EXPECTED_BASE);
    std::cin.rdbuf(input.rdbuf());

    const auto result = Reader::readStdIn();

    EXPECT_EQ(result, EXPECTED_BASE);
}

TEST(ReaderTest, CanReadSTDIN_MultiLine) {
    std::istringstream input(EXPECTED_MULTILINE);
    std::cin.rdbuf(input.rdbuf());

    const auto result = Reader::readStdIn();

    EXPECT_EQ(result, EXPECTED_MULTILINE);
}

TEST(ReaderTest, CanReadSTDIN_Special) {
    std::istringstream input(EXPECTED_SPECIAL);
    std::cin.rdbuf(input.rdbuf());

    const auto result = Reader::readStdIn();

    EXPECT_EQ(result, EXPECTED_SPECIAL);
}