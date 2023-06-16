#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>


/*
Template test case for RandUniform
*/
template <typename T>
void randUniform_test()
{
    // Create generator with seed
    ippe::RandUniform<T> gen(0, 1, 100);

    // Check internals
    REQUIRE(gen.getHigh() == 1);
    REQUIRE(gen.getLow() == 0);
    REQUIRE(gen.getSeed() == 100);

    // Create without seed
    ippe::RandUniform<T> gen2(0, 1);

    // Check internals
    REQUIRE(gen2.getHigh() == 1);
    REQUIRE(gen2.getLow() == 0);
    REQUIRE(gen2.getSeed() == 0);

    // Create another via automatic copy constructor
    ippe::RandUniform<T> gen3 = gen2;

    // Generate some data
    ippe::vector<T> data(1000);
    ippe::vector<T> data2(1000);
    ippe::vector<T> data3(1000);

    gen.generate(data.data(), 1000);
    gen2.generate(data2.data(), 1000);
    gen3.generate(data3.data(), 1000);

    // Same seed should be equal
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(data2[i] == data3[i]);
    }

    // There should be at least 1 different value when seeds are different
    bool isDifferent = false;
    for (int i = 0; i < 1000; i++)
    {
        if (data[i] != data2[i])
        {
            isDifferent = true;
            break;
        }
    }
    REQUIRE(isDifferent);

    // The values should be within the range
    for (int i = 0; i < 1000; i++)
    {
        REQUIRE(((data[i] >= 0) && (data[i] <= 1)));
        REQUIRE(((data2[i] >= 0) && (data2[i] <= 1)));
        REQUIRE(((data3[i] >= 0) && (data3[i] <= 1)));
    }
}

TEST_CASE("ippe RandUniform", "[random], [uniform]")
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

/*
Template test case for RandGauss
*/
template <typename T>
void randGauss_test()
{
    // Create generator with seed
    ippe::RandGauss<T> gen(10, 1, 100);

    // Check internals
    REQUIRE(gen.getMean() == 10);
    REQUIRE(gen.getStddev() == 1);
    REQUIRE(gen.getSeed() == 100);

    // Create without seed
    ippe::RandGauss<T> gen2(0, 1);

    // Check internals
    REQUIRE(gen2.getMean() == 0);
    REQUIRE(gen2.getStddev() == 1);
    REQUIRE(gen2.getSeed() == 0);

    // Create another via automatic copy constructor
    ippe::RandGauss<T> gen3 = gen2;

    // Generate some data
    ippe::vector<T> data(10);
    ippe::vector<T> data2(10);
    ippe::vector<T> data3(10);

    gen.generate(data.data(), 10);
    gen2.generate(data2.data(), 10);
    gen3.generate(data3.data(), 10);

    // Same seed should be equal
    for (int i = 0; i < 10; i++)
    {
        REQUIRE(data2[i] == data3[i]);
    }

    // There should be at least 1 different value when seeds are different
    bool isDifferent = false;
    for (int i = 0; i < 10; i++)
    {
        if (data[i] != data2[i])
        {
            isDifferent = true;
            break;
        }
    }
    REQUIRE(isDifferent);

    // Can't really definitively test for stddeviation/mean values, nor range of values
    T estMean = 0, estMean2 = 0, estMean3 = 0;
    for (int i = 0; i < 10; i++)
    {
        estMean += data[i];
        estMean2 += data2[i];
        estMean3 += data3[i];
    }
    estMean = estMean / (T)10;
    estMean2 = estMean2 / (T)10;
    estMean3 = estMean3 / (T)10;

    REQUIRE(estMean > estMean2); // First one should be sufficiently bigger
    REQUIRE(estMean2 == estMean3);
}

TEST_CASE("ippe RandGauss", "[random], [gauss]")
{
    SECTION("Ipp8u")
    {
        randGauss_test<Ipp8u>();
    }

    SECTION("Ipp16s")
    {
        randGauss_test<Ipp16s>();
    }

    SECTION("Ipp32f")
    {
        randGauss_test<Ipp32f>();
    }

    SECTION("Ipp64f")
    {
        randGauss_test<Ipp64f>();
    }
}