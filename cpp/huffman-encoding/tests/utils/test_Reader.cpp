//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../../src/utils/Reader.h"

TEST(FileReaderTest, ReadFileAsBytes){
    const std::string filepath = "../tests/testFile";
    std::vector<uint8_t> expected = {'a', 'b', 'c', 'd'};

    auto result = HmcReader::readBytes(filepath);
    EXPECT_EQ(result, expected);
}

TEST(FileReaderTest, ReadFileAsString){
    const std::string filepath = "../tests/testFileStr.txt";
    const std::string expected = "Hello\n\nThis, my dear friends, is a test file.\n\nIt is used to exemplify.";

    auto result = HmcReader::readAsString(filepath);
    EXPECT_EQ(result, expected);
}