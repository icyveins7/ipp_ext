#include <iostream>
#include <cmath>
#include <vector>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

// template <typename T>
// void manual_filter_complex(T* src, T* dst, int len, T* taps, int tapslen)
// {
//     T x;
//     for (int i = 0; i < len; i++)
//     {
//         x = {0.0, 0.0};
//         for (int j = 0; j < tapslen; j++)
//         {
//             if (i-j >= 0)
//             {
//                 x.re += taps[j].re * src[i - j].re;
//                 x.im += taps[j].re * src[i - j].im; // note that the filter taps are real-only
//             }
//         }
//         dst[i] = x;
//     }
// }

// template <typename T>
// void manual_filter(T* src, T* dst, int len, T* taps, int tapslen)
// {
//     T x;
//     for (int i = 0; i < len; i++)
//     {
//         x = 0.0;
//         for (int j = 0; j < tapslen; j++)
//         {
//             if (i-j >= 0)
//                 x += taps[j] * src[i - j];
//         }
//         dst[i] = x;
//     }
// }

// // test taps generation
// TEST_CASE("ippe filter taps generation", "[filter],[taps]")
// {
//     double tolerance = 1e-6;
//     // hard coded taps
//     const int tapsLen = 8;
//     const double window = 0.5;
//     Ipp64f taps_ref[tapsLen] = {
//         -0.0051643 , -0.02288252,  0.09675565,  0.43129117,
//         0.43129117,  0.09675565, -0.02288252, -0.0051643
//     };

//     SECTION("Ipp32fc lowpass"){
//         // These are some standard parameters that are akin to python/matlab defaults
//         ippe::FIRSRLowpass<Ipp32fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);

//         // check the taps
//         Ipp32fc *taps = lowpass.getTaps();

//         // check with threshold
//         for (int i = 0; i < tapsLen; i++){
//             REQUIRE(fabs(taps[i].re - taps_ref[i]) < tolerance);
//             REQUIRE(taps[i].im == 0);
//         }
//     }

//     SECTION("Ipp64fc lowpass"){
//         // These are some standard parameters that are akin to python/matlab defaults
//         ippe::FIRSRLowpass<Ipp64fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
//         // check the taps
//         Ipp64fc *taps = lowpass.getTaps();
        
//         // check with threshold
//         for (int i = 0; i < tapsLen; i++){
//             REQUIRE(fabs(taps[i].re - taps_ref[i]) < tolerance);
//             REQUIRE(taps[i].im == 0);
//         }
//     }

//     SECTION("Ipp32f lowpass"){
//         // These are some standard parameters that are akin to python/matlab defaults
//         ippe::FIRSRLowpass<Ipp32f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
//         // check the taps
//         Ipp32f *taps = lowpass.getTaps();
        
//         // check with threshold
//         for (int i = 0; i < tapsLen; i++){
//             REQUIRE(fabs(taps[i] - taps_ref[i]) < tolerance);
//         }
//     }

//     SECTION("Ipp64f lowpass"){
//         // These are some standard parameters that are akin to python/matlab defaults
//         ippe::FIRSRLowpass<Ipp64f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
//         // check the taps
//         Ipp64f *taps = lowpass.getTaps();
        
//         // check with threshold
//         for (int i = 0; i < tapsLen; i++){
//             REQUIRE(fabs(taps[i] - taps_ref[i]) < tolerance);
//         }
//     }
// }

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
    ippe::vector<T> taps = ippe::filter::generateLowpassTaps<T>(window/2.0, tapsLen, ippWinHamming, ippTrue);

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
    ippe::vector<T> taps = ippe::filter::generateLowpassTaps<T>(window/2.0, tapsLen, ippWinHamming, ippTrue);

    // check with threshold
    for (int i = 0; i < tapsLen; i++)
    {
        REQUIRE(std::abs(taps[i].re - taps_ref[i]) < tolerance);
    }
}

TEST_CASE("ippe filter taps generation", "[filter],[taps]")
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
    ippe::vector<T> taps = ippe::filter::generateLowpassTaps<T>(0.5/2.0, 8, ippWinHamming, ippTrue);

    // Create the filter with taps
    ippe::filter::FIRSR<T, U> filter(taps);

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
    ippe::vector<U> data(16);
    for (int i = 0; i < data.size(); i++)
    {
        data[i] = i;
    }

    // Apply the filter
    ippe::vector<U> result(data.size());
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
    const ippe::vector<U> &delay = filter.getDelayVector();
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
    std::vector<ippe::filter::FIRSR<T,U>> filters(1);
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
    ippe::vector<T> taps = ippe::filter::generateLowpassTaps<T>(0.5/2.0, 8, ippWinHamming, ippTrue);

    // Create the filter with taps
    ippe::filter::FIRSR<T, U> filter(taps);

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
    ippe::vector<U> data(16);
    for (int i = 0; i < data.size(); i++)
    {
        data[i].re = i;
        data[i].im = i + 1;
    }

    // Apply the filter
    ippe::vector<U> result(data.size());
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
    const ippe::vector<U> &delay = filter.getDelayVector();
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
    std::vector<ippe::filter::FIRSR<T,U>> filters(1);
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

