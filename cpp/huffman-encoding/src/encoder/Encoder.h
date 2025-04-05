//
// Created by pbarbeira on 05-04-2025.
//

#ifndef ENCODER_H
#define ENCODER_H

#include <unordered_map>
#include <string>

#include "HuffmanTree.h"

/**
 * Encapsulates the core Huffman Encoding logic. Uses a map containing
 * the prefix codes for each character to encode strings.
 */
class Encoder {
    //Map with the characters and their prefix codes.
    std::unordered_map<char, std::string> _prefixTable;

    /**
     * Helper function to DFS travel the HuffmanTree and build the prefix table.
     * @param node the node being encoded.
     * @param encoding the current encode string.
     */
    void _encodeNode(const HuffmanNode* node, const std::string& encoding){
        if(node->isLeaf()){
            _prefixTable[node->letter] = encoding;
            return;
        }
        _encodeNode(node->left.get(), encoding + "0");
        _encodeNode(node->right.get(), encoding + "1");
    }

    public:
    /**
     * Base constructor. Receives a pointer to a Huffman Tree's root and
     * uses it to build the prefix table.
     * @param root the root of the HuffmanTree.
     */
    explicit Encoder(HuffmanNode* root){
            _encodeNode(root, "");
        }

    /**
     * Returns the prefix table
     * @return the prefix table.
     */
    std::unordered_map<char, std::string> getPrefixTable() const {
            return _prefixTable;
        }

    /**
     * Encodes a given input string using Huffman Encoding by inspecting
     * the prefix table and appending the corresponding prefix for each
     * character of the string.
     * @param input the text to be encoded.
     * @return the encoded text.
     */
    std::string encode(const std::string &input) const {
            std::stringstream ss;
            for (int i = 0; i < input.size(); i++) {
                if (char c = input[i]; _prefixTable.contains(c)) {
                    ss << _prefixTable.at(c);
                    continue;
                }
                throw std::runtime_error("Invalid character");
            }
            return ss.str();
        }
};

#endif //ENCODER_H
