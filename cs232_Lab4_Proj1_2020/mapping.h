/**************************************************************************
 * File name: mapping.h
 * --------------------
 * This file contains the mapping function for the Table class.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/01/2020
 * Date Last Revised: 10/14/2020
**************************************************************************/

#ifndef MAPPING_H
#define MAPPING_H

#include "lockTypes.h"
#include "table.h"

/* Index function for Table class */
int mappingOfData(Pair<stateT, eventT > pair);

#endif //MAPPING_H
