//
// Created by pbarbeira on 05-04-2025.
//

#ifndef DECODER_H
#define DECODER_H

#include "HuffmanTree.h"
#include <algorithm>

/**
 * Encapsulates the core Huffman Decoding logic. Creates the Huffman Tree from
 * the header and uses it to decode the body.
 */
class Decoder {
        /**
         * Decodes the body portion of a .hmc file by traversing the bitstream and
         * retracing the routes of the Huffman Tree back to each character of the
         * original string.
         * @param bitstream the string representation of the bitstream to be decoded.
         * @param node the root of the Huffman Tree used to encode the bitstream.
         * @return the original decoded string.
         */
        static std::wstring _decodeBody(const std::string& bitstream, HuffmanNode* node) {
        std::wstringstream ss;
        HuffmanNode* tmpNode = node;;
        for (char c : bitstream) {
            if (c == '0') {
                tmpNode = tmpNode->left.get();
            }else if (c == '1') {
                tmpNode = tmpNode->right.get();
            }
            if (tmpNode->isLeaf()) {
                ss << tmpNode->letter;
                tmpNode = node;
            }
        }
        return ss.str();
    }

    public:
        /**
         * Decodes a given input string using Huffman Encoding by inspecting
         * building the Huffman Tree from the file's header information and
         * using it to decode the body of the file, which contains the original
         * data.
         * @param data the data to be decoded.
         * @return the decoded data.
         */
        static std::wstring decode(const std::string& data) {
            auto stopItr = std::ranges::find(data, '=');
            const std::string treeData(data.begin(), stopItr);

           const auto root = HuffmanTree::buildTree(treeData);

            //skip the '=1'
            const std::string bodyData(++++stopItr, data.end());
            return _decodeBody(bodyData, root.get());
        }

};

#endif //DECODER_H
