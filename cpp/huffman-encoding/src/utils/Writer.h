//
// Created by pbarbeira on 05-04-2025.
//

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <fstream>

#include "ByteConverter.h"

/**
 * Base writer class. Encapsulates writing strings and bytes to output streams.
 */
class Writer {
    public:
    /**
     * Writes a string to a given output stream.
     * @param out the output stream.
     * @param str the string to be written.
     */
    static void write(std::wostream& out, const std::wstring& str) {
        out.imbue(std::locale("en_US.UTF-8"));
        out.write(str.c_str(), str.length());
    }

    /**
     * Writes a byte string to a given output stream.
     * @param out the output stream.
     * @param bytes the byte string to be written.
     */
    static void write(std::ostream& out, const std::vector<uint8_t>& bytes) {
        out.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
    }

    /**
     * Writes a wide string it a given file.
     * @param filepath the file to be written.
     * @param header the .hmc header data.
     */
    static void writeString(const std::string& filepath, const std::wstring& str) {
        if (std::wofstream outFile(filepath); outFile.is_open()) {
            write(outFile, str);
            outFile.close();
            return;
        }
        throw std::runtime_error("Could not open output file");
    }
};

/**
 * Specialized class to write .hmc files
 */
class HmcWriter : public Writer {
    public:
        /**
         * Writes the .hmc body data as a sequence of raw bytes.
         * @param filepath the file to be written.
         * @param body the .hmc body data.
         */
        static void writeBody(const std::string& filepath, const std::vector<uint8_t> & bytes) {
        if (std::ofstream out(filepath, std::ios::app | std::ios::binary); out.is_open()) {
            write(out, bytes);
            out.close();
            return;
        }
        throw std::runtime_error("Could not open file");
    }
};

#endif //FILEWRITER_H
