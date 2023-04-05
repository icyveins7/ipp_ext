#include <iostream>
#include "ipp.h"
#include <vector>
#include <string>

#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ippe vector instantiation", "[vector],[instantiation]")
{
    SECTION("instantiate 8u"){
        ippe::vector<Ipp8u> v8u;
    }

    SECTION("instantiate 16u"){
        ippe::vector<Ipp16u> v16u;
    }

    SECTION("instantiate 32u"){
        ippe::vector<Ipp32u> v32u;
    }

    SECTION ("instantiate 64u"){
        ippe::vector<Ipp64u> v64u;
    }

    SECTION ("instantiate 8s") {
        ippe::vector<Ipp8s> v8s;
    }

    SECTION ("instantiate 16s") {
        ippe::vector<Ipp16s> v16s;
    }

    SECTION ("instantiate 32s") {
        ippe::vector<Ipp32s> v32s;
    }

    SECTION ("instantiate 64s"){
        ippe::vector<Ipp64s> v64s;
    }

    SECTION ("instantiate 32f") {
        ippe::vector<Ipp32f> v32f;
    }

    SECTION ("instantiate 64f"){
        ippe::vector<Ipp64f> v64f;
    }

    SECTION ("instantiate 8sc"){
        ippe::vector<Ipp8sc> v8sc;
    }

    SECTION ("instantiate 16sc"){
        ippe::vector<Ipp16sc> v16sc;
    }

    SECTION ("instantiate 32sc"){
        ippe::vector<Ipp32sc> v32sc;
    }

    SECTION ("instantiate 64sc"){
        ippe::vector<Ipp64sc> v64sc;
    }

    SECTION ("instantiate 32fc") {
        ippe::vector<Ipp32fc> v32fc;
    }

    SECTION ("instantiate 64fc"){
        ippe::vector<Ipp64fc> v64fc;
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

	



