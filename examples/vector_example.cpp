/*
cl /EHsc /O2 /I"../include/" vector_example.cpp ippcore.lib ipps.lib
*/
#include <iostream>
#include "ipp_ext.h"

int main()
{
    ippe::vector<Ipp16s> v;
    printf("v.size() = %zd\n", v.size());
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    printf("v.size() = %zd\n", v.size());
    for (int i = 0; i < v.size(); ++i){
        printf("v[%d] = %d\n", i, v[i]);
    }

    return 0;
}