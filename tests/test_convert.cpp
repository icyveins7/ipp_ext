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

// =====================================================
template <typename T, typename U>
void test_Convert()
{
    // Make vectors for the src and dst types
    ippe::vector<T> src(10);
    ippe::vector<U> dst(10);

    // Write values for src
    for (int i = 0; i < 10; i++)
    {
        src[i] = 1 + i;
    }

    // Run conversion
    ippe::convert::Convert<T, U>(src.data(), dst.data(), src.size());

    // Check
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dst[i] == (U)src[i]);
    }
}

TEST_CASE("ippe convert Convert", "[convert], [Convert]")
{
    // 8s to 16s
    SECTION("Ipp8s to Ipp16s"){
        test_Convert<Ipp8s, Ipp16s>();
    }
    // 8s to 32f
    SECTION("Ipp8s to Ipp32f"){
        test_Convert<Ipp8s, Ipp32f>();
    }
    // 8u to 32f
    SECTION("Ipp8u to Ipp32f"){
        test_Convert<Ipp8u, Ipp32f>();
    }
    // 8s to 8u
    SECTION("Ipp8s to Ipp8u"){
        test_Convert<Ipp8s, Ipp8u>();
    }
    // 16s to 32s
    SECTION("Ipp16s to Ipp32s") {
        test_Convert<Ipp16s, Ipp32s>();
    }
    // 16s to 32f
    SECTION("Ipp16s to Ipp32f") {
        test_Convert<Ipp16s, Ipp32f>();
    }
    // 16u to 32f
    SECTION("Ipp16u to Ipp32f"){
        test_Convert<Ipp16u, Ipp32f>();
    }
    // 32s to 16s
    SECTION("Ipp32s to Ipp16s") {
        test_Convert<Ipp32s, Ipp16s>();
    }
    // 32s to 32f
    SECTION("Ipp32s to Ipp32f") {
        test_Convert<Ipp32s, Ipp32f>();
    }
    // 32s to 64f
    SECTION("Ipp32s to Ipp64f") {
        test_Convert<Ipp32s, Ipp64f>();
    }
    // 32f to 64f
    SECTION("Ipp32f to Ipp64f") {
        test_Convert<Ipp32f, Ipp64f>();
    }
    // 64s to 64f
    SECTION("Ipp64s to Ipp64f") {
        test_Convert<Ipp64s, Ipp64f>();
    }
    // 64f to 32f
    SECTION("Ipp64f to Ipp32f") {
        test_Convert<Ipp64f, Ipp32f>();
    }
}

template <typename T, typename U>
void test_Convert_Sfs()
{
    // Make vectors for the src and dst types
    ippe::vector<T> src(10);
    ippe::vector<U> dst(10);

    // Write values for src
    for (int i = 0; i < 10; i++)
    {
        src[i] = 1 + i;
    }

    // Run conversion
    ippe::convert::Convert_Sfs<T, U>(src.data(), dst.data(), src.size(), 0); // ignore scalefactor and rndmode

    // Check
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(dst[i] == (U)src[i]);
    }
}

TEST_CASE("ippe convert Convert_Sfs", "[convert], [Convert_Sfs]")
{
    // 8u to 8s
    SECTION("Ipp8u to Ipp8s"){
        test_Convert_Sfs<Ipp8u, Ipp8s>();
    }

    // 16s to 8s
    SECTION("Ipp16s to Ipp8s"){
        test_Convert_Sfs<Ipp16s, Ipp8s>();
    }

    // 16s to 32f
    SECTION("Ipp16s to Ipp32f"){
        test_Convert_Sfs<Ipp16s, Ipp32f>();
    }

    // 16s to 64f
    SECTION("Ipp16s to Ipp64f"){
        test_Convert_Sfs<Ipp16s, Ipp64f>();
    }

    // 32s to 16s
    SECTION("Ipp32s to Ipp16s"){
        test_Convert_Sfs<Ipp32s, Ipp16s>();
    }

    // 32s to 32f
    SECTION("Ipp32s to Ipp32f"){
        test_Convert_Sfs<Ipp32s, Ipp32f>();
    }

    // 32s to 64f
    SECTION("Ipp32s to Ipp64f"){
        test_Convert_Sfs<Ipp32s, Ipp64f>();
    }

    // 32f to 8s
    SECTION("Ipp32f to Ipp8s"){
        test_Convert_Sfs<Ipp32f, Ipp8s>();
    }

    // 32f to 8u
    SECTION("Ipp32f to Ipp8u"){
        test_Convert_Sfs<Ipp32f, Ipp8u>();
    }

    // 32f to 16s
    SECTION("Ipp32f to Ipp16s"){
        test_Convert_Sfs<Ipp32f, Ipp16s>();
    }

    // 32f to 16u
    SECTION("Ipp32f to Ipp16u"){
        test_Convert_Sfs<Ipp32f, Ipp16u>();
    }

    // 32f to 32s
    SECTION("Ipp32f to Ipp32s"){
        test_Convert_Sfs<Ipp32f, Ipp32s>();
    }

    // 64f to 8s
    SECTION("Ipp64f to Ipp8s"){
        test_Convert_Sfs<Ipp64f, Ipp8s>();
    }

    // 64f to 8u
    SECTION("Ipp64f to Ipp8u"){
        test_Convert_Sfs<Ipp64f, Ipp8u>();
    }

    // 64f to 16u
    SECTION("Ipp64f to Ipp16u"){
        test_Convert_Sfs<Ipp64f, Ipp16u>();
    }

    // 64s to 32s
    SECTION("Ipp64s to Ipp32s"){
        test_Convert_Sfs<Ipp64s, Ipp32s>();
    }

    // 64f to 16s
    SECTION("Ipp64f to Ipp16s"){
        test_Convert_Sfs<Ipp64f, Ipp16s>();
    }

    // 64f to 32s
    SECTION("Ipp64f to Ipp32s"){
        test_Convert_Sfs<Ipp64f, Ipp32s>();
    }

    // 64f to 64s
    SECTION("Ipp64f to Ipp64s"){
        test_Convert_Sfs<Ipp64f, Ipp64s>();
    }
}