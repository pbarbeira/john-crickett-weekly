//
// Created by pbarbeira on 23-03-2025.
//

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <memory>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <queue>

struct HuffmanNode{
    char letter{};
    int freq{};
    std::unique_ptr<HuffmanNode> left;
    std::unique_ptr<HuffmanNode> right;
};

class HuffmanTree{
    static std::vector<std::unique_ptr<HuffmanNode>> _buildNodes(const std::unordered_map<char, int>& frequencies){
        std::vector<std::unique_ptr<HuffmanNode>> nodes;
        std::ranges::for_each(frequencies, [&](const auto& pair){
            auto node = std::make_unique<HuffmanNode>();
            node->letter = pair.first;
            node->freq = pair.second;
            nodes.emplace_back(std::move(node));
        });
        return nodes;
    }

    static bool _heapCmp(const std::unique_ptr<HuffmanNode>& lhs, const std::unique_ptr<HuffmanNode>& rhs) {
        return lhs->freq > rhs->freq;
    }

    static std::unique_ptr<HuffmanNode> _getHeapFront(std::vector<std::unique_ptr<HuffmanNode>>& nodes) {
        auto out = std::move(nodes.front());
        std::ranges::pop_heap(nodes, _heapCmp);
        nodes.pop_back();
        return std::move(out);
    }

    public:
        static std::unique_ptr<HuffmanNode> buildTree(const std::unordered_map<char, int>& frequencies){
            auto nodes = _buildNodes(frequencies);
            std::ranges::make_heap(nodes, _heapCmp);
            while (nodes.size() != 1) {
                auto newNode = std::make_unique<HuffmanNode>();
                newNode->left = _getHeapFront(nodes);
                newNode->right = _getHeapFront(nodes);
                newNode->freq = newNode->left->freq + newNode->right->freq;
                nodes.emplace_back(std::move(newNode));
                std::ranges::push_heap(nodes, _heapCmp);
            }
            return std::move(nodes.front());
        }

        static std::vector<int> encode(HuffmanNode* node) {
            std::queue<HuffmanNode*> queue;
            queue.push(node);
            std::vector<int> out;
            while (!queue.empty()) {
                auto tmpNode = queue.front();
                queue.pop();
                out.push_back(tmpNode->freq);
                if (tmpNode->left != nullptr) {
                    queue.push(tmpNode->left.get());
                }
                if (tmpNode->right != nullptr) {
                    queue.push(tmpNode->right.get());
                }
            }
            return out;
        }

};

#endif //HUFFMANTREE_H