TEST_CASE("ippe filter FIRSR lowpass", "[filter],[firsr],[lowpass]")
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
    // Special case
    SECTION("Ipp32f taps, Ipp32fc data")
    {
        // Create the taps
        ippe::vector<Ipp32f> taps = ippe::filter::generateLowpassTaps<Ipp32f>(0.5/2.0, 8, ippWinHamming, ippTrue);

        // Create the filter with taps
        ippe::filter::FIRSR<Ipp32f, Ipp32fc> filter(taps);

        // Check that the delay is all zeros
        for (int i = 0; i < filter.getDelayVector().size(); i++)
        {
            REQUIRE(filter.getDelayVector()[i].re == 0);
            REQUIRE(filter.getDelayVector()[i].im == 0);
        }

        // Check that the taps are correct
        for (int i = 0; i < 8; i++)
        {
            REQUIRE(filter.getTaps()[i] == taps[i]);
        }

        // Create some data
        ippe::vector<Ipp32fc> data(16);
        for (int i = 0; i < data.size(); i++)
        {
            data[i].re = i;
            data[i].im = i + 1;
        }

        // Apply the filter
        ippe::vector<Ipp32fc> result(data.size());
        filter.filter(data.data(), result.data(), (int)result.size());

        // Check that the result is correct
        for (int i = 0; i < result.size(); i++)
        {
            Ipp32fc value = {0, 0};
            for (int j = 0; j < taps.size(); j++)
            {
                if (i - j >= 0)
                {
                    value.re += taps[j] * data[i - j].re;
                    value.im += taps[j] * data[i - j].im;
                }
            }
            printf("%d, %f %f\n", i, result[i].re, result[i].im);
            REQUIRE(std::abs(result[i].re - value.re) < 1e-6); // use some threshold cause it's not exact
            REQUIRE(std::abs(result[i].im - value.im) < 1e-6);
        }

        // Check that the delay is set correctly
        const ippe::vector<Ipp32fc> &delay = filter.getDelayVector();
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
        std::vector<ippe::filter::FIRSR<Ipp32f, Ipp32fc>> filters(1);
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

    // Skipping the mixed int/floating tests for now; would need to perform a lot of custom conversions
    // SECTION("Ipp32fc taps, Ipp16s data"){
    //     test_FIRSR_lowpass_cplx<Ipp32fc, Ipp16s>();
    // }
    // SECTION("Ipp32f taps, Ipp16s data"){
    //     test_FIRSR_lowpass<Ipp32f, Ipp16s>();
    // }
}

// TEST_CASE("ippe filter copy/assignment", "[filter],[copy],[assignment]")
// {
//     SECTION("Ipp32fc lowpass copy"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp32fc> lowpass(0.5, 8, ippWinHamming, ippTrue);

//         // Copy by pushing it into a vector
//         std::vector<ippe::FIRSRLowpass<Ipp32fc>> lowpass_vec;
//         lowpass_vec.push_back(lowpass);

//         // Check that the copy is correct

//         // taps values should be the same
//         for (int i = 0; i < lowpass.getNumTaps(); i++){
//             REQUIRE(lowpass_vec.at(0).getTaps()[i].re == lowpass.getTaps()[i].re);
//             REQUIRE(lowpass_vec.at(0).getTaps()[i].im == lowpass.getTaps()[i].im);
//         } 
//         // taps pointer should be distinct
//         REQUIRE(lowpass_vec.at(0).getTaps()!= lowpass.getTaps());
//         // check that all the other pointers are also distinct
//         REQUIRE(lowpass_vec.at(0).getDelayBuffer() != lowpass.getDelayBuffer());
//         REQUIRE(lowpass_vec.at(0).getFilterSpec()!= lowpass.getFilterSpec());
//         REQUIRE(lowpass_vec.at(0).getWorkBuffer() != lowpass.getWorkBuffer());
//     }

//     SECTION("Ipp64fc lowpass copy"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp64fc> lowpass(0.5, 8, ippWinHamming, ippTrue);
        
