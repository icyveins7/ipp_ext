#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template<typename T, typename U>
void test_PolarToCart()
{
    ippe::vector<T> srcMag(10);
    ippe::vector<T> srcPhase(10);
    ippe::vector<U> dst(10);

    for (int i = 0; i < 10; i++)
    {
        srcMag[i] = 1 + i;
        srcPhase[i] = i*0.1;
    }

    ippe::convert::PolarToCart(srcMag.data(), srcPhase.data(), dst.data(), dst.size());

    for (int i = 0; i < 10; i++)
    {
        REQUIRE(std::abs(dst[i].re - srcMag[i] * std::cos(srcPhase[i])) < 1e-6);
        REQUIRE(std::abs(dst[i].im - srcMag[i] * std::sin(srcPhase[i])) < 1e-6);
    }
}

TEST_CASE("ippe convert PolarToCart", "[convert], [PolarToCart]")
{
    SECTION("Ipp32fc"){
        test_PolarToCart<Ipp32f, Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_PolarToCart<Ipp64f, Ipp64fc>();
    }
}

template<typename T, typename U>
void test_CartToPolar()
{
    ippe::vector<T> src(10);
    ippe::vector<U> dstMag(10);
    ippe::vector<U> dstPhase(10);

    for (int i = 0; i < 10; i++)
    {
        src[i].re = i;
        src[i].im = 1 + i;
    }
    ippe::convert::CartToPolar(src.data(), dstMag.data(), dstPhase.data(), dstMag.size());

    for (int i = 0; i < 10; i++)
    {
        U mag = std::sqrt(src[i].re * src[i].re + src[i].im * src[i].im);
        U phase = std::atan2(src[i].im, src[i].re);
        REQUIRE(std::abs(dstMag[i] - mag) < 1e-6);
        REQUIRE(std::abs(dstPhase[i] - phase) < 1e-6);
    }
}

TEST_CASE("ippe convert CartToPolar", "[convert], [CartToPolar]")
{
    SECTION("Ipp32fc"){
        test_CartToPolar<Ipp32fc, Ipp32f>();
    }
    SECTION("Ipp64fc"){
        test_CartToPolar<Ipp64fc, Ipp64f>();
    }
}