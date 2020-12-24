// Jian Zhong
// Prof. Streller
// CS232 Lab1
// 09/10/2020
// cs232_lab1_ZHONG.cpp

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

template <typename T>
void msSort(T* arrayptr, const int& arraySize); // algorithm for sorting blocks
const size_t MAX_MEM_SIZE = 20;  // max memory size
const size_t TOTAL_SIZE = 120;   // total data size

// Function Prototypes:
int* readBlockFromFile(ifstream& in);
void storeToFile(int* arrPtr, ofstream& out);
void setupFiles(ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2);
void closeFiles(ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2);
void mergeRuns(int& record1, int& record2, size_t runSize, ifstream& inFile1, ifstream& inFile2, ofstream& outFile);
void mergeFiles(ifstream& inFile1, ifstream& inFile2, ofstream& outFile);
void splitFiles(int& blockNum, ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2);
void mergeFileRuns(int times, ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2);
void askUserForInputFile(string prompt, ifstream& inFile);

// Main Function:
int main() {
    ifstream inFile1, inFile2;
    ofstream outFile1, outFile2;
    int blockNum = TOTAL_SIZE / MAX_MEM_SIZE;  // block number specified by memory size

    // Open source files to read data:
    setupFiles(inFile1, inFile2, outFile1, outFile2);

    // Split files into blocks:
    splitFiles(blockNum, inFile1, inFile2, outFile1, outFile2);

    // Merge runs from outFile1 and outFile2  to  inFile1 and inFile2:
    inFile1.open("outFile1.txt");      // open necessary files in correct read/write mode
    inFile2.open("outFile2.txt");
    outFile1.open("inFile1.txt");
    outFile2.open("inFile2.txt");
    mergeFileRuns(0, inFile1, inFile2, outFile1, outFile2);     // Merge runs
    closeFiles(inFile1, inFile2, outFile1, outFile2);           // close all files

    // Now merge runs from inFile1 and inFile2  to  outFile1 and outFile2:
    inFile1.open("inFile1.txt");       // open necessary files in correct read/write mode in reverse
    inFile2.open("inFile2.txt");
    outFile1.open("outFile1.txt");
    outFile2.open("outFIle2.txt");
    mergeFileRuns(1, inFile1, inFile2, outFile1, outFile2);     // Merge runs
    closeFiles(inFile1, inFile2, outFile1, outFile2);           // close all files

    // Finally, merge from outFile1 and outFile2  to  Sorted.txt:
    inFile1.open("outFile1.txt");      // open necessary files in correct read/write mode
    inFile2.open("outFile2.txt");
    outFile1.open("Sorted.txt");
    mergeFiles(inFile1, inFile2, outFile1);                     // Merge runs
    closeFiles(inFile1, inFile2, outFile1, outFile2);           // close all files

    cout << "Final result is in \"Sorted.txt\"." << endl;
    cout << "Have a good day!" << endl;
    return 0;
}  /* end of main */


/// Opens a text file whose name is entered by the user.
/// If the file does not exist, the user is given additional chances to enter a valid file.
/// @param prompt used to tell the user what kind of file is required.
/// @param inFile input file stream
void askUserForInputFile(string prompt, ifstream& inFile)
{
    while (true)
    {
        string file;
        cout << prompt;
        getline(cin, file);
        inFile.open(file); // trying to open file path
        if (!inFile.fail()) break;
        cout << "Unable to locate file \"" << file << "\""<< endl;
        inFile.clear(); // recover from input file failure
    }
}

/// Open files and check if it is correctly opened.
/// @param inFile1 first input file
/// @param inFile2 second input file
/// @param outFile1 first output file
/// @param outFile2 second output file
void setupFiles(ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2)
{
    askUserForInputFile("Input file(data.txt)? ", inFile1);
    inFile2.open("inFile2.txt");        // open all the necessary files for sorting
    outFile1.open("outFile1.txt");
    outFile2.open("outFile2.txt");
    cout << " *** File loaded successfully ***" << endl;
}

/// Close all the opened file.
/// @param inFile1 first input file
/// @param inFile2 second input file
/// @param outFile1 first output file
/// @param outFile2 second output file
void closeFiles(ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2)
{
    inFile1.close();
    inFile2.close();
    outFile1.close();
    outFile2.close();
}

/// Merge all runs from two input files into two output files
/// @param times the # of runs in input files
/// @param inFile1 first input file
/// @param inFile2 second input file
/// @param outFile1 first output file
/// @param outFile2 second output file
void mergeFileRuns(int times, ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2)
{
    int record1, record2;  // data in file1 and file2
    inFile1 >> record1;    //  read data1 from outFile1
    inFile2 >> record2;    //  read data2 from outFile2
    int whoseTurn = 0;     //  needed for alternately place in the two files
    size_t runSize = MAX_MEM_SIZE * pow(2.0, times); // the size of each run inside a file

    while (!inFile1.eof() && !inFile2.eof())    // while neither the end inFile 1 nor inFile 2
    {
        if (whoseTurn % 2 == 0)  // alternately place run in the outFile1 and outFile2
            mergeRuns(record1, record2, runSize, inFile1, inFile2, outFile1); // merge runs into output file 1
        else
            mergeRuns(record1, record2, runSize, inFile1, inFile2, outFile2); // merge runs into output file 2
        whoseTurn++;
    }

    if (inFile1.eof()) {                        // Now reach the end of inFile 1 or inFile 2, copy the rest if necessarily
        while (!inFile2.eof())
        {
            outFile1 << record2 << "  ";
            inFile2 >> record2;
        }
    }
    else if (inFile2.eof())
    {
        while (!inFile1.eof())
        {
            outFile2 << record1 << "  ";
            inFile1 >> record1;
        }
    }
}

