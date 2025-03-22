//
// Created by pbarbeira on 21-03-2025.
//

#ifndef JSONNODE_H
#define JSONNODE_H

#include <string>
#include <memory>
#include <vector>
#include <algorithm>

enum NodeType {
    VALUE, OBJECT, LIST, ITEM
};

class JsonNode{
        std::vector<std::unique_ptr<JsonNode>> _children;
        std::string _value;
        std::string _key;
        NodeType _type;

        std::vector<std::unique_ptr<JsonNode>>::iterator _findKey(const std::string& key){
            return std::find_if(_children.begin(), _children.end(),
                [key](const std::unique_ptr<JsonNode>& child){
                    return child->_key == key;
                }
            );
        }

        void _printIndent(int level) {
            for (int i = 0; i < level; i++) {
                std::cout << '\t';
            }
        }

        void _printKeyValue(int indent) {
            std::cout << _value << '\n';
        }

        void _printObject(int indent) {
            std::cout  << "{\n";
            for (int i = 0 ; i < _children.size(); i++) {
                auto child = _children[i].get();
                _printIndent(indent + 1);
                std::cout << child->_key << ": ";
                child->_printHelper(indent + 1);
            }
            _printIndent(indent);
            std::cout << "}\n";
        }

        void _printList(int indent) {
            std::cout  << "[\n";
            for (int i = 0 ; i < _children.size(); i++) {
                _printIndent(indent + 1);
                _children[i].get()->_printHelper(indent + 1);
            }
            _printIndent(indent);
            std::cout << "]\n";
        }

        void  _printHelper(int indent) {
            switch (_type) {
                case VALUE: return _printKeyValue(indent);
                case OBJECT: return _printObject(indent);
                case LIST: return _printList(indent);
            }
        }
    public:
        JsonNode(const NodeType& type):
            _type(type){}

        JsonNode(const std::string& value, const NodeType& type):
            _value(value), _type(type){}

        bool addChild(const std::string& key, std::unique_ptr<JsonNode> child){
            if (!key.empty()) {
                if(_findKey(key) != _children.end()){
                    return false;
                }
                child->_key = key;
            }
            _children.emplace_back(std::move(child));
            return true;
        }

        JsonNode* getChild(const std::string& key){
            auto found = _findKey(key);
            if(found != _children.end()){
                return found->get();
            }
            return nullptr;
        }

        void print() {
            _printHelper(0);
        }
};

#endif //JSONNODE_H
