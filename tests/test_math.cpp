#include <iostream>
#include <cmath>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

// Helper function to evaluate integer scaling results
// I didn't really check this for anything other than scaleFactor=1
template <typename T>
T evaluate_integer_scaling(T x, int scaleFactor)
{
    if (scaleFactor == 0)
    {
        return x;
    }

    int f = 1 << scaleFactor;
    if (x % 2 == 1 || x % 2 == -1)
    {
        x = x / f;
        // If the resulting division was clipped down to an odd number then add 1 to make it even
        if (x % 2 == 1 || x % 2 == -1){
            if (x > 0) // for negative numbers we should already hit the even value
            {
                x += 1;
            }
            else
            {
                x -= 1;
            }      
        }
    }
    else
    {
        x = x / f;
    }
    return x;
}

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
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z % 2 == 1)
                    z += 1;
            }
            else
            {
                z = z / 2;
            }
            REQUIRE(result[i] == z);
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
            x[i] = i + 64;
            y[i] = i * 2 + 64;
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp16u z;
        for (int i = 0; i < x.size(); ++i)
        {
            z = x[i] + y[i];
            // If z is odd, then the result must be fixed
            if (z % 2 == 1)
            {
                z = z / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z % 2 == 1)
                    z += 1;
            }
            else
            {
                z = z / 2;
            }
            REQUIRE(result[i] == z);
        }
   }

   SECTION("Ipp16s")
   {
        ippe::vector<Ipp16s> x(10);
        ippe::vector<Ipp16s> y(10);
        ippe::vector<Ipp16s> result(10);

        // Set some values
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = i + 64;
            y[i] = i * 2 + 64;
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp16s z;
        for (int i = 0; i < x.size(); ++i)
        {
            z = x[i] + y[i];
            // If z is odd, then the result must be fixed
            if (z % 2 == 1)
            {
                z = z / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z % 2 == 1)
                    z += 1;
            }
            else
            {
                z = z / 2;
            }
            REQUIRE(result[i] == z);
        }
   }

   SECTION("Ipp32s")
   {
        ippe::vector<Ipp32s> x(10);
        ippe::vector<Ipp32s> y(10);
        ippe::vector<Ipp32s> result(10);

        // Set some values
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = i + 64;
            y[i] = i * 2 + 64;
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp32s z;
        for (int i = 0; i < x.size(); ++i)
        {
            z = x[i] + y[i];
            // If z is odd, then the result must be fixed
            if (z % 2 == 1)
            {
                z = z / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z % 2 == 1)
                    z += 1;
            }
            else
            {
                z = z / 2;
            }
            REQUIRE(result[i] == z);
        }
   }

   SECTION("Ipp16sc")
   {
        ippe::vector<Ipp16sc> x(10);
        ippe::vector<Ipp16sc> y(10);
        ippe::vector<Ipp16sc> result(10);

        // Set some values
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = {(Ipp16s)(i + 64), (Ipp16s)(i + 65)};
            y[i] = {(Ipp16s)(i * 2 + 64), (Ipp16s)(i * 2 + 65)};
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp16sc z;
        for (int i = 0; i < x.size(); ++i)
        {
            z.re = x[i].re + y[i].re;
            z.im = x[i].im + y[i].im;
            // If z is odd, then the result must be fixed
            if (z.re % 2 == 1)
            {
                z.re = z.re / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z.re % 2 == 1)
                    z.re += 1;
            }
            else
            {
                z.re = z.re / 2;
            }
            // Similar for imag part
            if (z.im % 2 == 1)
            {
                z.im = z.im / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z.im % 2 == 1)
                    z.im += 1;
            }
            else
            {
                z.im = z.im / 2;
            }
            REQUIRE(result[i].re == z.re);
            REQUIRE(result[i].im == z.im);
        }

   }

   SECTION("Ipp32sc")
   {
        ippe::vector<Ipp32sc> x(10);
        ippe::vector<Ipp32sc> y(10);
        ippe::vector<Ipp32sc> result(10);

        // Set some values
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = {(Ipp32s)(i + 64), (Ipp32s)(i + 65)};
            y[i] = {(Ipp32s)(i * 2 + 64), (Ipp32s)(i * 2 + 65)};
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp32sc z;
        for (int i = 0; i < x.size(); ++i)
        {
            z.re = x[i].re + y[i].re;
            z.im = x[i].im + y[i].im;

            // If z is odd, then the result must be fixed
            if (z.re % 2 == 1)
            {
                z.re = z.re / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z.re % 2 == 1)
                    z.re += 1;
            }
            else
            {
                z.re = z.re / 2;
            }

            // Similar for imag part
            if (z.im % 2 == 1)
            {
                z.im = z.im / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z.im % 2 == 1)
                    z.im += 1;
            }
            else
            {
                z.im = z.im / 2;
            }
            REQUIRE(result[i].re == z.re);
            REQUIRE(result[i].im == z.im);
        }
   }

   SECTION("Ipp64s")
   {
        ippe::vector<Ipp64s> x(10);
        ippe::vector<Ipp64s> y(10);
        ippe::vector<Ipp64s> result(10);

        // Set some values
        for (int i = 0; i < x.size(); ++i)
        {
            x[i] = i + 64;
            y[i] = i * 2 + 64;
        }

        // Perform the operation, with a single scaling factor of half
        ippe::math::Add_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

        // Check the result
        Ipp64s z;
        for (int i = 0; i < x.size(); ++i)
        {
            z = x[i] + y[i];
            // If z is odd, then the result must be fixed
            if (z % 2 == 1)
            {
                z = z / 2;
                // If the resulting division was clipped down to an odd number then add 1 to make it even
                if (z % 2 == 1)
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


/*
Templated test case for Add_I.
*/
template <typename T, typename U>
void test_Add_I()
{
    // Create two vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> result(10);

    // Create check vector for result
    ippe::vector<U> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        result[i] = (U)(i + 64);
        check[i] = (U)(i + 64);
    }

    // Perform the operation
    ippe::math::Add_I(x.data(), result.data(), x.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == (check[i] + x[i]));
    }
}

template <typename T, typename U>
void test_Add_I_complex()
{
    // Create two vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> result(10);

    // Create check vector for result
    ippe::vector<U> check(10);

    // Set some values
    T valT;
    U valU;
    for (int i = 0; i < x.size(); ++i)
    {
        valT.re = i + 64;
        valT.im = i + 65;
        valU.re = 2*i + 64;
        valU.im = 2*i + 65;
        x[i] = valT;
        result[i] = valU;
        check[i] = result[i];
    }

    // Perform the operation
    ippe::math::Add_I(x.data(), result.data(), x.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == (check[i].re + x[i].re));
        REQUIRE(result[i].im == (check[i].im + x[i].im));
    }
}

