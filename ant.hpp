/*********************************************************************
** Author: Kimberly Tom
** Date: 4/12/18
** Description: The header file for ant.cpp
*********************************************************************/

#ifndef PROJECT1A_ANT_HPP
#define PROJECT1A_ANT_HPP
#include "board.hpp"

enum Direction {NORTH, EAST, SOUTH, WEST};

class Ant {

private:
    int antRow;
    int antCol;
    int antStep;
    Direction antDirect = NORTH;
    Board *showBoard;
public:
    Ant(); // default constructor
    ~Ant(); // destructor
    void setAntInitial(); // set initial starting point of ant
    void setRow(int row); // set row position of ant
    void setCol(int col); // set column position of ant
    int randomRow(int minRow, int maxRow); // obtain random row for starting position of ant
    int randomCol(int minCol, int maxCol); // obtain random column for starting position of ant
    void beginSim(); // start Langton's Ant Simulation
    void setDirection(Direction direct); // set direction ant faces
    void antMove (); // the ant's move
    void setSteps(int steps); // set number of steps of simulation

};


#endif
