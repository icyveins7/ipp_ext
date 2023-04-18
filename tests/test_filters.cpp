#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

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

    SECTION("Ipp32fc"){
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

    SECTION("Ipp64fc"){
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

    SECTION("Ipp32f"){
        // These are some standard parameters that are akin to python/matlab defaults
        ippe::FIRSRLowpass<Ipp32f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
        // check the taps
        Ipp32f *taps = lowpass.getTaps();
        
        // check with threshold
        for (int i = 0; i < tapsLen; i++){
            REQUIRE(abs(taps[i] - taps_ref[i]) < tolerance);
        }
    }

    SECTION("Ipp64f"){
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