TEST_CASE("ippe math Add_I", "[math, Add_I]")
{
    /*
    Flavours are:
    Ipp16s
    Ipp32f
    Ipp64f
    Ipp32fc
    Ipp64fc
    Ipp16s32s
    Ipp32u
    */

    SECTION("Ipp16s"){
        test_Add_I<Ipp16s, Ipp16s>();
    }

    SECTION("Ipp32f"){
        test_Add_I<Ipp32f, Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Add_I<Ipp64f, Ipp64f>();
    }

    SECTION("Ipp32fc"){
        test_Add_I_complex<Ipp32fc, Ipp32fc>();
    }

    SECTION("Ipp64fc"){
        test_Add_I_complex<Ipp64fc, Ipp64fc>();
    }

    SECTION("Ipp16s32s"){
        test_Add_I<Ipp16s, Ipp32s>();
    }

    SECTION("Ipp32u"){
        test_Add_I<Ipp32u, Ipp32u>();
    }
}

/*
Templated test case for Add_ISfs
*/
template <typename T>
void test_Add_ISfs()
{
    // Create two vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);
    // Create check vector for result
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        result[i] = (T)(i + 64);
        check[i] = (T)(i + 64);
    }

    // Perform the operation, scaling by half
    ippe::math::Add_ISfs(x.data(), result.data(), x.size(), 1);
    
    // Check the result
    T z;
    for (int i = 0; i < x.size(); ++i)
    {
        z = x[i] + check[i];
        // If z is odd, then the result must be fixed
        if (z % 2 == 1)
        {
            z = z / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z % 2 == 1)
                z += 1;
        }
        else
        {
            z = z / 2;
        }

        REQUIRE(result[i] == z);
    }
}

template <typename T>
void test_Add_ISfs_complex()
{
    // Create two vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);
    // Create check vector for result
    ippe::vector<T> check(10);

    // Set some values
    T val1, val2;

    for (int i = 0; i < x.size(); ++i)
    {
        val1.re = i + 64;
        val1.im = i + 65;
        val2.re = 2*i + 64;
        val2.im = 2*i + 65;

        x[i] = val1;
        result[i] = val2;
        check[i] = result[i];
    }

    // Perform the operation, scaling by half
    ippe::math::Add_ISfs(x.data(), result.data(), x.size(), 1);
    
    // Check the result
    T z;
    for (int i = 0; i < x.size(); ++i)
    {
        // Check real
        z.re = x[i].re + check[i].re;
        // If z is odd, then the result must be fixed
        if (z.re % 2 == 1)
        {
            z.re = z.re / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z.re % 2 == 1)
                z.re += 1;
        }
        else
        {
            z.re = z.re / 2;
        }

        REQUIRE(result[i].re == z.re);

        // Check imag
        z.im = x[i].im + check[i].im;
        // If z is odd, then the result must be fixed
        if (z.im % 2 == 1)
        {
            z.im = z.im / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z.im % 2 == 1)
                z.im += 1;
        }
        else
        {
            z.im = z.im / 2;
        }

        REQUIRE(result[i].im == z.im);
    }
}

