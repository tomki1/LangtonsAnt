/*********************************************************************
** Author: Kimberly Tom
** Date: 4/12/18
** Description: The ant class has functions that set the ant on the board, print the current board,
 * moves the ant throughout the board, and asks the user how many steps of Langton's Ant to perform.
*********************************************************************/

#include "ant.hpp"
#include "inputValidation.hpp"
#include<iostream>
#include<sstream>
#include<cstdlib>
#include<ctime>


using std::string;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;

// default constructor
Ant::Ant() {
    showBoard = NULL;
}

// This function sets the ant's row
void Ant::setRow(int row) {
        antRow = row;
}

// This function sets the ant's column
void Ant::setCol(int col) {
     antCol = col;
}

// This function randomly generates an initial ant row
int Ant::randomRow(int minRow, int maxRow) {
    static bool errRanRow = true;
    if (errRanRow) {
        srand(time(NULL));
        errRanRow = false;
    }
    return minRow + rand() % ((maxRow+1) - minRow);
}

// This functions randomly generates an initial ant column
int Ant::randomCol(int minCol, int maxCol) {
    static bool errRanCol = true;
    if (errRanCol) {
        srand(time(NULL));
        errRanCol = false;
    }
    return minCol + rand() % ((maxCol+1) - minCol);
}

// This function sets the ant's initial row and column
void Ant::setAntInitial() {
    cout << "Would you like to start the ant at a random location?" << endl;
    cout << "1. Yes" << endl;
    cout << "2. No" << endl;

    bool errFlag = false;
    string inputRand;
    int validRand;
    do {
        getline(cin, inputRand);
        stringstream sStream(inputRand);

        if (sStream >> validRand && !(sStream >> inputRand))
        {

            if (validRand != 1 && validRand != 2)
            {
                cout << "please enter 1 or 2" << endl;
            }
            else
            {
                errFlag = true;
            }
        }
        else
        {
            cout << "Please enter 1 or 2" << endl;
        }

    } while (errFlag == false);

    switch (validRand) {

        case 1: {
            cout << "Random ant position has been selected" << endl;
            setRow(randomRow(1, showBoard->getBoardRows())-1); // randomly generate initial ant row
            setCol(randomCol(1, showBoard->getBoardCols())-1); // randomly generate initial ant column
            break;
        }
        case 2: {
            cout << "Random ant position has not been selected" << endl;

            cout << "Please select a row to start the ant. Please note the first row is row 1." << endl;

            // input validation of initial ant row
            bool errFlag = false;
            string input;
            int row;

            do {
                getline(cin, input);
                stringstream sStream(input);

                if (sStream >> row && !(sStream >> input)) {

                    if (row < 1 || row > showBoard->getBoardRows()) {
                        cout << "invalid, select a row between 1 and " << showBoard->getBoardRows() << endl;
                    } else {
                        errFlag = true;
                    }
                } else {
                    cout << "invalid, select a row between 1 and " << showBoard->getBoardRows() << endl;        }

            } while (errFlag == false);
            setRow(row-1);

            cout << "Please select a column to start the ant. Please note the first column is column 1." << endl;

            // input validation on initial ant column
            bool errFlag2 = false;
            string inputCol;
            int col;
            do {
                getline(cin, inputCol);
                stringstream sStream(inputCol);

                if (sStream >> col && !(sStream >> inputCol)) {

                    if (col < 1 || col > showBoard->getBoardCols()) {
                        cout << "invalid, select a column between 1 and " << showBoard->getBoardCols() << endl;
                    } else {
                        errFlag2 = true;
                    }
                } else {
                    cout << "invalid, select a column between 1 and " << showBoard->getBoardCols() << endl;        }

            } while (errFlag2 == false);
            setCol(col-1);
            break;
        }
        default: {
            cout << "Invalid menu choice, choose again." << endl;
            break;
        }
    }

    showBoard->setBoardChar(antRow, antCol, '*'); // set the ant on the board

    showBoard->printBoard(); // print current board

    showBoard->setBoardChar(antRow, antCol, '#');  // replace ant's initial position with black square
}

