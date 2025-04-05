//
// Created by pbarbeira on 05-04-2025.
//

#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <iostream>
#include <fstream>

#include "ByteConverter.h"

class Writer {
    public:
        static void write(std::ostream& out, const std::string& str) {
            out << str;
        }

        static void write(std::ostream& out, const std::vector<uint8_t>& bytes) {
            out.write(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        }
};

class FileWriter : public Writer {
    public:
        static void writeHeader(const std::string& filepath, const std::string& header) {
            if (std::ofstream out(filepath); out.is_open()) {
                write(out, header);
                out.close();
                return;
            }
            throw std::runtime_error("Could not open file");
        }

        static void writeBody(const std::string& filepath, const std::string& body) {
            const std::vector<uint8_t> bytes = ByteConverter::toBytes(body);

            if (std::ofstream out(filepath, std::ios::app | std::ios::binary); out.is_open()) {
                write(out, bytes);
                out.close();
                return;
            }
            throw std::runtime_error("Could not open file");
        }
};

class ConsoleWriter : public Writer {
    public:
        static void write(const std::string& str) {
            Writer::write(std::cout, str);
        }
};

#endif //FILEWRITER_H