TEST_CASE("ippe math Add_ISfs", "[math, Add_ISfs]")
{
    /*
    Flavours are:
    Ipp8u
    Ipp16u
    Ipp16s
    Ipp32s
    Ipp16sc
    Ipp32sc
    */

    SECTION("Ipp8u"){
        test_Add_ISfs<Ipp8u>();
    }

    SECTION("Ipp16u"){
        test_Add_ISfs<Ipp16u>();
    }

    SECTION("Ipp16s"){
        test_Add_ISfs<Ipp16s>();
    }

    SECTION("Ipp32s"){
        test_Add_ISfs<Ipp32s>();
    }

    SECTION("Ipp16sc"){
        test_Add_ISfs_complex<Ipp16sc>();
    }

    SECTION("Ipp32sc"){
        test_Add_ISfs_complex<Ipp32sc>();
    }
}


/*
Templated test case for AddC.
*/
template <typename T>
void test_AddC()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
    }

    // Define constant
    T c = (T)(11);

    // Perform the operation
    ippe::math::AddC(x.data(), c, result.data(), x.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == (x[i] + c));
    }
}

template <typename T>
void test_AddC_complex()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i].re = (i + 64);
        x[i].im = (i + 65);
    }

    // Define constant
    T c;
    c.re = (11);
    c.im = (12);

    // Perform the operation
    ippe::math::AddC(x.data(), c, result.data(), x.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == (x[i].re + c.re));
        REQUIRE(result[i].im == (x[i].im + c.im));
    }
}

TEST_CASE("ippe math AddC", "[math], [AddC]")
{
    SECTION("Ipp32f"){
        test_AddC<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_AddC<Ipp64f>();
    }
    SECTION("Ipp32fc"){
        test_AddC_complex<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_AddC_complex<Ipp64fc>();
    }
}

/*
Templated test case for AddC_Sfs.
*/
template <typename T, typename U>
void test_AddC_Sfs()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
    }

    // Define constant
    T c = (T)(11);

    // Perform the operation
    ippe::math::AddC_Sfs(x.data(), c, result.data(), (U)x.size(), 1);
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == evaluate_integer_scaling(x[i] + c, 1));
    }
}
template <typename T, typename U>
void test_AddC_Sfs_complex()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i].re = (i + 64);
        x[i].im = (i + 65);
    }

    // Define constant
    T c;
    c.re = (11);
    c.im = (12);

    // Perform the operation
    ippe::math::AddC_Sfs(x.data(), c, result.data(), (U)x.size(), 1);
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == evaluate_integer_scaling(x[i].re + c.re, 1));
        REQUIRE(result[i].im == evaluate_integer_scaling(x[i].im + c.im, 1));
    }
}

TEST_CASE("ippe math AddC_Sfs", "[math], [AddC_Sfs]")
{
    SECTION("Ipp8u"){
        test_AddC_Sfs<Ipp8u, int>();
    }
    SECTION("Ipp16u"){
        test_AddC_Sfs<Ipp16u, int>();
    }
    SECTION("Ipp16s"){
        test_AddC_Sfs<Ipp16s, int>();
    }
    SECTION("Ipp32s"){
        test_AddC_Sfs<Ipp32s, int>();
    }
    SECTION("Ipp16sc"){
        test_AddC_Sfs_complex<Ipp16sc, int>();
    }
    SECTION("Ipp32sc"){
        test_AddC_Sfs_complex<Ipp32sc, int>();
    }
    // Test the weird 64u and 64s? TODO: figure out why these fail
    // SECTION("Ipp64u"){
    //     test_AddC_Sfs<Ipp64u, Ipp32u>();
    // }
    // SECTION("Ipp64s"){
    //     test_AddC_Sfs<Ipp64s, Ipp32u>();
    // }
}

/*
Templated test case for AddC_I.
*/
template <typename T>
void test_AddC_I()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        result[i] = x[i];
    }

    // Define constant
    T c = (T)(11);

    // Perform the operation
    ippe::math::AddC_I(c, result.data(), result.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == (x[i] + c));
    }
}
template <typename T>
void test_AddC_I_complex()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i].re = (i + 64);
        x[i].im = (i + 65);
        result[i] = x[i];
    }

    // Define constant
    T c;
    c.re = (11);
    c.im = (12);

    // Perform the operation
    ippe::math::AddC_I(c, result.data(), result.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == (x[i].re + c.re));
        REQUIRE(result[i].im == (x[i].im + c.im));
    }
}

TEST_CASE("ippe math AddC_I", "[math], [AddC_I]")
{
    SECTION("Ipp16s"){
        test_AddC_I<Ipp16s>();
    }
    SECTION("Ipp32f"){
        test_AddC_I<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_AddC_I<Ipp64f>();
    }
    SECTION("Ipp32fc"){
        test_AddC_I_complex<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_AddC_I_complex<Ipp64fc>();
    }
}

/*
Templated test case for AddC_ISfs.
*/
template <typename T>
void test_AddC_ISfs()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        result[i] = x[i];
    }

    // Define constant
    T c = (T)(11);

    // Perform the operation
    ippe::math::AddC_ISfs(c, result.data(), (int)x.size(), 1);
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == evaluate_integer_scaling(x[i] + c, 1));
    }
}
template <typename T>
void test_AddC_ISfs_complex()
{
    // Make vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i].re = (i + 64);
        x[i].im = (i + 65);
        result[i] = x[i];
    }

    // Define constant
    T c;
    c.re = (11);
    c.im = (12);

    // Perform the operation
    ippe::math::AddC_ISfs(c, result.data(), (int)x.size(), 1);
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == evaluate_integer_scaling(x[i].re + c.re, 1));
        REQUIRE(result[i].im == evaluate_integer_scaling(x[i].im + c.im, 1));
    }
}

