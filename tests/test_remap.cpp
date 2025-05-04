#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include "catch2/catch_test_macros.hpp"

/*
 * All combinations for 32f interpolating:
 * 8u: C1, C3, C4
 * 16u: C1, C3, C4, AC4
 * 16s: C1, C3, C4, AC4
 * 32f: C1, C3, C4, AC4
 *
 * All combinations for 64f interpolating:
 * 64f: C1, C3, C4, AC4
 *
 */

template <typename T, typename U>
bool bilinearInterpolateC1(
    const ippi::image<T, ippi::channels::C1>& src,
    const U xPixel, const U yPixel, // these are the positions we want
    T& output
){
    // check if valid position is out of bounds, note the -1
    if (xPixel < 0 || xPixel > src.width() - 1 || yPixel < 0 || yPixel > src.height() - 1)
        return false;

    // get 4 corner pixels
    size_t i0 = static_cast<size_t>(std::floor(yPixel));
    size_t j0 = static_cast<size_t>(std::floor(xPixel));
    size_t i1 = static_cast<size_t>(std::ceil(yPixel));
    size_t j1 = static_cast<size_t>(std::ceil(xPixel));
    // cast to U type when reading
    // let the image class handle out of bounds access with our .at()
    // this is to check if position is in bounds
    U p00 = static_cast<U>(src.at(i0, j0));
    U p01 = static_cast<U>(src.at(i0, j1));
    U p10 = static_cast<U>(src.at(i1, j0));
    U p11 = static_cast<U>(src.at(i1, j1));

    // interpolate top two first
    U p0 = p00 * (1 - (xPixel - std::floor(xPixel))) + p10 * (xPixel - std::floor(xPixel));
    U p1 = p01 * (1 - (xPixel - std::floor(xPixel))) + p11 * (xPixel - std::floor(xPixel));
    // then combine
    output = static_cast<T>(p0 * (1 - (yPixel - std::floor(yPixel))) + p1 * (yPixel - std::floor(yPixel)));

    return true;
}

template <ippi::channels C, typename T, typename U>
void test_remap(int interpolation)
{
    // Create simple 100 x 100 image
    ippi::image<T, C> src(100, 100);
    // Fill with sequence
    for (int i = 0; i < src.height(); i++)
        for (int j = 0; j < src.width(); j++)
            src.at(i, j) = (T)j;

    // Create x and y map requests, 5x5
    // We want the border to be outside the image to test validity
    // We can start at (-10, -5) and add 30
    // This should end at (110, 105)
    const size_t L = 5;
    ippi::image<U, C> xmap(L, L);
    ippi::image<U, C> ymap(xmap.size());

    // Fill with values outside the range
    for (int i = 0; i < xmap.height(); i++)
    {
        for (int j = 0; j < xmap.width(); j++)
        {
            xmap.at(i, j) = j * 30.0f - 10.0f;
            ymap.at(i, j) = i * 30.0f - 5.0f;
        }
    }

    // Request the remap
    IppiRect srcRoi = { 0, 0, static_cast<int>(src.width()), static_cast<int>(src.height()) };
    ippi::image<T, C> dst(xmap.size());
    // Initialize to large value
    for (int i = 0; i < dst.height(); i++)
        for (int j = 0; j < dst.width(); j++)
            dst.at(i, j) = 255;
    ippi::image<T, C> check = dst; // copy the dst into check

    // Call the IPP remap
    ippi::Remap<C>(
        src.data(), src.size(), (int)src.stepBytes(), srcRoi,
        xmap.data(), (int)xmap.stepBytes(),
        ymap.data(), (int)ymap.stepBytes(),
        dst.data(), (int)dst.stepBytes(), dst.size(), interpolation
    );

    // do the same with a manual check
    for (int i = 0; i < check.height(); i++)
    {
        for (int j = 0; j < check.width(); j++)
        {
            T outPixel;
            if (
                bilinearInterpolateC1<T, U>(
                    src,
                    xmap.at(i, j), ymap.at(i, j),
                    outPixel
                )
            )
                check.at(i, j) = outPixel;
        }
    }

    // Check that the results are the same
    for (int i = 0; i < dst.height(); i++)
    {
        for (int j = 0; j < dst.width(); j++)
        {
            REQUIRE(dst.at(i, j) == check.at(i, j));
        }
    }

    // Test some edge cases, just outside the bounds, all these should be invalid
    // left of top left
    xmap.at(0, 0) = -0.01f; ymap.at(0, 0) = 0.0f;
    // right of top right
    xmap.at(0, 1) = src.width() - 0.99f; ymap.at(0, 1) = 0.0f;
    // top of top left
    xmap.at(1, 0) = 0.0f; ymap.at(1, 0) = -0.01f;
    // top of top right
    xmap.at(1, 1) = 0.0f; ymap.at(1, 1) = -0.01f;
    // btm right of btm right
    xmap.at(2, 2) = src.width() - 0.99f; ymap.at(2, 2) = src.height() - 0.99f;

    // Call IPP remap again
    ippi::Remap<C>(
        src.data(), src.size(), (int)src.stepBytes(), srcRoi,
        xmap.data(), (int)xmap.stepBytes(),
        ymap.data(), (int)ymap.stepBytes(),
        dst.data(), (int)dst.stepBytes(), dst.size(), interpolation
    );
    // calculate check again
    for (int i = 0; i < check.height(); i++)
    {
        for (int j = 0; j < check.width(); j++)
        {
            T outPixel;
            if (
                bilinearInterpolateC1<T, U>(
                    src,
                    xmap.at(i, j), ymap.at(i, j),
                    outPixel
                )
            )
                check.at(i, j) = outPixel;
        }
    }
    // validate again
    for (int i = 0; i < dst.height(); i++)
    {
        for (int j = 0; j < dst.width(); j++)
        {
            REQUIRE(dst.at(i, j) == check.at(i, j));
        }
    }
}

// NOTE: i think it's sufficient to just test linear with C1, everything else is a bit complicated..
// We also don't have a test for 64f since there isn't an ippiMalloc for 64f, hence no ippi::image template

TEST_CASE("ippi Remap, linear, no smoothing", "[transform], [Remap], [linear]")
{
    SECTION("Ipp8u, C1, interp using Ipp32f"){
        test_remap<ippi::channels::C1, Ipp8u, Ipp32f>(IPPI_INTER_LINEAR);
    }

    SECTION("Ipp16u, C1, interp using Ipp32f"){
        test_remap<ippi::channels::C1, Ipp16u, Ipp32f>(IPPI_INTER_LINEAR);
    }

    SECTION("Ipp16s, C1, interp using Ipp32f"){
        test_remap<ippi::channels::C1, Ipp16s, Ipp32f>(IPPI_INTER_LINEAR);
    }

    SECTION("Ipp32f, C1, interp using Ipp32f"){
        test_remap<ippi::channels::C1, Ipp32f, Ipp32f>(IPPI_INTER_LINEAR);
    }

}

