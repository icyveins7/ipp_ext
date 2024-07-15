#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T, typename U>
void test_Norm_L2()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }

    U norm;
    ipps::stats::Norm_L2(x.data(), x.size(), &norm);

    U checkNorm = 0;
    for (int i = 0; i < 10; i++)
    {
        checkNorm += x[i] * x[i];
    }
    checkNorm = std::sqrt(checkNorm);
    REQUIRE(std::abs(norm - checkNorm) < 1e-10);
}

template <typename T, typename U>
void test_Norm_L2_complex()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i].re = i;
        x[i].im = i;
    }

    U norm;
    ipps::stats::Norm_L2(x.data(), x.size(), &norm);

    U checkNorm = 0;
    for (int i = 0; i < 10; i++)
    {
        checkNorm += x[i].re * x[i].re + x[i].im * x[i].im;
    }
    checkNorm = std::sqrt(checkNorm);
    REQUIRE(std::abs(norm - checkNorm) < 1e-10);
}

TEST_CASE("ipps stats Norm_L2", "[stats], [Norm_L2]")
{
    SECTION("Ipp32f"){
        test_Norm_L2<Ipp32f, Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Norm_L2<Ipp64f, Ipp64f>();
    }
    SECTION("Ipp16s"){
        test_Norm_L2<Ipp16s, Ipp32f>();
    }
    SECTION("Ipp32fc"){
        test_Norm_L2_complex<Ipp32fc, Ipp64f>();
    }
    SECTION("Ipp64fc"){
        test_Norm_L2_complex<Ipp64fc, Ipp64f>();
    }

}

// =====================================================================================================================
template <typename T>
void test_Sum()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }
    
    T sum;
    ipps::stats::Sum(x.data(), x.size(), &sum);
    
    T checkSum = 0;
    for (int i = 0; i < 10; i++){
        checkSum += x[i];
    }
    REQUIRE(std::abs(sum - checkSum) < 1e-10);
}

template <typename T>
void test_Sum_complex()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i].re = i;
        x[i].im = i;
    }
    
    T sum;
    ipps::stats::Sum(x.data(), x.size(), &sum);
    
    T checkSum = {0.0, 0.0};
    for (int i = 0; i < 10; i++){
        checkSum.re += x[i].re;
        checkSum.im += x[i].im;
    }
    REQUIRE(std::abs(sum.re - checkSum.re) < 1e-10);
    REQUIRE(std::abs(sum.im - checkSum.im) < 1e-10);
}

TEST_CASE("ipps stats Sum", "[stats], [Sum]")
{
    SECTION("Ipp32f"){
        test_Sum<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Sum<Ipp64f>();
    }
    SECTION("Ipp32fc"){
        test_Sum_complex<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_Sum_complex<Ipp64fc>();
    }
}

// =====================================================================================================================
template <typename T>
void test_Max()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }
    
    T max;
    ipps::stats::Max(x.data(), x.size(), &max);
    
    T checkMax = 0;
    for (int i = 0; i < 10; i++){
        checkMax = std::max(checkMax, x[i]);
    }
    REQUIRE(std::abs(max - checkMax) < 1e-10);
}

TEST_CASE("ipps stats Max", "[stats], [Max]")
{
    SECTION("Ipp16s"){
        test_Max<Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_Max<Ipp32s>();
    }
    SECTION("Ipp32f"){
        test_Max<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Max<Ipp64f>();
    }
}

// =====================================================================================================================
template <typename T>
void test_MaxIndx()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }
    
    T max;
    int idx;
    ipps::stats::MaxIndx(x.data(), x.size(), &max, &idx);
    
    T checkMax = 0;
    int checkIdx = 0;
    for (int i = 0; i < 10; i++){
        checkMax = std::max(checkMax, x[i]);
        if (checkMax == x[i]){
            checkIdx = i;
        }
    }

    REQUIRE(std::abs(max - checkMax) < 1e-10);
    REQUIRE(idx == checkIdx);
}

