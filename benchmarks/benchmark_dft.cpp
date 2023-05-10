#include <iostream>
#include <vector>
#include <thread>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Benchmark DFT single-threaded", "[dftCToC],[singlethread]") {
    SECTION("ipp32fc, length 10000"){
        // Setup the DFT object
        ippe::DFTCToC<Ipp32fc> dft(10000);
        ippe::vector<Ipp32fc> in(10000);
        ippe::vector<Ipp32fc> out(10000);
        BENCHMARK("fwd()"){
            return dft.fwd(in.data(), out.data());
        };
    }

    SECTION("ipp32fc, length 100000"){
        // Setup the DFT object
        ippe::DFTCToC<Ipp32fc> dft(100000);
        ippe::vector<Ipp32fc> in(100000);
        ippe::vector<Ipp32fc> out(100000);
        BENCHMARK("fwd()"){
            return dft.fwd(in.data(), out.data());
        };
    }

    SECTION("ipp32fc, length 1000000"){
        // Setup the DFT object
        ippe::DFTCToC<Ipp32fc> dft(1000000);
        ippe::vector<Ipp32fc> in(1000000);
        ippe::vector<Ipp32fc> out(1000000);
        BENCHMARK("fwd()"){
            return dft.fwd(in.data(), out.data());
        };
    }

    SECTION("ipp32fc, length 10000000"){
        // Setup the DFT object
        ippe::DFTCToC<Ipp32fc> dft(10000000);
        ippe::vector<Ipp32fc> in(10000000);
        ippe::vector<Ipp32fc> out(10000000);
        BENCHMARK("fwd()"){
            return dft.fwd(in.data(), out.data());
        };
    }
}



void thread_work(
        ippe::DFTCToC<Ipp32fc> *dft,
        ippe::vector<Ipp32fc> *in,
        ippe::vector<Ipp32fc> *out
){
    dft->fwd(in->data(), out->data());
}
TEST_CASE("Benchmark DFT, 4 threads", "[dftCToC],[multithread]") {
    SECTION("ipp32fc, length 10000"){
        // Setup 4 objects, 1 per thread
        ippe::DFTCToC<Ipp32fc> dft[4];
        ippe::vector<Ipp32fc> in[4];
        ippe::vector<Ipp32fc> out[4];
        for (int i = 0; i < 4; i++){
            dft[i] = ippe::DFTCToC<Ipp32fc>(10000);
            in[i] = ippe::vector<Ipp32fc>(10000);
            out[i] = ippe::vector<Ipp32fc>(10000);
        }

        BENCHMARK("fwd()"){
            // Create threads and time until joined
            std::thread thd[4];
            for (int i = 0; i < 4; i++){
                thd[i] = std::thread(thread_work, &dft[i], &in[i], &out[i]);
            }
            for (int i = 0; i < 4; i++){
                thd[i].join();
            }
    
        };
    }
}

