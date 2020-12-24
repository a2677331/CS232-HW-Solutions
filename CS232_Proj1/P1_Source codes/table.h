/**************************************************************************
 * File name: table.h
 * ------------------
 * This file defines the Table class, which implements the table ADT.
 *
 * Programmer: Jian Zhong
 * Date Written: 10/01/2020
 * Date Last Revised: 10/14/2020
 **************************************************************************/

#ifndef  TABLE_H
#define  TABLE_H

#include <stdexcept>
#include "pair.h"    // Pair class

template<class Key, typename T>
class Table
{
public:
    typedef Key key_type;           // for convenience

/* Private section */
private:
    int tableCapacity;              // total size of the table
    int tableSize;                  // current size of the table
    Pair<key_type, T> *the_table;   // a dynamic array pointer to table array

    /* Index function: to map table pair into array index */
    int (*Mapping)(Key k);

    /* Perform deep copy from initTable */
    void deepCopy(const Table& initTable);

/* Public section */
public:
    /* Constructor */
    Table(int n, int (*map)(Key k));

    /* Destructor */
    ~Table();

    /* Copy Constructor */
    Table(const Table& initTable);

    /* Overload Assignment Operator */
    Table &operator=(const Table& initTable);

    /* Insert a key into table */
    bool insert(Pair<Key, T> kvpair);

    /* Remove a key from table */
    bool remove(const Key aKey);

    /* Look up a key in table */
    T lookUp(const Key aKey);

    /* Return true if table contains a key */
    bool isIn(const Key &key) const;

    /* Return true if table is empty */
    bool empty() const;

    /* Return current size of the table */
    int size() const;

    /* Return true if the table is full */
    bool full() const;

}; /* end of Table class */

#include "table.t"

#endif