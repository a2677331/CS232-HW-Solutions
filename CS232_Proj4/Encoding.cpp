/**********************************************************************
 * File name: Encoding.cpp
 * -----------------------
 * This file implements various utility functions that implements
 * the Huffman algorithm.
 *
 * Programmer: Jian Zhong
 * Date Written: 12/7/2020
 * Date Last Revised: 12/11/2020
 **********************************************************************/

#include "Encoding.h"

/*******************************************************************************************
 * Function Name: buildFreqTable
 *
 * Purpose: function to build frequency table from input file stream and
 *          return a the table back to caller.
 *
 *          First, read all letters in file, construct frequency table by counting
 *          frequency of different letters. After reading all letters,
 *          sort them in ascending order.
 *          Note: the file must be ending with '*'.
 *
 * Input Parameters:
 *          inFile: input file steam.
 *          textData: text data from input file.
 *
 * Output parameters:
 *          textData: all text in file will be stored in this string.
 * Return Value:
 *          list<info*> type: frequency table of info pointers.
 *******************************************************************************************/
list<info*> buildFreqTable(ifstream& inFile, string& textData)
{
    // Building Frequency Table:
    list<info*> freqTable;    // frequency table of letter count
    string textStr;           // text data in input file
    for (char ch = inFile.get(); ch != '*'; ch = inFile.get())  // read letter one by one
        if (isalpha(ch))      // only want letter
        {                     // add new letter or increase frequency count
            addOrIncrease(freqTable, toupper(ch));
            textData += ch;   // collect text data store in file
        }

    // Sort in ascending order after read in:
    freqTable.sort(comp);

//    std::sort(freqTable.begin(), freqTable.end());  // ⚠️ You can't use std::sort to sort std::list, because std::sort requires iterators to be random access, and std::list iterators are only bidirectional.
    return freqTable;         // return completed Huffman Table
}


/*******************************************************************************************
 * Function Name: addOrIncrease
 *
 * Purpose: function to add new letter or increase existing letter's frequency count
 *          in frequency table.
 *
 *          First, read letter from file one at a time. Second, check frequency table,
 *          if already exists, increase the count, if not in table, add to table.
 *
 * Input Parameters:
 *          freqTable: frequency table.
 *          letter: text letter.
 *
 * Output parameters:
 *          freqTable: the table has been modified either by adding a new letter or
 *                      increasing existing letter's count by one.
 * Return Value: none.
 *******************************************************************************************/
void addOrIncrease(list<info*> & freqTable, const char& letter)
{
    bool found = false;             // letter found or not

    for (info* & item : freqTable)
        if (item->letter == letter) // Search through the table
        {
            item->count++;          // if letter found, increase count.
            found = true;
            break;
        }

    if (!found)                     // if not found, then add.
    {
        info* newLetter = new info (letter, 1, nullptr, nullptr);  // construct new letter obj
        freqTable.push_back(newLetter);
    }
}


/*******************************************************************************************
 * Function Name: HuffTree_from_FreqTable
 *
 * Purpose: function to build Huffman Tree recursively from a given frequency table.
 *
 *          Huffman tree is built recursively from two least frequency nodes
 *          in frequency table, and is completed when only one node(root of Huffman tree)
 *          left in frequency table.
 *
 * Input Parameters:
 *          freqTable: frequency table passed by reference.
 *
 * Output parameters: none.
 * Return Value:
 *          info* type: the root pointer to the constructed Huffman Tree.
 *******************************************************************************************/
info* HuffTree_from_FreqTable(list<info*> & freqTable)
{
    // If one item left in freqTable, complete building huffTree:
    if (freqTable.size() == 1)
        return freqTable.front();

    // Build new tree from first two node/tree from freqTable:
    info* huffTree = new info();                // create a new tree node
    huffTree->lLink = freqTable.front();        // setup left link
    int leftCount = freqTable.front()->count;   // get left count
    freqTable.pop_front();                      // remove from freq table

    huffTree->rLink = freqTable.front();        // setup right link
    int rightCount = freqTable.front()->count;  // get right count
    freqTable.pop_front();                      // remove from freq table
    huffTree->count = leftCount + rightCount;   // setup total count

    // Add new tree back and reorder freqTable:
    freqTable.push_back(huffTree);              // add into freqTable
    freqTable.sort(comp);                       // sort in increasing order

    // Proceed by recursion:
    return HuffTree_from_FreqTable(freqTable);
}


