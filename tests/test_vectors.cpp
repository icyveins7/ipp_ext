#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

#include "test_vectors_encapsulation.h"

TEST_CASE("ippe vector instantiation", "[vector],[instantiation]")
{
    SECTION("instantiate 8u"){
        ippe::vector<Ipp8u> v8u;
        REQUIRE(v8u.size() == 0);
        REQUIRE(v8u.capacity() == 0);
        REQUIRE(v8u.data() == nullptr);

        ippe::vector<Ipp8u> v8u_size(2);
        REQUIRE(v8u_size.size() == 2);
        REQUIRE(v8u_size.capacity() == 2);
        REQUIRE(v8u_size.at(0) == 0); // both values should be 0
        REQUIRE(v8u_size.at(1) == 0);
    }

    SECTION("instantiate 16u"){
        ippe::vector<Ipp16u> v16u;
        REQUIRE(v16u.size() == 0);
        REQUIRE(v16u.capacity() == 0);

        ippe::vector<Ipp16u> v16u_size(2);
        REQUIRE(v16u_size.size() == 2);
        REQUIRE(v16u_size.capacity() == 2);
        REQUIRE(v16u_size.at(0) == 0); // both values should be 0
        REQUIRE(v16u_size.at(1) == 0);
    }

    SECTION("instantiate 32u"){
        ippe::vector<Ipp32u> v32u;
        REQUIRE(v32u.size() == 0);
        REQUIRE(v32u.capacity() == 0);

        ippe::vector<Ipp32u> v32u_size(2);
        REQUIRE(v32u_size.size() == 2);
        REQUIRE(v32u_size.capacity() == 2);
        REQUIRE(v32u_size.at(0) == 0); // both values should be 0
        REQUIRE(v32u_size.at(1) == 0);
    }

    SECTION ("instantiate 64u"){
        ippe::vector<Ipp64u> v64u;
        REQUIRE(v64u.size() == 0);
        REQUIRE(v64u.capacity() == 0);

        ippe::vector<Ipp64u> v64u_size(2);
        REQUIRE(v64u_size.size() == 2);
        REQUIRE(v64u_size.capacity() == 2);
        REQUIRE(v64u_size.at(0) == 0); // both values should be 0
        REQUIRE(v64u_size.at(1) == 0);
    }

    SECTION ("instantiate 8s") {
        ippe::vector<Ipp8s> v8s;
        REQUIRE(v8s.size() == 0);
        REQUIRE(v8s.capacity() == 0);

        ippe::vector<Ipp8s> v8s_size(2);
        REQUIRE(v8s_size.size() == 2);
        REQUIRE(v8s_size.capacity() == 2);
        REQUIRE(v8s_size.at(0) == 0); // both values should be 0
        REQUIRE(v8s_size.at(1) == 0);
    }

    SECTION ("instantiate 16s") {
        ippe::vector<Ipp16s> v16s;
        REQUIRE(v16s.size() == 0);
        REQUIRE(v16s.capacity() == 0);

        ippe::vector<Ipp16s> v16s_size(2);
        REQUIRE(v16s_size.size() == 2);
        REQUIRE(v16s_size.capacity() == 2);
        REQUIRE(v16s_size.at(0) == 0); // both values should be 0
        REQUIRE(v16s_size.at(1) == 0);
    }

    SECTION ("instantiate 32s") {
        ippe::vector<Ipp32s> v32s;
        REQUIRE(v32s.size() == 0);
        REQUIRE(v32s.capacity() == 0);

        ippe::vector<Ipp32s> v32s_size(2);
        REQUIRE(v32s_size.size() == 2);
        REQUIRE(v32s_size.capacity() == 2);
        REQUIRE(v32s_size.at(0) == 0); // both values should be 0
        REQUIRE(v32s_size.at(1) == 0);
    }

    SECTION ("instantiate 64s"){
        ippe::vector<Ipp64s> v64s;
        REQUIRE(v64s.size() == 0);
        REQUIRE(v64s.capacity() == 0);

        ippe::vector<Ipp64s> v64s_size(2);
        REQUIRE(v64s_size.size() == 2);
        REQUIRE(v64s_size.capacity() == 2);
        REQUIRE(v64s_size.at(0) == 0); // both values should be 0
        REQUIRE(v64s_size.at(1) == 0);
    }

    SECTION ("instantiate 32f") {
        ippe::vector<Ipp32f> v32f;
        REQUIRE(v32f.size() == 0);
        REQUIRE(v32f.capacity() == 0);

        ippe::vector<Ipp32f> v32f_size(2);
        REQUIRE(v32f_size.size() == 2);
        REQUIRE(v32f_size.capacity() == 2);
        REQUIRE(v32f_size.at(0) == 0); // both values should be 0
        REQUIRE(v32f_size.at(1) == 0);
    }

    SECTION ("instantiate 64f"){
        ippe::vector<Ipp64f> v64f;
        REQUIRE(v64f.size() == 0);
        REQUIRE(v64f.capacity() == 0);

        ippe::vector<Ipp64f> v64f_size(2);
        REQUIRE(v64f_size.size() == 2);
        REQUIRE(v64f_size.capacity() == 2);
        REQUIRE(v64f_size.at(0) == 0); // both values should be 0
        REQUIRE(v64f_size.at(1) == 0);
    }

    SECTION ("instantiate 8sc"){
        ippe::vector<Ipp8sc> v8sc;
        REQUIRE(v8sc.size() == 0);
        REQUIRE(v8sc.capacity() == 0);

        ippe::vector<Ipp8sc> v8sc_size(2);
        REQUIRE(v8sc_size.size() == 2);
        REQUIRE(v8sc_size.capacity() == 2);
        REQUIRE((v8sc_size.at(0).re == 0 && v8sc_size.at(0).im == 0)); // both values should be 0
        REQUIRE((v8sc_size.at(1).re == 0 && v8sc_size.at(1).im == 0));
    }

    SECTION ("instantiate 16sc"){
        ippe::vector<Ipp16sc> v16sc;
        REQUIRE(v16sc.size() == 0);
        REQUIRE(v16sc.capacity() == 0);

        ippe::vector<Ipp16sc> v16sc_size(2);
        REQUIRE(v16sc_size.size() == 2);
        REQUIRE(v16sc_size.capacity() == 2);
        REQUIRE((v16sc_size.at(0).re == 0 && v16sc_size.at(0).im == 0)); // both values should be 0
        REQUIRE((v16sc_size.at(1).re == 0 && v16sc_size.at(1).im == 0));
    }

    SECTION ("instantiate 32sc"){
        ippe::vector<Ipp32sc> v32sc;
        REQUIRE(v32sc.size() == 0);
        REQUIRE(v32sc.capacity() == 0);

        ippe::vector<Ipp32sc> v32sc_size(2);
        REQUIRE(v32sc_size.size() == 2);
        REQUIRE(v32sc_size.capacity() == 2);
        REQUIRE((v32sc_size.at(0).re == 0 && v32sc_size.at(0).im == 0)); // both values should be 0
        REQUIRE((v32sc_size.at(1).re == 0 && v32sc_size.at(1).im == 0));
    }

    SECTION ("instantiate 64sc"){
        ippe::vector<Ipp64sc> v64sc;
        REQUIRE(v64sc.size() == 0);
        REQUIRE(v64sc.capacity() == 0);

        ippe::vector<Ipp64sc> v64sc_size(2);
        REQUIRE(v64sc_size.size() == 2);
        REQUIRE(v64sc_size.capacity() == 2);
        REQUIRE((v64sc_size.at(0).re == 0 && v64sc_size.at(0).im == 0)); // both values should be 0
        REQUIRE((v64sc_size.at(1).re == 0 && v64sc_size.at(1).im == 0));
    }

    SECTION ("instantiate 32fc") {
        ippe::vector<Ipp32fc> v32fc;
        REQUIRE(v32fc.size() == 0);
        REQUIRE(v32fc.capacity() == 0);

        ippe::vector<Ipp32fc> v32fc_size(2);
        REQUIRE(v32fc_size.size() == 2);
        REQUIRE(v32fc_size.capacity() == 2);
        REQUIRE((v32fc_size.at(0).re == 0 && v32fc_size.at(0).im == 0)); // both values should be 0
        REQUIRE((v32fc_size.at(1).re == 0 && v32fc_size.at(1).im == 0));
    }

    SECTION ("instantiate 64fc"){
        ippe::vector<Ipp64fc> v64fc;
        REQUIRE(v64fc.size() == 0);
        REQUIRE(v64fc.capacity() == 0);

        ippe::vector<Ipp64fc> v64fc_size(2);
        REQUIRE(v64fc_size.size() == 2);
        REQUIRE(v64fc_size.capacity() == 2);
        REQUIRE((v64fc_size.at(0).re == 0 && v64fc_size.at(0).im == 0)); // both values should be 0
        REQUIRE((v64fc_size.at(1).re == 0 && v64fc_size.at(1).im == 0));
    }

}

