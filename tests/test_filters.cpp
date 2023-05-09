#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T>
void manual_filter_complex(T* src, T* dst, int len, T* taps, int tapslen)
{
    T x;
    for (int i = 0; i < len; i++)
    {
        x = {0.0, 0.0};
        for (int j = 0; j < tapslen; j++)
        {
            if (i-j >= 0)
            {
                x.re += taps[j].re * src[i - j].re;
                x.im += taps[j].re * src[i - j].im; // note that the filter taps are real-only
            }
        }
        dst[i] = x;
    }
}

template <typename T>
void manual_filter(T* src, T* dst, int len, T* taps, int tapslen)
{
    T x;
    for (int i = 0; i < len; i++)
    {
        x = 0.0;
        for (int j = 0; j < tapslen; j++)
        {
            if (i-j >= 0)
                x += taps[j] * src[i - j];
        }
        dst[i] = x;
    }
}

// test taps generation
TEST_CASE("ippe filter taps generation", "[filter],[taps]")
{
    double tolerance = 1e-6;
    // hard coded taps
    const int tapsLen = 8;
    const double window = 0.5;
    Ipp64f taps_ref[tapsLen] = {
        -0.0051643 , -0.02288252,  0.09675565,  0.43129117,
        0.43129117,  0.09675565, -0.02288252, -0.0051643
    };

    SECTION("Ipp32fc lowpass"){
        // These are some standard parameters that are akin to python/matlab defaults
        ippe::FIRSRLowpass<Ipp32fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);

        // check the taps
        Ipp32fc *taps = lowpass.getTaps();

        // check with threshold
        for (int i = 0; i < tapsLen; i++){
            REQUIRE(abs(taps[i].re - taps_ref[i]) < tolerance);
            REQUIRE(taps[i].im == 0);
        }
    }

    SECTION("Ipp64fc lowpass"){
        // These are some standard parameters that are akin to python/matlab defaults
        ippe::FIRSRLowpass<Ipp64fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // check the taps
        Ipp64fc *taps = lowpass.getTaps();
        
        // check with threshold
        for (int i = 0; i < tapsLen; i++){
            REQUIRE(abs(taps[i].re - taps_ref[i]) < tolerance);
            REQUIRE(taps[i].im == 0);
        }
    }

    SECTION("Ipp32f lowpass"){
        // These are some standard parameters that are akin to python/matlab defaults
        ippe::FIRSRLowpass<Ipp32f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // check the taps
        Ipp32f *taps = lowpass.getTaps();
        
        // check with threshold
        for (int i = 0; i < tapsLen; i++){
            REQUIRE(abs(taps[i] - taps_ref[i]) < tolerance);
        }
    }

    SECTION("Ipp64f lowpass"){
        // These are some standard parameters that are akin to python/matlab defaults
        ippe::FIRSRLowpass<Ipp64f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // check the taps
        Ipp64f *taps = lowpass.getTaps();
        
        // check with threshold
        for (int i = 0; i < tapsLen; i++){
            REQUIRE(abs(taps[i] - taps_ref[i]) < tolerance);
        }
    }
}

