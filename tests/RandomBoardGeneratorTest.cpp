#include <gtest/gtest.h>

#include "RandomBoardGenerator.h"
#include "Board.h"
#include "Utility.h"
#include <functional>
#include <vector>
#include <random>

class RandomBoardGeneratorTest : public ::testing::Test {
protected:
    s_ptr<Board> board;
    double probOfFilled;
    int rows;
    int cols;

    std::random_device dev;
    std::mt19937 rng_base;
    std::uniform_real_distribution<> distr;

    std::function<double()> rng;

    void SetUp() override {
        probOfFilled = 0.5;
        rng_base = std::mt19937(dev());
        rng = std::bind(distr, rng_base);
        rows = 10;
        cols = 10;
    }
};

TEST_F(RandomBoardGeneratorTest, GenerateEmptyBoardProbZero) {
    RandomBoardGenerator boardGenerator(0, rng);

    Result<s_ptr<Board>> generationResult = boardGenerator.generateBoard(rows, cols);
    EXPECT_TRUE(generationResult.second);

    board = generationResult.first;

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row = board->getRow(i);

        for (Cell c : row) {
            EXPECT_EQ(c, Cell::DEFAULT);
        }
    }
}

// RNG being 0 generates a full board.
TEST_F(RandomBoardGeneratorTest, GenerateEmptyBoardRngZero) {
    RandomBoardGenerator boardGenerator(probOfFilled, []() -> double {return 0.0;});

    Result<s_ptr<Board>> generationResult = boardGenerator.generateBoard(rows, cols);
    EXPECT_TRUE(generationResult.second);

    board = generationResult.first;

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row = board->getRow(i);

        for (Cell c : row) {
            EXPECT_EQ(c, Cell::FILLED);
        }
    }
}

TEST_F(RandomBoardGeneratorTest, GenerateFullBoardProbOne) {
    RandomBoardGenerator boardGenerator(1, rng);

    Result<s_ptr<Board>> generationResult = boardGenerator.generateBoard(rows, cols);
    EXPECT_TRUE(generationResult.second);

    board = generationResult.first;

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row = board->getRow(i);

        for (Cell c : row) {
            EXPECT_EQ(c, Cell::FILLED);
        }
    }
}

// RNG being 1 generates an empty board.
TEST_F(RandomBoardGeneratorTest, GenerateFullBoardRngOne) {
    RandomBoardGenerator boardGenerator(probOfFilled, []() -> double {return 1.0;});

    Result<s_ptr<Board>> generationResult = boardGenerator.generateBoard(rows, cols);
    EXPECT_TRUE(generationResult.second);

    board = generationResult.first;

    for (int i = 0; i < rows; i++) {
        std::vector<Cell> row = board->getRow(i);

        for (Cell c : row) {
            EXPECT_EQ(c, Cell::DEFAULT);
        }
    }
}

TEST_F(RandomBoardGeneratorTest, GenerateRandomBoard) {
    RandomBoardGenerator boardGenerator(probOfFilled, rng);

    Result<s_ptr<Board>> generationResult = boardGenerator.generateBoard(rows, cols);
    EXPECT_TRUE(generationResult.second);
}