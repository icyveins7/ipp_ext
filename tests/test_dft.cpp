#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

// test simple instantiation and cleanup for all supported templates of DFTCToC:
// Ipp32f, Ipp64f, Ipp32fc, Ipp64fc
TEST_CASE("ipps dft instantiation", "[dft],[instantiation]")
{
    SECTION("Ipp32f"){
        {
            ipps::DFTCToC<Ipp32f> dft(1000);
        }
    }

    SECTION("Ipp64f"){
        {
            ipps::DFTCToC<Ipp64f> dft(1000);
        }
    }

    SECTION("Ipp32fc"){
        {
            ipps::DFTCToC<Ipp32fc> dft(1000);
        }
    }

    SECTION("Ipp64fc"){
        {
            ipps::DFTCToC<Ipp64fc> dft(1000);
        }
    }
}


// Test copy and assignment
template<typename T>
void test_dft_copy_assign_use(bool test_run)
{
    // Make some data
    size_t len = 2016;
    ipps::vector<T> data(len);
    ipps::vector<T> out(len);

    std::vector<ipps::DFTCToC<T>> dfts;
    // Copy
    ipps::DFTCToC<T> dft(len);
    dfts.push_back(dft);

    REQUIRE(dft.getDFTSpec().data() != dfts.at(0).getDFTSpec().data());
    REQUIRE(dft.getDFTBuf().data() != dfts.at(0).getDFTBuf().data());
    REQUIRE(dft.getMemInit().data() != dfts.at(0).getMemInit().data());
    // Check that these internal vectors contain the same data
    for (size_t i = 0; i < dft.getDFTSpec().size(); ++i)
        REQUIRE(dft.getDFTSpec().at(i) == dfts.at(0).getDFTSpec().at(i));

    for (size_t i = 0; i < dft.getDFTBuf().size(); ++i)
        REQUIRE(dft.getDFTBuf().at(i) == dfts.at(0).getDFTBuf().at(i));

    for (size_t i = 0; i < dft.getMemInit().size(); ++i)
        REQUIRE(dft.getMemInit().at(i) == dfts.at(0).getMemInit().at(i));


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

        for (size_t j = 0; j < dft.getDFTSpec().size(); ++j)
            REQUIRE(dft.getDFTSpec().at(j) == dfts.at(0).getDFTSpec().at(j));

        for (size_t j = 0; j < dft.getDFTBuf().size(); ++j)
            REQUIRE(dft.getDFTBuf().at(j) == dfts.at(0).getDFTBuf().at(j));

        for (size_t j = 0; j < dft.getMemInit().size(); ++j)
            REQUIRE(dft.getMemInit().at(j) == dfts.at(0).getMemInit().at(j));
    }

    // Change after assignment
    if (test_run)
    {
        dfts.at(0) = ipps::DFTCToC<T>(len+10);
        ipps::vector<T> datalong(len+10);
        ipps::vector<T> outlong(len+10);
        dfts.at(0).fwd(datalong.data(), outlong.data());

        // Then change back with another assignment
        dfts.at(0) = dft;
        dfts.at(0).fwd(data.data(), out.data());
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

TEST_CASE("ipps dft copy and assignment", "[dft], [copy],[assignment]")
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
TEST_CASE("ipps dft execution", "[dft],[execution]")
{
    int length = 100;
    double tolerance = 1e-4; // tolerance for floating point comparison

    SECTION("Ipp32f"){
        ipps::DFTCToC<Ipp32f> dft(length);
        // make some data for input and output
        ipps::vector<Ipp32f> in_re(length);
        ipps::vector<Ipp32f> in_im(length);
        ipps::vector<Ipp32f> out_re(length);
        ipps::vector<Ipp32f> out_im(length);
        // we need 2 output vectors..
        ipps::vector<Ipp32f> out_re2(length);
        ipps::vector<Ipp32f> out_im2(length);
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
        ipps::DFTCToC<Ipp64f> dft(length);
        // make some data for input and output
        ipps::vector<Ipp64f> in_re(length);
        ipps::vector<Ipp64f> in_im(length);
        ipps::vector<Ipp64f> out_re(length);
        ipps::vector<Ipp64f> out_im(length);
        // we need 2 output vectors..
        ipps::vector<Ipp64f> out_re2(length);
        ipps::vector<Ipp64f> out_im2(length);
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
        ipps::DFTCToC<Ipp32fc> dft(length);
        // make some data for input and output
        ipps::vector<Ipp32fc> in(length);
        ipps::vector<Ipp32fc> out(length);
        // we need 2 output vectors..
        ipps::vector<Ipp32fc> out2(length);
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
        ipps::DFTCToC<Ipp64fc> dft(length);
        // make some data for input and output
        ipps::vector<Ipp64fc> in(length);
        ipps::vector<Ipp64fc> out(length);
        // we need 2 output vectors..
        ipps::vector<Ipp64fc> out2(length);
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
