#include "PlayerInput.h"
#include "Utility.h"

#include <ostream>
#include <istream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <sstream>

PlayerInput::PlayerInput(std::istream& cin, std::ostream& cout) : m_cin(cin), m_cout(cout) {}

u_ptr<Settings> PlayerInput::getGameInitializationSettings() const {
    u_ptr<Settings> settings(new Settings());

    bool keepAsking = true;
    while (keepAsking) {
        m_cout << "How many rows would you like your board to be?\n";
        
        std::string rowString;
        std::getline(m_cin, rowString);

        if (validIntegralAnswer(rowString)) {
            keepAsking = false;
            (*settings)[GameSetting::ROW_SIZE] = rowString;
        }
    }

    keepAsking = true;
    while (keepAsking) {
        m_cout << "How many columns would you like your board to be?\n";
        
        std::string colString;
        std::getline(m_cin, colString);

        if (validIntegralAnswer(colString)) {
            keepAsking = false;
            (*settings)[GameSetting::COLUMN_SIZE] = colString;
        }
    }

    keepAsking = true;
    while (keepAsking) {
        m_cout << "How likely would you like each cell to be filled?\n";
        
        std::string probString;
        std::getline(m_cin, probString);

        if (validProbAnswer(probString)) {
            keepAsking = false;
            (*settings)[GameSetting::FILL_PROBABILITY] = probString;
        }
    }

    return settings;
}

Move PlayerInput::getMove(int numRows, int numCols) const {
    bool keepAsking = true;
    std::string actionString;
    while (keepAsking) {
        m_cout << "What action would you like to perform? (f)ill, (e)liminate, (t)est.\n";

        std::getline(m_cin, actionString);

        if (actionString.size() != 1 || actionString.find_first_not_of("fet") != std::string::npos) {
            m_cout << "You must choose an action from the options (f), (e), or (t).\n";
        }

        else {
            keepAsking = false;
        }
    }

    keepAsking = true;
    int firstX;
    int firstY;

    while (keepAsking) {
        m_cout << "Where would you like to start from? Provide a coordinate where the values are deliminated by a space.\n";

        std::string coordinateString;
        std::getline(m_cin, coordinateString);
        
        Result<Point> pointCoversionResult = convertStringToPoint(coordinateString);
        if (pointCoversionResult.second) {
            firstX = pointCoversionResult.first.first;
            firstY = pointCoversionResult.first.second;

            if (firstX < numRows && firstY < numCols) {
                keepAsking = false;
            }

            else {
                m_cout << "Coordinates must be within the board boundaries.\n";
            }
        }
    }

    keepAsking = true;
    int secondX;
    int secondY;

    while (keepAsking) {
        m_cout << "Where would you like to end? Coordinate must be vertically or horizontally in line with the previous point.\n";

        std::string coordinateString;
        std::getline(m_cin, coordinateString);
        
        Result<Point> pointCoversionResult = convertStringToPoint(coordinateString);
        if (pointCoversionResult.second) {
            secondX = pointCoversionResult.first.first;
            secondY = pointCoversionResult.first.second;

            if (secondX < numRows && secondY < numCols) {

                if (firstX == secondX || firstY == secondY) {
                    keepAsking = false;
                }

                else {
                    m_cout << "The second coordinate must be vertically or horizontally aligned with the first point.\n";
                }
            }

            else {
                m_cout << "Coordinates must be within the board boundaries.\n";
            }
        }
    }

    return {charToAction(actionString[0]), {{firstX, firstY}, {secondX, secondY}}};
}

Result<Point> PlayerInput::convertStringToPoint(const std::string& s) const {
    std::stringstream deliminationStream(s);

    std::string xString;
    std::string yString;
    std::getline(deliminationStream, xString, ' ');
    std::getline(deliminationStream, yString, ' ');

    if (xString.empty() || yString.empty()) {
        m_cout << "Coordinate must be in the form \"X Y\".\n";
        return {{0, 0}, false};
    }

    if (!(xString.find_first_not_of("1234567890") == std::string::npos && 
        yString.find_first_not_of("1234567890") == std::string::npos)) {
        
        m_cout << "Coordinates must be positive integral numbers.\n";
        return {{0, 0}, false};
    }

    int x;
    int y;

    x = std::stoi(xString);
    y = std::stoi(yString);

    return {{x, y}, true};
}

bool PlayerInput::validIntegralAnswer(std::string s) const {
    bool result = false;

    if (s.empty()) {
        m_cout << "Reponse cannot be empty.\n";
    }

    else if (s.find_first_not_of("0123456789") == std::string::npos) {
        result = true;
    }

    else {
        m_cout << "Response must be a positive integer.\n";
    }

    return result;
}

bool PlayerInput::validProbAnswer(std::string s) const {
    bool result = false;

    if (s.empty()) {
        m_cout << "Reponse cannot be empty.\n";
    }

    else if (s.find_first_not_of("0123456789.") == std::string::npos) {
        // Check that there is exactly one or no periods.
        size_t firstPeriod = s.find_first_of(".");
        if (firstPeriod == s.find_last_of(".")) {
            // If there is no period
            if (firstPeriod == std::string::npos) {

                // If the string does not contain any digit besides 1 or 0
                if (s.find_first_not_of("10") == std::string::npos) {
                    size_t firstOne = s.find_first_of("1");

                    // If the string is just zeros or is in the form of 0...01
                    if (firstOne == std::string::npos || 
                        firstOne == s.find_last_of("1") && firstOne == s.size() - 1) {
                        result = true;
                    }
                }
            }

            // If there is a period
            else {
                std::string wholeNumber = s.substr(0, firstPeriod);
                std::string decimal = s.substr(firstPeriod + 1);

                // If the integral part of the float is empty
                if (wholeNumber.empty()) {
                    if (!decimal.empty()) {
                        result = true;
                    }
                }

                // Trap just to filter out numbers greater than 1 using digits other than 1 and 0.
                else if (wholeNumber.find_first_not_of("01") != std::string::npos) {

                }

                else {
                    size_t firstOne = wholeNumber.find_first_of("1");

                    // If the integral part is just zeros or is in the form of (0*)1.(0*)
                    if (firstOne == std::string::npos || 
                        (decimal.empty() || decimal.find_first_not_of("0") == std::string::npos) && firstOne == wholeNumber.find_last_of("1") && firstOne == s.size() - 1) {
                        result = true;
                    }
                }
            }
        }
    }

    if (!result) {
        m_cout << "Response must be a floating point number between 0 and 1, inclusive.\n";
    }

    return result;
}

Action PlayerInput::charToAction(char c) const {
    Action a;

    switch(c) {
    case 'f':
        a = Action::FILL;
        break;
    case 'e':
        a = Action::ELIMINATE;
        break;
    case 't':
        a = Action::TEST;
        break;
    case 'q':
        a = Action::QUIT;
        break;
    default:
        a = Action::ERROR;
    }

    return a;
}