/**************************************************************************
 * File name: mapping.cpp
 * ----------------------
 * This file contains the implementation of mappingOfData function.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/01/2020
 * Date Last Revised: 10/14/2020
**************************************************************************/

#include "mapping.h"

/*******************************************************************************************
 * Function Name: mappingOfData
 *
 * Purpose: Function to map a given table entry into one-dimensional array index.
 *          array index = n * i + j
 *          n is total columns of the table
 *          i is current element's row
 *          j is current element's col
 *
 * Input Parameters:
 *          pair: a key-value pair from pair.h
 *
 * Output parameters: none.
 *
 * Return Value:
 *          index of an array for the specified element within the table.
 ********************************************************************************************/
int mappingOfData(Pair<stateT, eventT > pair)
{
    return 5 * pair.first + pair.second;
}