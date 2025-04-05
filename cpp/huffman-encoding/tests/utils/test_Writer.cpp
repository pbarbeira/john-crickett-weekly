//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>

#include "../../src/utils/Reader.h"
#include "../../src/utils/Writer.h"

TEST(FileWriterTest, WritesHeader) {
    std::string header = "15,6,14|6,e|14,12,13|12,1,7|13,4,11|1,u|7,d|4,l|11,8,10|8,c|10,9,3|9,2,5|3,m|2,z|5,k|=";
    std::string filepath = "./testWriter.txt";

    HmcWriter::writeHeader(filepath, header);

    std::ifstream file(filepath);
    std::string line;

    std::getline(file, line);
    file.close();
    std::remove(filepath.c_str());

    EXPECT_EQ(line, header);
}

TEST(FileWriterTest, WritesBody) {
    std::vector<uint8_t> expected = { 0xac, 0xde, 0x7f, 0xde};

    std::string body = "0101100110111100111111111011110";
    std::string filepath = "./testWriter";

    HmcWriter::writeBody(filepath, body);

    auto bytes = HmcReader::readBytes(filepath);
    std::remove(filepath.c_str());

    EXPECT_EQ(bytes.size(), expected.size());
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(bytes[i], expected[i]);
    }
}

TEST(FileWriterTest, WritesEncodedFile) {
    std::string header = "15,6,14|6,e|14,12,13|12,1,7|13,4,11|1,u|7,d|4,l|11,8,10|8,c|10,9,3|9,2,5|3,m|2,z|5,k|=";
    std::vector<uint8_t> expected;
    for (int i = 0; i < header.size(); i++) {
        expected.push_back(header[i]);
    }
    expected.push_back(0xac);
    expected.push_back(0xde);
    expected.push_back(0x7f);
    expected.push_back(0xde);

    std::string body = "0101100110111100111111111011110";
    std::string filepath = "./testWriter";

    HmcWriter::writeHeader(filepath, header);
    HmcWriter::writeBody(filepath, body);

    auto bytes = HmcReader::readBytes(filepath);
    std::remove(filepath.c_str());

    EXPECT_EQ(bytes.size(), expected.size());
    for (int i = 0; i < expected.size(); i++) {
        EXPECT_EQ(bytes[i], expected[i]);
    }
}
