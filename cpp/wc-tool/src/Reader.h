//
// Created by pbarbeira on 05-04-2025.
//

#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>

class Reader{
    static std::string _readStream(std::istream& stream){
        std::ostringstream buffer;
        buffer << stream.rdbuf();
        return buffer.str();
    }

    public:
        static std::string readFile(const std::string& fileName){
            std::ifstream file(fileName);
            std::string out;
            if(file.is_open()){
                out = _readStream(file);
                file.close();
            }
            return out;
        }

        static std::string readStdIn(){
            return _readStream(std::cin);
        }
};

#endif //READER_H
