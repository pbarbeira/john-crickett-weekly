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

std::string serverStub(Logger* logger, sockaddr_storage& addr) {
    char buffer[INET6_ADDRSTRLEN];
    inet_ntop(addr.ss_family, get_in_addr(reinterpret_cast<sockaddr *>(&addr)),
        buffer, sizeof buffer);
    logger->debug( std::format("Received request from [{}]", buffer));
    logger->debug("Get / HTTP/1.1");
    logger->debug("Host: localhost");
    logger->debug("User-Agent: curl/7.85.0");
    logger->debug("Accept: */*");

    return "Hello from Load Balancer!";
}

int main(int argc, char* argv[]){
    const auto logger = std::make_unique<ConsoleLogger>(false);

    if (argc != 2) {
        logger->error("Usage: ./lb <port>");
        exit(1);
    }

    auto server = Server(logger.get(), argv[1], 20);
    server.run(serverStub);

    return 0;
}