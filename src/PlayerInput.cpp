#include "PlayerInput.h"
#include "Utility.h"

#include <ostream>
#include <istream>
#include <string>
#include <unordered_map>

PlayerInput::PlayerInput(std::istream& cin, std::ostream& cout) : m_cin(cin), m_cout(cout) {}

u_ptr<std::unordered_map<Setting, std::string>> PlayerInput::getGameInitializationSettings() {
    u_ptr<std::unordered_map<Setting, std::string>> settings(new std::unordered_map<Setting, std::string>());

    bool keepAsking = true;
    while (keepAsking) {
        m_cout << "How many rows would you like your board to be?\n";
        
        std::string rowString;
        std::getline(m_cin, rowString);

        if (validIntegralAnswer(rowString)) {
            keepAsking = false;
            (*settings)[Setting::ROW_SIZE] = rowString;
        }
    }

    keepAsking = true;
    while (keepAsking) {
        m_cout << "How many columns would you like your board to be?\n";
        
        std::string colString;
        std::getline(m_cin, colString);

        if (validIntegralAnswer(colString)) {
            keepAsking = false;
            (*settings)[Setting::COLUMN_SIZE] = colString;
        }
    }

    keepAsking = true;
    while (keepAsking) {
        m_cout << "How likely would you like each cell to be filled?\n";
        
        std::string probString;
        std::getline(m_cin, probString);

        if (validProbAnswer(probString)) {
            keepAsking = false;
            (*settings)[Setting::FILL_PROBABILITY] = probString;
        }
    }

    return settings;
}

bool PlayerInput::validIntegralAnswer(std::string s) {
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

bool PlayerInput::validProbAnswer(std::string s) {
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
                else if (wholeNumber.find_first_not_of("01")) {

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