TEST_CASE("ippe filter filter execution", "[filter],[execution]")
{
    const double tolerance = 1e-6;
    // parameters
    const int dataLen = 100;
    const int tapsLen = 8;
    const double window = 0.5;

    SECTION("Ipp32fc lowpass"){
        // Create some data
        ippe::vector<Ipp32fc> data(dataLen, Ipp32fc{1.0, 1.0});

        // Create a filter
        ippe::FIRSRLowpass<Ipp32fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);

        // Allocate two outputs
        ippe::vector<Ipp32fc> out1(dataLen);
        ippe::vector<Ipp32fc> out2(dataLen);

        // Execute the filter using the object
        lowpass.filter(data.data(), out1.data(), out1.size());

        // And also with the manual function
        manual_filter_complex<Ipp32fc>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);

        // Check the results
        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i].re - out2[i].re) < tolerance);
            REQUIRE(abs(out1[i].im - out2[i].im) < tolerance);
        }

        // reset the filter and run the filter again, to show that it's identical
        lowpass.reset();
        lowpass.filter(data.data(), out1.data(), out1.size());

        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i].re - out2[i].re) < tolerance);
            REQUIRE(abs(out1[i].im - out2[i].im) < tolerance);
        }

        // Show that not resetting and running it will cause the first few to be wrong
        lowpass.filter(data.data(), out1.data(), out1.size());

        for (int i = 0; i < tapsLen - 1; i++){
            REQUIRE(abs(out1[i].re - out2[i].re) > tolerance);
            REQUIRE(abs(out1[i].im - out2[i].im) > tolerance);
        }
    }

    SECTION("Ipp64fc lowpass"){
        // Create some data
        ippe::vector<Ipp64fc> data(dataLen, Ipp64fc{1.0, 1.0});

        // Create a filter
        ippe::FIRSRLowpass<Ipp64fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // Allocate two outputs
        ippe::vector<Ipp64fc> out1(dataLen);
        ippe::vector<Ipp64fc> out2(dataLen);

        // Execute the filter using the object
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        // And also with the manual function
        manual_filter_complex<Ipp64fc>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);
        
        // Check the results
        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i].re - out2[i].re) < tolerance);
            REQUIRE(abs(out1[i].im - out2[i].im) < tolerance);
        }
        
        // reset the filter and run the filter again, to show that it's identical
        lowpass.reset();
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i].re - out2[i].re) < tolerance);
            REQUIRE(abs(out1[i].im - out2[i].im) < tolerance);
        }
        
        // Show that not resetting and running it will cause the first few to be wrong
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        for (int i = 0; i < tapsLen - 1; i++){
            REQUIRE(abs(out1[i].re - out2[i].re) > tolerance);
            REQUIRE(abs(out1[i].im - out2[i].im) > tolerance);
        }
    }

    SECTION("Ipp32f lowpass"){
        // Create some data
        ippe::vector<Ipp32f> data(dataLen, 1.0);

        // Create a filter
        ippe::FIRSRLowpass<Ipp32f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // Allocate two outputs
        ippe::vector<Ipp32f> out1(dataLen);
        ippe::vector<Ipp32f> out2(dataLen);
        
        // Execute the filter using the object
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        // And also with the manual function
        manual_filter<Ipp32f>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);
        
        // Check the results
        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i] - out2[i]) < tolerance);
        }
        
        // reset the filter and run the filter again, to show that it's identical
        lowpass.reset();
        lowpass.filter(data.data(), out1.data(), out1.size());

        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i] - out2[i]) < tolerance);
        }
        
        // Show that not resetting and running it will cause the first few to be wrong
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        for (int i = 0; i < tapsLen - 1; i++){
            REQUIRE(abs(out1[i] - out2[i]) > tolerance);
        }
    }

    SECTION("Ipp64f lowpass"){
        // Create some data
        ippe::vector<Ipp64f> data(dataLen, 1.0);

        // Create a filter
        ippe::FIRSRLowpass<Ipp64f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // Allocate two outputs
        ippe::vector<Ipp64f> out1(dataLen);
        ippe::vector<Ipp64f> out2(dataLen);
        
        // Execute the filter using the object
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        // And also with the manual function
        manual_filter<Ipp64f>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);
        
        // Check the results
        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i] - out2[i]) < tolerance);
        }
        
        // reset the filter and run the filter again, to show that it's identical
        lowpass.reset();
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        for (int i = 0; i < dataLen; i++){
            REQUIRE(abs(out1[i] - out2[i]) < tolerance);
        }
        
        // Show that not resetting and running it will cause the first few to be wrong
        lowpass.filter(data.data(), out1.data(), out1.size());
        
        for (int i = 0; i < tapsLen - 1; i++){
            REQUIRE(abs(out1[i] - out2[i]) > tolerance);
        }
    }
}