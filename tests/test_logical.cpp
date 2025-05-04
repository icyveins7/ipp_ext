#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

template <typename T>
void test_Xor()
{
    // Create 3 vectors
    ipps::vector<T> a(256);
    ipps::vector<T> b(256);
    ipps::vector<T> c(256);

    // Fill first 2 vectors
    for (int i = 0; i < a.size(); i++)
    {
        a[i] = (T)i;
        b[i] = (T)(i + 1);
    }

    // XOR with IPPE
    ipps::logical::Xor(a.data(), b.data(), c.data(), (int)c.size());

    // Check results
    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(c[i] == (a[i] ^ b[i]));
    }
}

TEST_CASE("ipps logical Xor", "[logical], [Xor]")
{
    SECTION("Ipp8u"){
        test_Xor<Ipp8u>();
    }
    SECTION("Ipp16u"){
        test_Xor<Ipp16u>();
    }
    SECTION("Ipp32u"){
        test_Xor<Ipp32u>();
    }
}

template <typename T>
void test_Xor_I()
{
    // Create 3 vectors
    ipps::vector<T> a(256);
    ipps::vector<T> b(256);
    ipps::vector<T> c(256);

    // Fill first 2 vectors
    for (int i = 0; i < a.size(); i++)
    {
        a[i] = (T)i;
        b[i] = (T)(i + 1);
        // Copy to c
        c[i] = b[i];
    }

    // XOR_I with IPPE
    ipps::logical::Xor_I(a.data(), b.data(), (int)b.size());

    // Check results
    for (int i = 0; i < a.size(); i++)
    {
        REQUIRE(b[i] == (a[i] ^ c[i]));
    }
}

TEST_CASE("ipps logical Xor_I", "[logical], [Xor_I]")
{
    SECTION("Ipp8u"){
        test_Xor_I<Ipp8u>();
    }
    SECTION("Ipp16u"){
        test_Xor_I<Ipp16u>();
    }
    SECTION("Ipp32u"){
        test_Xor_I<Ipp32u>();
    }
}