/// Merge two runs in terms of run size in two sub files and produce output into a output file.
/// @param record1 data in input file1
/// @param record2 data in input file2
/// @param runSize run number in a file
/// @param inFile1 first input file
/// @param inFile2 second input file
/// @param outFile output file stream
void mergeRuns(int& record1, int& record2, size_t runSize,
               ifstream& inFile1, ifstream& inFile2, ofstream& outFile)
{
    int i1 = 0, i2 = 0;   // merge runs into outFile from inFile1 and inFile2
    while (i1 < runSize && i2 < runSize)
    {
        if (record1 < record2)             // take whichever record is smaller
        {
            outFile << record1 << "  ";    // take out from outFile1
            inFile1 >> record1;
            i1++;
        }
        else {
            outFile << record2 << "  ";    // take out from outFile2
            inFile2 >> record2;
            i2++;
        }
    }

    if (i1 >= runSize)     // if either end of run is encountered, copy another's remaining.
    {
        while (i2 < runSize)
        {
            outFile << record2 << "  ";
            inFile2 >> record2;
            i2++;
        }
    }
    else if (i2 >= runSize)
    {
        while (i1 < runSize)
        {
            outFile << record1 << "  ";
            inFile1 >> record1;
            i1++;
        }
    }
}

/// Read a block of data from an input file,
/// and return a pointer to a dynamic array containing that block.
/// @param in input file stream
int* readBlockFromFile(ifstream& in)
{
    int* blockArray = new int[MAX_MEM_SIZE];
    int record;

    for (int i = 0; i < MAX_MEM_SIZE; i++)    // read (20 ints)1 block from file
    {
        in >> record;
        blockArray[i] = record;
    }

    return blockArray;
}

/// Store the a dynamic array into an output file stream.
/// @param arrPtr pointer to a dynamic array of int
/// @param out output fie stream
void storeToFile(int* arrPtr, ofstream& out)
{
    for (int i = 0; i < MAX_MEM_SIZE; i++) // store 1 block in outFile1.
        out << arrPtr[i] << "  ";
}

/// Produce final sorted results from two input file stream.
/// @param inFile1 first input file
/// @param inFile2 second input file
/// @param outFile output file stream
void mergeFiles(ifstream& inFile1, ifstream& inFile2, ofstream& outFile)
{
    int x, y;
    inFile1 >> x;
    inFile2 >> y;
    while (!inFile1.eof() && !inFile2.eof()) // Read from files and place the smaller into outFile.
    {
        if (x < y)
        {
            outFile << x << "  ";
            inFile1 >> x;
        }
        else
        {
            outFile << y << "  ";
            inFile2 >> y;
        }
    }

    if (inFile1.eof())  // if either end of file is encountered, copy another's remaining.
    {
        while (!inFile2.eof())
        {
            outFile << y << " ";
            inFile2 >> y;
        }
    }
    else if (inFile2.eof())
    {
        while (!inFile1.eof())
        {
            outFile << x << " ";
            inFile1 >> x;
        }
    }
}

/// Split files into blocks:
/// @param blockNum number of unsorted block in a file
/// @param inFile1 first input file
/// @param inFile2 second input file
/// @param outFile1 first output file
/// @param outFile2 second output file
void splitFiles(int& blockNum, ifstream& inFile1, ifstream& inFile2, ofstream& outFile1, ofstream& outFile2)
{
    // Split the source file into 2 other sub-files, sort it, and alternately place in outFile1 and outFile2:
    for (int i = 0; i < blockNum / 2; i++)  // 3 runs in each sub file.
    {
        // Read 1 block(20 ints) from inFile1, sort it, store in outFile1.
        int* blockArray1 = readBlockFromFile(inFile1);  // Read 20 ints(1 block) from source file
        msSort(blockArray1, MAX_MEM_SIZE);                 // sort it
        storeToFile(blockArray1, outFile1);             // store the first run in outFile1.

        // Read 1 block(20 ints) from inFile1, sort it, store in outFile2.
        int* blockArray2 = readBlockFromFile(inFile1);  // Read 20 ints(1 block) from source file
        msSort(blockArray2, MAX_MEM_SIZE);                 // sort it
        storeToFile(blockArray2, outFile2);             // store the first run in outFile2.
    }
    closeFiles(inFile1, inFile2, outFile1, outFile2); // Close all opened files
}

/// Merge sort algorithm:
template <typename T>
void merge2(T* source, T* arrayptr, int l, int mid, int r)
{
    int i = l;
    int j = mid + 1;
    int k = l;

    while ((i <= mid) && (j <= r))       // Compare current item from each list
        if (source[i] < source[j])          // Then i item comes first
            arrayptr[k++] = source[i++];
        else                                      // j item comes first
            arrayptr[k++] = source[j++];
    // Move what is left of remaining list

    if (i > mid)
        while (j <= r)
            arrayptr[k++] = source[j++];
    else
        while (i <= mid)
            arrayptr[k++] = source[i++];
}

template <typename T>
void mergesort2(T* source, T* dest, int l, int r)
{
    if (l != r)
    {
        int mid = (l + r) / 2;
        mergesort2(dest, source, l, mid);
        mergesort2(dest, source, mid + 1, r);
        merge2(source, dest, l, mid, r);
    }
}

template <typename T>
void msSort(T* arrayptr, const int& arraySize)
{
    T* copy = new T[arraySize];
    int i;
    for (i = 0; i < arraySize; i++)
        copy[i] = arrayptr[i];

    mergesort2(copy, arrayptr, 0, arraySize - 1);
}
