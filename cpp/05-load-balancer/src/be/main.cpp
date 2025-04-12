#include <memory>

#include "../Server.h"
#include "../lib/Logger.h"

int main(const int argc, char* argv[]){
    const auto logger = std::make_unique<ConsoleLogger>(false);

    if (argc != 2) {
        logger->error("Usage: ./be <port>");
        exit(1);
    }

    auto server = HttpServer(argv[1], 20, logger.get());
    auto serverStub = [&](std::unique_ptr<HttpRequest> request)-> std::unique_ptr<HttpResponse> {
        std::stringstream ss;
        ss << "HTTP/1.1 200 OK\n"
            << "Content-length: 27\n"
            << "Content-type: text/plain\n"
            << "\n";
        ss << "Hello from Backend Server!";
        return HttpResponse::createResponse(ss);
    };

    server.run(serverStub);

    return 0;
}