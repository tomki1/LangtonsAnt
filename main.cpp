/*********************************************************************
** Program name: Langton's Ant Progam - Project 1
** Author: Kimberly Tom
** Date: 4/12/18  
** Description: This program runs a simulation of Langton's Ant.  User specifies the dimension of the board,
 * how many steps the program should run, and starting position of ant. The ant starts in the North position.
 * If the ant is on a white space, turn right 90 degrees and change the space to black. If the ant is on a black
 * space, turn left 90 degrees and change the space to white.  If the ant hits an edge, it will wrap around to the
 * other side of the board.
*********************************************************************/

#include "menu.hpp"
#include<iostream>

using std::cout;
using std::endl;

int main() {

// show Langton's Ant main menu
cout << "Welcome to the Langton's Ant Program" << endl;
showMenu();

return 0;
}