//         // Copy by pushing it into a vector
//         std::vector<ippe::FIRSRLowpass<Ipp64fc>> lowpass_vec;
//         lowpass_vec.push_back(lowpass);
        
//         // Check that the copy is correct
        
//         // taps values should be the same
//         for (int i = 0; i < lowpass.getNumTaps(); i++){
//             REQUIRE(lowpass_vec.at(0).getTaps()[i].re == lowpass.getTaps()[i].re);
//             REQUIRE(lowpass_vec.at(0).getTaps()[i].im == lowpass.getTaps()[i].im);
//         } 
//         // taps pointer should be distinct
//         REQUIRE(lowpass_vec.at(0).getTaps()!= lowpass.getTaps());
//         // check that all the other pointers are also distinct
//         REQUIRE(lowpass_vec.at(0).getDelayBuffer()!= lowpass.getDelayBuffer());
//         REQUIRE(lowpass_vec.at(0).getFilterSpec()!= lowpass.getFilterSpec());
//         REQUIRE(lowpass_vec.at(0).getWorkBuffer()!= lowpass.getWorkBuffer());
//     }

//     SECTION("Ipp32f lowpass copy"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp32f> lowpass(0.5, 8, ippWinHamming, ippTrue);
        
//         // Copy by pushing it into a vector
//         std::vector<ippe::FIRSRLowpass<Ipp32f>> lowpass_vec;
//         lowpass_vec.push_back(lowpass);
        
//         // Check that the copy is correct
        
//         // taps values should be the same
//         for (int i = 0; i < lowpass.getNumTaps(); i++){
//             REQUIRE(lowpass_vec.at(0).getTaps()[i] == lowpass.getTaps()[i]);
//         } 
//         // taps pointer should be distinct
//         REQUIRE(lowpass_vec.at(0).getTaps()!= lowpass.getTaps());
//         // check that all the other pointers are also distinct
//         REQUIRE(lowpass_vec.at(0).getDelayBuffer()!= lowpass.getDelayBuffer());
//         REQUIRE(lowpass_vec.at(0).getFilterSpec()!= lowpass.getFilterSpec());
//         REQUIRE(lowpass_vec.at(0).getWorkBuffer()!= lowpass.getWorkBuffer());
//     }

//     SECTION("Ipp64f lowpass copy"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp64f> lowpass(0.5, 8, ippWinHamming, ippTrue);
        
//         // Copy by pushing it into a vector
//         std::vector<ippe::FIRSRLowpass<Ipp64f>> lowpass_vec;
//         lowpass_vec.push_back(lowpass);
        
//         // Check that the copy is correct
        
//         // taps values should be the same
//         for (int i = 0; i < lowpass.getNumTaps(); i++){
//             REQUIRE(lowpass_vec.at(0).getTaps()[i] == lowpass.getTaps()[i]);
//         } 
//         // taps pointer should be distinct
//         REQUIRE(lowpass_vec.at(0).getTaps()!= lowpass.getTaps());
//         // check that all the other pointers are also distinct
//         REQUIRE(lowpass_vec.at(0).getDelayBuffer()!= lowpass.getDelayBuffer());
//         REQUIRE(lowpass_vec.at(0).getFilterSpec()!= lowpass.getFilterSpec());
//         REQUIRE(lowpass_vec.at(0).getWorkBuffer()!= lowpass.getWorkBuffer());
//     }

//     SECTION("Ipp32fc lowpass assignment"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp32fc> lowpass(0.5, 8, ippWinHamming, ippTrue);

//         // create vector of filters
//         std::vector<ippe::FIRSRLowpass<Ipp32fc>> lowpass_vec(2);

//         // assign to vector
//         for (int i = 0; i < lowpass_vec.size(); i++){
//             lowpass_vec.at(i) = lowpass;

//             // Check that the assignment is correct
//             // taps values should be the same
//             for (int j = 0; j < lowpass.getNumTaps(); j++){
//                 REQUIRE(lowpass_vec.at(i).getTaps()[j].re == lowpass.getTaps()[j].re);
//                 REQUIRE(lowpass_vec.at(i).getTaps()[j].im == lowpass.getTaps()[j].im);
//             } 
//             // taps pointer should be distinct
//             REQUIRE(lowpass_vec.at(i).getTaps()!= lowpass.getTaps());
//             // check that all the other pointers are also distinct
//             REQUIRE(lowpass_vec.at(i).getDelayBuffer()!= lowpass.getDelayBuffer());
//             REQUIRE(lowpass_vec.at(i).getFilterSpec()!= lowpass.getFilterSpec());
//             REQUIRE(lowpass_vec.at(i).getWorkBuffer()!= lowpass.getWorkBuffer());
//         }
//     }

