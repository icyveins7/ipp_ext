#include <iostream>
#include "ipp_ext.h"
#include <stdexcept>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ipps matrix instantiation", "[matrix],[instantiation]")
{
    SECTION("instantiate 8u")
    {
        ipps::matrix<Ipp8u> m8u;
        // Matrix-specific
        REQUIRE(m8u.rows() == 0);
        REQUIRE(m8u.columns() == 0);
        // Inherited from vector
        REQUIRE(m8u.size() == 0);
        REQUIRE(m8u.capacity() == 0);
        REQUIRE(m8u.data() == nullptr);

        // construct with only columns
        ipps::matrix<Ipp8u> m8u_cols(2);
        // Matrix-specific
        REQUIRE(m8u_cols.rows() == 1);
        REQUIRE(m8u_cols.columns() == 2);
        // Inherited from vector
        REQUIRE(m8u_cols.size() == 2);
        REQUIRE(m8u_cols.capacity() == 2);
        REQUIRE(m8u_cols.data() != nullptr);

        // construct with rows/columns
        ipps::matrix<Ipp8u> m8rc(2,2);
        // Matrix-specific
        REQUIRE(m8rc.rows() == 2);
        REQUIRE(m8rc.columns() == 2);
        // Inherited from vector
        REQUIRE(m8rc.size() == 4);
        REQUIRE(m8rc.capacity() == 4);
        REQUIRE(m8rc.data()!= nullptr);

        // construct with rows/columns and zeroed
        ipps::matrix<Ipp8u> m8rcz(2,2,0);
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
        ipps::matrix<Ipp8u> m8rcf(2,2,v);
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

TEST_CASE("ipps matrix access", "[matrix],[access]")
{
    SECTION("access 8u")
    {
        ipps::matrix<Ipp8u> m8u(3,5);

        // Check row access
        for (int i = 0; i < m8u.rows(); ++i)
        {
            REQUIRE(m8u.row(i) == &m8u.at(i * m8u.columns())); // check reference
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

TEST_CASE("ipps matrix resize", "[matrix],[resize]")
{
    SECTION("Ipp8u")
    {
        ipps::matrix<Ipp8u> m8u(3,5, 0);

        m8u.redim(2,3);
        REQUIRE(m8u.rows() == 2);
        REQUIRE(m8u.columns() == 3);
        // The values should all be 0, since it is smaller and they were previously set to 0
        for (int i = 0; i < m8u.size(); ++i)
        {
            REQUIRE(m8u.at(i) == 0);
        }

        m8u.redim(7, 7, 1);
        REQUIRE(m8u.rows() == 7);
        REQUIRE(m8u.columns() == 7);
        for (int i = 0; i < m8u.size(); ++i)
        {
            if (i < 6) // previous original size
                REQUIRE(m8u.at(i) == 0);
            else
                REQUIRE(m8u.at(i) == 1);
        }
    }
}

TEST_CASE("ipps matrix math", "[matrix],[math]")
{
    SECTION("16u operator+")
    {
        ipps::matrix<Ipp16u> x(3,5);
        ipps::matrix<Ipp16u> y(3,5);
        for (int i = 0; i < x.size(); ++i)
            x.at(i) = (Ipp16u)i;
        for (int i = 0; i < y.size(); ++i)
            y.at(i) = (Ipp16u)(i + 1);

        ipps::matrix<Ipp16u> z = x + y;
        for (int i = 0; i < z.size(); ++i)
            REQUIRE(z.at(i) == x.at(i) + y.at(i));

        // Demonstrate failure with mismatched shapes
        ipps::matrix<Ipp16u> ywrong(5,3);

        REQUIRE_THROWS_AS(z = x + ywrong, std::out_of_range);
    }

    SECTION("16s operator-")
    {
        ipps::matrix<Ipp16s> x(3,5);
        ipps::matrix<Ipp16s> y(3,5);
        for (int i = 0; i < x.size(); ++i)
            x.at(i) = (Ipp16s)i;
        for (int i = 0; i < y.size(); ++i)
            y.at(i) = (Ipp16s)(i + 1);

        ipps::matrix<Ipp16s> z = y - x;
        for (int i = 0; i < z.size(); ++i)
            REQUIRE(z.at(i) == y.at(i) - x.at(i));

        // Demonstrate failure with mismatched shapes
        ipps::matrix<Ipp16s> ywrong(5,3);

        REQUIRE_THROWS_AS(z = ywrong - x, std::out_of_range);
    }

    SECTION("16s operator+=")
    {
        ipps::matrix<Ipp16s> x(3,5);
        ipps::matrix<Ipp16s> y(3,5);
        ipps::matrix<Ipp16s> check(3,5);
        for (int i = 0; i < x.size(); ++i)
        {
            x.at(i) = (Ipp16s)i;
            y.at(i) = (Ipp16s)(i+1);
            check.at(i) = x.at(i);
        }

        // Demonstrate chaining as well
        (x += y) += y; // x = x + y + y, leaves y untouched
        for (int i = 0; i < x.size(); ++i)
            REQUIRE(x.at(i) ==  y.at(i) + y.at(i) + check.at(i));

        // Demonstrate failure with mismatched shapes
        ipps::matrix<Ipp16s> ywrong(5,3);

        REQUIRE_THROWS_AS(x += ywrong, std::out_of_range);
    }

    SECTION("16s operator-=")
    {
        ipps::matrix<Ipp16s> x(3,5);
        ipps::matrix<Ipp16s> y(3,5);
        ipps::matrix<Ipp16s> check(3,5);
        for (int i = 0; i < x.size(); ++i)
        {
            x.at(i) = (Ipp16s)i;
            y.at(i) = (Ipp16s)(2*(i+1));
            check.at(i) = y.at(i);
        }

        // Demonstrate chaining as well
        (y -= x) -= x; // y = y - x - x, leaves x untouched
        for (int i = 0; i < x.size(); ++i)
            REQUIRE(y.at(i) == check.at(i) - x.at(i) - x.at(i));

        // Demonstrate failure with mismatched shapes
        ipps::matrix<Ipp16s> ywrong(5,3);

        REQUIRE_THROWS_AS(ywrong -= x, std::out_of_range);
    }

    SECTION("32f operator+ constant"){
        ipps::matrix<Ipp32f> x(3,5);
        Ipp32f y = 22;

        for (int i = 0; i < x.size(); ++i)
        {
            x.at(i) = (Ipp32f)i;
        }

        // Perform operation
        ipps::matrix<Ipp32f> result = x + y;
        // ipps::matrix<Ipp32f> result = y + x; // Note that this doesn't compile..

        for (int i = 0; i < result.size(); ++i)
        {
            REQUIRE(result.at(i) == x.at(i) + y);
        }
    }

    SECTION("32f operator*")
    {
        ipps::matrix<Ipp32f> x(2,3);
        ipps::matrix<Ipp32f> y(3,2);

        for (int i = 0; i < x.size(); ++i)
        {
            x.at(i) = (Ipp32f)i;
        }
        for (int i = 0; i < y.size(); ++i)
        {
            y.at(i) = (Ipp32f)(i + 1);
        }
        
        // Perform matmul
        ipps::matrix<Ipp32f> result = x * y;

        int L = (int)x.columns();

        for (int i = 0; i < result.rows(); ++i)
        {
            for (int j = 0; j < result.columns(); ++j)
            {
                Ipp32f sum = 0;
                for (int l = 0; l < L; ++l)
                {
                    sum += x.index(i, l) * y.index(l, j);
                }
                REQUIRE(result.index(i,j) == sum);
            }
        }

        // Perform mat-vec mul
        ipps::matrix<Ipp32f> c(3,1);

        for (int i = 0; i < c.size(); ++i)
        {
            c.at(i) = (Ipp32f)(i + 2);
        }

        ipps::matrix<Ipp32f> matvecresult = x * c;

        for (int i = 0; i < matvecresult.rows(); ++i)
        {
            for (int j = 0; j < matvecresult.columns(); ++j)
            {
                Ipp32f sum = 0;
                for (int l = 0; l < L; ++l)
                {
                    sum += x.index(i, l) * c.index(l, j);
                }
                REQUIRE(matvecresult.index(i,j) == sum);
            }
        }
    }
}