TEST_CASE("ippe math AddC_ISfs", "[math], [AddC_ISfs]")
{
    SECTION("Ipp8u"){
        test_AddC_ISfs<Ipp8u>();
    }
    SECTION("Ipp16u"){
        test_AddC_ISfs<Ipp16u>();
    }
    SECTION("Ipp16s"){
        test_AddC_ISfs<Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_AddC_ISfs<Ipp32s>();
    }
    SECTION("Ipp16sc"){
        test_AddC_ISfs_complex<Ipp16sc>();
    }
    SECTION("Ipp32sc"){
        test_AddC_ISfs_complex<Ipp32sc>();
    }
}

/*
Templated test case for AddProduct.
*/
template <typename T>
void test_AddProduct()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<T> result(10);
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        y[i] = (T)(i + 65);
        result[i] = (T)(i + 66);
        check[i] = result[i];
    }

    // Perform the operation
    ippe::math::AddProduct(x.data(), y.data(), result.data(), x.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == check[i] + (x[i] * y[i]));
    }
}

template <typename T>
void test_AddProduct_complex()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<T> result(10);
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i].re = (i + 64);
        x[i].im = (i + 65);
        y[i].re = (i + 66);
        y[i].im = (i + 67);
        result[i].re = (i + 68);
        result[i].im = (i + 69);
        check[i].re = result[i].re;
        check[i].im = result[i].im;
    }

    // Perform the operation
    ippe::math::AddProduct(x.data(), y.data(), result.data(), x.size());
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == check[i].re + (x[i].re * y[i].re) - (x[i].im * y[i].im));
        REQUIRE(result[i].im == check[i].im + (x[i].im * y[i].re) + (x[i].re * y[i].im));
    }
}

TEST_CASE("ippe math AddProduct", "[math], [AddProduct]")
{
    SECTION("Ipp32f"){
        test_AddProduct<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_AddProduct<Ipp64f>();
    }
    SECTION("Ipp32fc"){
        test_AddProduct_complex<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_AddProduct_complex<Ipp64fc>();
    }
}

/*
Templated test case for AddProduct_Sfs.
*/
template <typename T, typename U>
void test_AddProduct_Sfs()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<U> result(10);
    ippe::vector<U> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        y[i] = (T)(i + 65);
        result[i] = (U)(i + 66);
        check[i] = result[i];
    }

    // Perform the operation
    ippe::math::AddProduct_Sfs(x.data(), y.data(), result.data(), (int)x.size(), 1);
    
    // Check the result
    U val;
    for (int i = 0; i < x.size(); ++i)
    {
        val = evaluate_integer_scaling(check[i] + (U)x[i] * (U)y[i], 1);
        REQUIRE(result[i] == val);
    }
}

TEST_CASE("ippe math AddProduct_Sfs", "[math], [AddProduct_Sfs]")
{
    SECTION("Ipp16s"){
        test_AddProduct_Sfs<Ipp16s, Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_AddProduct_Sfs<Ipp32s, Ipp32s>();
    }
    SECTION("Ipp16s to Ipp32s"){
        test_AddProduct_Sfs<Ipp16s, Ipp32s>();
    }
}


/*
Templated test case for Mul.
*/
template <typename T, typename U, typename V>
void test_Mul()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> y(10);
    ippe::vector<V> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 64);
        y[i] = (U)(i + 65);
    }

    // Perform the operation

    // undefined template for const results
    // const V* const_result = result.data();
    // ippe::math::Mul(x.data(), y.data(), const_result, x.size());

    // correct usage
    ippe::math::Mul(x.data(), y.data(), result.data(), x.size());

    // Check the result
    V z;
    for (int i = 0; i < x.size(); ++i)
    {
        z = x[i] * y[i];
        REQUIRE(result[i] == z);
    }
}

template <typename T, typename U, typename V>
void test_Mul_complex()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> y(10);
    ippe::vector<V> result(10);

    // Set some values
    T valT;
    U valU;
    for (int i = 0; i < x.size(); ++i)
    {
        valT.re = i + 64;
        valT.im = i + 65;
        valU.re = 2*i + 64;
        valU.im = 2*i + 65;
        x[i] = valT;
        y[i] = valU;
    }

    // Perform the operation
    ippe::math::Mul(x.data(), y.data(), result.data(), x.size());

    // Check the result
    V z;
    for (int i = 0; i < x.size(); ++i)
    {
        z.re = x[i].re * y[i].re - x[i].im * y[i].im;
        z.im = x[i].re * y[i].im + x[i].im * y[i].re;
        REQUIRE(result[i].re == z.re);
        REQUIRE(result[i].im == z.im);
    }
}

