#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>

#include "../include/ipp_ext.h"

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

template <typename T>
void benchmark_baseStdMedian(IppiSize srcSize, IppiSize maskSize, IppiBorderType borderType)
{

}

template <typename T, ippi::channels C>
void benchmark_filterMedianBorder(IppiSize srcSize, IppiSize maskSize, IppiBorderType borderType)
{
    // Make an image
    ippi::image<T, C> img(srcSize);
    // Make a filter median object
    ippi::FilterMedianBorder<T, C> filter(img.size(), maskSize);

    // Make an output image
    ippi::image<T, C> out(img.size());

    // Run the filter (replicate border)
    T borderVal[4] = {0, 0, 0, 0};

    BENCHMARK("FilterMedianBorder")
    {
        filter.filter(img.data(), (int)img.stepBytes(), out.data(), (int)out.stepBytes(), borderType, borderVal);
        return 0;
    };
}

TEST_CASE("Benchmark FilterMedianBorder implementations", "[FilterMedianBorder]")
{
    // ============= Ipp16u C1 =============================

    SECTION("Ipp16u, C1, src 64x64, mask 3x3, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {64, 64}, {3, 3}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 19x1, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {19, 1}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 19x3, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {19, 3}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 1x19, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {1, 19}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 3x19, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {3, 19}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 33x1, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {33, 1}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 33x3, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {33, 3}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 1x33, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {1, 33}, ippBorderRepl);
    }

    SECTION("Ipp16u, C1, src 1024x1024, mask 3x33, replicate border")
    {
        benchmark_filterMedianBorder<Ipp16u, ippi::channels::C1>(
            {1024, 1024}, {3, 33}, ippBorderRepl);
    }
}
