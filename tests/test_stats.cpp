#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T, typename U>
void test_Norm_L2()
{
    ippe::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    U norm;
    ippe::stats::Norm_L2(x.data(), x.size(), &norm);

    U checkNorm = 0;
    for (int i = 0; i < 10; i++)
    {
        checkNorm += x[i] * x[i];
    }
    checkNorm = std::sqrt(checkNorm);
    REQUIRE(std::abs(norm - checkNorm) < 1e-10);
}

template <typename T, typename U>
void test_Norm_L2_complex()
{
    ippe::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i].re = i;
        x[i].im = i;
    }

    U norm;
    ippe::stats::Norm_L2(x.data(), x.size(), &norm);

    U checkNorm = 0;
    for (int i = 0; i < 10; i++)
    {
        checkNorm += x[i].re * x[i].re + x[i].im * x[i].im;
    }
    checkNorm = std::sqrt(checkNorm);
    REQUIRE(std::abs(norm - checkNorm) < 1e-10);
}

TEST_CASE("ippe stats Norm_L2", "[stats], [Norm_L2]")
{
    SECTION("Ipp32f"){
        test_Norm_L2<Ipp32f, Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Norm_L2<Ipp64f, Ipp64f>();
    }
    SECTION("Ipp16s"){
        test_Norm_L2<Ipp16s, Ipp32f>();
    }
    SECTION("Ipp32fc"){
        test_Norm_L2_complex<Ipp32fc, Ipp64f>();
    }
    SECTION("Ipp64fc"){
        test_Norm_L2_complex<Ipp64fc, Ipp64f>();
    }

}