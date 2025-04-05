//
// Created by pbarbeira on 05-04-2025.
//

#ifndef READER_H
#define READER_H

#include<fstream>
#include <vector>

/**
 * Base reader class. Encapsulates reading strings and bytes to from input streams.
 */
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

        static std::string readAsString(std::istream& in) {
            std::stringstream ss;
            std::string buffer;
            while (std::getline(in, buffer)) {
                ss << buffer << '\n';
                buffer.clear();
            }
            return ss.str();
        }
};

/**
 * Specialized class to write .hmc files
 */
class HmcReader : public Reader {
    public:
        static std::vector<uint8_t> readBytes(const std::string& filepath) {
            std::ifstream inFile(filepath, std::ios::binary);
            std::vector<uint8_t> ret;
            if (inFile.is_open()) {
                ret = Reader::readBytes(inFile);
                inFile.close();
            }

            return ret;
        }

        static std::string readAsString(const std::string& filepath) {
            std::ifstream inFile(filepath);
            std::string ret;
            if (inFile.is_open()) {
                ret = Reader::readAsString(inFile);
                inFile.close();
            }
            return ret;
        }
};

#endif //READER_H
