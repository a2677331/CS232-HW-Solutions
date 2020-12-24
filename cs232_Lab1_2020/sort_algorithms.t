

/*****************************************************************************************
*
*   File name:			sort_algorithms.t
*
*   This file contains the implementations of basic sorting algorithms
*
*
*   Programmer:			B.J. Streller
*
*   Date Written:		June 2009
*
*   Date Last Revised:		March 2010 - added mergesort algorithms
*
******************************************************************************************/



#ifndef SORT_ALGORITHMS_T__
#define SORT_ALGORITHMS_T__


#include <cstdio>
#include <cstdlib>
#include <fstream>
using std::fstream;
using std::streampos;

#include <iostream>
using std::ios;
using std::endl;





/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void swap( T &a, T &b )
{
  T temp = a;

  a = b;
  b = temp;
}


/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void selectSort( T* arrayptr, int arraySize,  bool ( *cmp )( T &baseData1, T &baseData2 ) )
{
  int smallindex; // index of smallest element in the sublist
  int pass, j;

  // pass has the range 0 to n-2
  for ( pass = 0; pass < arraySize - 1; pass++ )
    {
      // scan the sublist starting at index pass
      smallindex = pass;

      // j traverses the sublist arrayptr[pass+1] to aarrayptr[n-1]
      for ( j = pass + 1; j < arraySize; j++ )
        // update if smaller element found
        if ( cmp ( arrayptr[j], arrayptr[smallindex] ) )
          smallindex = j;

      // when finished,  exchange smallest item with arrayptr[pass]
      swap( arrayptr[pass], arrayptr[smallindex] );
    }
}


/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void doubleSeletcSort( T* arrayptr, int arraySize,  bool ( *cmp )( T &baseData1, T &baseData2 ) )
{
  // index of smallest and largest elements in a sublist
  int smallIndex, largeIndex;
  int i, j, k;
  T temp;

  // start indices
  i = 0;
  j =  arraySize - 1;
  // as long as i < j
  while (i < j)
    {
      // scan the sublist {arrayptr[i], ..., arrayptr[j]}
      smallIndex = i;
      largeIndex = i;

      // k traverses the sublist {arrayptr[i+1], ..., arrayptr[j]}
      for (k = i+1; k <= j; k++)
        // update if smaller element found
        if (  cmp( arrayptr[k], arrayptr[smallIndex] )    )
          smallIndex = k;
      // update if larger element found
        else if (  cmp( arrayptr[largeIndex], arrayptr[k] )  )
          largeIndex = k;

      // if smallIndex and i are not the same location,
      // swap smallest item in the sublist with arrayptr[i]
      if (smallIndex != i)
        {
          swap( arrayptr[i], arrayptr[smallIndex] );

          // at index i, arrayptr[i] maybe largest element
          // if so, swap moves the largest value to index smallIndex
          if (largeIndex == i)
            largeIndex = smallIndex;
        }

      // if largeIndex and j are not the same location,
      // swap largest item in the sublist with arrayptr[j]
      if (largeIndex != j)
        {
          swap( arrayptr[j], arrayptr[largeIndex]  );
        }

      // move i forward and j backward
      i++;
      j--;
    }
}


/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void insertionSort( T* arrayptr, int arraySize,  bool ( *cmp )( T &baseData1, T &baseData2 )   )
{
  int i, j;
  T target;

  // place arrayptr[i] into the sublist
  //   arrayptr[0] ... arrayptr[i-1], 1 <= i < n,
  // so it is in the correct position
  for (i = 1; i <  arraySize; i++)
    {
      // index j scans down list from arrayptr[i] looking for
      // correct position to locate target. assigns it to
      // arrayptr[j]
      j = i;
      target = arrayptr[i];
      // locate insertion point by scanning downward as long
      // as target < arrayptr[j-1] and we have not encountered the
      // beginning of the list
      while (j > 0 && target < arrayptr[j-1])
        {
          // shift elements up list to make room for insertion
          arrayptr[j] = arrayptr[j-1];
          j--;
        }
      // the location is found; insert target
      arrayptr[j] = target;
    }
}


