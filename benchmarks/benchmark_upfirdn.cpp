#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "../include/ipp_ext.h"

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Benchmark upfirdn implementations", "[upfirdn],[naive],[FIRMR]")
{
    SECTION("Ipp32fc taps length 128, Ipp32fc data length 30000, factors 5/3")
    {
        ipps::vector<Ipp32fc> data(30000);
        int up = 5, down = 3;
        ipps::filter::FIRMR<Ipp32fc, Ipp32fc> filter(
            ipps::filter::generateLowpassTaps<Ipp32fc>(0.2/2, 128, ippWinHamming, ippTrue),
            up, 0, down, 0
        );

        ipps::vector<Ipp32fc> result(data.size() * up / down);

        BENCHMARK("FIRMR")
        {
            filter.filter(
                data.data(), result.data(),
                data.size(), result.size()
            );

            return 0;
        };

        BENCHMARK("upfirdn naive")
        {
            auto& taps = filter.getTaps();
            for (int i = 0; i < (int)result.size(); i++)
            {
                Ipp32fc value = {0, 0};
                for (int j = 0; j < (int)taps.size(); j++)
                {
                    if ((i * down - j) >= 0 && (i * down - j) % up == 0 )
                    {
                        value.re += taps[j].re * data[ (i * down - j) / up].re;
                        value.im += taps[j].re * data[ (i * down - j) / up].im;
                    }
                }

                result[i] = value;
            }

            return 0;
        };
    }
}
