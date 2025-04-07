//
// Created by pbarbeira on 06-04-2025.
//

#ifndef READER_H
#define READER_H

#include <vector>
#include <fstream>

class Reader{
    static std::vector<std::string> _readStream(std::istream& stream) {
        std::vector<std::string> lines;
        std::string line;
        while(std::getline(stream, line)){
            lines.push_back(line);
        }
        return lines;
    }
public:
    static std::vector<std::string> readFile(const std::string& fileName){
        if(std::ifstream file(fileName); file.is_open()){
            return _readStream(file);
        }
        throw std::runtime_error("Could not open file");
    }

    static std::vector<std::string> read(const std::string& fileName){
        return _readStream(std::cin);
    }
};

#endif //READER_H
