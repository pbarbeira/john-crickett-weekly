#include <memory>
#include <arpa/inet.h>

#include "../Server.h"
#include "../lib/Logger.h"

void* get_in_addr(sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(reinterpret_cast<sockaddr_in *>(sa)->sin_addr);
    }
    return &(reinterpret_cast<sockaddr_in6 *>(sa)->sin6_addr);
}

void serverStub(Logger* log, int sockfd, sockaddr_storage& addr) {
    char buffer[INET6_ADDRSTRLEN];
    inet_ntop(addr.ss_family, get_in_addr(reinterpret_cast<sockaddr *>(&addr)),
        buffer, sizeof buffer);
    log->debug( std::format("Received request from [{}]", buffer));
    log->debug("Get / HTTP/1.1");
    log->debug("Host: localhost");
    log->debug("User-Agent: curl/7.85.0");
    log->debug("Accept: */*");

    const std::string msg = "Hello from Backend Server!\n";
    if (send(sockfd, msg.c_str(), msg.size(), 0) == -1) {
        log->log(ERROR, "Server: could not send response");
    };
}

int main(int argc, char* argv[]){
    const auto logger = std::make_unique<ConsoleLogger>(false);

    if (argc != 2) {
        logger->error("Usage: ./be <port>");
        exit(1);
    }

    auto server = Server(logger.get(), argv[1], 20);
    server.run(serverStub);

    return 0;
}