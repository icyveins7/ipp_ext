#include "ipp_ext.h"
#include <iostream>

int main()
{
    // Make some data
    ipps::vector<Ipp16s> x(10);
    ipps::generator::Slope(x.data(), (int)x.size(), 0.0f, 1.0f);

    // Sample it up
    int factor = 3;
    int phase = 0;
    ipps::vector<Ipp16s> y(x.size()*factor);

    int ylen = (int)y.size();
    ipps::sampling::SampleUp(
        x.data(), (int)x.size(), 
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
    ylen = (int)y.size()/2;
    ipps::sampling::SampleUp(
        x.data(), (int)x.size(), 
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

    // ipps::vector<Ipp16s> z(factor); // in this small test, it appears to seldom leak
    // printf("z.capacity() = %zd\n", z.capacity());
    // int zlen = z.size();
    // ipps::sampling::SampleUp(
    //     x.data(), x.size(), 
    //     z.data(), &zlen, 
    //     factor, &phase);
    // for (int i = 0; i < z.size(); i++)
    // {
    //     printf("%d ", z[i]);
    // }
    // printf("\nLength %d, Phase = %d, zlen = %d\n", (int)z.size(), phase, zlen);

    // Sample up to a longer length
    ipps::vector<Ipp16s> w(x.size()*factor*2 - 1);
    int wlen = (int)w.size();
    ipps::sampling::SampleUp(
        x.data(), (int)x.size(), 
        w.data(), &wlen, 
        factor, &phase);
    for (int i = 0; i < w.size(); i++)
    {
        printf("%d ", w[i]);
    }
    printf("\nLength %d, Phase = %d, wlen = %d\n", (int)w.size(), phase, wlen);

    printf("===================================\n");
    // Create a long vector
    ipps::vector<Ipp16s> a(150);
    ipps::generator::Slope(a.data(), (int)a.size(), 0.0f, 1.0f);

    // Perform downsample
    ipps::vector<Ipp16s> b(50);
    int blen = 0;
    size_t bWritten = 0;
    printf("Complete step-wise in 3 blocks\n");
    printf("Phase = %d first\n", phase);
    ipps::sampling::SampleDown(
        a.data(), (int)a.size() / 3, // do the first half first
        b.data(), &blen,
        factor, &phase
    );
    bWritten += blen;

    for (int i = 0; i < b.size(); i++)
    {
        printf("%d ", b[i]);
    }
    printf("\nLength %d, Phase = %d, blen = %d\n", (int)b.size(), phase, blen);

    ipps::sampling::SampleDown(
        &a.at(a.size()/3), (int)a.size() / 3, // do the second
        &b.at(bWritten), &blen,
        factor, &phase
    );
    bWritten += blen;

    for (int i = 0; i < b.size(); i++)
    {
        printf("%d ", b[i]);
    }
    printf("\nLength %d, Phase = %d, blen = %d\n", (int)b.size(), phase, blen);


    ipps::sampling::SampleDown(
        &a.at(2*a.size()/3), (int)a.size() / 3, // do the third part
        &b.at(bWritten), &blen,
        factor, &phase
    );
    bWritten += blen;

    for (int i = 0; i < b.size(); i++)
    {
        printf("%d ", b[i]);
    }
    printf("\nLength %d, Phase = %d, blen = %d\n", (int)b.size(), phase, blen);


    return 0;
}
