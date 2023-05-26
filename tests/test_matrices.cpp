#include <iostream>
#include "ipp_ext_matrix.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ippe matrix instantiation", "[matrix],[instantiation]")
{
    SECTION("instantiate 8u")
    {
        ippe::matrix<Ipp8u> m8u;
        // Matrix-specific
        REQUIRE(m8u.rows() == 0);
        REQUIRE(m8u.columns() == 0);
        // Inherited from vector
        REQUIRE(m8u.size() == 0);
        REQUIRE(m8u.capacity() == 0);
        REQUIRE(m8u.data() == nullptr);

        // construct with rows/columns
        ippe::matrix<Ipp8u> m8rc(2,2);
        // Matrix-specific
        REQUIRE(m8rc.rows() == 2);
        REQUIRE(m8rc.columns() == 2);
        // Inherited from vector
        REQUIRE(m8rc.size() == 4);
        REQUIRE(m8rc.capacity() == 4);
        REQUIRE(m8rc.data()!= nullptr);

        // construct with rows/columns and zeroed
        ippe::matrix<Ipp8u> m8rcz(2,2,0);
        // Matrix-specific
        REQUIRE(m8rcz.rows() == 2);
        REQUIRE(m8rcz.columns() == 2);
        // Inherited from vector
        REQUIRE(m8rcz.size() == 4);
        REQUIRE(m8rcz.capacity() == 4);
        REQUIRE(m8rcz.data()!= nullptr);
        // Check all zero
        Ipp8u z = 0;
        for (int i = 0; i < m8rcz.size(); ++i)
            REQUIRE(m8rcz.data()[i] == z);

        // construct with rows/columns and filled
        Ipp8u v = 255;
        ippe::matrix<Ipp8u> m8rcf(2,2,v);
        // Matrix-specific
        REQUIRE(m8rcf.rows() == 2);
        REQUIRE(m8rcf.columns() == 2);
        // Inherited from vector
        REQUIRE(m8rcf.size() == 4);
        REQUIRE(m8rcf.capacity() == 4);
        REQUIRE(m8rcf.data()!= nullptr);
        // Check all filled
        for (int i = 0; i < m8rcf.size(); ++i)
            REQUIRE(m8rcf.data()[i] == v);
    }
}

TEST_CASE("ippe matrix access", "[matrix],[access]")
{
    SECTION("access 8u")
    {
        ippe::matrix<Ipp8u> m8u(3,5);

        // Check row access
        for (int i = 0; i < m8u.rows(); ++i)
        {
            REQUIRE(&m8u.row(i) == &m8u.at(i * m8u.columns())); // check reference
        }

        // Check indexed access
        for (int i = 0; i < m8u.rows(); ++i)
        {
            for (int j = 0; j < m8u.columns(); ++j)
            {
                REQUIRE(&m8u.index(i,j) == &m8u.at(i * m8u.columns() + j)); // check reference
            }
        }
    }
}