TEST_CASE("ippe vector capacity and resizes", "[vector],[resize]"){
    ippe::vector<Ipp64fc> data;

    SECTION("resize once"){
        data.resize(256);
        REQUIRE(data.size() == 256);
    }

    SECTION("resize twice, to a smaller value"){
        data.resize(256); // this should have reserved to 256
        data.resize(8); // this does not affect the reserved capacity
        REQUIRE(data.size() == 8);
        REQUIRE(data.capacity() == 256);
    }
}

TEST_CASE("ippe vector writes", "[vector],[write]"){
    ippe::vector<Ipp64fc> data(128);

    SECTION("pushback and access"){
        Ipp64fc val = {1.0, 0.0};
        data.push_back(val);
        REQUIRE(data.size() == 129);
        REQUIRE(data.back().re == val.re);
        REQUIRE(data.back().im == val.im);
        REQUIRE(data.at(128).re == val.re);
        REQUIRE(data.at(128).im == val.im);
    }
}

TEST_CASE("ippe vector throws on non-IPP types", "[vector],[exceptions]"){
    SECTION("double"){
        try{
            ippe::vector<double> data(128);
        }
        catch(const std::exception& e){
            REQUIRE_THROWS_AS(throw e, std::domain_error);
        }
    }

    SECTION("float"){
        try{
            ippe::vector<float> data(128);
        }
        catch(const std::exception& e){
            REQUIRE_THROWS_AS(throw e, std::domain_error);
        }
    }
}

TEST_CASE("ippe vector exceptions", "[vector],[exceptions]"){
    ippe::vector<Ipp64fc> data(128);

    SECTION("access out of range"){
        REQUIRE_THROWS_AS(data.at(128), std::out_of_range);
    }
}

// this test is mainly here to ensure that compilation still works
// when the header is included and used in several cpp files
TEST_CASE("ippe vector encapsulation compile test", "[vector],[compile]"){
    EncapsulateVector ev;
}

	



