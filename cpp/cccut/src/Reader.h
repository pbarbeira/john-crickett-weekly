//
// Created by pbarbeira on 06-04-2025.
//

#ifndef READER_H
#define READER_H

#include <vector>
#include <fstream>

class Reader{
public:
    static std::vector<std::string> readFile(const std::string& fileName){
        if(std::ifstream file(fileName); file.is_open()){
            std::vector<std::string> lines;
            std::string line;
            while(std::getline(file, line)){
              lines.push_back(line);
            }
            return lines;
        }
        throw std::runtime_error("Could not open file");
    }
};

#endif //READER_H
