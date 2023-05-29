/*
This is not strictly an ipp_ext benchmark, but rather just a benchmark of IPP vs Eigen.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "ipp_ext.h"

#include <Eigen/Dense>

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

TEST_CASE("Benchmark with Eigen Vector", "[Vector]") {
    SECTION("Add, length 100000"){
        // Create eigen vector
        Eigen::VectorXf e_a(100000);
        Eigen::VectorXf e_b(100000);
        Eigen::VectorXf e_out(100000);

        // Set some values
        for (int i = 0; i < 100000; i++) {
            e_a[i] = (float)i;
            e_b[i] = (float)(i*2 + 0.1);
        }

        BENCHMARK("Eigen Vector Add") {
            e_out = e_a + e_b;
            return e_out;
        };

        // Create ipp vectors
        ippe::vector<Ipp32f> i_a(100000);
        ippe::vector<Ipp32f> i_b(100000);
        ippe::vector<Ipp32f> i_out(100000);

        // Set some values
        for (int i = 0; i < i_a.size(); i++) {
            i_a[i] = (float)i;
            i_b[i] = (float)(i*2 + 0.1);
        }

        BENCHMARK("IPP Vector Add") {
            return ippsAdd_32f(i_a.data(), i_b.data(), i_out.data(), i_out.size());
        };

        BENCHMARK("Raw Loop"){
            for (int i = 0; i < i_a.size(); i++) {
                i_out[i] = i_a[i] + i_b[i];
            }
            return i_out;
        };
    }

    SECTION("Add, length 1000000"){
        // Create eigen vector
        Eigen::VectorXf e_a(1000000);
        Eigen::VectorXf e_b(1000000);
        Eigen::VectorXf e_out(1000000);
        
        // Set some values
        for (int i = 0; i < 1000000; i++) {
            e_a[i] = (float)i;
            e_b[i] = (float)(i*2 + 0.1);
        }

        BENCHMARK("Eigen Vector Add") {
            e_out = e_a + e_b;
            return e_out;
        };
        
        // Create ipp vectors
        ippe::vector<Ipp32f> i_a(1000000);
        ippe::vector<Ipp32f> i_b(1000000);
        ippe::vector<Ipp32f> i_out(1000000);

        // Set some values
        for (int i = 0; i < i_a.size(); i++) {
            i_a[i] = (float)i;
            i_b[i] = (float)(i*2 + 0.1);
        }
        
        BENCHMARK("IPP Vector Add") {
            return ippsAdd_32f(i_a.data(), i_b.data(), i_out.data(), i_out.size());
        };

        BENCHMARK("Raw Loop"){
            for (int i = 0; i < i_a.size(); i++) {
                i_out[i] = i_a[i] + i_b[i];
            }
            return i_out;
        };
    }  
}

TEST_CASE("Benchmark with Eigen Array", "[Array]") {
    SECTION("Element-wise multiply, length 100000"){
        // Create eigen array, for element-wise multiply
        Eigen::ArrayXf e_a(100000);
        Eigen::ArrayXf e_b(100000);
        Eigen::ArrayXf e_out(100000);
        
        // Set some values
        for (int i = 0; i < 100000; i++) {
            e_a[i] = (float)i;
            e_b[i] = (float)(i*2 + 0.1);
        }
        
        BENCHMARK("Eigen Array Multiply") {
            e_out = e_a * e_b;
            return e_out;
        };

        // Create ipp vectors
        ippe::vector<Ipp32f> i_a(100000);
        ippe::vector<Ipp32f> i_b(100000);
        ippe::vector<Ipp32f> i_out(100000);

        // Set some values
        for (int i = 0; i < i_a.size(); i++) {
            i_a[i] = (float)i;
            i_b[i] = (float)(i*2 + 0.1);
        }

        BENCHMARK("IPP Array Multiply") {
            return ippsMul_32f(i_a.data(), i_b.data(), i_out.data(), i_out.size());
        };

        BENCHMARK("Raw Loop"){
            for (int i = 0; i < i_a.size(); i++) {
                i_out[i] = i_a[i] * i_b[i];
            }
            return i_out;
        };
    }
}