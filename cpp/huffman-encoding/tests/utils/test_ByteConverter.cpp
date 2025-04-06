//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>
#include "../../src/utils/ByteConverter.h"

TEST(ByteConverterTest, ConvertToBytes) {
    const std::string byteString = "0101100110111100111111111011110";
    const std::vector<uint8_t> expected = { 0xac, 0xde, 0x7f, 0xde};

    const auto result = ByteConverter::toBytes(byteString);

    ASSERT_EQ(result, expected);
}

TEST(ByteConverterTest, ConvertFromBytes) {
    const std::vector<uint8_t> bytes = { 0xac, 0xde, 0x7f, 0xde};
    const std::string expected = "0101100110111100111111111011110";

    const auto result = ByteConverter::fromBytes(bytes);

    ASSERT_EQ(result, expected);
}

TEST(ByteConverterTest, ConvertFromBytessStartZeroEndZero) {
    const std::vector<uint8_t> bytes = { 0xac, 0xde, 0x7f, 0xde};
    const std::string expected = "0101100110111100111111111011110";

    const auto result = ByteConverter::fromBytes(bytes);

    ASSERT_EQ(result, expected);
}

TEST(ByteConverterTest, ConvertFromBytesStartZeroEndOne) {
    const std::vector<uint8_t> bytes = { 0xac, 0xde, 0x7f, 0xdf};
    const std::string expected = "0101100110111100111111111011111";

    const auto result = ByteConverter::fromBytes(bytes);

    ASSERT_EQ(result, expected);
}

TEST(ByteConverterTest, ConvertFromBytesStartOneEndZero) {
    const std::vector<uint8_t> bytes = { 0xec, 0xde, 0x7f, 0xde};
    const std::string expected = "1101100110111100111111111011110";

    const auto result = ByteConverter::fromBytes(bytes);

    ASSERT_EQ(result, expected);
}

TEST(ByteConverterTest, ConvertFromBytesStartOneEndOne) {
    const std::vector<uint8_t> bytes = { 0xec, 0xde, 0x7f, 0xdf};
    const std::string expected = "1101100110111100111111111011111";

    const auto result = ByteConverter::fromBytes(bytes);

    ASSERT_EQ(result, expected);
}