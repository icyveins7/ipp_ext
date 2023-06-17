#include <iostream>
#include "ipp_ext_generator.h"
#include "ipp_ext_vec.h"

#include <catch2/catch_test_macros.hpp>


/*
Template test case for Slope sample generators
*/
template <typename T, typename U>
void test_slope_sample_generator()
{
    // make a vector
    ippe::vector<T> vec(10);

    // generate slope samples into it
    ippe::generator::Slope(vec.data(), 10, (U)1, (U)1);

    // check if the samples are correct
    for (int i = 0; i < vec.size(); ++i)
    {
        REQUIRE(vec[i] == 1 + i);
    }
}

TEST_CASE("ippe Slope sample generator", "[generator],[slope]")
{
    /*
    Flavours are:
    Ipp8u, Ipp32f
    Ipp16u, Ipp32f
    Ipp16s, Ipp32f
    Ipp32u, Ipp64f
    Ipp32s, Ipp64f
    Ipp32f, Ipp32f
    Ipp64f, Ipp64f
    */

    SECTION("Ipp8u, Ipp32f")
    {
        test_slope_sample_generator<Ipp8u, Ipp32f>();
    }

    SECTION("Ipp16u, Ipp32f")
    {
        test_slope_sample_generator<Ipp16u, Ipp32f>();
    }

    SECTION("Ipp16s, Ipp32f")
    {
        test_slope_sample_generator<Ipp16s, Ipp32f>();
    }

    SECTION("Ipp32u, Ipp64f")
    {
        test_slope_sample_generator<Ipp32u, Ipp64f>();
    }

    SECTION("Ipp32s, Ipp64f")
    {
        test_slope_sample_generator<Ipp32s, Ipp64f>();
    }

    SECTION("Ipp32f, Ipp32f")
    {
        test_slope_sample_generator<Ipp32f, Ipp32f>();
    }

    SECTION("Ipp64f, Ipp64f")
    {
        test_slope_sample_generator<Ipp64f, Ipp64f>();
    }
}