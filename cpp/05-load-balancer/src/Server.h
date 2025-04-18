//
// Created by pbarbeira on 10-04-2025.
//

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <utility>

#include "lib/Logger.h"
#include "Http.h"

class Server{
    protected:
        Logger* _log;
        std::string _port;
        int _backlog;
        int _sockfd{};
    private:
        void _init() {
            addrinfo hints{}, *servinfo, *p;
            constexpr int yes=1;

            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_flags = AI_PASSIVE; // use my IP


            if (int rv; (rv = getaddrinfo(nullptr, _port.c_str(), &hints, &servinfo)) != 0) {
                _log->log(ERROR, "Server: getaddrinfo: %s");
                _log->log(ERROR, gai_strerror(rv));
                exit(1);
            }

            // listen on sock_fd, new connection on new_fd
            for(p = servinfo; p != nullptr; p = p->ai_next) {
                if ((_sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
                    _log->log(ERROR, "Server: could not find socket\n");
                    continue;
                }
                if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
                    _log->log(ERROR, "Server: could not set sockoptbind\n");
                    exit(1);
                }
                if (bind(_sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                    close(_sockfd);
                    _log->log(ERROR, "Server: failed to bind\n");
                    continue;
                }
                break;
            }

            freeaddrinfo(servinfo); // all done with this structure

            if (p == nullptr)  {
                _log->log(ERROR, "Server: failed to bind\n");
                exit(1);
            }

            if (listen(_sockfd, _backlog) == -1) {
                _log->log(ERROR, "Server: Socket failed to listen \n");
                exit(1);
            }
        }
    public:
        Server() = delete;

    template<typename Handle>
    void run(Handle serverStub) {
        _log->log(DEBUG, std::format("Listening on localhost:{}", _port));
        while(1) {
            sockaddr_storage their_addr{}; // connector's address information

            socklen_t sin_size = sizeof their_addr;
            const int new_fd = accept(_sockfd, reinterpret_cast<sockaddr *>(&their_addr), &sin_size);
            if (new_fd == -1) {
                _log->log(ERROR, std::format("Could not accept file descriptor [{}]", _sockfd));
                continue;
            }

            serverStub(_log, new_fd, their_addr);
            close(new_fd);
        }
    }

    explicit Server(std::string  port, const int backlog, Logger* logger = nullptr):
        _log(logger), _port(std::move(port)), _backlog(backlog) {
        _init();
    }
};

class HttpServer : public Server{
    [[nodiscard]] std::unique_ptr<HttpRequest> _handleHttpRequest(int sockfd) const {
        constexpr size_t BUFFER_SIZE = 8192;
        char buffer[BUFFER_SIZE];
        std::string request_data;

        ssize_t bytes_received;
        while ((bytes_received = recv(sockfd, buffer, sizeof(buffer), 0)) > 0) {
            request_data.append(buffer, bytes_received);
            if (request_data.find("\r\n\r\n") != std::string::npos)
                break;
        }

        _log->debug("Server: HTTP/1.1 200 OK");

        std::erase(request_data, '\r');
        const std::stringstream ss(request_data);

        return std::move(HttpRequest::createRequest(ss));
    }

    public:
        explicit HttpServer(const std::string& port, int backlog, Logger* logger = nullptr):
            Server(port, backlog, logger) {}

        void run(const std::function<const std::unique_ptr<HttpResponse>(std::unique_ptr<HttpRequest>)>& handle) {
            _log->log(DEBUG, std::format("Listening on localhost:{}", _port));
            while(1) {
                sockaddr_storage their_addr{}; // connector's address information

                socklen_t sin_size = sizeof their_addr;
                const int new_fd = accept(_sockfd, reinterpret_cast<sockaddr *>(&their_addr), &sin_size);
                if (new_fd == -1) {
                    _log->log(ERROR, std::format("Could not accept file descriptor [{}]", _sockfd));
                    continue;
                }

                auto request = std::move(_handleHttpRequest(new_fd));

                const auto response = handle(std::move(request));
                const std::string msg = response->buildMsg();

                if (send(new_fd, msg.c_str(), msg.size(), 0) == -1) {
                    _log->log(ERROR, "Server: could not send response");
                }
                close(new_fd);
            }
        }
};

#endif //SERVER_H
