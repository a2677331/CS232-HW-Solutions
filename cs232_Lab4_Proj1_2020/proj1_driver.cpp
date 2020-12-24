/**************************************************************************
 * File name: proj1_driver.cpp
 * ---------------------------
 * This file contains codes for a console based simulation of a lock
 * in which you can enter a 4-letter combination to trigger related action.
 * The code involves variables and functions to model the simulation.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/01/2020
 * Date Last Revised: 10/14/2020
**************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include "mapping.h"
#include "pair.h"
#include "table.h"
#include "lockTypes.h"

using namespace std;

/* Function Prototypes */

// Function to get an alarm action from reading an input file.
actionT getAction(ifstream& inFile);

// Function to get a lock state from reading an input file.
stateT getState(ifstream& inFile);

// Function to get an event from user input.
eventT getEventFormInput();

// Function to open a file from specified file path.
void inputFile(ifstream& inFile, string filePath);

// Function to eat 3 lines in input file.
void skip3Lines(ifstream& inFile);

// Function to setup transition table ADT.
void loadTransitionTable(Table< Pair<stateT,eventT>,  stateT > & table, ifstream& inFile);

// Function to setup action table ADT.
void loadActionTable(Table< Pair<stateT,eventT>,  actionT > & table, ifstream& inFile);

// Function to return true/false, depending if user needs to unlock the lock again.
bool reCrack();

// Function to verify user input.
void verifyInput(char &input);

// Function to print welcome messages.
void print_Greetings();

// Function to perform proper lock actions from user input.
void perform_Event_From_User(Table<Pair<stateT, eventT>, stateT> & transitionTable,
                             Table<Pair<stateT, eventT>, actionT> & actionTable);

// Function to setup transition table and action table from input files.
void setup_Tables(ifstream& inFile, Table<Pair<stateT, eventT>, stateT> & transitionTable,
                                    Table<Pair<stateT, eventT>, actionT> & actionTable);


/* Main program begins */
int main()
{
    /* Greetings */
    print_Greetings();

    /* Create tables */
    Table< Pair<stateT,eventT >, stateT > transitionTable(tableSize, mappingOfData); // Transition table
    Table< Pair<stateT,eventT >, actionT > actionTable(tableSize, mappingOfData);    // Action table

    /* Setup Tables */
    ifstream inFile;    // input file stream
    setup_Tables(inFile, transitionTable, actionTable);

    /* Repeatedly prompt the user to crack the lock
       until the user enter a 'n' or 'N' */
    do {
        perform_Event_From_User(transitionTable, actionTable); // user to crack the lock
    } while (reCrack());

    cout << "Have a nice day!";
    inFile.close();
    return 0;
} /* end of main program */



/* Function Definitions */
/*******************************************************************************************
 * Function Name: setup_Tables()
 *
 * Purpose: function to setup transition table and action table from input files.
 *
 * Input Parameters:
 *          inFile: file stream pointer, which is used to open data files.
 *          transitionTable: A reference to the Table representing the transition table.
 *          actionTable:     A reference to the Table representing the action table.
 *
 * Output parameters:
 *          transitionTable: transition table has been setup.
 *          actionTable:     action table has been setup.
 *
 * Return Value: none.
 *******************************************************************************************/
void setup_Tables(ifstream& inFile, Table<Pair<stateT, eventT>, stateT> & transitionTable,
                                    Table<Pair<stateT, eventT>, actionT> & actionTable) {
    /* Setup transition table */
    inputFile(inFile, "transition_table.txt"); // open transition table
    loadTransitionTable(transitionTable, inFile);  // load transition data

    /* Setup action table */
    inputFile(inFile, "action_table.txt");     // open action table
    loadActionTable(actionTable, inFile);          // load action data
}

/*******************************************************************************************
 * Function Name: print_Greetings()
 *
 * Purpose: function to print welcome messages and purpose of the program.
 *
 * Input Parameters: none.
 *
 * Output parameters: none.
 *
 * Return Value: none.
 *******************************************************************************************/
void print_Greetings() {
    cout << "----------------------------------------------------------------\n"
         << "Welcome to the CS 232 Project 1!\n"
         << "This program simulates the a lock when 5 characters are entered.\n"
         << "The actions of the lock are unlock and an alarm.\n"
         << "The lock can accept characters A, B, C, D, E, one at a time.\n"
         << "A four character sequence is needed to \"crack\" the lock.\n"
         << "----------------------------------------------------------------\n";
}

/*******************************************************************************************
 * Function Name: getAction()
 *
 * Purpose: function to return alarm action from an input file,
 *          return alarm action if read "alarm" string,
 *          return unlock action if read "unlock" string.
 *
 * Input Parameters:
 *          inFile: input file stream.
 *
 * Output parameters: none.
 *
 * Return Value:
 *          an enumerated type representing lock action.
 *******************************************************************************************/
