#include <iostream>
#include "ipp_ext.h"
#include <cmath>

#include <catch2/catch_test_macros.hpp>


/*
Template test case for Slope sample generators
*/
template <typename T, typename U>
void test_slope_sample_generator()
{
    // make a vector
    ipps::vector<T> vec(10);

    // generate slope samples into it
    ipps::generator::Slope(vec.data(), 10, (U)1, (U)1);

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


/*
Template test case for Tone sample generators
*/
template <typename T, typename U, typename V>
void test_tone_sample_generator_complex()
{
    // Make output vector
    ipps::vector<T> out(10);

    // Define magn and freq
    U magn = 1;
    V freq = 0.1;

    // Define phase
    V phase = 0;

    // Generate tone samples into it
    ipps::generator::Tone(
        out.data(), out.size(),
        magn, freq, &phase
    );

    // Check if the samples are correct
    for (int i = 0; i < out.size(); ++i)
    {
        double real = magn * std::cos(IPP_2PI*freq*i + phase);
        double imag = magn * std::sin(IPP_2PI*freq*i + phase);
        REQUIRE(out[i].re - real < 1e-5);
        REQUIRE(out[i].im - imag < 1e-5); // arbitrary threshold
    }
}

TEST_CASE("ippe Tone sample generator", "[generator],[tone]")
{
    // Comparing integer output is a bit weird and i'm lazy to write special test for this
    // SECTION("Ipp16sc output"){
    //     test_tone_sample_generator_complex<Ipp16sc, Ipp16s, Ipp32f>();
    // }

    SECTION("Ipp32fc output"){
        test_tone_sample_generator_complex<Ipp32fc, Ipp32f, Ipp32f>();
    }
    
    SECTION("Ipp64fc output"){
        test_tone_sample_generator_complex<Ipp64fc, Ipp64f, Ipp64f>();
    }

    // TODO: test real tone output
}
