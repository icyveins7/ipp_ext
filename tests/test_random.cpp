#include <iostream>
#include "ipp_ext_random.h"
#include "ipp_ext_vec.h"

#include <catch2/catch_test_macros.hpp>


/*
Template instantiation test case
*/
template <typename T>
void randUniform_test()
{
    // Create generator with seed
    ippe::RandUniform<Ipp8u> gen(0, 1, 100);

    // Check internals
    REQUIRE(gen.getHigh() == 1);
    REQUIRE(gen.getLow() == 0);
    REQUIRE(gen.getSeed() == 100);

    // Create without seed
    ippe::RandUniform<Ipp8u> gen2(0, 1);

    // Check internals
    REQUIRE(gen2.getHigh() == 1);
    REQUIRE(gen2.getLow() == 0);
    REQUIRE(gen2.getSeed() == 0);
}

TEST_CASE("ippe RandUniform instantiation", "[random], [uniform]")
{
    SECTION("Ipp8u")
    {
        randUniform_test<Ipp8u>();
    }

    SECTION("Ipp16s")
    {
        randUniform_test<Ipp16s>();
    }

    SECTION("Ipp32f")
    {
        randUniform_test<Ipp32f>();
    }

    SECTION("Ipp64f")
    {
        randUniform_test<Ipp64f>();
    }
}