actionT getAction(ifstream& inFile)
{
    string actionStr;
    inFile >> actionStr;    // read next state from table file
    if (actionStr == "alarm")
        return alarm;
    else if (actionStr == "unlock")
        return unlock;

    // for debugging: belows shows up if read invalid string.
    cout << " *** Reading invalid state \"" << actionStr << "\" *** " << endl;
    cout << " *** Please check the format of the table file data *** " << endl;
    return (actionT)0; // returning garbage value
}


/*******************************************************************************************
 * Function Name: getState
 *
 * Purpose: function to return lock state from string read from an input file.
 *
 * Input Parameters:
 *          inFile: input file stream.
 *
 * Output parameters: none.
 *
 * Return Value:
 *          an enumerated type representing lock state.
 *******************************************************************************************/
stateT getState(ifstream& inFile)
{
    string stateStr;

    inFile >> stateStr;    // read next state from table file
    if (stateStr == "nke") return nke;
    else if (stateStr == "ok1") return ok1;
    else if (stateStr == "ok2") return ok2;
    else if (stateStr == "ok3") return ok3;
    else if (stateStr == "fa1") return fa1;
    else if (stateStr == "fa2") return fa2;
    else if (stateStr == "fa3") return fa3;

    // for debugging: belows shows up if read invalid string.
    cout << " *** Reading invalid state \"" << stateStr << "\" *** " << endl;
    cout << " *** Please check the format of the table file data *** " << endl;
    return (stateT)0; // returning garbage value
}

/*******************************************************************************************
 * Function Name: inputFile
 *
 * Purpose: function to open a file from specified file path,
 *          if fail to open, user can specify another file path.
 *
 * Input Parameters:
 *          inFile: input file stream.
 *          filePath: file path name.
 *
 * Output parameters: none.
 *
 * Return Value: none.
 *******************************************************************************************/
void inputFile(ifstream& inFile, string filePath)
{
    while (true)
    {
        inFile.close(); // ensure the file is close when opening.
        inFile.open(filePath);
        if (!inFile.fail()) break;  // if open fail, user can try again.
        cout << "Can't locate the file: \"" << filePath << "\"" << endl;
        cout << "Please re-enter file path: ";
        getline(cin, filePath);
    }
}

/*******************************************************************************************
 * Function Name: skip3Lines
 *
 * Purpose: function to eat 3 lines in input file.
 *
 * Input Parameters:
 *          inFile: input file stream.
 *
 * Output parameters: none.
 *
 * Return Value: none.
 *******************************************************************************************/
void skip3Lines(ifstream& inFile) {
    for (int i = 0; i < 3; i++)
        inFile.ignore(999, '\n');
}


/*******************************************************************************************
 * Function Name: loadTransitionTable
 *
 * Purpose: function to setup transition table ADT
 *
 * Input Parameters:
 *          table: transition table ADT that needs to be setup.
 *          inFile: input file stream.
 *
 * Output parameters:
 *          table: transition table ADT that has been setup.
 *
 * Return Value: none.
 *******************************************************************************************/
void loadTransitionTable(Table< Pair<stateT,eventT>,  stateT > & table, ifstream& inFile)
{
    Pair< Pair<stateT,eventT>, stateT> entry;    // an entry of table ADT
    stateT STATE,                                // state label in transition table
           nextSTATE;                            // value of transition_table[row, column]
    eventT EVENT;                                // column label in transition table
    string rowLabel;                             // row label to be skipped

    // Jump to the line with actual value
    skip3Lines(inFile);

    // Read and Load all next state values from transition_table file into table ADT
    for (int row = 0; row < 7; row++)     // 7 rows
    {
        STATE = stateT(row);          // get state label from row
        inFile >> rowLabel;           // skip the row label string

        for (int col = 0; col < 5; col++)    // 5 columns
        {
            EVENT = eventT(col);             // get letter label from column
            nextSTATE = getState(inFile); // get new state from table[STATE, EVENT]
            entry = makePair( makePair(STATE,EVENT), nextSTATE ); // construct an entry for transition table ADT
            table.insert(entry);              // insert entry into transition table ADT
        }
    }
}

/*******************************************************************************************
 * Function Name: loadActionTable
 *
 * Purpose: function to setup action table ADT
 *
 * Input Parameters:
 *          table: action table ADT that needs to be setup.
 *          inFile: input file stream.
 *
 * Output parameters:
 *          table: action table ADT that has been setup.
 *
 * Return Value: none.
 *******************************************************************************************/
