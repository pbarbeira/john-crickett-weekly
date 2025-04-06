//
// Created by pbarbeira on 23-03-2025.
//

#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <memory>
#include <algorithm>
#include <format>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <queue>

#include "../utils/StringUtils.h"

using ull = unsigned long long;

//Automatically sets the id of the next node.
inline int nextId = 1;

/**
 * Auxiliary data structure to keep the Node-related information.
 */
struct HuffmanNode{
    //The id of the Node.
    int id;

    //The letter of the node, if it is a Leaf
    wchar_t letter{};
    //The frequency of the node, if it is a Leaf
    int freq{};

    //Pointer to the left node, if it is a Node
    std::unique_ptr<HuffmanNode> left;
    //Pointer to the right node, if it is a Node
    std::unique_ptr<HuffmanNode> right;

    /**
     * Default HuffmanNode constructor. Automatically sets the Node's ID.
     */
    HuffmanNode():
        id(nextId++){}

    explicit HuffmanNode(const int id):
        id(id){}

    /**
     * Checks if this HuffmanNode is a Leaf.
     * @return true if the Node is a Leaf, false otherwise.
     */
    [[nodiscard]] bool isLeaf() const {
        return left == nullptr && right == nullptr;
    }
};

/**
 * Auxiliary data structure to keep NodeData as references between conversions.
 */
struct NodeData {
    //The Node's ID
    int id;
    //The ID of the node's left Node
    int leftId;
    //The ID of the node's right Node
    int rightId;
    //The Node's value.
    char value;

    /**
     * Default NodeData constructor.
     * @param id the id of the Node.
     */
    explicit NodeData(const int& id):
        id(id), leftId(-1), rightId(-1), value('\0'){}

    /**
     * Checks if this NodeData is a Leaf.
     * @return true if the Node is a Leaf, false otherwise.
     */
    bool isLeaf() const{
        return leftId == -1 && rightId == -1;
    }

};

/**
 * Static class that encapsulates most algorithmic behavir and operations that
 * require the Huffman Tree.
 */
class HuffmanTree{
    /**
     * Builds a list of the existing HuffmanNodes from the character frequency
     * table. Used to build the tree using the maxHeap algorithm.
     * @param frequencies the character frequency table.
     * @return the list of build HuffmanNodes.
     */
    static std::vector<std::unique_ptr<HuffmanNode>> _buildNodes(const std::unordered_map<wchar_t, ull>& frequencies){
        std::vector<std::unique_ptr<HuffmanNode>> nodes;
        std::ranges::for_each(frequencies, [&](const auto& pair){
            auto node = std::make_unique<HuffmanNode>();
            node->letter = pair.first;
            node->freq = pair.second;
            nodes.emplace_back(std::move(node));
        });
        return nodes;
    }

    /**
     * Builds a map containing the tree's nodes' metadata from the .hmc header
     * string data. Used to build the HuffmanTree when decoding.
     * @param data the .hmc header data.
     * @return the tree's metadata.
     */
    static std::unordered_map<int, std::unique_ptr<NodeData>> _buildNodes(const std::string& data){
        std::unordered_map<int, std::unique_ptr<NodeData>> nodes;
        auto nodeTokens = StringUtils::split(data, '|');
        for (int i = 0; i < nodeTokens.size(); i++) {
            auto token = nodeTokens[i];
            if (token == "=") break;
            auto valueTokens = StringUtils::split(token, ',');
            int id = std::stoi(valueTokens[0]);
            auto nodeData = std::make_unique<NodeData>(id);
            if (valueTokens.size() == 2) {
                std::string value = valueTokens[1];
                char ch = value[0];
                if (value == "\\c") ch = ',';
                if (value == "\\n") ch = '\n';
                if (value == "\\s") ch = ' ';
                if (value == "\\t") ch = '\t';
                if (value == "\\r") ch = '\r';

                nodeData->value = ch;
            }else {
                nodeData->leftId = std::stoi(valueTokens[1]);
                nodeData->rightId = std::stoi(valueTokens[2]);
            }
            nodes.emplace(id, std::move(nodeData));
        }
        return nodes;
    }

