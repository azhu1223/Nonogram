#include <gtest/gtest.h>

#include "Board.h"
#include "Utility.h"
#include <vector>
#include <iostream>

class BoardTest : public ::testing::Test {
protected:
    std::vector<std::vector<Cell>> boardVector;

    void SetUp() override {
        boardVector.emplace_back(3, Cell::EMPTY);
        boardVector.emplace_back(3, Cell::EMPTY);
        boardVector.emplace_back(3, Cell::EMPTY);
    }
};

TEST_F(BoardTest, ConstructorTest) {
    Board b(&boardVector);

    EXPECT_EQ(b.getVector(), &boardVector);
}

TEST_F(BoardTest, FillRowTest) {
    Board b(&boardVector);

    EXPECT_TRUE(b.fill(FillDirection::ROW, {0, 0}, {0, 2}, Cell::FILLED));

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(boardVector[0][i], Cell::FILLED);
    }
}

TEST_F(BoardTest, FillColumnTest) {
    Board b(&boardVector);

    EXPECT_TRUE(b.fill(FillDirection::COLUMN, {0, 0}, {2, 0}, Cell::FILLED));

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(boardVector[i][0], Cell::FILLED);
    }
}

TEST_F(BoardTest, FillCellTest) {
    Board b(&boardVector);

    EXPECT_TRUE(b.fill(FillDirection::COLUMN, {0, 0}, {0, 0}, Cell::FILLED));

    EXPECT_EQ(boardVector[0][0], Cell::FILLED);
}