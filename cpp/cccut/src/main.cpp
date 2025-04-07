#include <iostream>

#include "Grid.h"
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

        const auto grid = Grid::make_grid(data, options->delimiter);

        const auto tokens = grid->handle(options.get());

        for (const auto& row : tokens) {
            for (const auto& token : row) {
                std::cout << token << "\t";
            }
            std::cout << std::endl;
        }
    }catch (const std::runtime_error& e) {
        logger->log(DEBUG, std::format("RuntimeException\n\t{}", e.what()));
    }catch (const std::invalid_argument& e) {
        logger->log(DEBUG, std::format("InvalidArgumentException\n\t{}", e.what()));
    }
    return 0;
}