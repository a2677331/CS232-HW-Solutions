/**************************************************************************
 * File name: p4driver.cpp
 * -----------------------
 * Menu/Prompt-driven test driver for Huffman algorithm.
 * This program uses the Huffman coding algorithm for file compression
 * and decompression.
 *
 * Programmer: Jian Zhong
 * Date Written: 12/7/2020
 * Date Last Revised: 12/11/2020
**************************************************************************/

#include <iostream>
#include <string>
#include "Encoding.h"
using namespace std;


/* Function Prototypes */
template<typename T>
void verifyInput(T& input);                               // Input option validation
void intro();                                             // program purpose
string menu();                                            // Main Menu
string readFile(ifstream& inFile, string prompt);         // read file from user input
string writeFile(ofstream& outFile, string prompt);       // output file to specified path
void printFreqTable(const list<info*>& freqTable);        // print frequency table
void test_huffmanTable(string& textStr, string& huffTablePath);           // test frequency table and huffman table
void test_encodeData(const string& textStr, const string& huffTablePath); // test compression
void text_decodeData();                                   // test decompression


// Main function
int main()
{
    intro();                                 // program introduction

    while (true)
    {
        string choice = menu();              // menu options
        if (choice == "Q" || choice == "q")
            break;
        else if (choice == "1")              // 1) encode option:
        {
            string textStr;                  // uncompressed text data stored in file
            string huffTablePath;            // huffman table is stored in which path
            test_huffmanTable(textStr, huffTablePath);  // construct huffman table
            test_encodeData(textStr, huffTablePath);           // encode data
        }
        else if (choice == "2")              // 2) decode option:
            text_decodeData();               // decode data
        cout << endl;
    }

    cout << "Exiting.\n";
    return 0;
}  // End of main



/*******************************************************************************************
 * Function Name: verifyInput
 *
 * Purpose: function to verify input, user is given unlimited
 *          chances to enter a legal input.
 *
 * Input Parameters:
 *          input: input of char type.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
template<typename T>
void verifyInput(T& input)
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
 * Function Name: intro
 *
 * Purpose: function to print intro msg of the program.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void intro()
{
    cout << "Welcome to CS232 Project 4: Huffman Algorithm!\n";
    cout << "This program uses the Huffman coding algorithm for compression and decompression.\n";
}

/*******************************************************************************************
 * Function Name: menu
 *
 * Purpose: function to prints a menu of choices for the user
 *           and reads/returns the user's response.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value:
 *           string type: user's response.
 *******************************************************************************************/
string menu()
{
    cout << endl;
    cout << "1) Encode data" << endl;
    cout << "2) Decode data" << endl;
    cout << endl;
    cout << "Q) quit" << endl;

    cout << endl;
    cout << "Your choice? ";
    string choice;
    cin >> choice;
    verifyInput(choice);
    return choice;
}


/*******************************************************************************************
 * Function Name: readFile
 *
 * Purpose: function to prompt user for file path and open the input file stream,
 *          the file stream then needs to be closed manually by user.
 *
 * Input Parameters:
 *                  outFile: output file stream.
 *                  prompt: prompt msg.
 * Output parameters: none.
 * Return Value:
 *               string type: input file path from user input.
 *******************************************************************************************/
string readFile(ifstream& inFile, string prompt)
{
    string fileInput;
    while (true)
    {
        cout << prompt;
        getline(cin>>ws, fileInput);
        inFile.open(fileInput);
        if (!inFile.fail()) break;
        cout << "Can't locate the file, try again.\n";
    }
    return fileInput;
}


/*******************************************************************************************
 * Function Name: writeFile
 *
 * Purpose: function to prompt user for file path and open the output file stream,
 *          the file stream then needs to be closed manually by user.
 *
 * Input Parameters:
 *                  outFile: output file stream.
 *                  prompt: prompt msg.
 * Output parameters: none.
 * Return Value:
 *                  string type: output file path from user input.
 *******************************************************************************************/
