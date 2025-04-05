//
// Created by pbarbeira on 23-03-2025.
//

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <memory>
#include <algorithm>
#include <format>
#include <vector>
#include <unordered_map>
#include <queue>

#include "StringUtils.h"

using ull = unsigned long long;

inline int nextId = 1;

struct HuffmanNode{
    int id;
    char letter{};
    int freq{};
    std::unique_ptr<HuffmanNode> left;
    std::unique_ptr<HuffmanNode> right;

    HuffmanNode():
        id(nextId++){}

    [[nodiscard]] bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

struct NodeData {
    int id;
    int leftId;
    int rightId;
    char value;

    explicit NodeData(const int& id):
        id(id), leftId(-1), rightId(-1), value('\0'){}

    bool isLeaf() const{
        return value != '\0' && leftId == -1 && rightId == -1;
    }

};

class HuffmanTree{
    static std::vector<std::unique_ptr<HuffmanNode>> _buildNodes(const std::unordered_map<char, ull>& frequencies){
        std::vector<std::unique_ptr<HuffmanNode>> nodes;
        std::ranges::for_each(frequencies, [&](const auto& pair){
            auto node = std::make_unique<HuffmanNode>();
            node->letter = pair.first;
            node->freq = pair.second;
            nodes.emplace_back(std::move(node));
        });
        return nodes;
    }

    static std::unordered_map<int, std::unique_ptr<NodeData>> _buildNodes(const std::string& data){
        std::unordered_map<int, std::unique_ptr<NodeData>> nodes;
        auto nodeTokens = StringUtils::split(data, '|');
        for (const auto& token : nodeTokens) {
            auto valueTokens = StringUtils::split(token, ',');
            int id = std::stoi(valueTokens[0]);
            auto nodeData = std::make_unique<NodeData>(id);
            if (valueTokens.size() == 2) {
                nodeData->value = valueTokens[1][0];
            }else {
                nodeData->leftId = std::stoi(valueTokens[1]);
                nodeData->rightId = std::stoi(valueTokens[2]);
            }
            nodes.emplace(id, std::move(nodeData));
        }
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

    static int _getRootId(const std::string& str) {
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == ',') {
                std::string idStr = str.substr(0, i);
                return std::stoi(idStr);
            }
        }
        return -1;
    }

    public:
        static std::unique_ptr<HuffmanNode> buildTree(const std::unordered_map<char, ull>& frequencies){
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

        static std::unique_ptr<HuffmanNode> buildTree(const std::string& str){
            auto nodes = _buildNodes(str);
            auto rootId = _getRootId(str);

            std::queue<int> queue;
            queue.push(rootId);
            while (!queue.empty()) {
                                
            }
        }

        static std::vector<int> encodeFrequency(HuffmanNode* node) {
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

        static std::string encodeHeader(HuffmanNode* node) {
            std::stringstream ss;
            std::queue<HuffmanNode*> queue;
            queue.push(node);
            while (!queue.empty()) {
                auto tmpNode = queue.front();
                queue.pop();

                if (tmpNode->isLeaf()) {
                    ss << std::format("{},{}|", tmpNode->id, tmpNode->letter);
                }else {
                    auto left = tmpNode->left.get();
                    auto right = tmpNode->right.get();

                    ss << std::format("{},{},{}|", tmpNode->id, left->id, right->id);

                    queue.push(left);
                    queue.push(right);
                }
            }
            ss << "=";
            return ss.str();
        }

        static void resetId() {
            nextId = 1;
        }

};

#endif //HUFFMANTREE_H
