#include <iostream>
#include "Options.h"
#include "Reader.h"

int main(int argc, char* argv[]) {
    const auto logger = std::make_unique<ConsoleLogger>();
    try {
        auto options = OptionsParser::parse(argc, argv, logger.get());

        const auto data = Reader::readFile(options->filename);

        if (data.empty()) {
            logger->log(WARNING, "File is empty.");
        }
    }catch (const std::runtime_error& e) {
        logger->log(ERROR, std::format("RuntimeException", e.what()));
    }catch (const std::invalid_argument& e) {
        logger->log(ERROR, std::format("InvalidArgumentException", e.what()));
    }
    logger->dump();

    return 0;
}