// This function begins the Langton's Ant simulation
void Ant::beginSim() {
 showBoard = new Board; // create new board object
 showBoard->menuBoard(); // display board menu options
 showBoard->makeBoard(); // make the board
 showBoard->printBoard(); // print the board dimensions
 antMove(); // call the move function
}

// This function sets the ant's initial direction to North
void Ant::setDirection(Direction direct) {
antDirect = NORTH;
}

/* This function asks the user for the number of steps of the simulation to perform, then performs user's desired
 amount of steps and moves the ant. It makes calls to functions from the Board class to move the ant and show
 the current board */
void Ant::antMove () {
    setAntInitial();
    int steps = 1;
    cout << "How many steps do you want the simulation to perform? Please select a number between 1 and 20000." << endl;
    steps = checkStepCount(steps); // input validation for steps
    setSteps(steps);
    setDirection(NORTH); // set initial ant direction to North


    for (int a = 0; a < antStep; a++) {


        switch (antDirect) {
            case NORTH: {
                // if ant is facing North

                if (showBoard->getBoard(antRow, antCol) == '#') { // if ant currently on black square
                    {
                        if ((antCol + 2) > (showBoard->getBoardCols())) {
                            if (showBoard->getBoard(antRow, 0) ==
                                ' ') { //if ant lands on first column square that is white
                                showBoard->setBoardChar(antRow, 0, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow, 0,
                                                        '#'); // replace first column square with black square
                                setCol(0); // set new position of ant

                                antDirect = EAST; // change ant direction
                                break;
                            }
                            if (showBoard->getBoard(antRow, 0) ==
                                '#') { // if ant lands on first column square that is black square
                                showBoard->setBoardChar(antRow, 0, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow, 0,
                                                        ' '); // replace first column square with white square
                                setCol(0); // set new position of ant
                                antDirect = EAST; // change ant direction
                                break;
                            }

                        }
                        if (showBoard->getBoard(antRow, antCol + 1) ==
                            ' ') { // if ant lands on right square that is white

                            showBoard->setBoardChar(antRow, antCol + 1, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, antCol + 1, '#'); // replace right square with black square
                            setCol(antCol + 1); // set new position of ant
                            antDirect = EAST; // change ant direction
                            break;

                        }
                        if (showBoard->getBoard(antRow, antCol + 1) ==
                            '#') { // if ant lands on right square that is black square

                            showBoard->setBoardChar(antRow, antCol + 1, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, antCol + 1, ' '); // replace right square with white square
                            setCol(antCol + 1); // set new position of ant
                            antDirect = EAST; // change ant direction
                            break;
                        }
                    }
                }
                if (showBoard->getBoard(antRow, antCol) == ' ') { // if ant currently on white square


                    if (antCol - 1 < 0) // if ant lands on square less than first column
                    {
                        if (showBoard->getBoard(antRow, showBoard->getBoardCols() - 1) ==
                            ' ') { // if ant lands on last column that is white
                            showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                    '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                    '#'); // replace last column square with black square
                            setCol(showBoard->getBoardCols() - 1); // set new position of ant
                            antDirect = WEST; // change ant direction
                            break;
                        }
                        if (showBoard->getBoard(antRow, showBoard->getBoardCols() - 1) ==
                            '#') { // if ant lands on last column square that is black square

                            showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                    '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square

                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                    ' '); // replace last column square with white square
                            setCol(showBoard->getBoardCols() - 1); // set new position of ant
                            antDirect = WEST; // change ant direction
                            break;
                        }
                    }


                    if (showBoard->getBoard(antRow, antCol - 1) == ' ') { // if ant lands on left square that is white

                        showBoard->setBoardChar(antRow, antCol - 1, '*'); // place ant on new square
                        showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                        showBoard->printBoard(); // print current board
                        cout << "step " << a + 1 << " completed" << endl;
                        showBoard->setBoardChar(antRow, antCol - 1, '#'); // replace left square with black square
                        setCol(antCol - 1); // set new position of ant
                        antDirect = WEST; // change ant direction
                        break;
                    }
                    if (showBoard->getBoard(antRow, antCol - 1) == '#') { // if ant lands on left square that is black
                        showBoard->setBoardChar(antRow, antCol - 1, '*'); // place ant on new square
                        showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                        showBoard->printBoard(); // print current board
                        cout << "step " << a + 1 << " completed" << endl;
                        showBoard->setBoardChar(antRow, antCol - 1, ' '); // replace left square with white square
                        setCol(antCol - 1); // set new position of ant
                        antDirect = WEST; // change ant direction
                        break;
                    }

                }
            }

            case EAST: {
                // if ant is facing East

                if (showBoard->getBoard(antRow, antCol) == '#') // if ant currently on black square
                {
                    {
                        if ((antRow + 2 > showBoard->getBoardRows())) {
                            if (showBoard->getBoard(0, antCol) ==
                                ' ') { //if ant lands on first row that is white square
                                showBoard->setBoardChar(0, antCol, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(0, antCol, '#'); // replace first row square with black square
                                setRow(0); // set new position of ant
                                antDirect = SOUTH; // change ant direction
                                break;
                            }
                            if (showBoard->getBoard(0, antCol) ==
                                '#') { //if ant lands on first row that is black square
                                showBoard->setBoardChar(0, antCol, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(0, antCol, ' '); // replace first row square with white square
                                setRow(0); // set new position of ant
                                antDirect = SOUTH; // change ant direction
                                break;
                            }
                        }
                    }

                    if (showBoard->getBoard(antRow + 1, antCol) == ' ') { // if ant lands on down square that is white

                        showBoard->setBoardChar(antRow + 1, antCol, '*'); // place ant on new square
                        showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                        showBoard->printBoard(); // print current board
                        cout << "step " << a + 1 << " completed" << endl;
                        showBoard->setBoardChar(antRow + 1, antCol, '#'); // replace down square with black square
                        setRow(antRow + 1); // set new position of ant
                        antDirect = SOUTH; // change ant direction
                        break;
                    }
                    if (showBoard->getBoard(antRow + 1, antCol) == '#') { // if ant lands on down square that is black

                        showBoard->setBoardChar(antRow + 1, antCol, '*'); // place ant on new square
                        showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                        showBoard->printBoard(); // print current board
                        cout << "step " << a + 1 << " completed" << endl;
                        showBoard->setBoardChar(antRow + 1, antCol, ' '); // replace down square with white square
                        setRow(antRow + 1); // set new position of ant
                        antDirect = SOUTH; // change ant direction
                        break;
                    }
                }
                if (showBoard->getBoard(antRow, antCol) == ' ') // if ant currently on white square
                {
                    if (antRow - 1 < 0) {
                        if (showBoard->getBoard(showBoard->getBoardRows() - 1, antCol) ==
                            ' ') { //if ant lands on bottom row that is white square
                            showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                    '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol,
                                                    ' '); // replace old white square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                    '#'); // replace bottom square with black square
                            setRow(showBoard->getBoardRows() - 1); // set new position of ant
                            antDirect = NORTH; // change ant direction
                            break;
                        }
                        if (showBoard->getBoard(showBoard->getBoardRows() - 1, antCol) ==
                            '#') { //if ant lands on bottom row that is black square
                            showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                    '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol,
                                                    ' '); // replace old black square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                    ' '); // replace bottom square with white square
                            setRow(showBoard->getBoardRows() - 1); // set new position of ant
                            antDirect = NORTH; // change ant direction
                            break;
                        }
                    }
                    {
                        if (showBoard->getBoard(antRow - 1, antCol) == ' ') { // if ant lands on up square that is white

                            showBoard->setBoardChar(antRow - 1, antCol, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow - 1, antCol, '#'); // replace up square with black square
                            setRow(antRow - 1); // set new position of ant
                            antDirect = NORTH; // change ant direction
                            break;
                        }
                        if (showBoard->getBoard(antRow - 1, antCol) == '#') { // if ant lands on up square that is black

                            showBoard->setBoardChar(antRow - 1, antCol, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow - 1, antCol, ' '); // replace up square with white square
                            setRow(antRow - 1); // set new position of ant
                            antDirect = NORTH; // change ant direction
                            break;
                        }
                    }
                }

                case SOUTH: {
                    //if ant is facing South

                    if (showBoard->getBoard(antRow, antCol) == '#') // if ant currently on black square
                    {
                        if ((antCol - 1) < 0) {
                            if (showBoard->getBoard(antRow, showBoard->getBoardCols() - 1) ==
                                ' ') { //if ant lands last column square that is white
                                showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                        '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                        '#'); // replace last column square with black square
                                setCol(showBoard->getBoardCols() - 1); // set new position of ant
                                antDirect = WEST; // change ant direction
                                break;
                            }
                            if (showBoard->getBoard(antRow, showBoard->getBoardCols() - 1) ==
                                '#') { //if ant lands last column square that is black
                                showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                        '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow, showBoard->getBoardCols() - 1,
                                                        ' '); // replace last column square with black square
                                setCol(showBoard->getBoardCols() - 1); // set new position of ant
                                antDirect = WEST; // change ant direction
                                break;
                            }
                        }

                        if (showBoard->getBoard(antRow, antCol - 1) ==
                            ' ') { // if ant lands on left square that is white

                            showBoard->setBoardChar(antRow, antCol - 1, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, antCol - 1, '#'); // replace left square with black square
                            setCol(antCol - 1); // set new position of ant
                            antDirect = WEST; // change ant direction
                            break;
                        }
                        if (showBoard->getBoard(antRow, antCol - 1) ==
                            '#') { // if ant lands on left square that is white

                            showBoard->setBoardChar(antRow, antCol - 1, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, antCol - 1, ' '); // replace left square with black square
                            setCol(antCol - 1); // set new position of ant
                            antDirect = WEST; // change ant direction
                            break;
                        }
                    }
                    if (showBoard->getBoard(antRow, antCol) == ' ') // if ant currently on white square
                    {
                        if ((antCol + 2) > showBoard->getBoardCols()) {
                            if (showBoard->getBoard(antRow, 0) ==
                                ' ') { //if ant lands on first column square that is white
                                showBoard->setBoardChar(antRow, 0, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        ' '); // replace old black square with white square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow, 0,
                                                        '#'); // replace first column square with black square
                                setCol(0); // set new position of ant
                                antDirect = EAST; // change ant direction
                                break;
                            }
                            if (showBoard->getBoard(antRow, 0) ==
                                '#') { //if ant lands on first column square that is black
                                showBoard->setBoardChar(antRow, 0, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        ' '); // replace old black square with white square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow, 0,
                                                        ' '); // replace first column square with white square
                                setCol(0); // set new position of ant
                                antDirect = EAST; // change ant direction
                                break;
                            }
                        }

                        if (showBoard->getBoard(antRow, antCol + 1) ==
                            ' ') { // if ant lands on right square that is white

                            showBoard->setBoardChar(antRow, antCol + 1, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, antCol + 1, '#'); // replace right square with black square
                            setCol(antCol + 1); // set new position of ant
                            antDirect = EAST; // change ant direction
                            break;
                        }

                        if (showBoard->getBoard(antRow, antCol + 1) ==
                            '#') { // if ant lands on right square that is white

                            showBoard->setBoardChar(antRow, antCol + 1, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, ' '); // replace old black square with white square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow, antCol + 1, ' '); // replace right square with white square
                            setCol(antCol + 1); // set new position of ant
                            antDirect = EAST; // change ant direction
                            break;
                        }
                    }
                }

                case WEST: {
                    //  if ant is facing West

                    if (showBoard->getBoard(antRow, antCol) == '#') // if ant currently on black square
                    {
                        if (antRow - 1 < 0) {
                            if (showBoard->getBoard(showBoard->getBoardRows() - 1, antCol) ==
                                ' ') { //if ant lands on bottom row that is white square
                                showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                        '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                        '#'); // replace bottom square with black square
                                setRow(showBoard->getBoardRows() - 1); // set new position of ant
                                antDirect = NORTH; // change ant direction
                                break;
                            }
                            if (showBoard->getBoard(showBoard->getBoardRows() - 1, antCol) ==
                                '#') { //if ant lands on bottom row that is black square
                                showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                        '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        '#'); // replace old white square with black square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(showBoard->getBoardRows() - 1, antCol,
                                                        ' '); // replace bottom square with white square
                                setRow(showBoard->getBoardRows() - 1); // set new position of ant
                                antDirect = NORTH; // change ant direction
                                break;
                            }
                        }

                        if (showBoard->getBoard(antRow - 1, antCol) == ' ') { // if ant lands on up square that is white

                            showBoard->setBoardChar(antRow - 1, antCol, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol,
                                                    '#'); // replace old white square with black square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow - 1, antCol,
                                                    '#'); // replace up square with black square
                            setRow(antRow - 1); // set new position of ant
                            antDirect = NORTH; // change ant direction
                            break;
                        }
                        if (showBoard->getBoard(antRow - 1, antCol) == '#') { // if ant lands on up square that is black

                            showBoard->setBoardChar(antRow - 1, antCol, '*'); // place ant on new square
                            showBoard->setBoardChar(antRow, antCol, '#'); // replace old white square with black square
                            showBoard->printBoard(); // print current board
                            cout << "step " << a + 1 << " completed" << endl;
                            showBoard->setBoardChar(antRow - 1, antCol, ' '); // replace up square with white square
                            setRow(antRow - 1); // set new position of ant
                            antDirect = NORTH; // change ant direction
                            break;
                        }
                    }

                    if (showBoard->getBoard(antRow, antCol) == ' ') // if ant currently on white square
                    {
                        if (antRow + 2 > showBoard->getBoardRows()) {
                            if (showBoard->getBoard(0, antCol) == ' ') { //if ant lands on top row that is white square
                                showBoard->setBoardChar(0, antCol,
                                                        '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        ' '); // replace old black square with white square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(0, antCol,
                                                        '#'); // replace top row square with black square
                                setRow(0); // set new position of ant
                                antDirect = SOUTH; // change ant direction
                                break;
                            }
                            if (antRow + 2 > showBoard->getBoardRows()) {
                                if (showBoard->getBoard(0, antCol) ==
                                    '#') { //if ant lands on top row that is black square
                                    showBoard->setBoardChar(0, antCol,
                                                            '*'); // place ant on new square
                                    showBoard->setBoardChar(antRow, antCol,
                                                            ' '); // replace old black square with white square
                                    showBoard->printBoard(); // print current board
                                    cout << "step " << a + 1 << " completed" << endl;
                                    showBoard->setBoardChar(0, antCol,
                                                            ' '); // replace top row square with white square
                                    setRow(0); // set new position of ant
                                    antDirect = SOUTH; // change ant direction
                                    break;
                                }
                            }
                        }

                            if (showBoard->getBoard(antRow + 1, antCol) ==
                                ' ') { // if ant lands on down square that is white

                                showBoard->setBoardChar(antRow + 1, antCol, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        ' '); // replace old black square with white square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow + 1, antCol,
                                                        '#'); // replace down square with black square
                                setRow(antRow + 1); // set new position of ant
                                antDirect = SOUTH; // change ant direction
                                break;
                            }

                            if (showBoard->getBoard(antRow + 1, antCol) ==
                                '#')  // if ant lands on down square that is black
                            {
                                showBoard->setBoardChar(antRow + 1, antCol, '*'); // place ant on new square
                                showBoard->setBoardChar(antRow, antCol,
                                                        ' '); // replace old black square with white square
                                showBoard->printBoard(); // print current board
                                cout << "step " << a + 1 << " completed" << endl;
                                showBoard->setBoardChar(antRow + 1, antCol,
                                                        ' '); // replace down square with black square
                                setRow(antRow + 1); // set new position of ant
                                antDirect = SOUTH; // change ant direction
                                break;
                            }
                        }
                    }

                }
            }
        }
    }

void Ant::setSteps(int steps) {
    antStep = steps;
}

Ant::~Ant() {
delete showBoard;
}