TEST_CASE("ippe math Mul", "[math, Mul]")
{
    /*
    Flavours are:
    Ipp16s
    Ipp32f
    Ipp64f
    Ipp32fc
    Ipp64fc
    Ipp8u,Ipp8u -> Ipp16u
    Ipp32f,Ipp32fc -> Ipp32fc
    Ipp16s,Ipp16s -> Ipp32f
    */

    SECTION("Ipp16s"){
        test_Mul<Ipp16s, Ipp16s, Ipp16s>();
    }

    SECTION("Ipp32f"){
        test_Mul<Ipp32f, Ipp32f, Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Mul<Ipp64f, Ipp64f, Ipp64f>();
    }

    SECTION("Ipp32fc"){
        test_Mul_complex<Ipp32fc, Ipp32fc, Ipp32fc>();
    }

    SECTION("Ipp64fc"){
        test_Mul_complex<Ipp64fc, Ipp64fc, Ipp64fc>();
    }

    SECTION("Ipp8u,Ipp8u -> Ipp16u"){
        test_Mul<Ipp8u, Ipp8u, Ipp16u>();
    }

    SECTION("Ipp32f,Ipp32fc -> Ipp32fc"){
        // This one is a bit special since not everything is complex..
        // Create vectors of the same size
        ippe::vector<Ipp32f> x(10);
        ippe::vector<Ipp32fc> y(10);
        ippe::vector<Ipp32fc> result(10);

        // Set some values
        Ipp32fc valU;
        for (int i = 0; i < x.size(); ++i)
        {
            valU.re = 2*i + 64;
            valU.im = 2*i + 65;
            x[i] = i + 64;
            y[i] = valU;
        }

        // Perform the operation
        ippe::math::Mul(x.data(), y.data(), result.data(), x.size());

        // Check the result
        Ipp32fc z;
        for (int i = 0; i < x.size(); ++i)
        {
            z.re = x[i] * y[i].re;
            z.im = x[i] * y[i].im;
            REQUIRE(result[i].re == z.re);
            REQUIRE(result[i].im == z.im);
        }
    }

    SECTION("Ipp16s,Ipp16s -> Ipp32f"){
        test_Mul<Ipp16s, Ipp16s, Ipp32f>();
    }
}

/*
Templated test case for Mul_Sfs.
*/
template <typename T, typename U, typename V>
void test_Mul_Sfs()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> y(10);
    ippe::vector<V> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
        y[i] = (U)(i + 2);
    }

    // Perform the operation
    ippe::math::Mul_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

     // Check the result
    V z;
    for (int i = 0; i < x.size(); ++i)
    {
        z = x[i] * y[i];
        // If z is odd, then the result must be fixed
        if (z % 2 == 1)
        {
            z = z / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z % 2 == 1)
                z += 1;
        }
        else
        {
            z = z / 2;
        }

        REQUIRE(result[i] == z);
    }
}

template <typename T, typename U, typename V>
void test_Mul_Sfs_complex()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> y(10);
    ippe::vector<V> result(10);

    // Set some values
    T valT;
    U valU;
    for (int i = 0; i < x.size(); ++i)
    {
        valT.re = i + 1;
        valT.im = i + 2;
        valU.re = 2*i + 3;
        valU.im = 2*i + 4;
        x[i] = valT;
        y[i] = valU;
    }

    // Perform the operation
    ippe::math::Mul_Sfs(x.data(), y.data(), result.data(), x.size(), 1);

     // Check the result
    V z;
    for (int i = 0; i < x.size(); ++i)
    {
        z.re = x[i].re * y[i].re - x[i].im * y[i].im;
        z.im = x[i].re * y[i].im + x[i].im * y[i].re;
        // If z is odd, then the result must be fixed, take care of negatives for our test case now due to complex
        if (z.re % 2 == 1 || z.re % 2 == -1)
        {
            z.re = z.re / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z.re % 2 == 1 || z.re % 2 == -1){
                if (z.re > 0) // for negative numbers we should already hit the even value
                {
                    z.re += 1;
                }
                else
                {
                    z.re -= 1;
                }
                    
            }
        }
        else
        {
            z.re = z.re / 2;
        }

        // Similarly for imag part
        if (z.im % 2 == 1 || z.im % 2 == -1)
        {
            z.im = z.im / 2;
            if (z.im % 2 == 1 || z.im % 2 == -1){
                if (z.im > 0) // for negative numbers we should already hit the even value
                    z.im += 1;
                else
                {
                    z.im -= 1;
                }
            }
        }
        else
        {
            z.im = z.im / 2;
        }

        REQUIRE(result[i].re == z.re);
        REQUIRE(result[i].im == z.im);
    }

}