//     SECTION("Ipp64fc lowpass assignment"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp64fc> lowpass(0.5, 8, ippWinHamming, ippTrue);
        
//         // create vector of filters
//         std::vector<ippe::FIRSRLowpass<Ipp64fc>> lowpass_vec(2);
        
//         // assign to vector
//         for (int i = 0; i < lowpass_vec.size(); i++){
//             lowpass_vec.at(i) = lowpass;
            
//             // Check that the assignment is correct
//             // taps values should be the same
//             for (int j = 0; j < lowpass.getNumTaps(); j++){
//                 REQUIRE(lowpass_vec.at(i).getTaps()[j].re == lowpass.getTaps()[j].re);
//                 REQUIRE(lowpass_vec.at(i).getTaps()[j].im == lowpass.getTaps()[j].im);
//             } 
//             // taps pointer should be distinct
//             REQUIRE(lowpass_vec.at(i).getTaps()!= lowpass.getTaps());
//             // check that all the other pointers are also distinct
//             REQUIRE(lowpass_vec.at(i).getDelayBuffer()!= lowpass.getDelayBuffer());
//             REQUIRE(lowpass_vec.at(i).getFilterSpec()!= lowpass.getFilterSpec());
//             REQUIRE(lowpass_vec.at(i).getWorkBuffer()!= lowpass.getWorkBuffer());
//         }
//     }

//     SECTION("Ipp32f lowpass assignment"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp32f> lowpass(0.5, 8, ippWinHamming, ippTrue);
        
//         // create vector of filters
//         std::vector<ippe::FIRSRLowpass<Ipp32f>> lowpass_vec(2);
        
//         // assign to vector
//         for (int i = 0; i < lowpass_vec.size(); i++){
//             lowpass_vec.at(i) = lowpass;
            
//             // Check that the assignment is correct
//             // taps values should be the same
//             for (int j = 0; j < lowpass.getNumTaps(); j++){
//                 REQUIRE(lowpass_vec.at(i).getTaps()[j] == lowpass.getTaps()[j]);
//             } 
//             // taps pointer should be distinct
//             REQUIRE(lowpass_vec.at(i).getTaps()!= lowpass.getTaps());
//             // check that all the other pointers are also distinct
//             REQUIRE(lowpass_vec.at(i).getDelayBuffer()!= lowpass.getDelayBuffer());
//             REQUIRE(lowpass_vec.at(i).getFilterSpec()!= lowpass.getFilterSpec());
//             REQUIRE(lowpass_vec.at(i).getWorkBuffer()!= lowpass.getWorkBuffer());
//         }
//     }

//     SECTION("Ipp64f lowpass assignment"){
//         // Make a filter object
//         ippe::FIRSRLowpass<Ipp64f> lowpass(0.5, 8, ippWinHamming, ippTrue);
        
//         // create vector of filters
//         std::vector<ippe::FIRSRLowpass<Ipp64f>> lowpass_vec(2);
        
//         // assign to vector
//         for (int i = 0; i < lowpass_vec.size(); i++){
//             lowpass_vec.at(i) = lowpass;
            
//             // Check that the assignment is correct
//             // taps values should be the same
//             for (int j = 0; j < lowpass.getNumTaps(); j++){
//                 REQUIRE(lowpass_vec.at(i).getTaps()[j] == lowpass.getTaps()[j]);
//             } 
//             // taps pointer should be distinct
//             REQUIRE(lowpass_vec.at(i).getTaps()!= lowpass.getTaps());
//             // check that all the other pointers are also distinct
//             REQUIRE(lowpass_vec.at(i).getDelayBuffer()!= lowpass.getDelayBuffer());
//             REQUIRE(lowpass_vec.at(i).getFilterSpec()!= lowpass.getFilterSpec());
//             REQUIRE(lowpass_vec.at(i).getWorkBuffer()!= lowpass.getWorkBuffer());
//         }
//     }
// }

// TEST_CASE("ippe filter filter execution", "[filter],[execution]")
// {
//     const double tolerance = 1e-6;
//     // parameters
//     const int dataLen = 100;
//     const int tapsLen = 8;
//     const double window = 0.5;

//     SECTION("Ipp32fc lowpass"){
//         // Create some data
//         ippe::vector<Ipp32fc> data(dataLen, Ipp32fc{1.0, 1.0});

//         // Create a filter
//         ippe::FIRSRLowpass<Ipp32fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);

//         // Allocate two outputs
//         ippe::vector<Ipp32fc> out1(dataLen);
//         ippe::vector<Ipp32fc> out2(dataLen);

