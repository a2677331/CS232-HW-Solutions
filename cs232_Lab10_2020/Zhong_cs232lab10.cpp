/**************************************************************************
 * File name: lab10.cpp
 * ----------------------------
 * Driver file to demonstrate the optimal multiplication
 * of two complex numbers.
 *
 * Programmer: Jian Zhong
 * Date Written: 11/14/2020
 * Date Last Revised: 11/14/2020
**************************************************************************/

#include <iostream>
#include <complex>

using namespace std;

/*******************************************************************************************
 * Function Name: computeComplex( )
 *
 * Purpose: algorithm to perform the optimal multiplication of two complex numbers.
 * Input Parameters:
 *          int a: real part of first complex num
 *          int b: imag part of first complex num
 *          int c: real part of second complex num
 *          int d: imag part of second complex num
 * Output parameters: none.
 * Return Value:
 *          product of a+bi and c+di
 *******************************************************************************************/
complex<int> computeComplex(int a, int b, int c, int d)
{
    int p1 = a * c;             // first mul
    int p2 = b * d;             // second mul
    int p3 = (a + b) * (c + d); // third mul
    complex<int> result(p1 - p2, p3 - p1 - p2);  // Karatsuba multiplication
    
    return result; // pass back product
}


// Driver file to compute two complex numbers:
int main()
{
    int real1, imag1, real2, imag2;
    cout << "Compute the product of two complex numbers\n"
         << "Real part of the FIRST complex number : ";
    cin >> real1;
    cout << "Imaginary part of the FIRST complex number : ";
    cin >> imag1;
    cout << "Real part of the SECOND complex number : ";
    cin >> real2;
    cout << "Imaginary part of the SECOND complex number : ";
    cin >> imag2;
    
    complex<int> complex = computeComplex(real1, imag1, real2, imag2);
    cout << "\nProduct is: ";
    cout << real(complex) << " + " << imag(complex) << "i\n";
    
    return 0;
}


