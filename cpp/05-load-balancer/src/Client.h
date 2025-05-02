//
// Created by pbarbeira on 10-04-2025.
//

#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <utility>
#include "lib/Logger.h"
#include "Http.h"

#define MAXDATASIZE 1024

class Client{
    protected:
        std::string _host;
        std::string _port;

        Logger* _log;
        int _sockfd{};
        addrinfo* _p{};

        static void* _get_in_addr(struct sockaddr *sa)
        {
            if (sa->sa_family == AF_INET) {
                return &(reinterpret_cast<sockaddr_in *>(sa)->sin_addr);
            }

            return &(reinterpret_cast<sockaddr_in6 *>(sa)->sin6_addr);
        }

        void _init() {
            addrinfo hints{}, *servinfo;

            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;

            if (int rv; (rv = getaddrinfo(_host.c_str(), _port.c_str(), &hints, &servinfo)) != 0) {
                _log->error("Client: Could not get address info.");
                _log->error(gai_strerror(rv));
                exit(1);
            }

            // loop through all the results and connect to the first we can
            for(_p = servinfo; _p != nullptr; _p = _p->ai_next) {
                if ((_sockfd = socket(_p->ai_family, _p->ai_socktype, _p->ai_protocol)) == -1) {
                    _log->error("Client: Could not open socket.");
                    continue;
                }

                if (connect(_sockfd, _p->ai_addr, _p->ai_addrlen) == -1) {
                    close(_sockfd);
                    _log->error("Client: could not connect");
                    continue;
                }

                break;
            }

            freeaddrinfo(servinfo); // all done with this structure

            if (_p == nullptr) {
                _log->error("Client: Failed to connect");
                exit(2);
            }
        }
    public:
        Client(std::string host, std::string port, Logger* log = nullptr) :
            _host(std::move(host)), _port(std::move(port)), _log(log) {
            _p = new addrinfo{};
        }

        [[nodiscard]] std::string sendRequest() {
            _init();

            char buf[MAXDATASIZE];
            long numBytes;

            _log->info(std::format("Client: Connecting to {}:{}", _host, _port));

            if ((numBytes = recv(_sockfd, buf, MAXDATASIZE-1, 0)) == -1) {
                _log->error("Client: could not receive");
                exit(1);
            }

            buf[numBytes] = '\0';
            _log->info(std::format("Client: Received {} bytes", numBytes));
            close(_sockfd);
            return buf;
        }
};

class HttpClient : public Client{
    [[nodiscard]] std::unique_ptr<HttpResponse> _handleHttpResponse() const {
        constexpr size_t BUFFER_SIZE = 8192;
        char buffer[BUFFER_SIZE];
        std::string request_data;

        ssize_t bytes_received;
        while ((bytes_received = recv(_sockfd, buffer, sizeof(buffer), 0)) > 0) {
            request_data.append(buffer, bytes_received);
            if (request_data.find("\r\n\r\n") != std::string::npos)
                break;
        }

        _log->debug("Client: HTTP/1.1 200 OK");

        std::erase(request_data, '\r');
        const std::stringstream ss(request_data);

        return std::move(HttpResponse::createResponse(ss));
    }

    public:
        HttpClient(std::string host, std::string port, Logger* log = nullptr) :
            Client(std::move(host), std::move(port), log){}

        [[nodiscard]] std::unique_ptr<HttpResponse> sendRequest(const std::unique_ptr<HttpRequest> &request) {
            _init();

            _log->debug(std::format("Client: Connecting to {}:{}", _host, _port));

            const auto msg = request->buildMsg();
            if (send(_sockfd, msg.c_str(), msg.size(), 0) == -1) {
                _log->error("Client: could not send request");
            }

            auto response = _handleHttpResponse();

            close(_sockfd);
            return std::move(response);
        }
};

#endif //CLIENT_H
