#include <memory>
#include <arpa/inet.h>
#include <functional>

#include "../Server.h"
#include "../Client.h"
#include "../lib/Logger.h"


void* get_in_addr(sockaddr *sa){
    if (sa->sa_family == AF_INET) {
        return &(reinterpret_cast<sockaddr_in *>(sa)->sin_addr);
    }
    return &(reinterpret_cast<sockaddr_in6 *>(sa)->sin6_addr);
}

int main(int argc, char* argv[]) {
    const auto logger = std::make_unique<ConsoleLogger>(false);

    if (argc != 2) {
        logger->error("Usage: ./be <port>");
        exit(1);
    }

    auto server = HttpServer(logger.get(), argv[1], 20);
    const auto client = std::make_unique<Client>("localhost", "1338", logger.get());

    auto serverStub = [&]()-> std::unique_ptr<HttpResponse> {
        auto out = std::make_unique<HttpResponse>();
        auto result = client->sendRequest();
        out->status = 200;
        out->body = result;
        out->headers = {
            { "Content-type", "text/plain"},
            { "Content-length", std::format("{}", result.size())}
        };
        return std::move(out);
    };
    server.run(serverStub);

    return 0;
}