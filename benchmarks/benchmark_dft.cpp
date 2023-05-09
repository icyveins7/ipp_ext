#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Benchmark DFT", "[dftCToC]") {
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

// TEST_CASE("Benchmark containers", "[!benchmark]") {
//     static const int size = 100;

//     std::vector<int> v;
//     std::map<int, int> m;

//     SECTION("without generator") {
//         BENCHMARK("Load up a vector") {
//             v = std::vector<int>();
//             for (int i = 0; i < size; ++i)
//                 v.push_back(i);
//         };
//         REQUIRE(v.size() == size);

//         // test optimizer control
//         BENCHMARK("Add up a vector's content") {
//             uint64_t add = 0;
//             for (int i = 0; i < size; ++i)
//                 add += v[i];
//             return add;
//         };

//         BENCHMARK("Load up a map") {
//             m = std::map<int, int>();
//             for (int i = 0; i < size; ++i)
//                 m.insert({ i, i + 1 });
//         };
//         REQUIRE(m.size() == size);

//         BENCHMARK("Reserved vector") {
//             v = std::vector<int>();
//             v.reserve(size);
//             for (int i = 0; i < size; ++i)
//                 v.push_back(i);
//         };
//         REQUIRE(v.size() == size);

//         BENCHMARK("Resized vector") {
//             v = std::vector<int>();
//             v.resize(size);
//             for (int i = 0; i < size; ++i)
//                 v[i] = i;
//         };
//         REQUIRE(v.size() == size);

//         int array[size];
//         BENCHMARK("A fixed size array that should require no allocations") {
//             for (int i = 0; i < size; ++i)
//                 array[i] = i;
//         };
//         int sum = 0;
//         for (int i = 0; i < size; ++i)
//             sum += array[i];
//         REQUIRE(sum > size);

//         SECTION("XYZ") {

//             BENCHMARK_ADVANCED("Load up vector with chronometer")(Catch::Benchmark::Chronometer meter) {
//                 std::vector<int> k;
//                 meter.measure([&](int idx) {
//                     k = std::vector<int>();
//                     for (int i = 0; i < size; ++i)
//                         k.push_back(idx);
//                 });
//                 REQUIRE(k.size() == size);
//             };

//             int runs = 0;
//             BENCHMARK("Fill vector indexed", benchmarkIndex) {
//                 v = std::vector<int>();
//                 v.resize(size);
//                 for (int i = 0; i < size; ++i)
//                     v[i] = benchmarkIndex;
//                 runs = benchmarkIndex;
//             };

//             for (size_t i = 0; i < v.size(); ++i) {
//                 REQUIRE(v[i] == runs);
//             }
//         }
//     }

//     SECTION("with generator") {
//         auto generated = GENERATE(range(0, 10));
//         BENCHMARK("Fill vector generated") {
//             v = std::vector<int>();
//             v.resize(size);
//             for (int i = 0; i < size; ++i)
//                 v[i] = generated;
//         };
//         for (size_t i = 0; i < v.size(); ++i) {
//             REQUIRE(v[i] == generated);
//         }
//     }

//     SECTION("construct and destroy example") {
//         BENCHMARK_ADVANCED("construct")(Catch::Benchmark::Chronometer meter) {
//             std::vector<Catch::Benchmark::storage_for<std::string>> storage(meter.runs());
//             meter.measure([&](int i) { storage[i].construct("thing"); });
//         };

//         BENCHMARK_ADVANCED("destroy")(Catch::Benchmark::Chronometer meter) {
//             std::vector<Catch::Benchmark::destructable_object<std::string>> storage(meter.runs());
//             for(auto&& o : storage)
//                 o.construct("thing");
//             meter.measure([&](int i) { storage[i].destruct(); });
//         };
//     }
// }

// TEST_CASE("Skip benchmark macros", "[!benchmark]") {
//     std::vector<int> v;
//     BENCHMARK("fill vector") {
//         v.emplace_back(1);
//         v.emplace_back(2);
//         v.emplace_back(3);
//     };
//     REQUIRE(v.size() == 0);

//     std::size_t counter{0};
//     BENCHMARK_ADVANCED("construct vector")(Catch::Benchmark::Chronometer meter) {
//         std::vector<Catch::Benchmark::storage_for<std::string>> storage(meter.runs());
//         meter.measure([&](int i) { storage[i].construct("thing"); counter++; });
//     };
//     REQUIRE(counter == 0);
// }

