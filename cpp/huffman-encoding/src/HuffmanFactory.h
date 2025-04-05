//
// Created by pbarbeira on 05-04-2025.
//

#ifndef HUFFMANFACTORY_H
#define HUFFMANFACTORY_H

#include "HuffmanEngine.h"

/**
 * Factory class to create HuffmanEngines
 */
class HuffmanFactory{
    public:
    /**
     * Creates a HuffmanEncodeEngine or HuffmanDecodeEngine, to either encode
     * or decode a file, according to the passed parameter.
     * @param encode boolean representing whether we're encoding or decoding
     * @return unique pointer to the created instance
     */
    static std::unique_ptr<HuffmanEngine> build(const bool& encode){
            if(encode){
              return std::make_unique<HuffmanEncodeEngine>();
            }
            return std::make_unique<HuffmanDecodeEngine>();
        }
};

#endif //HUFFMANFACTORY_H
