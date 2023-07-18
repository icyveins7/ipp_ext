/*
cl /EHsc /O2 /I"../include/" matrix_example.cpp ippcore.lib ipps.lib
*/
#include <iostream>
#include "../include/ipp_ext.h"

int main()
{
    ippe::matrix<Ipp64f> x(1, 10, 1.0);
    ippe::matrix<Ipp64f> y(1, 10, 2.0);

    printf("------Copy elision by compiler if you construct along with the math\n");
    ippe::matrix<Ipp64f> z = x + y;

    printf("------Move assignment activated?\n");
    ippe::matrix<Ipp64f> z2;
    printf("z2 dimensions at start = %zd, %zd\n", z2.rows(), z2.columns());
    z2 = x + y;
    printf("z2 dimensions at end = %zd, %zd\n", z2.rows(), z2.columns());

    return 0;
}