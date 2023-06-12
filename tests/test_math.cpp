#include <iostream>
#include "ipp_ext_math.h"
#include "ipp_ext_vec.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("ippe math Add", "[math, Add]")
{
    SECTION("Errors")
    {
        ippe::vector<Ipp16s> x(10);
        ippe::vector<Ipp16s> y(10);
        ippe::vector<Ipp16s> z(10);
        // Throw when null pointer
        Ipp16s *nptr = nullptr;
        REQUIRE_THROWS_AS(
            ippe::math::Add(nptr, x.data(), z.data(), x.size()), std::runtime_error);

        // Throw when 0 length
        REQUIRE_THROWS_AS(
            ippe::math::Add(x.data(), y.data(), z.data(), 0), std::runtime_error);
    }

    /*
    Flavours are:
    Ipp16s
    Ipp32f
    Ipp64f
    Ipp32fc
    Ipp64fc
    Ipp8u to Ipp16u
    Ipp16u
    Ipp32u
    Ipp16s to Ipp32f
    */
   SECTION("Ipp16s")
   {
       ippe::vector<Ipp16s> x(10);
       ippe::vector<Ipp16s> y(10);
       ippe::vector<Ipp16s> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }

   SECTION("Ipp32f")
   {
       ippe::vector<Ipp32f> x(10);
       ippe::vector<Ipp32f> y(10);
       ippe::vector<Ipp32f> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }

   SECTION("Ipp64f")
   {
       ippe::vector<Ipp64f> x(10);
       ippe::vector<Ipp64f> y(10);
       ippe::vector<Ipp64f> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }

   SECTION("Ipp32fc")
   {
       ippe::vector<Ipp32fc> x(10);
       ippe::vector<Ipp32fc> y(10);
       ippe::vector<Ipp32fc> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = {(Ipp32f)i, (Ipp32f)(i+1)};
           y[i] = {(Ipp32f)(i*2), (Ipp32f)(i*2+1)};
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i].re == x[i].re + y[i].re);
           REQUIRE(result[i].im == x[i].im + y[i].im);
       }
   }

   SECTION("Ipp64fc")
   {
       ippe::vector<Ipp64fc> x(10);
       ippe::vector<Ipp64fc> y(10);
       ippe::vector<Ipp64fc> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = {(Ipp64f)i, (Ipp64f)(i+1)};
           y[i] = {(Ipp64f)(i*2), (Ipp64f)(i*2+1)};
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i].re == x[i].re + y[i].re);
           REQUIRE(result[i].im == x[i].im + y[i].im);
       }
   }

   SECTION("Ipp8u to Ipp16u")
   {
       ippe::vector<Ipp8u> x(10);
       ippe::vector<Ipp8u> y(10);
       ippe::vector<Ipp16u> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }

   SECTION("Ipp16u")
   {
       ippe::vector<Ipp16u> x(10);
       ippe::vector<Ipp16u> y(10);
       ippe::vector<Ipp16u> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }

   SECTION("Ipp32u")
   {
       ippe::vector<Ipp32u> x(10);
       ippe::vector<Ipp32u> y(10);
       ippe::vector<Ipp32u> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }

   SECTION("Ipp16s to Ipp32f")
   {
       ippe::vector<Ipp16s> x(10);
       ippe::vector<Ipp16s> y(10);
       ippe::vector<Ipp32f> result(10);
       // Set some values
       for (int i = 0; i < x.size(); ++i)
       {
           x[i] = i;
           y[i] = i * 2;
       }
       // Perform the operation
       ippe::math::Add(x.data(), y.data(), result.data(), x.size());
       // Check the result
       for (int i = 0; i < x.size(); ++i)
       {
           REQUIRE(result[i] == x[i] + y[i]);
       }
   }
}

TEST_CASE("ippe math Add_Sfs", "[math, Add_Sfs]")
{
    /*
    Flavours are:
    Ipp8u
    Ipp16u
    Ipp16s
    Ipp32s
    Ipp16sc
    Ipp32sc
    Ipp64s
    */

   SECTION("Ipp8u")
   {
        ippe::vector<Ipp8u> x(10);
        ippe::vector<Ipp8u> y(10);
        ippe::vector<Ipp8u> result(10);

        // Set some values
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = i + 64;
            y[i] = i * 2 + 64;
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp8u z;
        for (int i = 0; i < x.size(); ++i)
        {
            z = x[i] + y[i];
            // If z is odd, then the result must be fixed
            if (z % 2 == 1)
            {
                z = z / 2;
                z += 1;
            }
            else
            {
                z = z / 2;
            }
            REQUIRE(result[i] == z);
        }
   }
}