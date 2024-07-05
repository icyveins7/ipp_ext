/*
cl /EHsc /O2 /I"../include/" vector_example.cpp ippcore.lib ipps.lib
*/
#include <iostream>
#include "ipp_ext.h"

int main()
{
    ipps::vector<Ipp16s> v;
    printf("v.size() = %zd\n", v.size());
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);

    printf("v.size() = %zd\n", v.size());
    for (int i = 0; i < v.size(); ++i){
        printf("v[%d] = %d\n", i, v[i]);
    }

    // Copy the vector via copy assignment
    ipps::vector<Ipp16s> v_copy;
    v_copy = v;

    // Copy the vector via copy constructor
    ipps::vector<Ipp16s> v_copy2(v);

    return 0;
}
