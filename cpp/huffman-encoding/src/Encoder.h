//
// Created by pbarbeira on 05-04-2025.
//

#ifndef ENCODER_H
#define ENCODER_H

#include <unordered_map>
#include <string>

#include "HuffmanTree.h"

class Encoder {
    std::unordered_map<char, std::string> _map;

    void _encodeNode(const HuffmanNode* node, const std::string& encoding){
        if(node->isLeaf()){
            _map[node->letter] = encoding;
            return;
        }
        _encodeNode(node->left.get(), encoding + "0");
        _encodeNode(node->right.get(), encoding + "1");
    }

    public:
        explicit Encoder(HuffmanNode* root){
            _encodeNode(root, "");
        }

        std::unordered_map<char, std::string> getMap() const {
            return _map;
        }

        std::string encode(const std::string &input) const {
            std::stringstream ss;
            for (int i = 0; i < input.size(); i++) {
                if (char c = input[i]; _map.contains(c)) {
                    ss << _map.at(c);
                    continue;
                }
                throw std::runtime_error("Invalid character");
            }
            return ss.str();
        }
};

#endif //ENCODER_H
