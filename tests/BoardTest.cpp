#include <gtest/gtest.h>

#include "Board.h"
#include "Utility.h"
#include <vector>
#include <iostream>
#include <memory>
#include <utility>

class BoardTest : public ::testing::Test {
protected:
    u_ptr<std::vector<std::vector<Cell>>> boardVector;

    void SetUp() override {
        boardVector = u_ptr<std::vector<std::vector<Cell>>>(new std::vector<std::vector<Cell>>);
        boardVector->emplace_back(3, Cell::EMPTY);
        boardVector->emplace_back(3, Cell::EMPTY);
        boardVector->emplace_back(3, Cell::EMPTY);
    }
};

TEST_F(BoardTest, ConstructorTest) {
    Board b(std::move(boardVector));

    //EXPECT_EQ(b.getVector(), &boardVector);
}

TEST_F(BoardTest, FillRowTest) {
    Board b(std::move(boardVector));

    EXPECT_TRUE(b.fill(FillDirection::ROW, {0, 0}, {0, 2}, Cell::FILLED));

    std::vector<Cell> boardRow = b.getRow(0);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(boardRow[i], Cell::FILLED);
    }
}

TEST_F(BoardTest, FillColumnTest) {
    Board b(std::move(boardVector));

    EXPECT_TRUE(b.fill(FillDirection::COLUMN, {0, 0}, {2, 0}, Cell::FILLED));

    std::vector<Cell> boardColumn = b.getColumn(0);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(boardColumn[i], Cell::FILLED);
    }
}

TEST_F(BoardTest, FillCellTest) {
    Board b(std::move(boardVector));

    EXPECT_TRUE(b.fill(FillDirection::COLUMN, {0, 0}, {0, 0}, Cell::FILLED));

    std::vector<Cell> boardRow = b.getRow(0);

    EXPECT_EQ(boardRow[0], Cell::FILLED);
}