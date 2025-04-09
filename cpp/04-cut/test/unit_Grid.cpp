//
// Created by pbarbeira on 07-04-2025.
//

#ifndef UNIT_GRID_H
#define UNIT_GRID_H

#include <gtest/gtest.h>
#include "../src/Grid.h"

TEST(GridTest, NoInputEmptyGrid){
    std::vector<std::string> INPUT;
    char delim = ' ';

    auto grid = std::move(Grid::make_grid(INPUT, delim));

    ASSERT_EQ(grid->empty(), true);
}

//We encapsulate it to use in other tests
std::unique_ptr<Grid> _buildGrid(const char delim = '\t') {
    std::stringstream tmp;
    std::vector<std::string> INPUT;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tmp << "token" << i << j;
            if (j != 2) {
                tmp << delim;
            }
        }
        INPUT.push_back(tmp.str());
        tmp.str("");
    }

    return std::move(Grid::make_grid(INPUT, delim));
}

TEST(GridTest, InputSmallGrid){
    constexpr char DELIM = ',';
    const auto grid = _buildGrid(DELIM);

    ASSERT_EQ(grid->empty(), false);
    EXPECT_EQ(grid->cols(), 3);
    EXPECT_EQ(grid->rows(), 3);
}

TEST(GridTest, HandleFieldQueryDefaultDelimiter) {
    const std::vector EXPECTED = { "token00", "token10", "token20" };
    const auto options = std::make_unique<Options>();
    options->fields = { 1 };
    const auto grid = _buildGrid(options->delimiter);

    const auto rows = grid->handle(options.get());

    EXPECT_EQ(rows[0].size(), options->fields.size());
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(rows[i][0], EXPECTED[i]);
    }
}

TEST(GridTest, HandleFieldQueryCustomDelimiter) {
    const std::vector EXPECTED = { "token00", "token10", "token20" };
    const auto options = std::make_unique<Options>();
    options->fields = { 1 };
    options->delimiter = ',';
    const auto grid = _buildGrid(options->delimiter);

    const auto rows = grid->handle(options.get());

    EXPECT_EQ(rows[0].size(), options->fields.size());
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(rows[i][0], EXPECTED[i]);
    }
}

TEST(GridTest, HandleMultiField) {
    const std::vector<std::vector<std::string>> EXPECTED = {
        { "token00", "token01" },
        { "token10", "token11" },
        { "token20", "token21" },
    };
    const auto options = std::make_unique<Options>();
    options->fields = { 1, 2 };
    options->delimiter = ',';
    const auto grid = _buildGrid(options->delimiter);

    const auto rows = grid->handle(options.get());

    EXPECT_EQ(rows[0].size(), options->fields.size());
    EXPECT_EQ(rows.size(), EXPECTED.size());
    for (int i = 0; i < EXPECTED.size(); i++) {
        for (int j = 0; j < EXPECTED[i].size(); j++) {
            EXPECT_EQ(rows[i][j], EXPECTED[i][j]);
        }
    }
}




#endif //UNIT_GRID_H
