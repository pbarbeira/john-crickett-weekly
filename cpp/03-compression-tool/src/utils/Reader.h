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
            std::ostringstream ss;
            ss << in.rdbuf();
            return ss.str();
        }
};

struct DecodeData {
    std::wstring header;
    std::vector<uint8_t> body;
};

/**
 * Specialized class to write .hmc files
 */
class HmcReader : public Reader {
    public:
        static std::vector<uint8_t> readBytes(const std::string& filepath) {
            if (std::ifstream inFile(filepath, std::ios::binary); inFile.is_open()) {
                return Reader::readBytes(inFile);
            }
            throw std::runtime_error("Could not open file " + filepath);
        }

        static std::string readAsString(const std::string& filepath) {
            if (std::ifstream inFile(filepath, std::ios::binary); inFile.is_open()) {
                return Reader::readAsString(inFile);
            }
            throw std::runtime_error("Could not open file " + filepath);
        }

        static std::unique_ptr<DecodeData> readHmc(const std::string& filepath) {
            if (std::ifstream inFile(filepath, std::ios::binary); inFile.is_open()) {
                std::wstring widePart;
                wchar_t wc;

                while (inFile.read(reinterpret_cast<char*>(&wc), sizeof(wchar_t))) {
                    if (wc == L'=') break;
                    widePart.push_back(wc);
                }
                std::streampos posAfterWide = inFile.tellg();
                inFile.seekg(posAfterWide);
                std::vector<uint8_t> bytePart;

                inFile.seekg(0, std::ios::end);
                std::streamsize totalSize = inFile.tellg();
                std::streamsize remaining = totalSize - posAfterWide;

                inFile.seekg(posAfterWide);
                bytePart.resize(remaining);
                inFile.read(reinterpret_cast<char*>(bytePart.data()), remaining);

                return std::make_unique<DecodeData>(widePart,bytePart);
            }
            throw std::runtime_error("Could not open file " + filepath);
        }
};

#endif //READER_H
