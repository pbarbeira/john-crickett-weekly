//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../src/Reader.h"

TEST(FileReaderTest, ReadFileAsBytes){
    const std::string filepath = "../tests/testFile";
    std::vector<uint8_t> expected = {'a', 'b', 'c', 'd'};

    auto result = FileReader::readBytes(filepath);
    EXPECT_EQ(result, expected);
}