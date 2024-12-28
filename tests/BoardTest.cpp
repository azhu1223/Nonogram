#include <gtest/gtest.h>

#include "Board.h"
#include "Utility.h"
#include <vector>
#include <iostream>
#include <utility>

class BoardTest : public ::testing::Test {
protected:
    u_ptr<BoardData> boardVector;

    void SetUp() override {
        std::cerr << "Wtf is going on\n";
        std::vector<Cell> emptyRow(3, Cell::DEFAULT);
        boardVector = u_ptr<BoardData>(new BoardData(3, emptyRow));
        std::cout << "Wtf is going on 2\n";
    }
};

TEST_F(BoardTest, FillColumnTest) {
    std::cerr << "Constructing Board\n";

    Board b(std::move(boardVector));

    std::cerr << "Testing fill\n";

    EXPECT_TRUE(b.fill({0, 0}, {0, 2}, Cell::FILLED));

    std::cerr << "Ensuring fill was correct\n";

    const std::vector<Cell> boardRow = b.getColumn(0);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(boardRow[i], Cell::FILLED);
    }

    std::cerr << "Finished test\n";
}

TEST_F(BoardTest, FillRowTest) {
    Board b(std::move(boardVector));

    EXPECT_TRUE(b.fill({0, 0}, {2, 0}, Cell::FILLED));

    std::vector<Cell> boardColumn = b.getRow(0);

    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(boardColumn[i], Cell::FILLED);
    }
}

TEST_F(BoardTest, FillCellTest) {
    Board b(std::move(boardVector));

    EXPECT_TRUE(b.fill({0, 0}, {0, 0}, Cell::FILLED));

    std::vector<Cell> boardRow = b.getRow(0);

    EXPECT_EQ(boardRow[0], Cell::FILLED);
}