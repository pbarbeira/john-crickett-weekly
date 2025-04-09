//
// Created by pbarbeira on 05-04-2025.
//

#include <gtest/gtest.h>

#include "../../src/encoder/Decoder.h"



TEST(DecoderTest, DecodesByteStream) {
    const std::wstring EXPECTED = L"edulzmkc";

    auto bytes = ByteConverter::toBytes("0101100110111100111111111011110");
    const auto data = std::make_unique<DecodeData>(
        L"15,6,14|6,e|14,12,13|12,1,7|13,4,11|1,u|7,d|4,l|11,8,10|8,c|10,9,3|9,2,5|3,m|2,z|5,k|",
        bytes
    );

    const auto result = Decoder::decode(data.get());
    EXPECT_EQ(result, EXPECTED);
}