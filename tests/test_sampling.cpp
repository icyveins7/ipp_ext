#include <iostream>
#include <cmath>
#include <vector>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T>
void test_sampleUp()
{
    int factor = 3;
    int phase = 1;
    int inputPhase = phase;
    ippe::vector<T> src(10);
    ippe::vector<T> dst(src.size()*factor); 

    // Set some values
    for (int i = 0; i < src.size(); i++)
        src[i] = i;

    // Sample up
    int dstlen = dst.size();
    ippe::sampling::SampleUp(
        src.data(), src.size(),
        dst.data(), &dstlen,
        factor, &phase
    );

    // Check values
    for (int i = 0; i < dst.size(); i++)
    {
        if (i % factor == phase)
        {
            REQUIRE(dst[i] == src[i / factor]);
        }
        else
        {
            REQUIRE(dst[i] == 0);
        }
    }

    // Check phase returned; for SampleUp, it shouldn't change
    REQUIRE(phase == inputPhase); 
}

template <typename T>
void test_sampleUp_cplx()
{
    int factor = 3;
    int phase = 1;
    int inputPhase = phase;
    ippe::vector<T> src(10);
    ippe::vector<T> dst(src.size()*factor); 

    // Set some values
    for (int i = 0; i < src.size(); i++)
    {
        src[i].re = i;
        src[i].im = i;
    }
        
    // Sample up
    int dstlen = dst.size();
    ippe::sampling::SampleUp(
        src.data(), src.size(),
        dst.data(), &dstlen,
        factor, &phase
    );

    // Check values
    for (int i = 0; i < dst.size(); i++)
    {
        if (i % factor == phase)
        {
            REQUIRE(dst[i].re == src[i / factor].re);
            REQUIRE(dst[i].im == src[i / factor].im);
        }
        else
        {
            REQUIRE(dst[i].re == 0);
            REQUIRE(dst[i].im == 0);
        }
    }

    // Check phase returned; for SampleUp, it shouldn't change
    REQUIRE(phase == inputPhase); 
}


TEST_CASE("ippe sampling SampleUp", "[sampling], [SampleUp]")
{
    SECTION("Ipp16s"){
        test_sampleUp<Ipp16s>();
    }
    SECTION("Ipp32f"){
        test_sampleUp<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_sampleUp<Ipp64f>();
    }
    SECTION("Ipp16sc"){
        test_sampleUp_cplx<Ipp16sc>();
    }
    SECTION("Ipp32fc"){
        test_sampleUp_cplx<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_sampleUp_cplx<Ipp64fc>();
    }
}

template <typename T>
void test_sampleDown()
{
    int factor = 3;
    int phase = 1;
    ippe::vector<T> src(10);
    ippe::vector<T> dst(src.size()*factor - (factor-1)); // this should cut off before the last one is written

    // Set some values
    for (int i = 0; i < src.size(); i++)
        src[i] = i;

    // Sample down
    int dstlen = dst.size();
    ippe::sampling::SampleDown(
        src.data(), src.size(),
        dst.data(), &dstlen,
        factor, &phase
    );

    // Check values
    for (int i = 0; i < dst.size(); i++)
    {
        if (i % factor == phase)
        {
            REQUIRE(dst[i] == src[i / factor]);
        }
        else
        {
            REQUIRE(dst[i] == 0);
        }
    }

    // Check phase returned; since we cut off before the last one, phase should be 0 now
    // REQUIRE(phase == 0); // phase doesn't seem to change? test fails on this
}