/*******************************************************************************************
 * Function Name: recGenHuffTable
 *
 * Purpose: function to build Huffman Table(encoding) from Huffman encoding tree.
 *
 *          This function does the actual work of building the Huffman Table
 *          from a given Huffman table, if letter found, then output the encode,
 *          otherwise, move down the tree and collect encodes until the leaf.
 *
 *          Letter and count would be output to both console and file.
 *
 * Input Parameters:
 *          huffTreeNode: info pointer to huffman tree root.
 *          encode: encoded msg of a letter.
 *          outFile: output file stream.
 *          out: output stream.
 *          count: count the number of encoded letters in file.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void recGenHuffTable(info* huffTreeNode, string encode, ofstream& outFile, ostream& out, int& count)
{
    if (isalpha(huffTreeNode->letter))  // if meets letter
    {
        outFile << huffTreeNode->letter << "  " << encode << endl; // write encodes
        out << huffTreeNode->letter << "  " << encode << endl;     // also print console
        count++;
    }

    if (huffTreeNode->lLink)            // Moving down the tree to collect encoding:
        recGenHuffTable(huffTreeNode->lLink, encode + "0", outFile, out, count);
    if (huffTreeNode->rLink)
        recGenHuffTable(huffTreeNode->rLink, encode + "1", outFile, out, count);
}


/*******************************************************************************************
 * Function Name: genHuffTable
 *
 * Purpose: function to build Huffman Table(encoding) from Huffman encoding tree.
 *
 *          This function uses recGenHuffTable to do actual work of building.
 *          It passes an empty encode string by reference as a starter to make encode.
 *          After finish building, ending symbol '*' is added to file.
 *
 * Input Parameters:
 *          huffTreeNode: info pointer to huffman tree root.
 *          outFile: output file stream.
 *          out: output stream.
 *          count: count the number of encoded letters in file.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void genHuffTable(info* huffTreeNode, ofstream& outFile, ostream& out, int& count)
{
    string encode; // encode string


    // generate Huffman table and write to file
    recGenHuffTable(huffTreeNode, encode = "", outFile, out, count);
    outFile << '*';    // add ending symbol
}


/*******************************************************************************************
 * Function Name: encodeData
 *
 * Purpose: function to encode text data from a text file and a given Huffman table,
 *          and the encoded data would be output to console and another file.
 *
 *          First, search through encode of each letter in huffman table file.
 *          Second, find the encode of each character from the textStr,
 *          Third, output to console and file.
 *
 * Input Parameters:
 *          H_TablePath: Huffman table file path.
 *          textStr: text data in input file.
 *          inFile: input file stream.
 *          outFile: output file stream.
 *          out: output stream.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void encodeData(const string& H_TablePath, const string& textStr, ifstream& inFile, ofstream& outFile, ostream& out)
{
    char key;                     // key letter in huffman table
    string encode;                // encoded data
    inFile.open(H_TablePath);     // open huffman table file

    for (char letter : textStr)   // check each letter to be encoded
    {
        while(inFile >> key)                // search through huffman table
            if (key == toupper(letter))     // if found corresponding key
            {
                inFile >> encode;           // obtain its encode
                outFile << encode;          // write out encoded data to file
                out << encode;              // also print to console
                break;
            }
            else
                inFile.ignore(999, '\n'); // skip the line

        inFile.clear();                           // return back to the file's beginning
        inFile.seekg(0, ios::beg);
    }
}


/*******************************************************************************************
 * Function Name: HuffTree_from_HuffTable
 *
 * Purpose: function to build a Huffman Tree from a file contains Huffman table(encoding).
 *
 *          First read a letter and its encode in file,
 *          then construct Huffman tree. Stop reading when meets a '*' symbol.
 *          The encoding file must contain a '*' ending symbol.
 *
 * Input Parameters:
 *          inFile: input file stream.
 *
 * Output parameters: none.
 * Return Value:
 *          info*: pointer to encodingTree's root node.
 *******************************************************************************************/
info* HuffTree_from_HuffTable(ifstream& inFile)
{
    char letter;                      // letter in encoding table
    string encode;                    // encode in encoding table
    info* encodingTree = new info();  // Huffman Tree from encode file

    while (inFile >> letter)         // for each letter
    {
        if (letter == '*') break;    // stop when meets * symbol
        inFile >> encode;            // get encode
        insertLetterNode(encode, letter, encodingTree);  // insert a letter node into tree
    }
    return encodingTree;
}


