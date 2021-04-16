/*********************************************************************
** Author: Kimberly Tom
** Date: 4/12/18
** Description: The board functions set up the board for the Langton's Ant simulation.
*********************************************************************/

#include "board.hpp"
#include "menu.hpp"
#include "inputValidation.hpp"


using std::cout;
using std::cin;
using std::endl;

// default constructor
Board::Board() {
pBoard = NULL;
}

// This function returns the number of board rows
int Board::getBoardRows() {
return boardRows;
}

// This function returns the number of board columns
int Board::getBoardCols() {
return boardCols;
}

// This function obtains the current board
char Board::getBoard(int rows, int cols) {
    return pBoard[rows][cols];
}

// This function sets the characters on the board
void Board::setBoardChar(int rows, int cols, char image) {
    pBoard[rows][cols] = image;
}

// This function creates the board with user's desired specifications
void Board::makeBoard() {    
pBoard = new char *[boardRows];

    for (int i = 0; i < boardRows; i++) {
        pBoard[i] = new char [boardCols];
    }

        for (int i = 0; i < boardRows; i++) {
            for (int b = 0; b < boardCols; b++) {
                pBoard[i][b] = ' ';
            }
        }
    }

// This function obtains the user's desired board specifications
void Board::menuBoard() {
    int rows;
    int cols;
    cout << "What are the number of rows of the board? Please select row count between 2 and 150." << endl;
    rows = checkBoardRows(rows); //input validation of board rows
    boardRows = rows;


    cout << "What are the number of columns of the board? Please select row count between 2 and 150" << endl;
    cols = checkBoardCols(cols); //input validation of board columns
    boardCols = cols;

}

// This function prints the board
void Board::printBoard() {
    for (int i = 0; i < boardRows; i++) {
        for (int b = 0; b < boardCols; b++) {
            cout << pBoard[i][b];
        }
        cout << endl;
    }
}

// constructor
Board::~Board() {

    // deallocate column memory of array
    for (int i = 0; i < boardRows; i++) {
        delete[] pBoard[i];
    }

    // deallocate row memory
        delete[] pBoard;
}
