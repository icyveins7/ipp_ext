#include "ipp_ext.h"
#include <iostream>

int main()
{
    // Make some data
    ippe::vector<Ipp16s> x(10);
    ippe::generator::Slope(x.data(), (int)x.size(), 0.0f, 1.0f);

    // Sample it up
    int factor = 3;
    int phase = 0;
    ippe::vector<Ipp16s> y(x.size()*factor);

    int ylen = y.size();
    ippe::sampling::SampleUp(
        x.data(), x.size(), 
        y.data(), &ylen, 
        factor, &phase);

    for (int i = 0; i < y.size(); i++)
    {
        printf("%d ", y[i]);
    }
    printf("\nLength %d, Phase = %d, ylen = %d\n", (int)y.size(), phase, ylen);

    // Note that the dstLen variable is completely ignored and overwritten.
    // This means that if the destination is not large enough, there will be leaks
    y.zero(); // zero it out again first
    ylen = y.size()/2;
    ippe::sampling::SampleUp(
        x.data(), x.size(), 
        y.data(), &ylen, 
        factor, &phase);

    for (int i = 0; i < y.size(); i++)
    {
        printf("%d ", y[i]);
    }
    printf("\nLength %d, Phase = %d, ylen = %d\n", (int)y.size(), phase, ylen);

    // Sample it up to a shorter length, this should leak,
    // however do note that IPP allocates more than necessary (by 64+8 bytes) in order
    // to fulfill the 64-byte alignment
    // hence it may not leak on all cases, or on all runs

    // ippe::vector<Ipp16s> z(factor); // in this small test, it appears to seldom leak
    // printf("z.capacity() = %zd\n", z.capacity());
    // int zlen = z.size();
    // ippe::sampling::SampleUp(
    //     x.data(), x.size(), 
    //     z.data(), &zlen, 
    //     factor, &phase);
    // for (int i = 0; i < z.size(); i++)
    // {
    //     printf("%d ", z[i]);
    // }
    // printf("\nLength %d, Phase = %d, zlen = %d\n", (int)z.size(), phase, zlen);

    // Sample up to a longer length
    ippe::vector<Ipp16s> w(x.size()*factor*2 - 1);
    int wlen = w.size();
    ippe::sampling::SampleUp(
        x.data(), x.size(), 
        w.data(), &wlen, 
        factor, &phase);
    for (int i = 0; i < w.size(); i++)
    {
        printf("%d ", w[i]);
    }
    printf("\nLength %d, Phase = %d, wlen = %d\n", (int)w.size(), phase, wlen);

    return 0;
}