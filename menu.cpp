/*********************************************************************
** Author: Kimberly Tom
** Date: 4/12/18
** Description: The menu function displays the starting menu for the Langton's Ant simulation.
 * The user can start the program or quit.  After a simulation of Langton's Ant is completed, the menu will
 * prompt the user whether to start a new simulation or quit.
*********************************************************************/

#include "menu.hpp"
#include<sstream>

using std::string;
using std::stringstream;
using std::cout;
using std::cin;
using std::endl;

// This function displays the Langton's Ant main menu
void showMenu() {

        cout << "Langton's Ant Main Menu" << endl;
	cout << "1. Start Langton's Ant simulation" << endl;
        cout << "2. Quit" << endl;
        cout << "Enter Choice: " << endl;

// obtain user's choice and perform input validation on choice
        bool errFlag = false;
        string input;
        int validInteger;
        do {
            getline(cin, input);
            stringstream sStream(input);

            if (sStream >> validInteger && !(sStream >> input))
            {

                if (validInteger != 1 && validInteger != 2)
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

        switch (validInteger) {

            case 1: {
                cout << "Start Langton's Ant simulation was selected" << endl;
                Ant *pAnt = new Ant;
                pAnt->beginSim();
                delete pAnt;
                cout << "Langton's Ant simulation has completed. You may play again or quit the program." << endl;
                showMenu(); // after Langton's Ant simulation completed, ask user if they want to play again
                break;
            }
            case 2: {
                cout << "Langton's Ant program is quitting. Goodbye." << endl;
                break;
            }
            default: {
                cout << "Invalid menu choice, choose again." << endl;
                break;

            }
        }
    }

