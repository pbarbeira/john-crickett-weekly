//
// Created by pbarbeira on 10-04-2025.
//

#ifndef REQUEST_H
#define REQUEST_H

#include <memory>
#include <unordered_map>
#include <sstream>

#include "lib/StringUtils.h"

using VectorItStr = std::vector<std::string>::const_iterator;

struct _HttpBase {
    std::unordered_map<std::string, std::string> headers{};
    std::string body;

    void buildMsg(std::stringstream& ss, const std::string& lineBreak = "\r\n") const {
        for (const auto& [headerName, headerValue] : headers) {
            ss << headerName << ": " << headerValue << lineBreak;
        }
        ss << lineBreak << body << "\r\n";
    }

        void _parseHeaders(VectorItStr begin, const VectorItStr end) {
        while (begin != end) {
            if (*begin != "") {
                auto tokens = StringUtils::split(*begin, ' ');
                auto key = tokens[0].substr(0, tokens[0].length() - 1);
                const auto value = tokens[1];
                headers[key] = value;
            }
            ++begin;
        }
    }
};

enum class HttpMethod {
    GET,
};

struct HttpRequest : _HttpBase {
    HttpMethod method;
    std::string path;
    std::string host;

    std::string _method() {
        switch (method) {
            case HttpMethod::GET: return "GET";
            default:
                return "ERROR";
        }
    }

    static HttpMethod _method(const std::string &method){
      return HttpMethod::GET;
    }

    std::string buildMsg(const std::string& lineBreak = "\r\n") {
        std::stringstream ss;
        ss << _method() << " " << path<< " HTTP/1.1 " << lineBreak
            << "Host: " << host << lineBreak;
        _HttpBase::buildMsg(ss, lineBreak);

        return ss.str();
    }

    static std::unique_ptr<HttpRequest> createRequest(const std::stringstream& ss) {
        auto out = std::make_unique<HttpRequest>();
        const auto lines = StringUtils::split(ss.str(), '\n');

        out->_parseMethod(lines[0]);
        out->_parseHost(lines[1]);
        out->_parseHeaders(lines.begin() + 2, lines.end());

        return std::move(out);
    }
private:
    void _parseMethod(const std::string& line) {
        auto tokens = StringUtils::split(line, ' ');
        method = _method(tokens[0]);
        path = tokens[1];
        if (tokens[2] != "HTTP/1.1") {
            std::cout << "HTTP/1.1 required\n";
        }
    }

    void _parseHost(const std::string& line) {
        const auto tokens = StringUtils::split(line, ' ');
        host = tokens[1];
    }
};

struct HttpResponse : _HttpBase {
    int status;
    std::string message;

    static std::unique_ptr<HttpResponse> createResponse(const std::stringstream& ss) {
        auto out = std::make_unique<HttpResponse>();
        auto lines = StringUtils::split(ss.str(), '\n');
        out->_parseStatus(lines[0]);
        out->_parseHeaders(lines.begin() + 1, lines.end() - 1);
        out->_parseBody(lines.end()-1);
        return std::move(out);
    }

    std::string buildMsg() const {
        switch (status) {
            case 200: return ok();
            default: return "";
        }
    }

    std::string ok() const {
        std::stringstream ss;
        ss << "HTTP/1.1 " << status << " OK\r\n";
        if (!message.empty()) {
            ss << message << "\r\n";
        }
        _HttpBase::buildMsg(ss);

        return ss.str();
    }
    private:
        void _parseStatus(const std::string& line) {
            const auto tokens = StringUtils::split(line, ' ');
            status = std::stoi(tokens[1]);
        }

        void _parseBody(const VectorItStr lineItr) {
            body = *lineItr;
        }

};

#endif //REQUEST_H