/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void bubbleSort( T* arrayptr, int arraySize,  bool ( *cmp )( T &baseData1, T &baseData2 ) )
{
  register int i,j;
  // index of last exchange
  bool did_swap = true;

  // i is the index of last element in the current sublist
  i = arraySize - 1;

  // continue the process until we make no exchanges or
  // we have made n-1 passes
  while ( i > 0 && did_swap )
    {
      // assume no exchange occurs
      did_swap = false;

      // scan the sublist arr[0] to arr[i]
      for ( j = 0; j < i; j++ )
        // exchange a pair and assign true to exchangeOccurs
        if ( cmp( arrayptr[j + 1], arrayptr[j] ) )
          {
            swap( arrayptr[ j ], arrayptr[ j+1 ] );
            did_swap = true;
          }
      // move i downward one element
      i--;
    }
}



/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/



template <typename T>
void basicBubbleSort( T* arrayptr, int arraySize,  bool ( *cmp )( T &baseData1, T &baseData2 ) )
{
  register int i,j;

  for ( i = 1; i < arraySize; i++ )
    {
      for ( j = arraySize - 1; j >= i; j-- )
        {
          if  ( cmp( arrayptr[ j ], arrayptr[ j - 1 ] )  )
            swap( arrayptr[ j -1 ] , arrayptr[ j ]   );
        }

    }

}



/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void mergesort1(T* arrayptr, const int& arraySize )
{
  sortmerge1( arrayptr, arraySize, 0, arraySize - 1 );
}



/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void sortmerge1( T* arrayptr, const int& arraySize, int l, int r )
{

  int mid, i, j, k;



  if ( l < r )
    {
      mid = (r + l)/2;

      sortmerge1( arrayptr, arraySize, l, mid );
      sortmerge1( arrayptr, arraySize, mid + 1, r );

      T* temp = new T[ arraySize ]; 

      for ( i = mid + 1; i > l; i-- )
        temp[ i - 1 ]= arrayptr[ i - 1 ];

      for ( j = mid; j < r; j++ )
        temp[ r + mid - j ] = arrayptr[ j + 1 ];

      for ( k = l; k <= r; k++)
        arrayptr[k] = ( temp[i] < temp[j] )  ?  temp[i++] : temp[j--];

    }


  temp = 0;
  delete [] temp;
}



/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void msSort( T* arrayptr, const int& arraySize )
{

  T* copy = new T[ arraySize ];
  int i;
  for ( i =  0; i < arraySize; i++ )
    copy[i] = arrayptr[i];

  mergesort2( copy, arrayptr, 0, arraySize - 1 );

}



/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void mergesort2( T* source, T* dest, int l, int r )
{

  if ( l != r )
    {
      int mid = ( l + r )/2;
      mergesort2( dest, source, l, mid );
      mergesort2( dest, source, mid + 1, r );
      merge2( source, dest, l, mid, r );
    }

}



/******************************************************************************************
*
*   Function Name:
*
*   Purpose:
*
*
*   Input Parameters:
*
*   Output parameters:
*
*   Return Value:
*
******************************************************************************************/


template <typename T>
void merge2( T* source,  T* arrayptr , int l, int mid,  int r )
{

  int i = l;
  int j = mid + 1;
  int k = l;

  while ( ( i <= mid  ) && ( j <= r ) )   	// Compare current item from each list
    if ( source[ i ] < source[ j ]  )  		// Then i item comes first
      arrayptr[ k++ ] = source[ i++ ];
    else                                  	// j item comes first
      arrayptr[ k++ ] = source[ j++ ];
  						// Move what is left of remaining list
              
  if ( i > mid )
    while ( j <= r )
      arrayptr[ k++ ] = source[ j++ ];
  else
    while (i <= mid )
      arrayptr[ k++ ] = source[ i++ ];
      
     
}





#endif


////////////////////////////////////////////////////////////////////////////////////////

