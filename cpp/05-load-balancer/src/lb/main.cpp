#include <memory>
#include <arpa/inet.h>
#include <functional>

#include "../Server.h"
#include "../Client.h"
#include "../lib/Logger.h"

int main(int argc, char* argv[]) {
    const auto logger = std::make_unique<ConsoleLogger>(false);

    if (argc != 2) {
        logger->error("Usage: ./be <port>");
        exit(1);
    }

    auto server = HttpServer(argv[1], 20, logger.get());
    const auto client = std::make_unique<HttpClient>("localhost", "1338", logger.get());

    auto serverStub = [&](std::unique_ptr<HttpRequest> request)-> std::unique_ptr<HttpResponse> {
        return std::move(client->sendRequest(std::move(request)));
    };
    server.run(serverStub);

    return 0;
}