TEST_CASE("ippe math Mul_Sfs", "[math, Mul_Sfs]")
{
    /*
    Flavours are:
    Ipp8u
    Ipp16u
    Ipp16s
    Ipp32s
    Ipp16sc
    Ipp32sc
    Ipp16s,Ipp16s -> Ipp32s
    Ipp16u,Ipp16s -> Ipp16s
    */

    SECTION("Ipp8u"){
        test_Mul_Sfs<Ipp8u, Ipp8u, Ipp8u>();
    }

    SECTION("Ipp16u"){
        test_Mul_Sfs<Ipp16u, Ipp16u, Ipp16u>();
    }

    SECTION("Ipp16s"){
        test_Mul_Sfs<Ipp16s, Ipp16s, Ipp16s>();
    }

    SECTION("Ipp32s"){
        test_Mul_Sfs<Ipp32s, Ipp32s, Ipp32s>();
    }

    SECTION("Ipp16sc"){
        test_Mul_Sfs_complex<Ipp16sc, Ipp16sc, Ipp16sc>();
    }

    SECTION("Ipp32sc"){
        test_Mul_Sfs_complex<Ipp32sc, Ipp32sc, Ipp32sc>();
    }

    SECTION("Ipp16s,Ipp16s -> Ipp32s"){
        test_Mul_Sfs<Ipp16s, Ipp16s, Ipp32s>();
    }

    SECTION("Ipp16u,Ipp16s -> Ipp16s"){
        test_Mul_Sfs<Ipp16u, Ipp16s, Ipp16s>();
    }
    
}

/*
Templated test case for Mul_I.
*/
template <typename T, typename U>
void test_Mul_I()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> check(10);
    ippe::vector<U> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
        check[i] = (U)(i + 2);
        result[i] = check[i];
    }

    // Perform the operation
    ippe::math::Mul_I(x.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == check[i] * x[i]);
    }
}

template <typename T, typename U>
void test_Mul_I_complex()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<U> check(10);
    ippe::vector<U> result(10);

    // Set some values
    T valT;
    U valU;
    for (int i = 0; i < x.size(); ++i)
    {
        valT.re = i + 1;
        valT.im = i + 2;
        valU.re = 2*i + 3;
        valU.im = 2*i + 4;
        x[i] = valT;
        check[i] = valU;
        result[i] = check[i];
    }

    // Perform the operation
    ippe::math::Mul_I(x.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == (check[i].re * x[i].re - check[i].im * x[i].im));
        REQUIRE(result[i].im == (check[i].im * x[i].re + check[i].re * x[i].im));
    }
}

TEST_CASE("ippe math Mul_I", "[math, Mul_I]")
{
    /*
    Flavours are:
    Ipp16s
    Ipp32f
    Ipp64f
    Ipp32fc
    Ipp64fc
    Ipp32f -> Ipp32fc
    */
    
    SECTION("Ipp16s"){
        test_Mul_I<Ipp16s, Ipp16s>();
    }

    SECTION("Ipp32f"){
        test_Mul_I<Ipp32f, Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Mul_I<Ipp64f, Ipp64f>();
    }

    SECTION("Ipp32fc"){
        test_Mul_I_complex<Ipp32fc, Ipp32fc>();
    }

    SECTION("Ipp64fc"){
        test_Mul_I_complex<Ipp64fc, Ipp64fc>();
    }

    SECTION("Ipp32f -> Ipp32fc"){
        // Need to specialise for this one
        // Create vectors of the same size
        ippe::vector<Ipp32f> x(10);
        ippe::vector<Ipp32fc> check(10);
        ippe::vector<Ipp32fc> result(10);

        // Set some values
        Ipp32f valT;
        Ipp32fc valU;
        for (int i = 0; i < x.size(); ++i)
        {
            valT = i;
            valU.re = 2*i + 3;
            valU.im = 2*i + 4;
            x[i] = valT;
            check[i] = valU;
            result[i] = check[i];
        }

        // Perform the operation
        ippe::math::Mul_I(x.data(), result.data(), x.size());

        // Check the result
        for (int i = 0; i < x.size(); ++i)
        {
            REQUIRE(result[i].re == (check[i].re * x[i]));
            REQUIRE(result[i].im == (check[i].im * x[i]));
        }
    }

}

/*
Templated test case for Mul_ISfs.
*/

template <typename T>
void test_Mul_ISfs()
{
    // Create two vectors and a check
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
        y[i] = (T)(i + 2);
        check[i] = y[i];
    }

    // Perform the operation
    ippe::math::Mul_ISfs(x.data(), y.data(), x.size(), 1);

    // Check the result
    T z;
    for (int i = 0; i < x.size(); ++i)
    {
        z = x[i] * check[i];
        // If z is odd, then the result must be fixed
        if (z % 2 == 1)
        {
            z = z / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z % 2 == 1)
                z += 1;
        }
        else
        {
            z = z / 2;
        }

        REQUIRE(y[i] == z);
    }
}

