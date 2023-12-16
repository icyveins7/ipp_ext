#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "../include/ipp_ext.h"

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Benchmark (real) array, array to (real) array operations, length 100000")
{
    // Setup
    const int length = 100000;
    ippe::vector<Ipp32f> in1(length);
    ippe::vector<Ipp32f> in2(length);
    ippe::vector<Ipp32f> out(length);

    BENCHMARK("ippsAdd_32f")
    {
        return ippe::math::Add<Ipp32f>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsSub_32f")
    {
        return ippe::math::Sub<Ipp32f>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsMul_32f")
    {
        return ippe::math::Mul<Ipp32f>(
            in1.data(), in2.data(), out.data(), length);
    };


}