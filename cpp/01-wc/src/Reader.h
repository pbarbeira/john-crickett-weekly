//
// Created by pbarbeira on 05-04-2025.
//

#ifndef READER_H
#define READER_H

#include <iostream>
#include <fstream>

/**
 * Reader class. Used to handle input.
 */
class Reader{
    /**
     * Reads an input stream's content as a string.
     * @param stream the input stream.
     * @return the content of the input stream.
     */
    static std::string _readStream(std::istream& stream){
        std::ostringstream buffer;
        buffer << stream.rdbuf();
        return buffer.str();
    }

    public:
        /**
         * Reads contents from a file as a string by calling the
         * private method _readStream on the open file stream.
         * @param fileName the path to the file.
         * @return the contents of the file, as string.
         */
        static std::string readFile(const std::string& fileName){
            std::ifstream file(fileName);
            std::string out;
            if(file.is_open()){
                out = _readStream(file);
                file.close();
            }
            return out;
        }

        /**
         * Reads contents from stdin as a string by calling the
         * private method _readStream on std::cin.
         * @return
         */
        static std::string readStdIn(){
            return _readStream(std::cin);
        }
};

#endif //READER_H
