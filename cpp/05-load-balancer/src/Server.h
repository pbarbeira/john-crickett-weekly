//
// Created by pbarbeira on 10-04-2025.
//

#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <functional>
#include <csignal>


#include "lib/Logger.h"

class Server{
    Logger* _logger;
    std::string _port;
    int _backlog;
    int _sockfd;

    void _init() {
        addrinfo hints{}, *servinfo, *p;
        constexpr int yes=1;

        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE; // use my IP


        if (int rv; (rv = getaddrinfo(nullptr, _port.c_str(), &hints, &servinfo)) != 0) {
            _logger->log(ERROR, "Server: getaddrinfo: %s");
            _logger->log(ERROR, gai_strerror(rv));
            exit(1);
        }

        // listen on sock_fd, new connection on new_fd
        for(p = servinfo; p != nullptr; p = p->ai_next) {
            if ((_sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
                _logger->log(ERROR, "Server: could not find socket\n");
                continue;
            }
            if (setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,sizeof(int)) == -1) {
                _logger->log(ERROR, "Server: could not set sockoptbind\n");
                exit(1);
            }
            if (bind(_sockfd, p->ai_addr, p->ai_addrlen) == -1) {
                close(_sockfd);
                _logger->log(ERROR, "Server: failed to bind\n");
                continue;
            }
            break;
        }

        freeaddrinfo(servinfo); // all done with this structure

        if (p == nullptr)  {
            _logger->log(ERROR, "Server: failed to bind\n");
            exit(1);
        }

        if (listen(_sockfd, _backlog) == -1) {
            _logger->log(ERROR, "Server: Socket failed to listen \n");
            exit(1);
        }
    }
public:
    Server() = delete;
    explicit Server(Logger* logger, const std::string& port, int backlog):
        _logger(logger), _port(port), _backlog(backlog) {
        _init();
    }

    void run(std::function<std::string(Logger* logger, sockaddr_storage&)> serverStub) {
        _logger->log(DEBUG, std::format("Listening on localhost:{}", _port));
        while(1) {
            sockaddr_storage their_addr{}; // connector's address information

            socklen_t sin_size = sizeof their_addr;
            const int new_fd = accept(_sockfd, reinterpret_cast<sockaddr *>(&their_addr), &sin_size);
            if (new_fd == -1) {
                _logger->log(ERROR, std::format("Could not accept file descriptor [{}]", _sockfd));
                continue;
            }

            std::string response = serverStub(_logger, their_addr);
            if (send(new_fd, response.c_str(), 13, 0) == -1) {
                _logger->log(ERROR, "Server: could not send response");
            }
            close(new_fd);
        }
    }
};

#endif //SERVER_H
