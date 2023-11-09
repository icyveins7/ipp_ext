#include "ipp_ext.h"

int main()
{
    ippe::vector<Ipp8u> v(1);
    v.at(0) = 255;
    printf("Size of vector: %zd\n", v.size());

    // Use unsafe array pointer dereferencing
    printf("v[0] = %hhu\n", v[0]);
    printf("v[1] = %hhu\n", v[1]); // most likely okay due to extra allocation requirements
    printf("v[73] = %hhu\n", v[73]); // address sanitizer should flag this

    return 0;
}