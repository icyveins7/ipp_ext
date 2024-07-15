#include <iostream>
#include <cmath>
#include <vector>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T>
void test_gen_lowpass_taps()
{
    double tolerance = 1e-6;
    // hard coded taps
    const int tapsLen = 8;
    const double window = 0.5;
    Ipp64f taps_ref[tapsLen] = {
        -0.0051643 , -0.02288252,  0.09675565,  0.43129117,
        0.43129117,  0.09675565, -0.02288252, -0.0051643
    };

    // generate taps
    ipps::vector<T> taps = ipps::filter::generateLowpassTaps<T>(window/2.0, tapsLen, ippWinHamming, ippTrue);

    // check with threshold
    for (int i = 0; i < tapsLen; i++)
    {
        REQUIRE(std::abs(taps[i] - taps_ref[i]) < tolerance);
    }
}

template <typename T>
void test_gen_lowpass_taps_cplx()
{
    double tolerance = 1e-6;
    // hard coded taps
    const int tapsLen = 8;
    const double window = 0.5;
    Ipp64f taps_ref[tapsLen] = {
        -0.0051643 , -0.02288252,  0.09675565,  0.43129117,
        0.43129117,  0.09675565, -0.02288252, -0.0051643
    };

    // generate taps
    ipps::vector<T> taps = ipps::filter::generateLowpassTaps<T>(window/2.0, tapsLen, ippWinHamming, ippTrue);

    // check with threshold
    for (int i = 0; i < tapsLen; i++)
    {
        REQUIRE(std::abs(taps[i].re - taps_ref[i]) < tolerance);
    }
}

TEST_CASE("ipps filter taps generation", "[filter],[taps]")
{
    SECTION("Ipp32f lowpass"){
        test_gen_lowpass_taps<Ipp32f>();
    }
    SECTION("Ipp32fc lowpass"){
        test_gen_lowpass_taps_cplx<Ipp32fc>();
    }
    SECTION("Ipp64f lowpass"){
        test_gen_lowpass_taps<Ipp64f>();
    }
    SECTION("Ipp64fc lowpass"){
        test_gen_lowpass_taps_cplx<Ipp64fc>();
    }
}

////////////////////////////////////////////////////


template <typename T, typename U>
void test_FIRSR_lowpass()
{
    // Create the taps
    ipps::vector<T> taps = ipps::filter::generateLowpassTaps<T>(0.5/2.0, 8, ippWinHamming, ippTrue);

    // Create the filter with taps
    ipps::filter::FIRSR<T, U> filter(taps);

    // Check that the delay is all zeros
    for (int i = 0; i < filter.getDelayVector().size(); i++)
    {
        REQUIRE(filter.getDelayVector()[i] == (U)0.0);
    }

    // Check that the taps are correct
    for (int i = 0; i < 8; i++)
    {
        REQUIRE(filter.getTaps()[i] == taps[i]);
    }

    // Create some data
    ipps::vector<U> data(16);
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = i;
    }

    // Apply the filter
    ipps::vector<U> result(data.size());
    filter.filter(data.data(), result.data(), (int)result.size());

    // Check that the result is correct
    for (int i = 0; i < result.size(); i++)
    {
        U value = 0.0;
        for (int j = 0; j < taps.size(); j++)
        {
            if (i - j >= 0)
                value += taps[j] * data[i - j];
        }
        REQUIRE(std::abs(result[i] - value) < 1e-6); // use some threshold cause it's not exact
    }

    // Check that the delay is set correctly
    const ipps::vector<U> &delay = filter.getDelayVector();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i] == data[data.size()-delay.size()+i]);
    }

    // Reset the delay and check again
    filter.reset();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i] == (U)0.0);
    }

    // Test copy and assignment
    std::vector<ipps::filter::FIRSR<T,U>> filters(1);
    filters.at(0) = filter; // assignment
    filters.push_back(filter); // copy

    // Check that the internal vectors are distinct, but the values are the same
    for (int i = 0; i < filters.size(); i++)
    {
        REQUIRE(&filters.at(i).getTaps() != &filter.getTaps());
        REQUIRE(filters.at(i).getDelay() != filter.getDelay());
        for (int j = 0; j < filters.at(i).getTaps().size(); j++)
        {
            REQUIRE(filters.at(i).getTaps()[j] == filter.getTaps()[j]);
        }
    }
}

