//
// Created by pbarbeira on 07-04-2025.
//

#ifndef GRID_H
#define GRID_H

#include <memory>
#include <vector>
#include <string>

#include "Options.h"
#include "StringUtils.h"

class Grid{
    std::vector<std::vector<std::string>> _grid;

    public:
        Grid() = delete;

        explicit Grid(std::vector<std::vector<std::string>> grid):
            _grid(std::move(grid)){}

        std::vector<std::vector<std::string>> handle(Options* options) const {
            std::vector<std::vector<std::string>> out;
            for (int i = 0; i < _grid.size(); ++i) {
                std::vector<std::string> row;
                for (const auto& field : options->fields) {
                    //field columns start at 1, _grid starts at 0
                    row.push_back(_grid[i][field - 1]);
                }
                out.push_back(row);
            }
            return out;
        }

        static std::unique_ptr<Grid> make_grid(const std::vector<std::string>& input, char delim) {
            std::vector<std::vector<std::string>> grid;
            for (int i = 0; i < input.size(); ++i) {
                std::vector<std::string> row;
                auto rowData = input[i];
                const auto tokens = StringUtils::split(rowData, delim);
                for (const auto& token : tokens) {
                    row.push_back(token);
                }
                grid.push_back(row);
            }
            return std::make_unique<Grid>(grid);
        }

        bool empty() const{
            return _grid.size() == 0;
        }

        int cols() const {
            return _grid[0].size();
        }

        int rows() const {
            return _grid.size();
        }
};

#endif //GRID_H
