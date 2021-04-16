/*********************************************************************
** Author: Kimberly Tom
** Date: 4/12/18
** Description: The header file for board.cpp
*********************************************************************/

#ifndef PROJECT1A_BOARD_HPP
#define PROJECT1A_BOARD_HPP


class Board {

    private:
    int boardRows;
    int boardCols;
    char **pBoard;


    public:
    Board(); // default constructor
    ~Board(); // destructor
    int getBoardRows(); // get board row count
    int getBoardCols(); // get board column count
    char getBoard(int rows, int cols); // get current board
    void setBoardChar(int rows, int cols, char image); // set board characters
    void menuBoard(); // menu options for board
    void makeBoard(); // make initial board
    void printBoard(); // print board
};

#endif