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
    ipps::vector<T> src(10);
    ipps::vector<T> dst(src.size()*factor); 

    // Set some values
    for (int i = 0; i < src.size(); i++)
        src[i] = i;

    // Sample up
    int dstlen = dst.size();
    ipps::sampling::SampleUp(
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

    // Check error thrown when insufficient length
    int dstLen = src.size()/(factor+1);
    REQUIRE_THROWS_AS(
        ipps::sampling::SampleDown(
            src.data(), src.size(),
            dst.data(), &dstLen,
            factor, &phase
        ),
        std::out_of_range
    );
}

template <typename T>
void test_sampleUp_cplx()
{
    int factor = 3;
    int phase = 1;
    int inputPhase = phase;
    ipps::vector<T> src(10);
    ipps::vector<T> dst(src.size()*factor); 

    // Set some values
    for (int i = 0; i < src.size(); i++)
    {
        src[i].re = i;
        src[i].im = i;
    }
        
    // Sample up
    int dstlen = dst.size();
    ipps::sampling::SampleUp(
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

    // Check error thrown when insufficient length
    int dstLen = src.size()/(factor+1);
    REQUIRE_THROWS_AS(
        ipps::sampling::SampleDown(
            src.data(), src.size(),
            dst.data(), &dstLen,
            factor, &phase
        ),
        std::out_of_range
    );
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
    // For downsample, since phase and dstLen are not constant for different initial conditions,
    // we loop over the phases, and pick a non-multiple-of-factor length
    int factor = 3;
    ipps::vector<T> src(31);
    ipps::vector<T> dst(src.size()/factor + 1); 
    // Set some values
    for (int i = 0; i < src.size(); i++)
        src[i] = i;


    for (int initialPhase = 0; initialPhase < factor; initialPhase++)
    {
        int phase = initialPhase;
        
        // Sample down
        int dstlen = dst.size();
        ipps::sampling::SampleDown(
            src.data(), src.size(),
            dst.data(), &dstlen,
            factor, &phase
        );

        // Check values
        for (int i = 0; i < dstlen; i++)
        {
            REQUIRE(dst[i] == src[i * factor + initialPhase]);
        }

        // Check dstlen (which may be different for different phases)
        REQUIRE(dstlen == src.size()/factor + (
            src.size() % factor > initialPhase ? 1 : 0
        ));

        // check phase returned
        int expectedPhase = initialPhase - src.size() % factor;
        expectedPhase = expectedPhase < 0 ? expectedPhase + factor : expectedPhase;
        REQUIRE( phase == expectedPhase);
    }

    // Demonstrate custom error throwing if too short dst length
    int phase = 0;
    int dstLen = src.size()/(factor+1);
    REQUIRE_THROWS_AS(
        ipps::sampling::SampleDown(
            src.data(), src.size(),
            dst.data(), &dstLen,
            factor, &phase
        ),
        std::out_of_range
    );
}

template <typename T>
void test_sampleDown_cplx()
{
    // For downsample, since phase and dstLen are not constant for different initial conditions,
    // we loop over the phases, and pick a non-multiple-of-factor length
    int factor = 3;
    ipps::vector<T> src(31);
    ipps::vector<T> dst(src.size()/factor + 1); 
    // Set some values
    for (int i = 0; i < src.size(); i++)
    {
        src[i].re = i;
        src[i].im = i;
    }


    for (int initialPhase = 0; initialPhase < factor; initialPhase++)
    {
        int phase = initialPhase;
        
        // Sample down
        int dstlen = dst.size();
        ipps::sampling::SampleDown(
            src.data(), src.size(),
            dst.data(), &dstlen,
            factor, &phase
        );

        // Check values
        for (int i = 0; i < dstlen; i++)
        {
            REQUIRE(dst[i].re == src[i * factor + initialPhase].re);
            REQUIRE(dst[i].im == src[i * factor + initialPhase].im);
        }

        // Check dstlen (which may be different for different phases)
        REQUIRE(dstlen == src.size()/factor + (
            src.size() % factor > initialPhase? 1 : 0
        ));

        // check phase returned
        int expectedPhase = initialPhase - src.size() % factor;
        expectedPhase = expectedPhase < 0? expectedPhase + factor : expectedPhase;
        REQUIRE( phase == expectedPhase);
    }

    // Demonstrate custom error throwing if too short dst length
    int phase = 0;
    int dstLen = src.size()/(factor+1);
    REQUIRE_THROWS_AS(
        ipps::sampling::SampleDown(
            src.data(), src.size(),
            dst.data(), &dstLen,
            factor, &phase
        ),
        std::out_of_range
    );
}

TEST_CASE("ippe sampling SampleDown", "[sampling], [SampleDown]")
{
    SECTION("Ipp16s"){
        test_sampleDown<Ipp16s>();
    }
    SECTION("Ipp32f"){
        test_sampleDown<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_sampleDown<Ipp64f>();
    }
    SECTION("Ipp16sc"){
        test_sampleDown_cplx<Ipp16sc>();
    }
    SECTION("Ipp32fc"){
        test_sampleDown_cplx<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_sampleDown_cplx<Ipp64fc>();
    }
}
