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

// Test copy and assignment constructors
TEST_CASE("ippe dft copy and assignment", "[dft],[copy],[assignment]")
{
    SECTION("Ipp32f copy"){
        std::vector<ippe::DFTCToC<Ipp32f>> dfts;
        ippe::DFTCToC<Ipp32f> dft(1000);
        dfts.push_back(dft);

        REQUIRE(dft.getDFTSpec() != dfts.at(0).getDFTSpec());
        REQUIRE(dft.getDFTBuf() != dfts.at(0).getDFTBuf());
        REQUIRE(dft.getMemInit() != dfts.at(0).getMemInit());
    }

    SECTION("Ipp32f assignment"){
        std::vector<ippe::DFTCToC<Ipp32f>> dfts(2);
        ippe::DFTCToC<Ipp32f> dft(1000);
        
        for (int i = 0; i < dfts.size(); ++i){
            dfts.at(i) = dft;
            REQUIRE(dft.getDFTSpec()!= dfts.at(i).getDFTSpec());
            REQUIRE(dft.getDFTBuf()!= dfts.at(i).getDFTBuf());
            REQUIRE(dft.getMemInit()!= dfts.at(i).getMemInit());
        }
    }

    SECTION("Ipp64f copy"){
        std::vector<ippe::DFTCToC<Ipp64f>> dfts;
        ippe::DFTCToC<Ipp64f> dft(1000);
        dfts.push_back(dft);
        
        REQUIRE(dft.getDFTSpec()!= dfts.at(0).getDFTSpec());
        REQUIRE(dft.getDFTBuf()!= dfts.at(0).getDFTBuf());
        REQUIRE(dft.getMemInit()!= dfts.at(0).getMemInit());
    }

    SECTION("Ipp64f assignment"){
        std::vector<ippe::DFTCToC<Ipp64f>> dfts(2);
        ippe::DFTCToC<Ipp64f> dft(1000);
        
        for (int i = 0; i < dfts.size(); ++i){
            dfts.at(i) = dft;
            REQUIRE(dft.getDFTSpec()!= dfts.at(i).getDFTSpec());
            REQUIRE(dft.getDFTBuf()!= dfts.at(i).getDFTBuf());
            REQUIRE(dft.getMemInit()!= dfts.at(i).getMemInit());
        }
    }

    SECTION("Ipp32fc copy"){
        std::vector<ippe::DFTCToC<Ipp32fc>> dfts;
        ippe::DFTCToC<Ipp32fc> dft(1000);
        dfts.push_back(dft);
        
        REQUIRE(dft.getDFTSpec()!= dfts.at(0).getDFTSpec());
        REQUIRE(dft.getDFTBuf()!= dfts.at(0).getDFTBuf());
        REQUIRE(dft.getMemInit()!= dfts.at(0).getMemInit());
    }

    SECTION("Ipp32fc assignment"){
        std::vector<ippe::DFTCToC<Ipp32fc>> dfts(2);
        ippe::DFTCToC<Ipp32fc> dft(1000);
        
        for (int i = 0; i < dfts.size(); ++i){
            dfts.at(i) = dft;
            REQUIRE(dft.getDFTSpec()!= dfts.at(i).getDFTSpec());
            REQUIRE(dft.getDFTBuf()!= dfts.at(i).getDFTBuf());
            REQUIRE(dft.getMemInit()!= dfts.at(i).getMemInit());
        }
    }

    SECTION("Ipp64fc copy"){
        std::vector<ippe::DFTCToC<Ipp64fc>> dfts;
        ippe::DFTCToC<Ipp64fc> dft(1000);
        dfts.push_back(dft);
        
        REQUIRE(dft.getDFTSpec()!= dfts.at(0).getDFTSpec());
        REQUIRE(dft.getDFTBuf()!= dfts.at(0).getDFTBuf());
        REQUIRE(dft.getMemInit()!= dfts.at(0).getMemInit());
    }

    SECTION("Ipp64fc assignment"){
        std::vector<ippe::DFTCToC<Ipp64fc>> dfts(2);
        ippe::DFTCToC<Ipp64fc> dft(1000);
        
        for (int i = 0; i < dfts.size(); ++i){
            dfts.at(i) = dft;
            REQUIRE(dft.getDFTSpec()!= dfts.at(i).getDFTSpec());
            REQUIRE(dft.getDFTBuf()!= dfts.at(i).getDFTBuf());
            REQUIRE(dft.getMemInit()!= dfts.at(i).getMemInit());
        }
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