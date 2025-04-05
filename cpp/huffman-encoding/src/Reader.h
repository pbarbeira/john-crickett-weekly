//
// Created by pbarbeira on 05-04-2025.
//

#ifndef READER_H
#define READER_H

#include<fstream>
#include <vector>
#include <iostream>

#include "../cmake-build-debug/_deps/googletest-src/googlemock/include/gmock/gmock-actions.h"

class Reader{
    public:
        static std::vector<u_int8_t> readBytes(std::istream& in){
            std::vector<uint8_t> buffer;

            in.seekg(0, std::ios::end);
            std::streamsize size = in.tellg();
            in.seekg(0, std::ios::beg);

            buffer.resize(size);
            in.read(reinterpret_cast<char*>(buffer.data()), size);
            return buffer;
        }
};

class FileReader : public Reader {
    public:
        static std::vector<uint8_t> readBytes(const std::string& filepath) {
            std::ifstream inFile(filepath, std::ios::binary);

            auto ret = Reader::readBytes(inFile);
            inFile.close();

            return ret;
        }
};

#endif //READER_H
