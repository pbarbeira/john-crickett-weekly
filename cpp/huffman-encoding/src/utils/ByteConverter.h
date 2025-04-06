//
// Created by pbarbeira on 05-04-2025.
//

#ifndef BYTECONVERTER_H
#define BYTECONVERTER_H

#include <cstdint>
#include <vector>
#include <string>

/**
 * Utility class used to convert string representations of bit streams to bytes.
 */
class ByteConverter{
    /**
     * Used to convert uint8_t bytes into characters. The function uses a byte to
     * check whether a given bit of a given byte is set to 1 or not, and outputs
     * it to the stringstream accordingly.
     * @param ss the stringstream to output to
     * @param byte the byte being set
     * @param check the check byte
     */
    static void _setByte(std::stringstream& ss, const uint8_t& byte, const uint8_t& check) {
        if (byte & check) {
            ss << '1';
        }else {
            ss << '0';
        }
    }

    public:
    /**
     * Converts a string representation of a bit stream into raw bytes.
     * @param bitString the bitstream
     * @return a list of bytes
     */
    static std::vector<uint8_t> toBytes(const std::string& bitString) {
            std::vector<uint8_t> bytes;
            uint8_t byte = 1;
            int bitCount= byte;

            for (const char i : bitString) {
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

        /**
         * Converts a list of raw bytes into a string representation of their
         * bit stream. Encapsulates some case-specific logic that's only relevant
         * to our use case.
         * @param bytes the list of raw bytes.
         * @return a string representation of the bit stream.
         */
        static std::string fromBytes(const std::vector<uint8_t>& bytes) {
            std::stringstream ss;

            for (int i = 0; i < bytes.size(); i++) {
                for (uint8_t byte = 0x80; byte > 0; byte >>= 1) {
                    _setByte(ss, bytes[i], byte);
                }
            }

            return ss.str().substr(1);
        }

};

#endif //BYTECONVERTER_H
