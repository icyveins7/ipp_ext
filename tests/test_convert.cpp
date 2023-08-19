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

template <typename T, typename U>
void test_RealToCplx()
{
    ippe::vector<T> srcRe(10);
    ippe::vector<T> srcIm(10);
    ippe::vector<U> dst(10);

    for (int i = 0; i < 10; i++)
    {
        srcRe[i] = 1 + i;
        srcIm[i] = i*0.1;
    }
    ippe::convert::RealToCplx(srcRe.data(), srcIm.data(), dst.data(), dst.size());
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dst[i].re == srcRe[i]);
        REQUIRE(dst[i].im == srcIm[i]);
    }

    // Also test zero conversions with null pointers
    // note that the static_cast is required as we didn't handle nullptrs in the template
    ippe::convert::RealToCplx(static_cast<T*>(nullptr), srcIm.data(), dst.data(), dst.size());
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dst[i].re == 0);
        REQUIRE(dst[i].im == srcIm[i]);
    }

    ippe::convert::RealToCplx(srcRe.data(), static_cast<T*>(nullptr), dst.data(), dst.size());
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dst[i].re == srcRe[i]);
        REQUIRE(dst[i].im == 0);
    }
}

TEST_CASE("ippe convert RealToCplx", "[convert], [RealToCplx]")
{
    SECTION("Ipp16sc"){
        test_RealToCplx<Ipp16s, Ipp16sc>();
    }
    SECTION("Ipp32fc"){
        test_RealToCplx<Ipp32f, Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_RealToCplx<Ipp64f, Ipp64fc>();
    }
}

template <typename T, typename U>
void test_CplxToReal()
{
    ippe::vector<T> src(10);
    ippe::vector<U> dstRe(10);
    ippe::vector<U> dstIm(10);

    for (int i = 0; i < 10; i++)
    {
        src[i].re = 1 + i;
        src[i].im = i*0.1;
    }

    ippe::convert::CplxToReal(src.data(), dstRe.data(), dstIm.data(), src.size());
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dstRe[i] == src[i].re);
        REQUIRE(dstIm[i] == src[i].im);
    }
}

TEST_CASE("ippe convert CplxToReal", "[convert], [CplxToReal]")
{
    SECTION("Ipp16sc"){
        test_CplxToReal<Ipp16sc, Ipp16s>();
    }
    SECTION("Ipp32fc"){
        test_CplxToReal<Ipp32fc, Ipp32f>();
    }
    SECTION("Ipp64fc"){
        test_CplxToReal<Ipp64fc, Ipp64f>();
    }
}