template <typename T, typename U>
void test_FIRSR_lowpass_cplx()
{
    // Create the taps
    ipps::vector<T> taps = ipps::filter::generateLowpassTaps<T>(0.5/2.0, 8, ippWinHamming, ippTrue);

    // Create the filter with taps
    ipps::filter::FIRSR<T, U> filter(taps);

    // Check that the delay is all zeros
    for (int i = 0; i < filter.getDelayVector().size(); i++)
    {
        REQUIRE(filter.getDelayVector()[i].re == 0);
        REQUIRE(filter.getDelayVector()[i].im == 0);
    }

    // Check that the taps are correct
    for (int i = 0; i < 8; i++)
    {
        REQUIRE(filter.getTaps()[i].re == taps[i].re);
        REQUIRE(filter.getTaps()[i].im == taps[i].im);
    }

    // Create some data
    ipps::vector<U> data(16);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].re = i;
        data[i].im = i + 1;
    }

    // Apply the filter
    ipps::vector<U> result(data.size());
    filter.filter(data.data(), result.data(), (int)result.size());

    // Check that the result is correct
    for (int i = 0; i < result.size(); i++)
    {
        U value = {0, 0};
        for (int j = 0; j < taps.size(); j++)
        {
            if (i - j >= 0)
            {
                value.re += taps[j].re * data[i - j].re;
                value.im += taps[j].re * data[i - j].im;
            }
                
        }
        REQUIRE(std::abs(result[i].re - value.re) < 1e-6); // use some threshold cause it's not exact
        REQUIRE(std::abs(result[i].im - value.im) < 1e-6);
    }

    // Check that the delay is set correctly
    const ipps::vector<U> &delay = filter.getDelayVector();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i].re == data[data.size()-delay.size()+i].re);
        REQUIRE(delay[i].im == data[data.size()-delay.size()+i].im);
    }

    // Reset the delay and check again
    filter.reset();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i].re == 0);
        REQUIRE(delay[i].im == 0);
    }

    // Test copy and assignment
    std::vector<ipps::filter::FIRSR<T,U>> filters(1);
    filters.at(0) = filter; // assignment
    filters.push_back(filter); // copy

    // Check that the internal vectors are distinct, but the values are the same
    for (int i = 0; i < filters.size(); i++)
    {
        REQUIRE(&filters.at(i).getTaps() != &filter.getTaps());
        REQUIRE(filters.at(i).getDelay() != filter.getDelay());
        for (int j = 0; j < filters.at(i).getTaps().size(); j++)
        {
            REQUIRE(filters.at(i).getTaps()[j].re == filter.getTaps()[j].re);
            REQUIRE(filters.at(i).getTaps()[j].im == filter.getTaps()[j].im);
        }
    }

}

