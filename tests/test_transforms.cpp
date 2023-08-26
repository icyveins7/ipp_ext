#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T, typename U, typename V>
void test_Goertz_real()
{
    ippe::vector<T> x(10);
    U val;
    V rFreq = 0.1;

    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    U sum = {0.0, 0.0};
    
    // invoke the function
    ippe::transform::Goertz(x.data(), x.size(), &val, rFreq);

    // calculate manually
    for (int i = 0; i < x.size(); i++)
    {
        sum.re += x[i] * std::cos(-IPP_2PI * i * rFreq);
        sum.im += x[i] * std::sin(-IPP_2PI * i * rFreq);
    }
    REQUIRE(std::abs(sum.re - val.re) < 1e-6);
    REQUIRE(std::abs(sum.im - val.im) < 1e-6);
}

template <typename T, typename U, typename V>
void test_Goertz_complex()
{
    ippe::vector<T> x(10);
    U val;
    V rFreq = 0.1;

    for (int i = 0; i < 10; i++)
    {
        x[i].re = i;
        x[i].im = 0; // just make it real so the checking is easier
    }

    U sum = {0.0, 0.0};
    
    // invoke the function
    ippe::transform::Goertz(x.data(), x.size(), &val, rFreq);

    // calculate manually
    for (int i = 0; i < x.size(); i++)
    {
        sum.re += x[i].re * std::cos(-IPP_2PI * i * rFreq);
        sum.im += x[i].re * std::sin(-IPP_2PI * i * rFreq);
    }
    REQUIRE(std::abs(sum.re - val.re) < 1e-6);
    REQUIRE(std::abs(sum.im - val.im) < 1e-6);
}

TEST_CASE("ippe transform Goertz", "[transform], [Goertz]")
{
    SECTION("Ipp32f"){
        test_Goertz_real<Ipp32f, Ipp32fc, Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Goertz_real<Ipp64f, Ipp64fc, Ipp64f>();
    }
    SECTION("Ipp32fc"){
        test_Goertz_complex<Ipp32fc, Ipp32fc, Ipp32f>();
    }
    SECTION("Ipp64fc"){
        test_Goertz_complex<Ipp64fc, Ipp64fc, Ipp64f>();
    }
}

// Developer note: not testing the Sfs functions. Not sure how to test them.
