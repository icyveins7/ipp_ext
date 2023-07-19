/*
cl /EHsc /O2 /I"../include/" matrix_example.cpp ippcore.lib ipps.lib
*/
#include <iostream>
#include <vector>
#include "../include/ipp_ext.h"


int main()
{
    ippe::matrix<Ipp64f> x(1, 10, 1.0);
    ippe::matrix<Ipp64f> y(1, 10, 2.0);

    printf("------Copy elision by compiler if you construct along with the math\n");
    ippe::matrix<Ipp64f> z = x + y;

    printf("------Copy constructor\n");
    std::vector<ippe::matrix<Ipp64f>> v;
    v.push_back(x);

    printf("------Copy assignment\n");
    v[0] = y;

    printf("------Move assignment activated?\n");
    ippe::matrix<Ipp64f> z2(2,20); // put some existing memory in to make sure its released safely
    printf("z2 dimensions at start = %zd, %zd\n", z2.rows(), z2.columns());
    z2 = x + y; // move in the other memory
    printf("z2 dimensions at end = %zd, %zd\n", z2.rows(), z2.columns());

    printf("------Move constructor activated?\n");
    ippe::matrix<Ipp64f> z3(std::move(x));
    printf("z3 dimensions = %zd, %zd\n", z3.rows(), z3.columns());
    printf("x dimensions = %zd, %zd\n", x.rows(), x.columns());
    printf("x nullptr? %s\n", (x.data() == nullptr)? "true" : "false");

    return 0;
}