TEST_CASE("ipps filter FIRSR lowpass", "[filter],[firsr],[lowpass]")
{
    SECTION("Ipp32f taps, Ipp32f data"){
        test_FIRSR_lowpass<Ipp32f, Ipp32f>();
    }
    SECTION("Ipp64f taps, Ipp64f data"){
        test_FIRSR_lowpass<Ipp64f, Ipp64f>();
    }
    SECTION("Ipp32fc taps, Ipp32fc data"){
        test_FIRSR_lowpass_cplx<Ipp32fc, Ipp32fc>();
    }
    SECTION("Ipp64fc taps, Ipp64fc data"){
        test_FIRSR_lowpass_cplx<Ipp64fc, Ipp64fc>();
    }
    // Special case (disabled for now as I'm not sure how this mixed version works; it's not as i would expect)
    // SECTION("Ipp32f taps, Ipp32fc data")
    // {
    //     // Create the taps
    //     ipps::vector<Ipp32f> taps = ipps::filter::generateLowpassTaps<Ipp32f>(0.5/2.0, 8, ippWinHamming, ippTrue);

    //     // Create the filter with taps
    //     ipps::filter::FIRSR<Ipp32f, Ipp32fc> filter(taps);

    //     // Check that the delay is all zeros
    //     for (int i = 0; i < filter.getDelayVector().size(); i++)
    //     {
    //         REQUIRE(filter.getDelayVector()[i].re == 0);
    //         REQUIRE(filter.getDelayVector()[i].im == 0);
    //     }

    //     // Check that the taps are correct
    //     for (int i = 0; i < 8; i++)
    //     {
    //         REQUIRE(filter.getTaps()[i] == taps[i]);
    //     }

    //     // Create some data
    //     ipps::vector<Ipp32fc> data(16);
    //     for (int i = 0; i < data.size(); i++)
    //     {
    //         data[i].re = i;
    //         data[i].im = i + 1;
    //     }

    //     // Apply the filter
    //     ipps::vector<Ipp32fc> result(data.size());
    //     filter.filter(data.data(), result.data(), (int)result.size());

    //     // Check that the result is correct
    //     for (int i = 0; i < result.size(); i++)
    //     {
    //         Ipp32fc value = {0, 0};
    //         for (int j = 0; j < taps.size(); j++)
    //         {
    //             if (i - j >= 0)
    //             {
    //                 value.re += taps[j] * data[i - j].re;
    //                 value.im += taps[j] * data[i - j].im;
    //             }
    //         }
    //         printf("%d, %f %f\n", i, result[i].re, result[i].im);
    //         REQUIRE(std::abs(result[i].re - value.re) < 1e-6); // use some threshold cause it's not exact
    //         REQUIRE(std::abs(result[i].im - value.im) < 1e-6);
    //     }

    //     // Check that the delay is set correctly
    //     const ipps::vector<Ipp32fc> &delay = filter.getDelayVector();
    //     for (int i = 0; i < delay.size(); i++)
    //     {
    //         REQUIRE(delay[i].re == data[data.size()-delay.size()+i].re);
    //         REQUIRE(delay[i].im == data[data.size()-delay.size()+i].im);
    //     }

    //     // Reset the delay and check again
    //     filter.reset();
    //     for (int i = 0; i < delay.size(); i++)
    //     {
    //         REQUIRE(delay[i].re == 0);
    //         REQUIRE(delay[i].im == 0);
    //     }

    //     // Test copy and assignment
    //     std::vector<ipps::filter::FIRSR<Ipp32f, Ipp32fc>> filters(1);
    //     filters.at(0) = filter; // assignment
    //     filters.push_back(filter); // copy

    //     // Check that the internal vectors are distinct, but the values are the same
    //     for (int i = 0; i < filters.size(); i++)
    //     {
    //         REQUIRE(&filters.at(i).getTaps() != &filter.getTaps());
    //         REQUIRE(filters.at(i).getDelay() != filter.getDelay());
    //         for (int j = 0; j < filters.at(i).getTaps().size(); j++)
    //         {
    //             REQUIRE(filters.at(i).getTaps()[j] == filter.getTaps()[j]);
    //         }
    //     }
    // }

    // Skipping the mixed int/floating tests for now; would need to perform a lot of custom conversions
    // SECTION("Ipp32fc taps, Ipp16s data"){
    //     test_FIRSR_lowpass_cplx<Ipp32fc, Ipp16s>();
    // }
    // SECTION("Ipp32f taps, Ipp16s data"){
    //     test_FIRSR_lowpass<Ipp32f, Ipp16s>();
    // }
}

template <typename T, typename U>
void test_FIRMR_lowpass()
{
    // Create filter and taps
    int up = 5;
    int down = 3;
    ipps::filter::FIRMR<T,U> filter(
        ipps::filter::generateLowpassTaps<T>(0.5/2.0, 8, ippWinHamming, ippTrue),
        up, 0, down, 0
    );

    // Create some data
    ipps::vector<U> data(30);
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = 10 + i;
    }

    // Apply the filter
    ipps::vector<U> result(data.size() * up / down);
    filter.filter(data.data(), result.data(), data.size(), result.size());

    // Check results
    for (int i = 0; i < result.size(); i++)
    {
        U value = 0;
        for (int j = 0; j < filter.getTaps().size(); j++)
        {
            if ((i * down - j) >= 0 && (i * down - j) % up == 0 )
            {
                value += filter.getTaps()[j] * data[ (i * down - j) / up];
            }
        }
        REQUIRE(std::abs(result[i] - value) < 1e-6); // use some threshold cause it's not exact
    }

    // Check that the delay is set correctly
    const ipps::vector<U> &delay = filter.getDelayVector();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i] == data[data.size()-delay.size()+i]);
    }

    // Reset the delay and check again
    filter.reset();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i] == 0);
    }

    // Check that it will throw if the output is not long enough
    ipps::vector<U> tooshortresult(data.size());
    REQUIRE_THROWS_AS(
        filter.filter(data.data(), tooshortresult.data(), data.size(), tooshortresult.size()),
        std::invalid_argument
    );

    // Make a vector of filter objects
    std::vector<ipps::filter::FIRMR<T,U>> filters(1);
    // First show that it will throw if not constructed directly
    REQUIRE_THROWS_AS(
        filters.at(0).filter(data.data(), result.data(), data.size(), result.size()), 
        std::runtime_error
    );

    filters.at(0) = filter; // assignment
    filters.push_back(filter); // copy

    // Check that the delays are the same as the original
    for (int i = 0; i < filters.size(); i++)
    {
        for (int j = 0; j < filters.at(i).getDelayVector().size(); j++)
        {
            REQUIRE(filters.at(i).getDelayVector()[j] == filter.getDelayVector()[j]);
        }
        for (int j = 0; j < filters.at(i).getTaps().size(); j++)
        {
            REQUIRE(filters.at(i).getTaps()[j] == filter.getTaps()[j]);
        }
        // But that the actual pointers are different
        REQUIRE(&filters.at(i).getTaps()!= &filter.getTaps());
        REQUIRE(&filters.at(i).getDelayVector()!= &filter.getDelayVector());
    }
}