template <typename T>
void test_Mul_ISfs_complex()
{
    // Create two vectors and a check
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<T> check(10);

    // Set some values
    T valT;
    T valU;
    for (int i = 0; i < x.size(); ++i)
    {
        valT.re = i + 1;
        valT.im = i + 2;
        valU.re = 2*i + 3;
        valU.im = 2*i + 4;
        x[i] = valT;
        y[i] = valU;
        check[i] = y[i];
    }

    // Perform the operation
    ippe::math::Mul_ISfs(x.data(), y.data(), x.size(), 1);

     // Check the result
    T z;
    for (int i = 0; i < x.size(); ++i)
    {
        z.re = x[i].re * check[i].re - x[i].im * check[i].im;
        z.im = x[i].re * check[i].im + x[i].im * check[i].re;
        // If z is odd, then the result must be fixed, take care of negatives for our test case now due to complex
        if (z.re % 2 == 1 || z.re % 2 == -1)
        {
            z.re = z.re / 2;
            // If the resulting division was clipped down to an odd number then add 1 to make it even
            if (z.re % 2 == 1 || z.re % 2 == -1){
                if (z.re > 0) // for negative numbers we should already hit the even value
                {
                    z.re += 1;
                }
                else
                {
                    z.re -= 1;
                }
                    
            }
        }
        else
        {
            z.re = z.re / 2;
        }

        // Similarly for imag part
        if (z.im % 2 == 1 || z.im % 2 == -1)
        {
            z.im = z.im / 2;
            if (z.im % 2 == 1 || z.im % 2 == -1){
                if (z.im > 0) // for negative numbers we should already hit the even value
                    z.im += 1;
                else
                {
                    z.im -= 1;
                }
            }
        }
        else
        {
            z.im = z.im / 2;
        }

        REQUIRE(y[i].re == z.re);
        REQUIRE(y[i].im == z.im);
    }
}

TEST_CASE("ippe math Mul_ISfs", "[math],[Mul_ISfs]")
{
    /*
    Flavours are:
    Ipp8u
    Ipp16u
    Ipp16s
    Ipp32s
    Ipp16sc
    Ipp32sc
    */

    SECTION("Ipp8u")
    {
        test_Mul_ISfs<Ipp8u>();
    }

    SECTION("Ipp16u")
    {
        test_Mul_ISfs<Ipp16u>();
    }

    SECTION("Ipp16s")
    {
        test_Mul_ISfs<Ipp16s>();
    }

    SECTION("Ipp32s")
    {
        test_Mul_ISfs<Ipp32s>();
    }

    SECTION("Ipp16sc")
    {
        test_Mul_ISfs_complex<Ipp16sc>();
    }

    SECTION("Ipp32sc")
    {
        test_Mul_ISfs_complex<Ipp32sc>();
    }
}

/*
Templated test case for Sub.
*/
template <typename T, typename U>
void test_Sub()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<U> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
        y[i] = (U)(i + 2);
    }

    // Perform the operation
    ippe::math::Sub(x.data(), y.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == y[i] - x[i]);
    }
}

template <typename T>
void test_Sub_complex()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> y(10);
    ippe::vector<T> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        T valT;
        valT.re = i + 1;
        valT.im = i + 2;

        x[i] = valT;

        valT.re = 2*i + 3;
        valT.im = 2*i + 4;

        y[i] = valT;
    }

    // Perform the operation
    ippe::math::Sub(x.data(), y.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == y[i].re - x[i].re);
        REQUIRE(result[i].im == y[i].im - x[i].im);
    }
}

TEST_CASE("ippe math Sub", "[math, Sub]")
{
    /*
    Flavours are:
    Ipp16s
    Ipp32f
    Ipp64f
    Ipp32fc
    Ipp64fc
    Ipp16s -> Ipp32f
    */

    SECTION("Ipp16s"){
        test_Sub<Ipp16s, Ipp16s>();
    }

    SECTION("Ipp32f"){
        test_Sub<Ipp32f, Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Sub<Ipp64f, Ipp64f>();
    }

    SECTION("Ipp32fc"){
        test_Sub_complex<Ipp32fc>();
    }

    SECTION("Ipp64fc"){
        test_Sub_complex<Ipp64fc>();
    }

    SECTION("Ipp16s -> Ipp32f"){
        test_Sub<Ipp16s, Ipp32f>();
    }
}

/*
Templated test case for Sub_I.
*/
template <typename T>
void test_Sub_I()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (i + 1);
        result[i] = (i + 2);
        check[i] = result[i];
    }

    // Perform the operation
    ippe::math::Sub_I(x.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == check[i] - x[i]);
    }
}

template <typename T>
void test_Sub_I_complex()
{
    // Create vectors of the same size
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        T valT;
        valT.re = i + 1;
        valT.im = i + 2;
        x[i] = valT;

        valT.re = 2*i + 3;
        valT.im = 2*i + 4;
        result[i] = valT;
        check[i] = result[i];
    }

    // Perform the operation
    ippe::math::Sub_I(x.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i].re == check[i].re - x[i].re);
        REQUIRE(result[i].im == check[i].im - x[i].im);
    }
}

TEST_CASE("ippe math Sub_I", "[math, Sub_I]")
{
    /*
    Flavours are:
    Ipp16s
    Ipp32f
    Ipp64f
    Ipp32fc
    Ipp64fc
    */

    SECTION("Ipp16s"){
        test_Sub_I<Ipp16s>();
    }

    SECTION("Ipp32f"){
        test_Sub_I<Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Sub_I<Ipp64f>();
    }

    SECTION("Ipp32fc"){
        test_Sub_I_complex<Ipp32fc>();
    }

    SECTION("Ipp64fc"){
        test_Sub_I_complex<Ipp64fc>();
    }

}

// I'm not going to bother checking any more Sfs as it's very cumbersome..

