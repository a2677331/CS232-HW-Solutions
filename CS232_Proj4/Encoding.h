/**********************************************************************
 * File name: Encoding.h
 * ----------------------
 * This file implements the info node structure that will use in Huffman
 * encoding tree and declares various utility functions that implements
 * the Huffman algorithm.
 *
 * Programmer: Jian Zhong
 * Date Written: 12/7/2020
 * Date Last Revised: 12/11/2020
 **********************************************************************/

#ifndef ENCODING_H
#define ENCODING_H

#include <list>        // list<info> freqTable
#include <algorithm>   // freqTable.sort
#include <cctype>      // isalpha
#include <string>      // encode.substr
#include <iomanip>     // setw
#include <iostream>    // cout, out
#include <fstream>     // inFile, outFile
using namespace std;


/* Type: info
 * A node inside a Huffman encoding tree.
 * Each node stores four values:  the character,
 * pointers to the 0 and 1 subtrees,
 * and the character count (weight) of the tree.
 */
struct info {
    char letter;  // letter being represented by this node
    int count;    // number of occurrences of that letter
    info *lLink;  // 0 (left) subtree (NULL if empty)
    info *rLink;  // 1 (right) subtree (NULL if empty)

    /*
     * Constructs a new node to store the given letter and its count,
     * along with the given child pointers.
     */
    explicit info (char letter = '*', int count = 0, info* lLink = nullptr, info* rLink = nullptr)
    {
        this->letter = letter;
        this->count = count;
        this->lLink = lLink;
        this->rLink = rLink;
    }
};


// Build frequency table from input file stream and return the table back to caller.
list<info*> buildFreqTable(ifstream& inFile, string& textData);

// Add new letter or increase existing letter's frequency count in frequency table.
void addOrIncrease(list<info*> & freqTable, const char& letter);

// Build Huffman Tree recursively from a given frequency table.
info* HuffTree_from_FreqTable(list<info*> & freqTable);

// Build Huffman Table(encoding) from Huffman encoding tree.
void genHuffTable(info* huffTreeNode, ofstream& outFile, ostream& out, int& count);

// Recursive utility which does the actual work of building the Huffman table.
void recGenHuffTable(info* huffTreeNode, string encode, ofstream& outFile, ostream& out, int& count);

// Build Huffman Tree from a file stores Huffman table(encoding).
info* HuffTree_from_HuffTable(ifstream& inFile);

// Insert a letter into tree and build tree 0-1 branch along the path.
void insertLetterNode(string& encode, const char& letter, info* & node);

// Encode text data in file from a given Huffman table and output encoding to console and file.
void encodeData(const string& H_TablePath, const string& textStr, ifstream& inFile, ofstream& outFile, ostream& out);

// Decode text data from a given file by using given encoding tree.
void decodeData(info* encodingTree, ifstream& inFile);

// Function to print an indented horizontal view of the tree.
void treeGraph(ostream& out, int indent, info* node);

// Comparison function for sorting nodes in frequency table.
bool comp(info* lhs, info* rhs);

// Free memory occupied by encoding tree.
void freeTree(info* node);

#endif //ENCODING_H