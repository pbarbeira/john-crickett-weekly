//
// Created by pbarbeira on 05-04-2025.
//

#ifndef DECODER_H
#define DECODER_H

#include "HuffmanTree.h"
#include <algorithm>


class Decoder {
    static std::string _decodeBody(const std::string& bytes, HuffmanNode* node) {

    }

    public:
        static std::string decode(const std::string& bytes) {
            auto stopItr = std::ranges::find(bytes, '=');
            const std::string treeData(bytes.begin(), stopItr);

           const auto root = HuffmanTree::buildTree(treeData);

            //skip the '=1'
            const std::string bodyData(++++stopItr, bytes.end());
            // return _decodeBody(bodyData, root.get());
            return "";
        }

};

#endif //DECODER_H
