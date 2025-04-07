//
// Created by pbarbeira on 06-04-2025.
//

#include <gtest/gtest.h>
#include "../src/Options.h"

TEST(OptionsParserTest, ThrowOnInsufficientArguments) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "filename.txt" };
        const auto options = OptionsParser::parse(2, argv, logger.get());
        FAIL();
    } catch(const std::exception& e){
    }
}


TEST(OptionsParserTest, ThrowOnFieldNotSet) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "-f", "filename.txt" };
        const auto options = OptionsParser::parse(3, argv, logger.get());
        FAIL();
    } catch(const std::exception& e){
    }
}

TEST(OptionsParserTest, ThrowOnDelimiterNotSet) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "-d", "filename.txt" };
        const auto options = OptionsParser::parse(3, argv, logger.get());
        FAIL();
    } catch(const std::exception& e){}
}

TEST(OptionsParserTest, ThrowOnInvalidFilename) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "-d.", "filename.txt" };
        const auto options = OptionsParser::parse(3, argv, logger.get());
        FAIL();
    } catch(const std::exception& e){}
}

TEST(OptionsParserTest, OptionsNoFilename) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "-d.", "-f1" };
        const auto options = OptionsParser::parse(3, argv, logger.get());
        EXPECT_EQ(options->stdin, true);
    } catch(const std::exception& e) {
        FAIL();
    }
}

TEST(OptionsParserTest, HandleField) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "-f1", "filename.csv" };
        const auto options = OptionsParser::parse(3, argv, logger.get());

        EXPECT_EQ(options->filename, "filename.csv");
        EXPECT_EQ(options->fields.size(), 1);
        EXPECT_EQ(options->fields[0], 1);
    } catch(const std::exception& e){
        FAIL();
    }
}

TEST(OptionsParserTest, HandleDelimiter) {
    const auto logger = std::make_unique<StringLogger>();
    try{
        char* argv[] = { "main", "-d.", "filename.csv" };
        const auto options = OptionsParser::parse(3, argv, logger.get());

        EXPECT_EQ(options->delimiter, '.');
        EXPECT_EQ(options->filename, "filename.csv");
    } catch(const std::exception& e){
        FAIL();
    }
}

TEST(OptionsParserTest, HandleFieldAndDelimiter) {
    try{
        const auto logger = std::make_unique<StringLogger>();
        char* argv[] = { "main", "-f1", "-d.", "filename.csv" };
        const auto options = OptionsParser::parse(4, argv, logger.get());

        EXPECT_EQ(options->filename, "filename.csv");
        EXPECT_EQ(options->delimiter, '.');
        EXPECT_EQ(options->fields.size(), 1);
        EXPECT_EQ(options->fields[0], 1);
    } catch(const std::exception& e){
        FAIL();
    }
}
TEST(OptionsParserTest, HandleMultiFieldCommaSeparated) {
    try{
        const auto logger = std::make_unique<StringLogger>();
        char* argv[] = { "main", "-f1,2", "filename.csv" };
        const auto options = OptionsParser::parse(3, argv, logger.get());

        EXPECT_EQ(options->filename, "filename.csv");
        EXPECT_EQ(options->delimiter, '\t');
        EXPECT_EQ(options->fields.size(), 2);
        EXPECT_EQ(options->fields[0], 1);
        EXPECT_EQ(options->fields[1], 2);
    } catch(const std::exception& e){
        FAIL();
    }
}

TEST(OptionsParserTest, HandleMultiFieldSpaceSeparated) {
    try{
        const auto logger = std::make_unique<StringLogger>();
        char* argv[] = { "main", "-f\"1 2\"", "filename.csv" };
        const auto options = OptionsParser::parse(3, argv, logger.get());

        EXPECT_EQ(options->filename, "filename.csv");
        EXPECT_EQ(options->delimiter, '\t');
        EXPECT_EQ(options->fields.size(), 2);
        EXPECT_EQ(options->fields[0], 1);
        EXPECT_EQ(options->fields[1], 2);
    } catch(const std::exception& e){
        FAIL();
    }
}
