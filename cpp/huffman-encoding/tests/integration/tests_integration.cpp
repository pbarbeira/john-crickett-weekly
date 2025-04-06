//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../../src/HuffmanFactory.h"
#include "../../src/utils/Reader.h"

TEST(HuffmanEncodeEngineIntegrationTest, CanEncodeAndDecodeAsciiFile) {
    std::string INPUT_FILE = "../tests/testAscii.txt";
    std::string OUTPUT_FILE = "./encoded.hmc";

    std::ifstream inFile(INPUT_FILE);
    std::string INPUT_TEXT = Reader::readAsString(inFile);
    inFile.close();

    auto engine = HuffmanFactory::build();
    engine->run(INPUT_FILE, OUTPUT_FILE);

    std::ifstream encodedCheck(OUTPUT_FILE);
    EXPECT_EQ(encodedCheck.is_open(), true);
    encodedCheck.close();

    engine = HuffmanFactory::build(false);
    INPUT_FILE = OUTPUT_FILE;
    OUTPUT_FILE = "./decoded.txt";

    engine->run(INPUT_FILE, OUTPUT_FILE);

    std::ifstream decodedCheck(OUTPUT_FILE);
    std::string decodedText = Reader::readAsString(decodedCheck);
    decodedCheck.close();

    std::remove(OUTPUT_FILE.c_str());

    EXPECT_EQ(decodedText, INPUT_TEXT);
}

TEST(HuffmanEncodeEngineIntegrationTest, CanEncodeDecodeFewParagraphs) {
    std::string INPUT_FILE = "../tests/testLorem.txt";
    std::string OUTPUT_FILE = "./encoded.hmc";

    std::ifstream inFile(INPUT_FILE);
    std::string INPUT_TEXT = Reader::readAsString(inFile);
    inFile.close();

    auto engine = HuffmanFactory::build();
    engine->run(INPUT_FILE, OUTPUT_FILE);

    std::ifstream encodedCheck(OUTPUT_FILE);
    EXPECT_EQ(encodedCheck.is_open(), true);
    encodedCheck.close();

    engine = HuffmanFactory::build(false);
    INPUT_FILE = OUTPUT_FILE;
    OUTPUT_FILE = "./decoded.txt";

    engine->run(INPUT_FILE, OUTPUT_FILE);

    std::ifstream decodedCheck(OUTPUT_FILE);
    std::string decodedText = Reader::readAsString(decodedCheck);
    decodedCheck.close();

    std::remove(OUTPUT_FILE.c_str());

    EXPECT_EQ(decodedText, INPUT_TEXT);
}

TEST(HuffmanEncodeEngineIntegrationTest, CanEncodeDecodeLargeText) {
    std::string INPUT_FILE = "../tests/test.txt";
    std::string OUTPUT_FILE = "./encoded.hmc";

    std::ifstream inFile(INPUT_FILE);
    std::string INPUT_TEXT = Reader::readAsString(inFile);
    inFile.close();

    auto engine = HuffmanFactory::build();
    engine->run(INPUT_FILE, OUTPUT_FILE);

    std::ifstream encodedCheck(OUTPUT_FILE);
    EXPECT_EQ(encodedCheck.is_open(), true);
    encodedCheck.close();

    engine = HuffmanFactory::build(false);
    INPUT_FILE = OUTPUT_FILE;
    OUTPUT_FILE = "./decoded.txt";

    engine->run(INPUT_FILE, OUTPUT_FILE);

    std::ifstream decodedCheck(OUTPUT_FILE);
    std::string decodedText = Reader::readAsString(decodedCheck);
    decodedCheck.close();

    std::remove(OUTPUT_FILE.c_str());

    EXPECT_EQ(decodedText, INPUT_TEXT);
}