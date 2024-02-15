#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

// test simple instantiation and cleanup for all supported templates of DFTCToC:
// Ipp32f, Ipp64f, Ipp32fc, Ipp64fc
TEST_CASE("ippe dft instantiation", "[dft],[instantiation]")
{
    SECTION("Ipp32f"){
        {
            ippe::DFTCToC<Ipp32f> dft(1000);
        }
    }

    SECTION("Ipp64f"){
        {
            ippe::DFTCToC<Ipp64f> dft(1000);
        }
    }

    SECTION("Ipp32fc"){
        {
            ippe::DFTCToC<Ipp32fc> dft(1000);
        }
    }

    SECTION("Ipp64fc"){
        {
            ippe::DFTCToC<Ipp64fc> dft(1000);
        }
    }
}


// Test copy and assignment
template<typename T>
void test_dft_copy_assign_use(bool test_run)
{
    // Make some data
    ippe::vector<T> data(1000);
    ippe::vector<T> out(1000);

    std::vector<ippe::DFTCToC<T>> dfts;
    // Copy
    ippe::DFTCToC<T> dft(1000);
    dfts.push_back(dft);

    REQUIRE(dft.getDFTSpec().data() != dfts.at(0).getDFTSpec().data());
    REQUIRE(dft.getDFTBuf().data() != dfts.at(0).getDFTBuf().data());
    REQUIRE(dft.getMemInit().data() != dfts.at(0).getMemInit().data());


    // Use both dfts and run it
    if (test_run)
        dfts.at(0).fwd(data.data(), out.data());

    // Assign
    dfts.resize(2);
    for (int i = 0; i < dfts.size(); i++)
    {
        dfts.at(i) = dft;
        REQUIRE(dfts.at(i).getDFTSpec().data() != dft.getDFTSpec().data());
        REQUIRE(dfts.at(i).getDFTBuf().data() != dft.getDFTBuf().data());
        REQUIRE(dfts.at(i).getMemInit().data() != dft.getMemInit().data());
    }

    // Run using both objects in the vector
    if (test_run)
    {
        for (int i = 0; i < dfts.size(); i++)
        {
            dfts.at(i).fwd(data.data(), out.data());
        }
    }
}

TEST_CASE("ippe dft copy and assignment", "[dft], [copy],[assignment]")
{
    SECTION("Ipp32f"){
        test_dft_copy_assign_use<Ipp32f>(false);
    }
    SECTION("Ipp64f"){
        test_dft_copy_assign_use<Ipp64f>(false);
    }
    SECTION("Ipp32fc"){
        test_dft_copy_assign_use<Ipp32fc>(true);
    }
    SECTION("Ipp64fc"){
        test_dft_copy_assign_use<Ipp64fc>(true);
    }
}

// test execution for all supported templates of DFTCToC:
TEST_CASE("ippe dft execution", "[dft],[execution]")
{
    int length = 100;
    double tolerance = 1e-4; // tolerance for floating point comparison

    SECTION("Ipp32f"){
        ippe::DFTCToC<Ipp32f> dft(length);
        // make some data for input and output
        ippe::vector<Ipp32f> in_re(length);
        ippe::vector<Ipp32f> in_im(length);
        ippe::vector<Ipp32f> out_re(length);
        ippe::vector<Ipp32f> out_im(length);
        // we need 2 output vectors..
        ippe::vector<Ipp32f> out_re2(length);
        ippe::vector<Ipp32f> out_im2(length);
        for (int i = 0; i < length; i++) {
            in_re[i] = (Ipp32f)i;
            in_im[i] = 0;
        }
        // run the forwards and backwards dfts (should result in the same or almost the same)
        dft.fwd(in_re.data(), out_re.data(), in_im.data(), out_im.data());
        dft.bwd(out_re.data(), out_re2.data(), out_im.data(), out_im2.data());
        for (int i = 0; i < length; i++) {
            // final output should be equal to the original input, within tolerance
            REQUIRE(abs(out_re2[i] - in_re[i]) < tolerance);
            REQUIRE(abs(out_im2[i] - in_im[i]) < tolerance);
        }
    }

    SECTION("Ipp64f"){
        ippe::DFTCToC<Ipp64f> dft(length);
        // make some data for input and output
        ippe::vector<Ipp64f> in_re(length);
        ippe::vector<Ipp64f> in_im(length);
        ippe::vector<Ipp64f> out_re(length);
        ippe::vector<Ipp64f> out_im(length);
        // we need 2 output vectors..
        ippe::vector<Ipp64f> out_re2(length);
        ippe::vector<Ipp64f> out_im2(length);
        for (int i = 0; i < length; i++) {
            in_re[i] = i;
            in_im[i] = 0;
        }
        // run the forwards and backwards dfts (should result in the same or almost the same)
        dft.fwd(in_re.data(), out_re.data(), in_im.data(), out_im.data());
        dft.bwd(out_re.data(), out_re2.data(), out_im.data(), out_im2.data());
        for (int i = 0; i < length; i++) {
            // final output should be equal to the original input, within tolerance
            REQUIRE(abs(out_re2[i] - in_re[i]) < tolerance);
            REQUIRE(abs(out_im2[i] - in_im[i]) < tolerance);
        }
    }

    SECTION("Ipp32fc"){
        ippe::DFTCToC<Ipp32fc> dft(length);
        // make some data for input and output
        ippe::vector<Ipp32fc> in(length);
        ippe::vector<Ipp32fc> out(length);
        // we need 2 output vectors..
        ippe::vector<Ipp32fc> out2(length);
        for (int i = 0; i < length; i++) {
            in[i].re = (Ipp32f)i;
            in[i].im = 0;
        }

        // run forwards and backwards dfts, but for complex we don't need the last 2 args
        dft.fwd(in.data(), out.data());
        dft.bwd(out.data(), out2.data());
        for (int i = 0; i < length; i++) {
            // final output should be equal to the original input, within tolerance
            REQUIRE(abs(out2[i].re - in[i].re) < tolerance);
            REQUIRE(abs(out2[i].im - in[i].im) < tolerance);
        }
    }

    SECTION("Ipp64fc"){
        ippe::DFTCToC<Ipp64fc> dft(length);
        // make some data for input and output
        ippe::vector<Ipp64fc> in(length);
        ippe::vector<Ipp64fc> out(length);
        // we need 2 output vectors..
        ippe::vector<Ipp64fc> out2(length);
        for (int i = 0; i < length; i++) {
            in[i].re = i;
            in[i].im = 0;
        }
        // run forwards and backwards dfts, but for complex we don't need the last 2 args
        dft.fwd(in.data(), out.data());
        dft.bwd(out.data(), out2.data());
        for (int i = 0; i < length; i++) {
            // final output should be equal to the original input, within tolerance
            REQUIRE(abs(out2[i].re - in[i].re) < tolerance);
            REQUIRE(abs(out2[i].im - in[i].im) < tolerance);
        }
    }
            

}