/*********************************************************************
** Author: Kimberly Tom
** Date: 4/12/18
** Description: The inputValidation functions checks to make sure the board rows, board columns,
 * and number of steps are valid and within the restrictions.
*********************************************************************/

#include "inputValidation.hpp"
#include<iostream>
#include<sstream>


using std::string;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;

// This function checks to make sure the rows of the board are between 1 and 150
int checkBoardRows (int rows) {
    bool errFlag = false;
    string input;
    do {
        getline(cin, input);
        stringstream sStream(input);

        if (sStream >> rows && !(sStream >> input)) {

            if (rows < 2 || rows > 150) {
                cout << "invalid, select a number of rows between 1 and 150." << endl;
            } else {
                errFlag = true;
            }
        } else {
            cout << "invalid, select a number of rows between 1 and 150." << endl;
        }

    } while (errFlag == false);
    return rows;
}

// This function checks to make sure the columns of the board are between 1 and 150
int checkBoardCols(int cols) {
    bool errFlag = false;
    string input;
    do {
        getline(cin, input);
        stringstream sStream(input);

        if (sStream >> cols && !(sStream >> input)) {

            if (cols < 2 || cols > 150) {
                cout << "invalid, select a number of columns between 1 and 150." << endl;
            } else {
                errFlag = true;
            }
        } else {
            cout << "invalid, select a number of columns between 1 and 150." << endl;
        }

    } while (errFlag == false);
    return cols;
}

// This functions checks to make sure the number of steps is between 1 and 20000
int checkStepCount(int steps) {

    bool errFlag = false;
    string input;
    do {
        getline(cin, input);
        stringstream sStream(input);

        if (sStream >> steps && !(sStream >> input)) {

            if (steps < 1 || steps > 20000) {
                cout << "invalid, select a number of steps between 1 and 20000." << endl;
            } else {
                errFlag = true;
            }
        } else {
            cout << "invalid, select a number of steps between 1 and 20000." << endl;
        }

    } while (errFlag == false);
    return steps;
}