    /**
     * Heap compare function used in the maxHeap used to build the HuffmanTree
     * from the character frequency table.
     * @param lhs the left hand side HuffmanNode.
     * @param rhs the right hand side HuffmanNode.
     * @return the largest HuffmanNode.
     */
    static bool _heapCmp(const std::unique_ptr<HuffmanNode>& lhs, const std::unique_ptr<HuffmanNode>& rhs) {
        return lhs->freq > rhs->freq;
    }

    /**
     * Wraps heap access behavior to easily extract the first element.
     * @param nodes the heap.
     * @return the element at the front of the heap.
     */
    static std::unique_ptr<HuffmanNode> _getHeapFront(std::vector<std::unique_ptr<HuffmanNode>>& nodes) {
        auto out = std::move(nodes.front());
        std::ranges::pop_heap(nodes, _heapCmp);
        nodes.pop_back();
        return std::move(out);
    }

    /**
     * Extract's the tree's root node's id from the .hmc header string data.
     * @param str the .hmc header data.
     * @return the root node's id.
     */
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
    /**
     * Builds an HuffmanTree from the character frequency table.
     * @param frequencies the character frequency table.
     * @return unique pointer to the built HuffmanTree's root.
     */
    static std::unique_ptr<HuffmanNode> buildTree(const std::unordered_map<wchar_t, ull>& frequencies){
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

    /**
     * Builds and HuffmanTree from the .hmc header information.
     * @param str the .hmc header information.
     * @return unique pointer to the built HuffmanTree's root.
     */
    static std::unique_ptr<HuffmanNode> buildTree(const std::string& str){
        const auto nodes = std::move(_buildNodes(str));

        const auto rootId = _getRootId(str);
        auto root = std::make_unique<HuffmanNode>(rootId);

        std::queue<HuffmanNode*> queue;
        queue.push(root.get());
        while (!queue.empty()) {
            const auto node = queue.front();
            queue.pop();
            if (!nodes.contains(node->id)) {
                std::cout << node->id << std::endl;
            }
            const auto data = nodes.at(node->id).get();
            if (data->isLeaf()) {

                node->letter = data->value;
                continue;
            }

            auto left = std::make_unique<HuffmanNode>(data->leftId);
            auto right = std::make_unique<HuffmanNode>(data->rightId);

            queue.push(left.get());
            queue.push(right.get());

            node->left = std::move(left);
            node->right = std::move(right);
        }

        return std::move(root);
    }

    /**
     * Encodes the tree as alist of character frequencies. Used for testing purposes.
     * @param node the root of the tree.
     * @return the list with the tree's frequencies.
     */
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

    /**
     * Stores the tree's information according the .hmc header specification.
     * @param node the root of the tree.
     * @return the file header according to the .hmc specification.
     */
    static std::wstring encodeHeader(HuffmanNode* node) {
            std::wstring out = L"";
            std::queue<HuffmanNode*> queue;
            queue.push(node);
            while (!queue.empty()) {
                auto tmpNode = queue.front();
                queue.pop();

                if (tmpNode->isLeaf()) {
                    std::wstring letter(1, tmpNode->letter);
                    if (letter == L",") {
                        letter = L"\\c";
                    }
                    if (letter == L"\n") {
                        letter = L"\\n";
                    }
                    if (letter == L" ") {
                        letter = L"\\s";
                    }
                    if (letter == L"\t") {
                        letter = L"\\t";
                    }
                    if (letter == L"\r") {
                        letter = L"\\r";
                    }
                    out += std::format(L"{},{}|", tmpNode->id, letter);
                }else {
                    auto left = tmpNode->left.get();
                    auto right = tmpNode->right.get();

                    out += std::format(L"{},{},{}|", tmpNode->id, left->id, right->id);

                    queue.push(left);
                    queue.push(right);
                }
            }
            out += L"=";
            return out;
        }

    /**
     * Used to reset the global ID counter. Used for testing purposes.
     */
    static void resetId() {
            nextId = 1;
        }

};

#endif //HUFFMANTREE_H