//         // Execute the filter using the object
//         lowpass.filter(data.data(), out1.data(), out1.size());

//         // And also with the manual function
//         manual_filter_complex<Ipp32fc>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);

//         // Check the results
//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i].re - out2[i].re) < tolerance);
//             REQUIRE(fabs(out1[i].im - out2[i].im) < tolerance);
//         }

//         // reset the filter and run the filter again, to show that it's identical
//         lowpass.reset();
//         lowpass.filter(data.data(), out1.data(), out1.size());

//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i].re - out2[i].re) < tolerance);
//             REQUIRE(fabs(out1[i].im - out2[i].im) < tolerance);
//         }

//         // Show that not resetting and running it will cause the first few to be wrong
//         lowpass.filter(data.data(), out1.data(), out1.size());

//         for (int i = 0; i < tapsLen - 1; i++){
//             REQUIRE(fabs(out1[i].re - out2[i].re) > tolerance);
//             REQUIRE(fabs(out1[i].im - out2[i].im) > tolerance);
//         }
//     }

//     SECTION("Ipp64fc lowpass"){
//         // Create some data
//         ippe::vector<Ipp64fc> data(dataLen, Ipp64fc{1.0, 1.0});

//         // Create a filter
//         ippe::FIRSRLowpass<Ipp64fc> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
//         // Allocate two outputs
//         ippe::vector<Ipp64fc> out1(dataLen);
//         ippe::vector<Ipp64fc> out2(dataLen);

//         // Execute the filter using the object
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         // And also with the manual function
//         manual_filter_complex<Ipp64fc>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);
        
//         // Check the results
//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i].re - out2[i].re) < tolerance);
//             REQUIRE(fabs(out1[i].im - out2[i].im) < tolerance);
//         }
        
//         // reset the filter and run the filter again, to show that it's identical
//         lowpass.reset();
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i].re - out2[i].re) < tolerance);
//             REQUIRE(fabs(out1[i].im - out2[i].im) < tolerance);
//         }
        
//         // Show that not resetting and running it will cause the first few to be wrong
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         for (int i = 0; i < tapsLen - 1; i++){
//             REQUIRE(fabs(out1[i].re - out2[i].re) > tolerance);
//             REQUIRE(fabs(out1[i].im - out2[i].im) > tolerance);
//         }
//     }

//     SECTION("Ipp32f lowpass"){
//         // Create some data
//         ippe::vector<Ipp32f> data(dataLen, 1.0);

//         // Create a filter
//         ippe::FIRSRLowpass<Ipp32f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
//         // Allocate two outputs
//         ippe::vector<Ipp32f> out1(dataLen);
//         ippe::vector<Ipp32f> out2(dataLen);
        
//         // Execute the filter using the object
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         // And also with the manual function
//         manual_filter<Ipp32f>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);
        
//         // Check the results
//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i] - out2[i]) < tolerance);
//         }
        
//         // reset the filter and run the filter again, to show that it's identical
//         lowpass.reset();
//         lowpass.filter(data.data(), out1.data(), out1.size());

//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i] - out2[i]) < tolerance);
//         }
        
//         // Show that not resetting and running it will cause the first few to be wrong
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         for (int i = 0; i < tapsLen - 1; i++){
//             REQUIRE(fabs(out1[i] - out2[i]) > tolerance);
//         }
//     }

//     SECTION("Ipp64f lowpass"){
//         // Create some data
//         ippe::vector<Ipp64f> data(dataLen, 1.0);

//         // Create a filter
//         ippe::FIRSRLowpass<Ipp64f> lowpass(window, tapsLen, ippWinHamming, ippTrue);
        
//         // Allocate two outputs
//         ippe::vector<Ipp64f> out1(dataLen);
//         ippe::vector<Ipp64f> out2(dataLen);
        
//         // Execute the filter using the object
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         // And also with the manual function
//         manual_filter<Ipp64f>(data.data(), out2.data(), dataLen, lowpass.getTaps(), tapsLen);
        
//         // Check the results
//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i] - out2[i]) < tolerance);
//         }
        
//         // reset the filter and run the filter again, to show that it's identical
//         lowpass.reset();
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         for (int i = 0; i < dataLen; i++){
//             REQUIRE(fabs(out1[i] - out2[i]) < tolerance);
//         }
        
//         // Show that not resetting and running it will cause the first few to be wrong
//         lowpass.filter(data.data(), out1.data(), out1.size());
        
//         for (int i = 0; i < tapsLen - 1; i++){
//             REQUIRE(fabs(out1[i] - out2[i]) > tolerance);
//         }
//     }
// }