TEST_CASE("ipps stats MaxIndx", "[stats], [MaxIndx]")
{
    SECTION("Ipp16s"){
        test_MaxIndx<Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_MaxIndx<Ipp32s>();
    }
    SECTION("Ipp32f"){
        test_MaxIndx<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_MaxIndx<Ipp64f>();
    }
}

// =====================================================================================================================
template <typename T>
void test_Min()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }
    
    T min;
    ipps::stats::Min(x.data(), x.size(), &min);
    
    T checkMin = 0;
    for (int i = 0; i < 10; i++){
        checkMin = std::min(checkMin, x[i]);
    }
    REQUIRE(std::abs(min - checkMin) < 1e-10);
}

TEST_CASE("ipps stats Min", "[stats], [Min]")
{
    SECTION("Ipp16s"){
        test_Min<Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_Min<Ipp32s>();
    }
    SECTION("Ipp32f"){
        test_Min<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_Min<Ipp64f>();
    }
}

// =====================================================================================================================
template <typename T>
void test_MinIndx()
{
    ipps::vector<T> x(10);
    
    for (int i = 0; i < 10; i++)
    {
        x[i] = i;
    }
    
    T min;
    int idx;
    ipps::stats::MinIndx(x.data(), x.size(), &min, &idx);
    
    T checkMin = 0;
    int checkIdx = 0;
    for (int i = 0; i < 10; i++){
        checkMin = std::min(checkMin, x[i]);
        if (checkMin == x[i]){
            checkIdx = i;
        }
    }
    REQUIRE(std::abs(min - checkMin) < 1e-10);
    REQUIRE(idx == checkIdx);
}

TEST_CASE("ipps stats MinIndx", "[stats], [MinIndx]")
{
    SECTION("Ipp16s"){
        test_MinIndx<Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_MinIndx<Ipp32s>();
    }
    SECTION("Ipp32f"){
        test_MinIndx<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_MinIndx<Ipp64f>();
    }
}

// =====================================================================================================================
template <typename T, typename U, typename V>
void test_DotProd_realreal_real()
{
    ipps::vector<T> x(10);
    ipps::vector<U> y(10);
    V z;

    // Make some values
    for (int i = 0; i < 10; i++)
    {
        x[i] = (T)(i+10);
        y[i] = (U)(i+1);
    }

    ipps::stats::DotProd(x.data(), y.data(), x.size(), &z);

    V checkZ = 0;
    for (int i = 0; i < 10; i++){
        checkZ += x[i] * y[i];
    }
    REQUIRE(std::abs(z - checkZ) < 1e-7);
}

template <typename T, typename U, typename V>
void test_DotProd_realcomplex_complex()
{
    ipps::vector<T> x(10);
    ipps::vector<U> y(10);
    V z;

    // Make some values
    for (int i = 0; i < 10; i++)
    {
        x[i] = (T)(i+10);
        y[i].re = (i+1);
        y[i].im = (i+2);
    }

    ipps::stats::DotProd(x.data(), y.data(), x.size(), &z);

    V checkZ = {0, 0};
    for (int i = 0; i < 10; i++){
        checkZ.re += x[i] * y[i].re;
        checkZ.im += x[i] * y[i].im;
    }
    REQUIRE(std::abs(z.re - checkZ.re) < 1e-7);
    REQUIRE(std::abs(z.im - checkZ.im) < 1e-7);
}

template <typename T, typename U, typename V>
void test_DotProd_complexcomplex_complex()
{
    ipps::vector<T> x(10);
    ipps::vector<U> y(10);
    V z;

    // Make some values
    for (int i = 0; i < 10; i++)
    {
        x[i].re = (i+1);
        x[i].im = (i+2);
        y[i].re = (i+3);
        y[i].im = (i+4);
    }

    ipps::stats::DotProd(x.data(), y.data(), x.size(), &z);

    V checkZ = {0, 0};
    for (int i = 0; i < 10; i++){
        checkZ.re += x[i].re * y[i].re - x[i].im * y[i].im;
        checkZ.im += x[i].re * y[i].im + x[i].im * y[i].re;
    }
    REQUIRE(std::abs(z.re - checkZ.re) < 1e-7);
    REQUIRE(std::abs(z.im - checkZ.im) < 1e-7);
}

