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

    printf("------Copy assignment activated?\n");
    ippe::matrix<Ipp64f> z2;
    z2 = x + y;

    return 0;
}