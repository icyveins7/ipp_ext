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
Eigen::VectorXf* add_eigen(
    const Eigen::VectorXf &e_a,
    const Eigen::VectorXf &e_b,
    Eigen::VectorXf &e_out
){
    e_out = e_a + e_b;
    return &e_out;
}

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
            return add_eigen(e_a, e_b, e_out);
        };

        // Create ipp vectors
        ipps::vector<Ipp32f> i_a(100000);
        ipps::vector<Ipp32f> i_b(100000);
        ipps::vector<Ipp32f> i_out(100000);

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
            return i_out.data();
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
            return add_eigen(e_a, e_b, e_out);
        };
        
        // Create ipp vectors
        ipps::vector<Ipp32f> i_a(1000000);
        ipps::vector<Ipp32f> i_b(1000000);
        ipps::vector<Ipp32f> i_out(1000000);

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
            return i_out.data();
        };

        BENCHMARK("Raw loop with explicit pointer cast"){
            // This may help for MSVC, where loop vectorisation doesn't seem to work very well for vectors
            Ipp32f* i_out_ptr = (Ipp32f*) i_out.data();
            Ipp32f* i_a_ptr  = (Ipp32f*) i_a.data();
            Ipp32f* i_b_ptr  = (Ipp32f*) i_b.data();
            for (int i = 0; i < i_a.size(); i++) {
                i_out_ptr[i] = i_a_ptr[i] + i_b_ptr[i];
            }
            return i_out.data();
        };

        BENCHMARK("Raw loop with explicit pointer cast and explicit 4x UNROLL"){
            Ipp32f* i_out_ptr = (Ipp32f*) i_out.data();
            Ipp32f* i_a_ptr  = (Ipp32f*) i_a.data();
            Ipp32f* i_b_ptr  = (Ipp32f*) i_b.data();

            for (int i = 0; i < i_a.size() / 4; ++i){
                i_out_ptr[i*4 + 0] = i_a_ptr[i*4 + 0] + i_b_ptr[i*4 + 0];
                i_out_ptr[i*4 + 1] = i_a_ptr[i*4 + 1] + i_b_ptr[i*4 + 1];
                i_out_ptr[i*4 + 2] = i_a_ptr[i*4 + 1] + i_b_ptr[i*4 + 2];
                i_out_ptr[i*4 + 3] = i_a_ptr[i*4 + 3] + i_b_ptr[i*4 + 3]; 
            }
            return i_out.data();
        };
    }  
}

///////////////////////////////////////////////////////////////////////////////

Eigen::ArrayXf* multiply_eigen(
    const Eigen::ArrayXf &e_a,
    const Eigen::ArrayXf &e_b,
    Eigen::ArrayXf &e_out
){
    e_out = e_a * e_b;
    return &e_out;
}

TEST_CASE("Benchmark with Eigen Array", "[Array]") {
    SECTION("Element-wise multiply, length 100000"){

        size_t len = 100000;

        // Create eigen array, for element-wise multiply
        Eigen::ArrayXf e_a(len);
        Eigen::ArrayXf e_b(len);
        Eigen::ArrayXf e_out(len);
        
        // Set some values
        for (int i = 0; i < len; i++) {
            e_a[i] = (float)i;
            e_b[i] = (float)(i*2 + 0.1);
        }
        
        BENCHMARK("Eigen Array Multiply") {
            return multiply_eigen(e_a, e_b, e_out);
        };

        // Create ipp vectors
        ipps::vector<Ipp32f> i_a(len);
        ipps::vector<Ipp32f> i_b(len);
        ipps::vector<Ipp32f> i_out(len);

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
            return i_out.data();
        };
    }

    SECTION("Element-wise multiply, length 1000000"){

        size_t len = 1000000;

        // Create eigen array, for element-wise multiply
        Eigen::ArrayXf e_a(len);
        Eigen::ArrayXf e_b(len);
        Eigen::ArrayXf e_out(len);
        
        // Set some values
        for (int i = 0; i < len; i++) {
            e_a[i] = (float)i;
            e_b[i] = (float)(i*2 + 0.1);
        }
        
        BENCHMARK("Eigen Array Multiply") {
            return multiply_eigen(e_a, e_b, e_out);
        };

        // Create ipp vectors
        ipps::vector<Ipp32f> i_a(len);
        ipps::vector<Ipp32f> i_b(len);
        ipps::vector<Ipp32f> i_out(len);

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
            return i_out.data();
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
        return &e_out;
    };

    // Create ipp matrix
    ipps::matrix<Ipp32f> i_a(ii, jj);
    ipps::matrix<Ipp32f> i_b(jj, kk);
    ipps::matrix<Ipp32f> i_out(ii, kk);

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
        return i_out.data();
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
        return i_out.data();
    };
}

TEST_CASE("Benchmark with Eigen matrix multiplication", "[Matrix],[matmul]")
{
    // many rows, against 1 column vector
    SECTION("Matmul Ipp32f, 3x1000, 1000x1"){
        bench_matmul_32f(3, 1000, 1);
    }

    // few short inner dimensions
    SECTION("Matmul Ipp32f, 3x2, 2x3"){
        bench_matmul_32f(3, 2, 3);
    }

    // few long inner dimensions (this is when sampledown does well)
    SECTION("Matmul Ipp32f, 3x1000, 1000x3"){
        bench_matmul_32f(3, 1000, 3);
    }

    // few medium inner dimensions (find out when the breakeven point is)
    SECTION("Matmul Ipp32f, 3x100, 100x3"){
        bench_matmul_32f(3, 100, 3);
    }

    SECTION("Matmul Ipp32f, 3x10, 10x3"){
        bench_matmul_32f(3, 10, 3);
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