// Make corresponding complex test
template <typename T, typename U>
void test_FIRMR_lowpass_cplx()
{
        // Create filter and taps
    int up = 5;
    int down = 3;
    ipps::filter::FIRMR<T,U> filter(
        ipps::filter::generateLowpassTaps<T>(0.5/2.0, 8, ippWinHamming, ippTrue),
        up, 0, down, 0
    );

    // Create some data
    ipps::vector<U> data(30);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].re = 10 + i;
        data[i].im = 20 + i;
    }

    // Apply the filter
    ipps::vector<U> result(data.size() * up / down);
    filter.filter(data.data(), result.data(), data.size(), result.size());

    // Check results
    for (int i = 0; i < result.size(); i++)
    {
        U value = {0, 0};
        for (int j = 0; j < filter.getTaps().size(); j++)
        {
            if ((i * down - j) >= 0 && (i * down - j) % up == 0 )
            {
                value.re += filter.getTaps()[j].re * data[ (i * down - j) / up].re;
                value.im += filter.getTaps()[j].re * data[ (i * down - j) / up].im;
            }
        }
        REQUIRE(std::abs(result[i].re - value.re) < 1e-6); // use some threshold cause it's not exact
        REQUIRE(std::abs(result[i].im - value.im) < 1e-6);
    }

    // Check that the delay is set correctly
    const ipps::vector<U> &delay = filter.getDelayVector();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i].re == data[data.size()-delay.size()+i].re);
        REQUIRE(delay[i].im == data[data.size()-delay.size()+i].im);
    }

    // Reset the delay and check again
    filter.reset();
    for (int i = 0; i < delay.size(); i++)
    {
        REQUIRE(delay[i].re == 0);
        REQUIRE(delay[i].im == 0);
    }

    // Check that it will throw if the output is not long enough
    ipps::vector<U> tooshortresult(data.size());
    REQUIRE_THROWS_AS(
        filter.filter(data.data(), tooshortresult.data(), data.size(), tooshortresult.size()),
        std::invalid_argument
    );

    // Make a vector of filter objects
    std::vector<ipps::filter::FIRMR<T,U>> filters(1);
    // First show that it will throw if not constructed directly
    REQUIRE_THROWS_AS(
        filters.at(0).filter(data.data(), result.data(), data.size(), result.size()), 
        std::runtime_error
    );

    filters.at(0) = filter; // assignment
    filters.push_back(filter); // copy

    // Check that the delays are the same as the original
    for (int i = 0; i < filters.size(); i++)
    {
        for (int j = 0; j < filters.at(i).getDelayVector().size(); j++)
        {
            REQUIRE(filters.at(i).getDelayVector()[j].re == filter.getDelayVector()[j].re);
            REQUIRE(filters.at(i).getDelayVector()[j].im == filter.getDelayVector()[j].im);
        }
        for (int j = 0; j < filters.at(i).getTaps().size(); j++)
        {
            REQUIRE(filters.at(i).getTaps()[j].re == filter.getTaps()[j].re);
        }
        // But that the actual pointers are different
        REQUIRE(&filters.at(i).getTaps()!= &filter.getTaps());
        REQUIRE(&filters.at(i).getDelayVector()!= &filter.getDelayVector());
    }
}

TEST_CASE("ipps filter FIRMR lowpass", "[filter],[firmr],[lowpass]")
{
    SECTION("Ipp32f taps, Ipp32f data"){
        test_FIRMR_lowpass<Ipp32f, Ipp32f>();
    }
    SECTION("Ipp64f taps, Ipp64f data"){
        test_FIRMR_lowpass<Ipp64f, Ipp64f>();
    }
    SECTION("Ipp32fc taps, Ipp32fc data"){
        test_FIRMR_lowpass_cplx<Ipp32fc, Ipp32fc>();
    }
    SECTION("Ipp64fc taps, Ipp64fc data"){
        test_FIRMR_lowpass_cplx<Ipp64fc, Ipp64fc>();
    }
}