TEST_CASE("ipps stats DotProd", "[stats], [DotProd]")
{
    SECTION("Ipp32f, Ipp32f -> Ipp32f"){
        test_DotProd_realreal_real<Ipp32f, Ipp32f, Ipp32f>();
    }
    SECTION("Ipp32fc, Ipp32fc -> Ipp32fc"){
        test_DotProd_complexcomplex_complex<Ipp32fc, Ipp32fc, Ipp32fc>();
    }
    SECTION("Ipp32f, Ipp32fc -> Ipp32fc"){
        test_DotProd_realcomplex_complex<Ipp32f, Ipp32fc, Ipp32fc>();
    }

    SECTION("Ipp32f, Ipp32f -> Ipp64f"){
        test_DotProd_realreal_real<Ipp32f, Ipp32f, Ipp64f>();
    }
    SECTION("Ipp32fc, Ipp32fc -> Ipp64fc"){
        test_DotProd_complexcomplex_complex<Ipp32fc, Ipp32fc, Ipp64fc>();
    }
    SECTION("Ipp32f, Ipp32fc -> Ipp64fc"){
        test_DotProd_realcomplex_complex<Ipp32f, Ipp32fc, Ipp64fc>();
    }

    SECTION("Ipp64f, Ipp64f -> Ipp64f"){
        test_DotProd_realreal_real<Ipp64f, Ipp64f, Ipp64f>();
    }
    SECTION("Ipp64fc, Ipp64fc -> Ipp64fc"){
        test_DotProd_complexcomplex_complex<Ipp64fc, Ipp64fc, Ipp64fc>();
    }
    SECTION("Ipp64f, Ipp64fc -> Ipp64fc"){
        test_DotProd_realcomplex_complex<Ipp64f, Ipp64fc, Ipp64fc>();
    }

    SECTION("Ipp16s, Ipp16s -> Ipp64s"){
        test_DotProd_realreal_real<Ipp16s, Ipp16s, Ipp64s>();
    }
    SECTION("Ipp16sc, Ipp16sc -> Ipp64sc"){
        test_DotProd_complexcomplex_complex<Ipp16sc, Ipp16sc, Ipp64sc>();
    }
    SECTION("Ipp16s, Ipp16sc -> Ipp64sc"){
        test_DotProd_realcomplex_complex<Ipp16s, Ipp16sc, Ipp64sc>();
    }

    SECTION("Ipp16s, Ipp16s -> Ipp32f"){
        test_DotProd_realreal_real<Ipp16s, Ipp16s, Ipp32f>();
    }
}

// =====================================================================================================================
template <typename T, typename U, typename V>
void test_DotProdSfs()
{
    ipps::vector<T> x(10);
    ipps::vector<U> y(10);
    V z;

    // Make some values
    for (int i = 0; i < 10; i++)
    {
        x[i] = (T)(i+10);
        y[i] = (U)(i+1);
    }

    ipps::stats::DotProd_Sfs(x.data(), y.data(), x.size(), &z, -1);

    V checkZ = 0;
    for (int i = 0; i < 10; i++){
        checkZ += x[i] * y[i];
    }
    checkZ = checkZ * 2; // from the -1 scale factor?
    REQUIRE(std::abs(z - checkZ) < 1e-7);
}

TEST_CASE("ipps stats DotProd_Sfs", "[stats], [DotProd_Sfs]")
{
    SECTION("Ipp16s, Ipp16s -> Ipp32s"){
        test_DotProdSfs<Ipp16s, Ipp16s, Ipp32s>();
    }
    SECTION("Ipp16s, Ipp32s -> Ipp32s"){
        test_DotProdSfs<Ipp16s, Ipp32s, Ipp32s>();
    }
}