void loadActionTable(Table< Pair<stateT,eventT>,  actionT > & table, ifstream& inFile)
{
    Pair< Pair<stateT,eventT>, actionT> entry;  // an entry of table ADT
    stateT STATE;                               // row label in action table
    eventT EVENT;                               // column label in action table
    actionT ACTION;                             // value of action_table[row, column]
    string rowLabel;                            // row label to be skipped

    // Jump to the line with actual value
    skip3Lines(inFile);

    // Read and Load all lock actions from action_table file into table ADT
    for (int row = 0; row < 7; row++)      // 7 rows
    {
        STATE = stateT(row);   // get state label from row
        inFile >> rowLabel;    // skip the row label string

        for (int col = 0; col < 5; col++)  // 5 columns
        {
            EVENT = eventT(col);           // get letter label from column

            // Get action from the table[STATE, EVENT]
            if (row == 3 || row == 6)
                ACTION = getAction(inFile); // only state ok3 and fa3 have valid actions
            else
                ACTION = (actionT)0;           // other rows have no action.

            entry = makePair( makePair(STATE,EVENT), ACTION ); // construct an entry
            table.insert(entry);             //  insert entry into action table ADT
        }
    }
}

/*******************************************************************************************
 * Function Name: verifyInput
 *
 * Purpose: function to verify input, user is given unlimited chances to enter a legal input.
 *
 * Input Parameters:
 *          input: input of char type.
 *
 * Output parameters: none.
 *
 * Return Value: none.
 *******************************************************************************************/
void verifyInput(char &input)
{
    while (!cin || (cin.peek() != '\n'))
    {
        cin.clear();
        cin.ignore(999, '\n');
        cout << "Invalid input, try again: ";
        cin >> input;
    }
}

/*******************************************************************************************
 * Function Name: getEventFormInput
 *
 * Purpose: function to get event from user input, user
 *          is given unlimited chances to enter a legal input.
 *
 * Input Parameters: none.
 *
 * Output parameters: none.
 *
 * Return Value: an enumerated type representing event input from user.
 *******************************************************************************************/
eventT getEventFormInput()
{
    while (true)
    {
        char letter;   // letter input from user
        cout << "Enter a letter: ";
        cin >> letter;
        verifyInput(letter); // input validation

        switch (letter)  // return event type according to letter
        {
            case 'A': return A;
            case 'B': return B;
            case 'C': return C;
            case 'D': return D;
            case 'E': return E;
            default:
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Please enter one of A B C D E as your input, try again.\n";
                break;
        }
    }
}

/*******************************************************************************************
 * Function Name: reCrack
 *
 * Purpose: function to prompt user if needs to unlock the lock again,
 *          return true if user enter 'y' or 'Y',
 *          return false if user enter 'n' or 'N'.
 *
 * Input Parameters: none.
 *
 * Output parameters: none.
 *
 * Return Value: either true or false.
 *******************************************************************************************/
bool reCrack()
{
    while (true)
    {
        char answer;    // input input from user
        cout << "Try Again?(Y/N) ";
        cin >> answer;
        verifyInput(answer); // input validation

        switch (answer) // map input to if exit the program or try again
        {
            case 'y':
            case 'Y': return true;
            case 'n':
            case 'N': return false;
            default:
                cin.clear();
                cin.ignore(999, '\n');
                cout << "Please enter a 'N' or 'Y'" << endl;
                break;
        }
    }
}

/*******************************************************************************************
 * Function Name: perform_Event_From_User
 *
 * Purpose: function to perform proper lock actions from user input.
 *
 * Input Parameters:
 *          transitionTable: A reference to the Table representing the transition table.
 *          actionTable: A reference to the Table representing the action table.
 *
 * Output parameters: none.
 *
 * Return Value: none.
 *******************************************************************************************/
void perform_Event_From_User(Table<Pair<stateT, eventT>, stateT> & transitionTable,
                             Table<Pair<stateT, eventT>, actionT> & actionTable)
{
    stateT myState = nke;                 // initial state
    eventT myEvent = getEventFormInput(); // letter input from user
    int passwordNum = 4;                  // 4-letter password

    // Repeatedly prompt the user to input a letter until
    // the passwordNum variable becomes 0.
    while (passwordNum > 0)
    {
        Pair<stateT, eventT> myPair(myState, myEvent); // state-event pair

        if (actionTable.lookUp(myPair) != (actionT)0 ) // if there is action with myPair
        {
            // Perform either alarm or unlock action:
            if (actionTable.lookUp(myPair) == alarm)
                cout << "*** Lock Action: Alarming ***";
            else if (actionTable.lookUp(myPair) == unlock)
                cout << "*** Lock Action: Door Unlocked! ***";
            cout << endl << endl;
        }
        else                                          // otherwise, get next state
        {
            myState = transitionTable.lookUp(myPair);   // get next state
            myEvent = getEventFormInput();              // ask user for next letter input
            myPair = makePair(myState, myEvent);        // construct a new pair from next state and event
        }

        passwordNum--;
    }
}

