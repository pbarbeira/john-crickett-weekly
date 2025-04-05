//
// Created by pbarbeira on 05-04-2025.
//

#ifndef BYTECONVERTER_H
#define BYTECONVERTER_H

#include <cstdint>
#include <vector>
#include <string>

class ByteConverter{
    static void _setByte(std::stringstream& ss, uint8_t byte, uint8_t check) {
        if (byte & check) {
            ss << '1';
        }else {
            ss << '0';
        }
    }

    public:
        static std::vector<uint8_t> toBytes(const std::string& byteString) {
            std::vector<uint8_t> bytes;
            uint8_t byte = 1;
            int bitCount= byte;

            for (const char i : byteString) {
                byte <<= 1;
                if (i == '1') {
                    byte |= 0x01;
                }
                bitCount++;
                if (bitCount % 8 == 0) {
                    bytes.push_back(byte);
                    byte = 0x00;
                }
            }

            if (bitCount % 8 != 0) {
                while (bitCount % 8 != 0) {
                    byte <<= 1;
                    bitCount++;
                }
                bytes.push_back(byte);
            }

            return bytes;
        };

        static std::string fromBytes(const std::vector<uint8_t>& bytes) {
            std::stringstream ss;
            int i = 0;
            for (; i < bytes.size(); i++) {
                ss << bytes[i];
                if (bytes[i] == '=') {
                    //we ignore first bit of the bit string
                    i++;
                    break;
                }
            }

            for (; i < bytes.size(); i++) {
                for (uint8_t byte = 0x80; byte > 0; byte >>= 1) {
                    _setByte(ss, bytes[i], byte);
                }
            }

            return ss.str();
        }

};

#endif //BYTECONVERTER_H