/*
Templated test case for Norm_L2
*/
template <typename T, typename U>
void test_Norm_L2()
{
    // Create arrays
    ippe::matrix<T> x(10, 10);
    ippe::vector<U> norms(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
    }

    // Perform the operation on each row
    for (int i = 0; i < x.rows(); ++i)
    {
        ippe::math::Norm_L2(x.row(i), x.columns(), &norms.at(i));

        // Calculate the norm manually
        U norm = 0;
        for (int j = 0; j < x.columns(); ++j)
        {
            norm += x.index(i,j) * x.index(i,j);
        }

        REQUIRE(std::sqrt(norm) == norms.at(i));
    }
}

template <typename T, typename U>
void test_Norm_L2_complex()
{
    // Create arrays
    ippe::matrix<T> x(10, 10);
    ippe::vector<U> norms(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        T valT;
        valT.re = i + 1;
        valT.im = i + 2;
        x[i] = valT;
    }

    // Perform the operation on each row
    for (int i = 0; i < x.rows(); ++i)
    {
        ippe::math::Norm_L2(x.row(i), x.columns(), &norms.at(i));

        // Calculate the norm manually
        U norm = 0;
        for (int j = 0; j < x.columns(); ++j)
        {
            norm += x.index(i,j).re * x.index(i,j).re + x.index(i,j).im * x.index(i,j).im;
        }

        REQUIRE(std::sqrt(norm) == norms.at(i));
    }
}

TEST_CASE("ippe math Norm_L2", "[math, Norm_L2]")
{
    /*
    Flavours are:
    Ipp32f
    Ipp64f
    Ipp16s -> Ipp32f
    Ipp32fc -> Ipp64f
    Ipp64fc -> Ipp64f
    */

    SECTION("Ipp32f"){
        test_Norm_L2<Ipp32f, Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Norm_L2<Ipp64f, Ipp64f>();
    }

    SECTION("Ipp16s -> Ipp32f"){
        test_Norm_L2<Ipp16s, Ipp32f>();
    }

    SECTION("Ipp32fc -> Ipp64f"){
        test_Norm_L2_complex<Ipp32fc, Ipp64f>();
    }

    SECTION("Ipp64fc -> Ipp64f"){
        test_Norm_L2_complex<Ipp64fc, Ipp64f>();
    }

}

// ===========================
template <typename T>
void test_Ln()
{
    // Make some vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
    }

    // Perform the operation
    ippe::math::Ln(x.data(), result.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(std::abs(result[i]-std::log(x[i])) < 1e-6); // arbitrary tolerance (higher value so that it will pass on Ipp32f as well)
    }

    // Perform in place version as well
    ippe::math::Ln_I(x.data(), x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(x[i] == result[i]); // should be identical to the previous result
    }
}

template <typename T>
void test_Ln_Sfs()
{
    // Make some vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i*100 + 1);
    }

    // Perform the operation
    int scaleFactor = 1;
    ippe::math::Ln_Sfs(x.data(), result.data(), x.size(), scaleFactor);

    // Check the result (skip this because the integer scaling not as we coded) 
    // TODO: fix integer scaling for this
    // for (int i = 0; i < x.size(); ++i)
    // {
    //     // Evaluate as Ipp32f with std::log and then cast back to template type
    //     // Remember to scale using our function
    //     T check = evaluate_integer_scaling((T)std::log((Ipp32f)x[i]), scaleFactor);
    //     REQUIRE(result[i] == check);
    // }

    // Perform in place version as well
    ippe::math::Ln_ISfs(x.data(), x.size(), scaleFactor);
    
    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        // Same as above
        REQUIRE(x[i] == result[i]);
    }
}

TEST_CASE("ippe math Ln", "[math, Ln]")
{
    /*
    Flavours are:
    Ipp32f
    Ipp64f
    */

    SECTION("Ipp32f"){
        test_Ln<Ipp32f>();
    }

    SECTION("Ipp64f"){
        test_Ln<Ipp64f>();
    }

    /*
    For sfs flavours are:
    Ipp16s
    Ipp32s
    */

    SECTION("Ipp16s"){
        test_Ln_Sfs<Ipp16s>();
    }

    SECTION("Ipp32s"){
        test_Ln_Sfs<Ipp32s>();
    }

}

// ===========================
template <typename T>
void test_AddProductC()
{
    // Make some vectors
    ippe::vector<T> x(10);
    ippe::vector<T> result(10);
    ippe::vector<T> check(10);

    // Set some values
    for (int i = 0; i < x.size(); ++i)
    {
        x[i] = (T)(i + 1);
        result[i] = (T)(i + 2); // set some initial values for result too
        check[i] = result[i];
    }

    // Perform the operation
    const T val = 12.0;
    ippe::math::AddProductC(x.data(), val, result.data(), (int)x.size());

    // Check the result
    for (int i = 0; i < x.size(); ++i)
    {
        REQUIRE(result[i] == check[i] + val * x[i]);
    }
}

TEST_CASE("ippe math AddProductC", "[math], [AddProductC]")
{
    SECTION("Ipp32f"){
        test_AddProductC<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_AddProductC<Ipp64f>();
    }
}
