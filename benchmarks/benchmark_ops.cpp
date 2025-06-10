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
    ipps::vector<Ipp32f> in1(length);
    ipps::vector<Ipp32f> in2(length);
    ipps::vector<Ipp32f> out(length);

    BENCHMARK("ippsAdd_32f")
    {
        return ipps::math::Add<Ipp32f>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsSub_32f")
    {
        return ipps::math::Sub<Ipp32f>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsMul_32f")
    {
        return ipps::math::Mul<Ipp32f>(
            in1.data(), in2.data(), out.data(), length);
    };


}

TEST_CASE("Benchmark (complex) array, array to (complex) array operations, length 100000", "[complex],[basic]")
{
    // Setup
    const int length = 100000;
    ipps::vector<Ipp32fc> in1(length);
    ipps::vector<Ipp32fc> in2(length);
    ipps::vector<Ipp32fc> out(length);

    BENCHMARK("ippsAdd_32fc")
    {
        return ipps::math::Add<Ipp32fc>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsSub_32fc")
    {
        return ipps::math::Sub<Ipp32fc>(
            in1.data(), in2.data(), out.data(), length);
    };

    BENCHMARK("ippsMul_32fc")
    {
        return ipps::math::Mul<Ipp32fc>(
            in1.data(), in2.data(), out.data(), length);
    };
}

TEST_CASE("Benchmark conversions between complex and real arrays, length 100000", "[convert]")
{
    // Setup
    const int length = 100000;
    ipps::vector<Ipp32f> real1(length);
    ipps::vector<Ipp32f> real2(length);
    ipps::vector<Ipp32fc> complex1(length);
    ipps::vector<Ipp32f> real3(length);
    ipps::vector<Ipp32f> real4(length);

    BENCHMARK("ippsPolarToCart_32fc")
    {
        return ipps::convert::PolarToCart(
            real1.data(), real2.data(), complex1.data(), length
        );
    };

    BENCHMARK("ippsPolarToCart_32fc deinterleaved")
    {
        return ipps::convert::PolarToCartDeinterleaved(
            real1.data(), real2.data(), real3.data(), real4.data(), length
        );
    };

    BENCHMARK("ippsCartToPolar_32fc")
    {
        return ipps::convert::CartToPolar(
            complex1.data(), real1.data(), real2.data(), length
        );
    };

    BENCHMARK("ippsCplxToReal_32fc")
    {
        return ipps::convert::CplxToReal(
            complex1.data(), real1.data(), real2.data(), length
        );
    };

    BENCHMARK("ippsRealToCplx_32f")
    {
        return ipps::convert::RealToCplx(
            real1.data(), real2.data(), complex1.data(), length
        );
    };
}

TEST_CASE("Benchmark generators, length 100000", "[generators]")
{
    // Setup
    const int length = 100000;
    ipps::vector<Ipp32f> real1(length);
    ipps::vector<Ipp32fc> complex1(length);

    BENCHMARK("ippsTone_32fc")
    {
        Ipp32f phase = 0.0f;
        return ipps::generator::Tone(
            complex1.data(), (int)complex1.size(), 1.0f, 0.1f, &phase
        );
    };

    BENCHMARK("ippsSlope_32f")
    {
        return ipps::generator::Slope(
            real1.data(), (int)real1.size(), 0.0f, 1.0f
        );
    };
}

TEST_CASE("Benchmark statistics/reductions", "[statistics]")
{
    SECTION("32f, length 10000"){
        const int length = 10000;
        ipps::vector<Ipp32f> x(length);
        // Generate random numbers
        for (int i = 0; i < length; i++)
        {
            x[i] = static_cast<Ipp32f>(rand() % 100);
        }
        BENCHMARK("std::max_element"){
            auto max = std::max_element(x.begin(), x.end());
            return max;
        };

        BENCHMARK("loop with std::max"){
            Ipp32f max = x[0];
            for (int i = 1; i < length; i++)
                max = std::max(max, x[i]);

            return max;
        };

        BENCHMARK("ippsMax_32f"){
            Ipp32f max;
            ipps::stats::Max(x.data(), (int)x.size(), &max);

            return max;
        };

        BENCHMARK("ippsMaxIndx_32f"){
            Ipp32f max;
            int index;
            ipps::stats::MaxIndx(x.data(), (int)x.size(), &max, &index);

            return max;
        };
    }

    SECTION("32f, length 100000"){
        const int length = 100000;
        ipps::vector<Ipp32f> x(length);
        // Generate random numbers
        for (int i = 0; i < length; i++)
        {
            x[i] = static_cast<Ipp32f>(rand() % 100);
        }
        BENCHMARK("std::max_element"){
            auto max = std::max_element(x.begin(), x.end());
            return max;
        };

        BENCHMARK("loop with std::max"){
            Ipp32f max = x[0];
            for (int i = 1; i < length; i++)
                max = std::max(max, x[i]);

            return max;
        };

        BENCHMARK("ippsMax_32f"){
            Ipp32f max;
            ipps::stats::Max(x.data(), (int)x.size(), &max);

            return max;
        };

        BENCHMARK("ippsMaxIndx_32f"){
            Ipp32f max;
            int index;
            ipps::stats::MaxIndx(x.data(), (int)x.size(), &max, &index);

            return max;
        };
    }
}
