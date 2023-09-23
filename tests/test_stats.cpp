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

// =====================================================================================================================
template <typename T>
void test_Sum()
{
    ippe::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }
    
    T sum;
    ippe::stats::Sum(x.data(), x.size(), &sum);
    
    T checkSum = 0;
    for (int i = 0; i < 10; i++){
        checkSum += x[i];
    }
    REQUIRE(std::abs(sum - checkSum) < 1e-10);
}

template <typename T>
void test_Sum_complex()
{
    ippe::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i].re = i;
        x[i].im = i;
    }
    
    T sum;
    ippe::stats::Sum(x.data(), x.size(), &sum);
    
    T checkSum = {0.0, 0.0};
    for (int i = 0; i < 10; i++){
        checkSum.re += x[i].re;
        checkSum.im += x[i].im;
    }
    REQUIRE(std::abs(sum.re - checkSum.re) < 1e-10);
    REQUIRE(std::abs(sum.im - checkSum.im) < 1e-10);
}

TEST_CASE("ippe stats Sum", "[stats], [Sum]")
{
    SECTION("Ipp32f"){
        test_Sum<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Sum<Ipp64f>();
    }
    SECTION("Ipp32fc"){
        test_Sum_complex<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_Sum_complex<Ipp64fc>();
    }
}