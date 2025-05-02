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
        std::cout << request->buildMsg("\n");
        auto out = std::make_unique<HttpResponse>();
        out->status = 200;
        out->body = "Hello from Backend Server!";
        out->headers = {
            { "Content-length", std::to_string(out->body.size()) },
            { "Content-type", "text/plain" }
        };
        logger->debug("Responded with a hello message");
        return std::move(out);
    };

    server.run(serverStub);

    return 0;
}