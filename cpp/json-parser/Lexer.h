//
// Created by pbarbeira on 21-03-2025.
//

#ifndef LEXER_H
#define LEXER_H

#include "Token.h"
#include <regex>
#include <functional>
#include <memory>
#include <sstream>

class Lexer {
    static int _iPtr;
    static std::string _input;

    static std::unique_ptr<Token> _nextToken;

    static std::string _removeWhitespace(const std::string& s){
        std::stringstream ss;
        for(int i = 0; i < s.length(); i++){
            if(!isspace(s[i])){
                ss << s[i];
            }
        }
        return ss.str();
    }

    static std::unique_ptr<Token> _parseStringToken(const char& c){
        std::stringstream ss;
        ss << c;
        do{
            ss << _input[_iPtr];
        }while(_input[_iPtr++] != '\"');
        return std::make_unique<Token>(ss.str(), STRING);
    }

    static std::unique_ptr<Token> _parseNumberToken(const char& c){
        std::stringstream ss;
        ss << c;
        do{
            ss << _input[_iPtr++];
        }while(_input[_iPtr] == '.' || isdigit(_input[_iPtr]));
        return std::make_unique<Token>(ss.str(), NUMBER);
    }

    static std::unique_ptr<Token> _parseTrueToken(const char& c){
        std::stringstream ss;
        ss << c;
        do{
            ss << _input[_iPtr++];
        }while(ss.str() != "true" && _iPtr < _input.length());
        return std::make_unique<Token>(ss.str(), TRUE);
    }

    static std::unique_ptr<Token> _parseFalseToken(const char& c){
        std::stringstream ss;
        ss << c;
        do{
            ss << _input[_iPtr++];
        }while(ss.str() != "false" && _iPtr < _input.length());
        return std::make_unique<Token>(ss.str(), FALSE);
    }

    static std::unique_ptr<Token> _parseNullToken(const char& c){
        std::stringstream ss;
        ss << c;
        do{
            ss << _input[_iPtr++];
        }while(ss.str() != "null" && _iPtr < _input.length());
        return std::make_unique<Token>(ss.str(), NIL);
    }

public:
    Lexer() = delete;

    static void registerInput(const std::string& input) {
        _iPtr = 0;
        _input = _removeWhitespace(input);
    }

    static std::unique_ptr<Token> nextToken(){
        if (_nextToken != nullptr) {
            std::unique_ptr<Token> out = std::move(_nextToken);
            _nextToken = nullptr;
            return std::move(out);
        }
        switch(const char c = _input[_iPtr++]){
            case '{': return std::make_unique<Token>(std::string(1, c), LEFT_CURLY);
            case '}': return std::make_unique<Token>(std::string(1, c), RIGHT_CURLY);
            case '[': return std::make_unique<Token>(std::string(1, c), LEFT_SQUARE);
            case ']': return std::make_unique<Token>(std::string(1, c), RIGHT_SQUARE);
            case ':': return std::make_unique<Token>(std::string(1, c), COLON);
            case ',': return std::make_unique<Token>(std::string(1, c), COMMA);
            case 't': return _parseTrueToken(c);
            case 'f': return _parseFalseToken(c);
            case 'n': return _parseNullToken(c);
            case '\"': return _parseStringToken(c);
            default:
                if(isdigit(_input[_iPtr])){
                    return _parseNumberToken(c);
                }
                throw std::invalid_argument("Lexer error");
        }
    }

    [[nodiscard]] static bool hasNextToken() {
        if (_iPtr >= _input.length()) {
            _iPtr = 0;
            _input.clear();
        }
        return !_input.empty();
    }

    static Token* peekNextToken() {
        std::unique_ptr<Token> next = nextToken();
        _nextToken = std::move(next);
        return _nextToken.get();
    }
};

int Lexer::_iPtr = 0;
std::string Lexer::_input;
std::unique_ptr<Token> Lexer::_nextToken = nullptr;

#endif //LEXER_H
