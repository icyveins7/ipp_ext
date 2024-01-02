#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "../include/ipp_ext.h"

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Benchmark (real) array, array to (real) array operations, length 100000", "[real],[basic]")
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

TEST_CASE("Benchmark (complex) array, array to (complex) array operations, length 100000", "[complex],[basic]")
{
    // Setup
    const int length = 100000;
    ippe::vector<Ipp32fc> in1(length);
    ippe::vector<Ipp32fc> in2(length);
    ippe::vector<Ipp32fc> out(length);

    BENCHMARK("ippsAdd_32fc")
    {
        return ippe::math::Add<Ipp32fc>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsSub_32fc")
    {
        return ippe::math::Sub<Ipp32fc>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsMul_32fc")
    {
        return ippe::math::Mul<Ipp32fc>(
            in1.data(), in2.data(), out.data(), length);
    };
}

TEST_CASE("Benchmark conversions between complex and real arrays, length 100000", "[convert]")
{
    // Setup
    const int length = 100000;
    ippe::vector<Ipp32f> real1(length);
    ippe::vector<Ipp32f> real2(length);
    ippe::vector<Ipp32fc> complex1(length);
    ippe::vector<Ipp32f> real3(length);
    ippe::vector<Ipp32f> real4(length);

    BENCHMARK("ippsPolarToCart_32fc")
    {
        return ippe::convert::PolarToCart(
            real1.data(), real2.data(), complex1.data(), length
        );
    };

    BENCHMARK("ippsPolarToCart_32fc deinterleaved")
    {
        return ippe::convert::PolarToCartDeinterleaved(
            real1.data(), real2.data(), real3.data(), real4.data(), length
        );
    };

    BENCHMARK("ippsCartToPolar_32fc")
    {
        return ippe::convert::CartToPolar(
            complex1.data(), real1.data(), real2.data(), length
        );
    };

    BENCHMARK("ippsCplxToReal_32fc")
    {
        return ippe::convert::CplxToReal(
            complex1.data(), real1.data(), real2.data(), length
        );
    };

    BENCHMARK("ippsRealToCplx_32f")
    {
        return ippe::convert::RealToCplx(
            real1.data(), real2.data(), complex1.data(), length
        );
    };
}

TEST_CASE("Benchmark generators, length 100000", "[generators]")
{
    // Setup
    const int length = 100000;
    ippe::vector<Ipp32f> real1(length);
    ippe::vector<Ipp32fc> complex1(length);

    BENCHMARK("ippsTone_32fc")
    {
        Ipp32f phase = 0.0f;
        return ippe::generator::Tone(
            complex1.data(), complex1.size(), 1.0f, 0.1f, &phase
        );
    };

    BENCHMARK("ippsSlope_32f")
    {
        return ippe::generator::Slope(
            real1.data(), real1.size(), 0.0f, 1.0f
        );
    };
}