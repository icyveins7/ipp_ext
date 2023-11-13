/*
This is not strictly an ipp_ext benchmark, but rather just a benchmark of IPP vs Eigen.
*/

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "ipp_ext.h"

#define EIGEN_RUNTIME_NO_MALLOC // Define this symbol to enable runtime tests for allocations
#include <Eigen/Dense>

#include <catch2/catch_test_macros.hpp>
// Also include benchmarking headers, i don't really know which one is necessary
#include <catch2/benchmark/catch_benchmark.hpp>

///////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////
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


///////////////////////////////////////////////////////////////////////////////

void bench_matmul_32f(int ii, int jj, int kk)
{
    // Create eigen matrix
    Eigen::MatrixXf e_a(ii, jj);
    Eigen::MatrixXf e_b(jj, kk);
    Eigen::MatrixXf e_out(ii, kk);

    // Set some values
    for (int i = 0; i < ii; i++) {
        for (int j = 0; j < jj; j++) {
            e_a(i, j) = (float)i;
        }
    }

    for (int i = 0; i < jj; i++) {
        for (int j = 0; j < kk; j++) {
            e_b(i, j) = (float)(i*2 + 0.1);
        }
    }

    BENCHMARK("Eigen Matrix Multiply") {
        e_out.noalias() = e_a * e_b; // use noalias to avoid temporary copies according to Eigen?
        return e_out;
    };

    // Create ipp matrix
    ippe::matrix<Ipp32f> i_a(ii, jj);
    ippe::matrix<Ipp32f> i_b(jj, kk);
    ippe::matrix<Ipp32f> i_out(ii, kk);

    // Set some values
    for (int i = 0; i < ii; i++) {
        for (int j = 0; j < jj; j++) {
            i_a.index(i, j) = (float)i;
        }
    }

    for (int i = 0; i < jj; i++) {
        for (int j = 0; j < kk; j++) {
            i_b.index(i, j) = (float)(i*2 + 0.1);
        }
    }

    BENCHMARK("IPP Matrix Multiply") {
        i_out = i_a * i_b;
        return i_out;
    };

    BENCHMARK("Raw loop")
    {
        for (int i = 0; i < i_out.rows(); i++) {
            
            for (int j = 0; j < i_out.columns(); j++) {
                Ipp32f sum = 0.0f;
                for (int k = 0; k < i_a.columns(); k++) {
                    sum += i_a.index(i, k) * i_b.index(k, j);
                }
                i_out.index(i, j) = sum;
            }
        }
        return i_out;
    };
}

TEST_CASE("Benchmark with Eigen matrix multiplication", "[Matrix],[matmul]")
{
    // few short inner dimensions
    SECTION("Matmul Ipp32f, 3x2, 2x3"){
        bench_matmul_32f(3, 2, 3);
    }

    // few long inner dimensions
    SECTION("Matmul Ipp32f, 3x1000, 1000x3"){
        bench_matmul_32f(3, 1000, 3);
    }

    // many short inner dimensions
    SECTION("Matmul Ipp32f, 1000x3, 3x1000"){
        bench_matmul_32f(1000, 3, 1000);
    }

    // many long inner dimensions
    SECTION("Matmul Ipp32f, 1000x1000, 1000x1000"){
        bench_matmul_32f(1000, 1000, 1000);
    }
}