/*******************************************************************************************
 * Function Name: insertLetterNode
 *
 * Purpose: function to insert a letter into tree and
 *          build 0-1 tree branch along the path from that letter's encode.
 *
 *          First read in letter, second read encode one by one and recursively
 *          build 0 branch or 1 branch according to it. Lastly, add the letter at leaf.
 *
 * Input Parameters:
 *          letter: character.
 *          encode: encoding of that character.
 *          node: pointer to encoding tree node.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void insertLetterNode(string& encode, const char& letter, info* & node)
{
    if (encode.empty())                 // if no encode left
    {
        node = new info(letter);        // insert the letter at tree leaf
        return;                         // complete building one letter's branch!
    }

    if (encode[0] == '0')               // moving left
    {
        encode = encode.substr(1);  // remove the checked digit in encode
        if (node->lLink == nullptr)
            node->lLink = new info();    // insert '*' symbol along the left branch
        insertLetterNode(encode, letter, node->lLink);
    }
    else                                // moving right
    {
        encode = encode.substr(1);  // remove the checked digit in encode
        if (node->rLink == nullptr)
            node->rLink = new info();   // insert '*' symbol along the right branch
        insertLetterNode(encode, letter, node->rLink);
    }
}


/*******************************************************************************************
 * Function Name: decodeData
 *
 * Purpose: function to decode text data from input file and encoding tree.
 *          First read in a file, then use encoding tree to
 *          move along the tree to find letter and output to console when found.
 *
 * Input Parameters:
 *          encodingTree: info pointer to encoding tree.
 *          inFile: input file stream.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void decodeData(info* encodingTree, ifstream& inFile)
{
    char encode;                     // encode from encoding file
    info* currP = encodingTree;

    while (inFile >> encode)         // read encode one by one
    {
        if (encode == '0')           //  moving
            currP = currP->lLink;
        else
            currP = currP->rLink;

        if (currP->letter != '*')     // letter found!
        {
            cout << currP->letter;    // output to file
            currP = encodingTree;     // back to the root of the tree
        }
    }
}


/*******************************************************************************************
 * Function Name: treeGraph
 *
 * Purpose: function to print an indented horizontal view of the tree of
 *          info nodes with the given node as its root.
 *
 * Input Parameters:
 *          out: output file stream to console.
 *          indent: int type, indent size of printing format.
 *          node: info type, pointer to root node.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void treeGraph(ostream& out, int indent, info* node)
{
    if (node)
    {
        treeGraph(out, indent + 8, node->rLink);
        out << setw(indent) << "'" << node->letter << "'" << endl;
        treeGraph(out, indent + 8, node->lLink);
    }
}


/*******************************************************************************************
 * Function Name: comp
 *
 * Purpose: Comparison function so that nodes in frequency table
 *          would be properly arranged by conventions below.
 *
 * Comparison conventions:
 *      1) smaller on left
 *      2) if alpha chars frequency is the same, use lexicographical ordering to
 *         determine smaller if alpha and a Tree still smaller on left.
 *      3) if alpha and Tree have same frequency, alpha on left
 *      4) if both Trees have same frequency, lower numbered Tree on the left
 *
 * Input Parameters:
 *          lhs: info object pointer on the left side when comparing.
 *          rhs: info object pointer on the right side when comparing.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
bool comp(info* lhs, info* rhs)
{
    // put alpha on left if alpha and Tree have same frequency
    if (lhs->count == rhs->count)
    {
        if (lhs->letter == '*' && rhs->letter != '*')
            return lhs->letter > rhs->letter;
        if (rhs->letter == '*' && lhs->letter != '*')
            return lhs->letter > rhs->letter;
    }

    // if count is the same, then compare the letter, otherwise just compare count
    if (lhs->count == rhs->count)
        return lhs->letter < rhs->letter;
    else
        return lhs->count < rhs->count;
}


/*******************************************************************************************
 * Function Name: freeTree
 *
 * Purpose: function to free memory occupied by encoding tree.
 *
 * Input Parameters:
 *          node: pointer to info object.
 *
 * Output parameters: none.
 * Return Value: none.
 *******************************************************************************************/
void freeTree(info* node)
{
    if (node != nullptr)
    {   // post-order moving
        freeTree(node->lLink);
        freeTree(node->rLink);
        delete node;  // deallocate node's memory
    }
}