string writeFile(ofstream& outFile, string prompt)
{
    string fileInput;
    cout << prompt;
    cin >> fileInput;
    verifyInput(fileInput);
    outFile.open(fileInput);
    return fileInput;
}

/*******************************************************************************************
 * Function Name: printFreqTable
 *
 * Purpose: function to print frequency table and table's size.
 *
 * Input Parameters:
 *                  freqTable: stl list of info type.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void printFreqTable(const list<info*>& freqTable)
{
    cout << "\nPrinting Frequency Table... \nLetter  Count\n";
    for (info* item : freqTable)
        cout << "   " << item->letter << "      " << item->count << endl;
    cout << freqTable.size() << " letter frequencies found.\n";
}


/*******************************************************************************************
 * Function Name: test_huffmanTable
 *
 * Purpose: function to test building a huffman table from an uncompressed file,
 *          then the function will pass out file text data and
 *          the file path of where the huffman table stores.
 *
 * Input Parameters:
 *                string& textStr: any string parameter.
 *                string& huffTablePath: any string parameter.
 * Output parameters:
 *                string& textStr:  pass out uncompressed text data stored in file.
 *                string& HuffTablePath: pass out file path of the huffman table stored.
 * Return Value: none.
 *******************************************************************************************/
void test_huffmanTable(string& textStr, string& huffTablePath)
{
    ifstream inFile;       // input file stream
    ofstream outFile;      // output file stream
    string inFilePath;     // file path contains original text
    int count = 0;         // number of encodings found

    // Build and Print Frequency table:
    inFilePath = readFile(inFile, "Enter text file name(end with '*'): ");   // open file to be compressed
    list<info*> freqTable = buildFreqTable(inFile, textStr);  // get Huffman Table
    cout << "Text read: " << textStr << "*\n";
    printFreqTable(freqTable);  // print Frequency table:

    // Output Huffman table to file:
    huffTablePath = writeFile(outFile, "\nEnter name of file to store the Huffman table: "); // get huffman table path from user
    info* huffTree = HuffTree_from_FreqTable(freqTable);   // generate huffman tree from frequency table
    genHuffTable(huffTree, outFile, cout, count);    // output huffman table to text file
    cout << count << " character encodings found.\n";
    cout << "Table above has been stored to " << huffTablePath << endl;
    freeTree(huffTree);         // free huffman tree's allocated memory
    inFile.close();
    outFile.close();
}

/*******************************************************************************************
 * Function Name: test_encodeData
 *
 * Purpose: function to test encoding data from an uncompressed file and huffman table.
 *
 * Input Parameters:
 *                string& textStr: uncompressed text data stored in file.
 *                string& huffTablePath: file path of the huffman table.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void test_encodeData(const string& textStr, const string& huffTablePath)
{
    ifstream inFile;       // input file stream
    ofstream outFile;      // output file stream
    string encodePath;     // file path to store encoded msg

    // Write encoded msg to file:
    cout << "\nCreating Huffman coding...\n";
    encodePath = writeFile(outFile, "Enter the file name to hold the encoded msg: ");
    encodeData(huffTablePath, textStr, inFile, outFile, cout);  // build encoding from huffman table
    cout << "\nEncoded msg above has been stored to " << encodePath << endl;
    inFile.close();
    outFile.close();
}

/*******************************************************************************************
 * Function Name: text_decodeData
 *
 * Purpose: function to test decoding data from encoding msg and its huffman table.
 *
 * Input Parameters: none.
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void text_decodeData()
{
    ifstream inFile;

    // Get Huffman tree from Huffman table:
    readFile(inFile, "Enter Huffman table file name: ");
    info* encodingTree = HuffTree_from_HuffTable(inFile);   // build Huffman tree from Huffman table
    treeGraph(cout, 1, encodingTree);                // print the Tree to console
    inFile.close();

    // Decompressing file:
    cout << "\nDecompressing file...";
    readFile(inFile, "\nEnter compressed msg file name: ");
    decodeData(encodingTree, inFile);       // decode data from encoded file and Huffman tree
    freeTree(encodingTree);                    // free encoding tree's allocated memory
    inFile.close();
}

