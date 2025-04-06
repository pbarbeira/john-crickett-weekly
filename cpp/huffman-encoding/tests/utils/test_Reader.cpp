//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../../src/utils/Reader.h"

TEST(FileReaderTest, ReadFileAsBytes){
    const std::vector<uint8_t> EXPECTED = {'a', 'b', 'c', 'd'};
    const std::string filepath = "../tests/input/testFile";

    const auto result = HmcReader::readBytes(filepath);
    EXPECT_EQ(result, EXPECTED);
}

TEST(FileReaderTest, ReadFileAsString){
    const std::string EXPECTED = "Hello\n\nThis, my dear friends, is a test file.\n\nIt is used to exemplify.";
    const std::string filepath = "../tests/input/testFileStr.txt";

    const auto result = HmcReader::readAsString(filepath);
    EXPECT_EQ(result, EXPECTED);
}

//sizes determined using wc on Ubuntu 24.0
TEST(FileReaderTest, CanReadFewParagraphs){
    constexpr int EXPECTED = 3685;
    const std::string filepath = "../tests/input/testLorem.txt";

    const auto result = HmcReader::readAsString(filepath);
    EXPECT_EQ(result.size(), EXPECTED);
}

TEST(FileReaderTest, CanReadLargeFiles){
    constexpr int EXPECTED = 3369045;
    const std::string filepath = "../tests/input/test.txt";

    const auto result = HmcReader::readAsString(filepath);
    EXPECT_EQ(result.size(), EXPECTED);
}