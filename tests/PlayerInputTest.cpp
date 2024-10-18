#include <gtest/gtest.h>

#include "PlayerInput.h"
#include "Utility.h"
#include "Board.h"
#include <vector>
#include <sstream>
#include <string>
#include <unordered_map>

class PlayerInputTest : public ::testing::Test {
public:
    PlayerInputTest() : playerInput(cin, cout), board(numRows, numCols) {}
protected:
    int numRows = 5;
    int numCols = 10;

    std::stringstream cout;
    std::stringstream cin;
    PlayerInput playerInput;
    Board board;
};

TEST_F(PlayerInputTest, SuccessfulSettings) {
    cin << "6\n7\n0.5\n";

    u_ptr<Settings> settings = playerInput.getGameInitializationSettings();
    
    EXPECT_EQ((*settings)[Setting::ROW_SIZE], "6");
    EXPECT_EQ((*settings)[Setting::COLUMN_SIZE], "7");
    EXPECT_EQ((*settings)[Setting::FILL_PROBABILITY], "0.5");

    std::string outputString;
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many rows would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many columns would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How likely would you like each cell to be filled?");
}

TEST_F(PlayerInputTest, WrongRowSize) {
    cin << "a\n6\n7\n0.5\n";

    u_ptr<Settings> settings = playerInput.getGameInitializationSettings();
    
    EXPECT_EQ((*settings)[Setting::ROW_SIZE], "6");
    EXPECT_EQ((*settings)[Setting::COLUMN_SIZE], "7");
    EXPECT_EQ((*settings)[Setting::FILL_PROBABILITY], "0.5");

    std::string outputString;
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many rows would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "Response must be a positive integer.");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many rows would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many columns would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How likely would you like each cell to be filled?");
}

TEST_F(PlayerInputTest, WrongColumnSize) {
    cin << "6\na\n7\n0.5\n";

    u_ptr<Settings> settings = playerInput.getGameInitializationSettings();
    
    EXPECT_EQ((*settings)[Setting::ROW_SIZE], "6");
    EXPECT_EQ((*settings)[Setting::COLUMN_SIZE], "7");
    EXPECT_EQ((*settings)[Setting::FILL_PROBABILITY], "0.5");

    std::string outputString;
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many rows would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many columns would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "Response must be a positive integer.");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many columns would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How likely would you like each cell to be filled?");
}

TEST_F(PlayerInputTest, WrongProbabilityGreaterThanOne) {
    cin << "6\n7\n1.1\n0.5\n";

    u_ptr<Settings> settings = playerInput.getGameInitializationSettings();
    
    EXPECT_EQ((*settings)[Setting::ROW_SIZE], "6");
    EXPECT_EQ((*settings)[Setting::COLUMN_SIZE], "7");
    EXPECT_EQ((*settings)[Setting::FILL_PROBABILITY], "0.5");

    std::string outputString;
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many rows would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How many columns would you like your board to be?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How likely would you like each cell to be filled?");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "Response must be a floating point number between 0 and 1, inclusive.");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "How likely would you like each cell to be filled?");
}

TEST_F(PlayerInputTest, ValidGetMoveTest) {
    cin << "f\n1 2\n1 4";

    Move move = playerInput.getMove(board);

    EXPECT_EQ(move.first, Action::FILL);
    EXPECT_EQ(move.second.first, Point({1, 2}));
    EXPECT_EQ(move.second.second, Point({1, 4}));

    std::string outputString;
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "What action would you like to perform? (f)ill, (e)liminate, (t)est.");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "Where would you like to start from? Provide a coordinate where the values are deliminated by a space.");
    std::getline(cout, outputString);
    EXPECT_EQ(outputString, "Where would you like to end? Coordinate must be vertically or horizontally in line with the previous point.");
}