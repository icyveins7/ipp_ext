#include <iostream>
#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

#include "test_vectors_encapsulation.h"

TEST_CASE("ipps vector instantiation", "[vector],[instantiation]")
{
    SECTION("instantiate 8u"){
        ipps::vector<Ipp8u> v8u;
        REQUIRE(v8u.size() == 0);
        REQUIRE(v8u.capacity() == 0);
        REQUIRE(v8u.data() == nullptr);

        ipps::vector<Ipp8u> v8u_size(2);
        REQUIRE(v8u_size.size() == 2);
        REQUIRE(v8u_size.capacity() == 2);

        ipps::vector<Ipp8u> v8u_size_zeroed(2, 0);
        REQUIRE(v8u_size_zeroed.size() == 2);
        REQUIRE(v8u_size_zeroed.capacity() == 2);
        Ipp8u z = 0;
        REQUIRE(v8u_size_zeroed.at(0) == z);
        REQUIRE(v8u_size_zeroed.at(1) == z);

        Ipp8u v = 10;
        ipps::vector<Ipp8u> v8u_size_valued(2, v);
        REQUIRE(v8u_size_valued.size() == 2);
        REQUIRE(v8u_size_valued.capacity() == 2);
        REQUIRE(v8u_size_valued.at(0) == v);
        REQUIRE(v8u_size_valued.at(1) == v);
    }

    SECTION("instantiate 16u"){
        ipps::vector<Ipp16u> v16u;
        REQUIRE(v16u.size() == 0);
        REQUIRE(v16u.capacity() == 0);

        ipps::vector<Ipp16u> v16u_size(2);
        REQUIRE(v16u_size.size() == 2);
        REQUIRE(v16u_size.capacity() == 2);
        
        ipps::vector<Ipp16u> v16u_size_zeroed(2, 0);
        REQUIRE(v16u_size_zeroed.size() == 2);
        REQUIRE(v16u_size_zeroed.capacity() == 2);
        Ipp16u z = 0;
        REQUIRE(v16u_size_zeroed.at(0) == z);
        REQUIRE(v16u_size_zeroed.at(1) == z);

        Ipp16u v = 10;
        ipps::vector<Ipp16u> v16u_size_valued(2, v);
        REQUIRE(v16u_size_valued.size() == 2);
        REQUIRE(v16u_size_valued.capacity() == 2);
        REQUIRE(v16u_size_valued.at(0) == v);
        REQUIRE(v16u_size_valued.at(1) == v);
    }

    SECTION("instantiate 32u"){
        ipps::vector<Ipp32u> v32u;
        REQUIRE(v32u.size() == 0);
        REQUIRE(v32u.capacity() == 0);

        ipps::vector<Ipp32u> v32u_size(2);
        REQUIRE(v32u_size.size() == 2);
        REQUIRE(v32u_size.capacity() == 2);

        ipps::vector<Ipp32u> v32u_size_zeroed(2, 0);
        REQUIRE(v32u_size_zeroed.size() == 2);
        REQUIRE(v32u_size_zeroed.capacity() == 2);
        Ipp32u z = 0;
        REQUIRE(v32u_size_zeroed.at(0) == z);
        REQUIRE(v32u_size_zeroed.at(1) == z);

        Ipp32u v = 10;
        ipps::vector<Ipp32u> v32u_size_valued(2, v);
        REQUIRE(v32u_size_valued.size() == 2);
        REQUIRE(v32u_size_valued.capacity() == 2);
        REQUIRE(v32u_size_valued.at(0) == v);
        REQUIRE(v32u_size_valued.at(1) == v);
    }

    SECTION ("instantiate 64u"){
        ipps::vector<Ipp64u> v64u;
        REQUIRE(v64u.size() == 0);
        REQUIRE(v64u.capacity() == 0);

        ipps::vector<Ipp64u> v64u_size(2);
        REQUIRE(v64u_size.size() == 2);
        REQUIRE(v64u_size.capacity() == 2);

        ipps::vector<Ipp64u> v64u_size_zeroed(2, 0);
        REQUIRE(v64u_size_zeroed.size() == 2);
        REQUIRE(v64u_size_zeroed.capacity() == 2);
        Ipp64u z = 0;
        REQUIRE(v64u_size_zeroed.at(0) == z);
        REQUIRE(v64u_size_zeroed.at(1) == z);

        Ipp64u v = 10;
        ipps::vector<Ipp64u> v64u_size_valued(2, v);
        REQUIRE(v64u_size_valued.size() == 2);
        REQUIRE(v64u_size_valued.capacity() == 2);
        REQUIRE(v64u_size_valued.at(0) == v);
        REQUIRE(v64u_size_valued.at(1) == v);
    }

    SECTION ("instantiate 8s") {
        ipps::vector<Ipp8s> v8s;
        REQUIRE(v8s.size() == 0);
        REQUIRE(v8s.capacity() == 0);

        ipps::vector<Ipp8s> v8s_size(2);
        REQUIRE(v8s_size.size() == 2);
        REQUIRE(v8s_size.capacity() == 2);

        ipps::vector<Ipp8s> v8s_size_zeroed(2, 0);
        REQUIRE(v8s_size_zeroed.size() == 2);
        REQUIRE(v8s_size_zeroed.capacity() == 2);
        Ipp8s z = 0;
        REQUIRE(v8s_size_zeroed.at(0) == z);
        REQUIRE(v8s_size_zeroed.at(1) == z);

        Ipp8s v = 10;
        ipps::vector<Ipp8s> v8s_size_valued(2, v);
        REQUIRE(v8s_size_valued.size() == 2);
        REQUIRE(v8s_size_valued.capacity() == 2);
        REQUIRE(v8s_size_valued.at(0) == v);
        REQUIRE(v8s_size_valued.at(1) == v);
    }

    SECTION ("instantiate 16s") {
        ipps::vector<Ipp16s> v16s;
        REQUIRE(v16s.size() == 0);
        REQUIRE(v16s.capacity() == 0);

        ipps::vector<Ipp16s> v16s_size(2);
        REQUIRE(v16s_size.size() == 2);
        REQUIRE(v16s_size.capacity() == 2);
        
        ipps::vector<Ipp16s> v16s_size_zeroed(2, 0);
        REQUIRE(v16s_size_zeroed.size() == 2);
        REQUIRE(v16s_size_zeroed.capacity() == 2);
        Ipp16s z = 0;
        REQUIRE(v16s_size_zeroed.at(0) == z);
        REQUIRE(v16s_size_zeroed.at(1) == z);

        Ipp16s v = 10;
        ipps::vector<Ipp16s> v16s_size_valued(2, v);
        REQUIRE(v16s_size_valued.size() == 2);
        REQUIRE(v16s_size_valued.capacity() == 2);
        REQUIRE(v16s_size_valued.at(0) == v);
        REQUIRE(v16s_size_valued.at(1) == v);

    }

    SECTION ("instantiate 32s") {
        ipps::vector<Ipp32s> v32s;
        REQUIRE(v32s.size() == 0);
        REQUIRE(v32s.capacity() == 0);

        ipps::vector<Ipp32s> v32s_size(2);
        REQUIRE(v32s_size.size() == 2);
        REQUIRE(v32s_size.capacity() == 2);
        
        ipps::vector<Ipp32s> v32s_size_zeroed(2, 0);
        REQUIRE(v32s_size_zeroed.size() == 2);
        REQUIRE(v32s_size_zeroed.capacity() == 2);
        Ipp32s z = 0;
        REQUIRE(v32s_size_zeroed.at(0) == z);
        REQUIRE(v32s_size_zeroed.at(1) == z);

        Ipp32s v = 10;
        ipps::vector<Ipp32s> v32s_size_valued(2, v);
        REQUIRE(v32s_size_valued.size() == 2);
        REQUIRE(v32s_size_valued.capacity() == 2);
        REQUIRE(v32s_size_valued.at(0) == v);
        REQUIRE(v32s_size_valued.at(1) == v);
    }

    SECTION ("instantiate 64s"){
        ipps::vector<Ipp64s> v64s;
        REQUIRE(v64s.size() == 0);
        REQUIRE(v64s.capacity() == 0);

        ipps::vector<Ipp64s> v64s_size(2);
        REQUIRE(v64s_size.size() == 2);
        REQUIRE(v64s_size.capacity() == 2);
        
        ipps::vector<Ipp64s> v64s_size_zeroed(2, 0);
        REQUIRE(v64s_size_zeroed.size() == 2);
        REQUIRE(v64s_size_zeroed.capacity() == 2);
        Ipp64s z = 0;
        REQUIRE(v64s_size_zeroed.at(0) == z);
        REQUIRE(v64s_size_zeroed.at(1) == z);

        Ipp64s v = 10;
        ipps::vector<Ipp64s> v64s_size_valued(2, v);
        REQUIRE(v64s_size_valued.size() == 2);
        REQUIRE(v64s_size_valued.capacity() == 2);
        REQUIRE(v64s_size_valued.at(0) == v);
        REQUIRE(v64s_size_valued.at(1) == v);

    }

    SECTION ("instantiate 32f") {
        ipps::vector<Ipp32f> v32f;
        REQUIRE(v32f.size() == 0);
        REQUIRE(v32f.capacity() == 0);

        ipps::vector<Ipp32f> v32f_size(2);
        REQUIRE(v32f_size.size() == 2);
        REQUIRE(v32f_size.capacity() == 2);
        
        ipps::vector<Ipp32f> v32f_size_zeroed(2, 0);
        REQUIRE(v32f_size_zeroed.size() == 2);
        REQUIRE(v32f_size_zeroed.capacity() == 2);
        Ipp32f z = 0;
        REQUIRE(v32f_size_zeroed.at(0) == z);
        REQUIRE(v32f_size_zeroed.at(1) == z);

        Ipp32f v = 10.0;
        ipps::vector<Ipp32f> v32f_size_valued(2, v);
        REQUIRE(v32f_size_valued.size() == 2);
        REQUIRE(v32f_size_valued.capacity() == 2);
        REQUIRE(v32f_size_valued.at(0) == v);
        REQUIRE(v32f_size_valued.at(1) == v);

    }

    SECTION ("instantiate 64f"){
        ipps::vector<Ipp64f> v64f;
        REQUIRE(v64f.size() == 0);
        REQUIRE(v64f.capacity() == 0);

        ipps::vector<Ipp64f> v64f_size(2);
        REQUIRE(v64f_size.size() == 2);
        REQUIRE(v64f_size.capacity() == 2);
        
        ipps::vector<Ipp64f> v64f_size_zeroed(2, 0);
        REQUIRE(v64f_size_zeroed.size() == 2);
        REQUIRE(v64f_size_zeroed.capacity() == 2);
        Ipp64f z = 0;
        REQUIRE(v64f_size_zeroed.at(0) == z);
        REQUIRE(v64f_size_zeroed.at(1) == z);

        Ipp64f v = 10.0;
        ipps::vector<Ipp64f> v64f_size_valued(2, v);
        REQUIRE(v64f_size_valued.size() == 2);
        REQUIRE(v64f_size_valued.capacity() == 2);
        REQUIRE(v64f_size_valued.at(0) == v);
        REQUIRE(v64f_size_valued.at(1) == v);
    }

    SECTION ("instantiate 8sc"){
        ipps::vector<Ipp8sc> v8sc;
        REQUIRE(v8sc.size() == 0);
        REQUIRE(v8sc.capacity() == 0);

        ipps::vector<Ipp8sc> v8sc_size(2);
        REQUIRE(v8sc_size.size() == 2);
        REQUIRE(v8sc_size.capacity() == 2);
        
        Ipp8sc z = {0,0};
        ipps::vector<Ipp8sc> v8sc_size_zeroed(2, z);
        REQUIRE(v8sc_size_zeroed.size() == 2);
        REQUIRE(v8sc_size_zeroed.capacity() == 2);
        REQUIRE((v8sc_size_zeroed.at(0).re == z.re && v8sc_size_zeroed.at(0).im == z.im));
        REQUIRE((v8sc_size_zeroed.at(1).re == z.re && v8sc_size_zeroed.at(1).im == z.im));

        Ipp8sc v = {-10,-10};
        ipps::vector<Ipp8sc> v8sc_size_valued(2, v);
        REQUIRE(v8sc_size_valued.size() == 2);
        REQUIRE(v8sc_size_valued.capacity() == 2);
        REQUIRE((v8sc_size_valued.at(0).re == v.re && v8sc_size_valued.at(0).im == v.im));
        REQUIRE((v8sc_size_valued.at(1).re == v.re && v8sc_size_valued.at(1).im == v.im));
    }

    SECTION ("instantiate 16sc"){
        ipps::vector<Ipp16sc> v16sc;
        REQUIRE(v16sc.size() == 0);
        REQUIRE(v16sc.capacity() == 0);

        ipps::vector<Ipp16sc> v16sc_size(2);
        REQUIRE(v16sc_size.size() == 2);
        REQUIRE(v16sc_size.capacity() == 2);

        Ipp16sc z = {0,0};
        ipps::vector<Ipp16sc> v16sc_size_zeroed(2, z);
        REQUIRE(v16sc_size_zeroed.size() == 2);
        REQUIRE(v16sc_size_zeroed.capacity() == 2);
        REQUIRE((v16sc_size_zeroed.at(0).re == z.re && v16sc_size_zeroed.at(0).im == z.im));
        REQUIRE((v16sc_size_zeroed.at(1).re == z.re && v16sc_size_zeroed.at(1).im == z.im));

        Ipp16sc v = {10,10};
        ipps::vector<Ipp16sc> v16sc_size_valued(2, v);
        REQUIRE(v16sc_size_valued.size() == 2);
        REQUIRE(v16sc_size_valued.capacity() == 2);
        REQUIRE((v16sc_size_valued.at(0).re == v.re && v16sc_size_valued.at(0).im == v.im));
        REQUIRE((v16sc_size_valued.at(1).re == v.re && v16sc_size_valued.at(1).im == v.im));
    }

    SECTION ("instantiate 32sc"){
        ipps::vector<Ipp32sc> v32sc;
        REQUIRE(v32sc.size() == 0);
        REQUIRE(v32sc.capacity() == 0);

        ipps::vector<Ipp32sc> v32sc_size(2);
        REQUIRE(v32sc_size.size() == 2);
        REQUIRE(v32sc_size.capacity() == 2);
        
        Ipp32sc z = {0,0};
        ipps::vector<Ipp32sc> v32sc_size_zeroed(2, z);
        REQUIRE(v32sc_size_zeroed.size() == 2);
        REQUIRE(v32sc_size_zeroed.capacity() == 2);
        REQUIRE((v32sc_size_zeroed.at(0).re == z.re && v32sc_size_zeroed.at(0).im == z.im));
        REQUIRE((v32sc_size_zeroed.at(1).re == z.re && v32sc_size_zeroed.at(1).im == z.im));

        Ipp32sc v = {10,10};
        ipps::vector<Ipp32sc> v32sc_size_valued(2, v);
        REQUIRE(v32sc_size_valued.size() == 2);
        REQUIRE(v32sc_size_valued.capacity() == 2);
        REQUIRE((v32sc_size_valued.at(0).re == v.re && v32sc_size_valued.at(0).im == v.im));
        REQUIRE((v32sc_size_valued.at(1).re == v.re && v32sc_size_valued.at(1).im == v.im));

    }

    SECTION ("instantiate 64sc"){
        ipps::vector<Ipp64sc> v64sc;
        REQUIRE(v64sc.size() == 0);
        REQUIRE(v64sc.capacity() == 0);

        ipps::vector<Ipp64sc> v64sc_size(2);
        REQUIRE(v64sc_size.size() == 2);
        REQUIRE(v64sc_size.capacity() == 2);
        
        Ipp64sc z = {0,0};
        ipps::vector<Ipp64sc> v64sc_size_zeroed(2, z);
        REQUIRE(v64sc_size_zeroed.size() == 2);
        REQUIRE(v64sc_size_zeroed.capacity() == 2);
        REQUIRE((v64sc_size_zeroed.at(0).re == z.re && v64sc_size_zeroed.at(0).im == z.im));
        REQUIRE((v64sc_size_zeroed.at(1).re == z.re && v64sc_size_zeroed.at(1).im == z.im));

        Ipp64sc v = {10,10};
        ipps::vector<Ipp64sc> v64sc_size_valued(2, v);
        REQUIRE(v64sc_size_valued.size() == 2);
        REQUIRE(v64sc_size_valued.capacity() == 2);
        REQUIRE((v64sc_size_valued.at(0).re == v.re && v64sc_size_valued.at(0).im == v.im));
        REQUIRE((v64sc_size_valued.at(1).re == v.re && v64sc_size_valued.at(1).im == v.im));
    }

    SECTION ("instantiate 32fc") {
        ipps::vector<Ipp32fc> v32fc;
        REQUIRE(v32fc.size() == 0);
        REQUIRE(v32fc.capacity() == 0);

        ipps::vector<Ipp32fc> v32fc_size(2);
        REQUIRE(v32fc_size.size() == 2);
        REQUIRE(v32fc_size.capacity() == 2);

        Ipp32fc z = {0,0};
        ipps::vector<Ipp32fc> v32fc_size_zeroed(2, z);
        REQUIRE(v32fc_size_zeroed.size() == 2);
        REQUIRE(v32fc_size_zeroed.capacity() == 2);
        REQUIRE((v32fc_size_zeroed.at(0).re == z.re && v32fc_size_zeroed.at(0).im == z.im));
        REQUIRE((v32fc_size_zeroed.at(1).re == z.re && v32fc_size_zeroed.at(1).im == z.im));

        Ipp32fc v = {10,10};
        ipps::vector<Ipp32fc> v32fc_size_valued(2, v);
        REQUIRE(v32fc_size_valued.size() == 2);
        REQUIRE(v32fc_size_valued.capacity() == 2);
        REQUIRE((v32fc_size_valued.at(0).re == v.re && v32fc_size_valued.at(0).im == v.im));
        REQUIRE((v32fc_size_valued.at(1).re == v.re && v32fc_size_valued.at(1).im == v.im));
    }

    SECTION ("instantiate 64fc"){
        ipps::vector<Ipp64fc> v64fc;
        REQUIRE(v64fc.size() == 0);
        REQUIRE(v64fc.capacity() == 0);

        ipps::vector<Ipp64fc> v64fc_size(2);
        REQUIRE(v64fc_size.size() == 2);
        REQUIRE(v64fc_size.capacity() == 2);

        Ipp64fc z = {0,0};
        ipps::vector<Ipp64fc> v64fc_size_zeroed(2, z);
        REQUIRE(v64fc_size_zeroed.size() == 2);
        REQUIRE(v64fc_size_zeroed.capacity() == 2);
        REQUIRE((v64fc_size_zeroed.at(0).re == z.re && v64fc_size_zeroed.at(0).im == z.im));
        REQUIRE((v64fc_size_zeroed.at(1).re == z.re && v64fc_size_zeroed.at(1).im == z.im));

        Ipp64fc v = {10,10};
        ipps::vector<Ipp64fc> v64fc_size_valued(2, v);
        REQUIRE(v64fc_size_valued.size() == 2);
        REQUIRE(v64fc_size_valued.capacity() == 2);
        REQUIRE((v64fc_size_valued.at(0).re == v.re && v64fc_size_valued.at(0).im == v.im));
        REQUIRE((v64fc_size_valued.at(1).re == v.re && v64fc_size_valued.at(1).im == v.im));
    }

}

TEST_CASE("ipps vector capacity and resizes", "[vector],[resize]"){
    ipps::vector<Ipp64fc> data;

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

    SECTION("resize with value"){
        Ipp64fc a = {0, 0};
        Ipp64fc b = {1, 1};
        data.resize(1, a);
        data.resize(2, b);

        REQUIRE(data.size() == 2);
        REQUIRE((data.at(0).re == a.re && data.at(0).im == a.im));
        REQUIRE((data.at(1).re == b.re && data.at(1).im == b.im));
    }
}

TEST_CASE("ipps vector writes", "[vector],[write]"){

    SECTION("pushback and access from empty constructor"){
        ipps::vector<Ipp64fc> data;
        Ipp64fc a = {0, 0};
        data.push_back(a);
        REQUIRE(data.size() == 1);
        REQUIRE((data.at(0).re == a.re && data.at(0).im == a.im));
    }    

    SECTION("pushback and access from initial finite size"){
        ipps::vector<Ipp64fc> data(128);
        Ipp64fc val = {1.0, 0.0};
        data.push_back(val);
        REQUIRE(data.size() == 129);
        REQUIRE(data.back().re == val.re);
        REQUIRE(data.back().im == val.im);
        REQUIRE(data.at(128).re == val.re);
        REQUIRE(data.at(128).im == val.im);
    }
}

// NOTE: double and float automatically alias to Ipp64f and Ipp32f, so this test
// actually never throws. I'm leaving this here to remind myself/others in the future

// TEST_CASE("ipps vector throws on non-IPP types", "[vector],[exceptions]"){
//     SECTION("double"){
//         REQUIRE_THROWS_AS(
//             ipps::vector<double>(128),
//             std::domain_error);
//     }
//
//     SECTION("float"){
//         REQUIRE_THROWS_AS(
//             ipps::vector<float>(128),
//             std::domain_error);
//     }
// }

TEST_CASE("ipps vector exceptions", "[vector],[exceptions]"){
    ipps::vector<Ipp64fc> data(128);

    SECTION("access out of range"){
        REQUIRE_THROWS_AS(data.at(128), std::out_of_range);
    }

    SECTION("zero out of range"){
        REQUIRE_THROWS_AS(data.zero(-1, 10), std::out_of_range);
        REQUIRE_THROWS_AS(data.zero(127, 10), std::out_of_range);
    }

    SECTION("set out of range"){
        Ipp64fc v = {1.0, 0.0};
        REQUIRE_THROWS_AS(data.set(-1, 10, v), std::out_of_range);
        REQUIRE_THROWS_AS(data.set(127, 10, v), std::out_of_range);
    }
}

// this test is mainly here to ensure that compilation still works
// when the header is included and used in several cpp files
TEST_CASE("ipps vector encapsulation compile test", "[vector],[compile]"){
    EncapsulateVector ev;
}

// Test copy constructors
TEST_CASE("ipps vector copy/assignment", "[vector],[copy],[assignment]"){
    SECTION("ipp8u copy constructor"){
        // reference vector
        ipps::vector<Ipp8u> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp8u>> v;
        v.push_back(a);

        // should not be the same pointer
        REQUIRE(a.data() != v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp8u assignment operator"){
        std::vector<ipps::vector<Ipp8u>> v(4);

        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp8u>(100, 1);

            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp16u copy constructor"){
        // reference vector
        ipps::vector<Ipp16u> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp16u>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp16u assignment operator"){
        std::vector<ipps::vector<Ipp16u>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp16u>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp32u copy constructor"){
        // reference vector
        ipps::vector<Ipp32u> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp32u>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp32u assignment operator"){
        std::vector<ipps::vector<Ipp32u>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp32u>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp64u copy constructor"){
        // reference vector
        ipps::vector<Ipp64u> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp64u>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp64u assignment operator"){
        std::vector<ipps::vector<Ipp64u>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp64u>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp32f copy constructor"){
        // reference vector
        ipps::vector<Ipp32f> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp32f>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp32f assignment operator"){
        std::vector<ipps::vector<Ipp32f>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp32f>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp64f copy constructor"){
        // reference vector
        ipps::vector<Ipp64f> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp64f>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp64f assignment operator"){
        std::vector<ipps::vector<Ipp64f>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp64f>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp8s copy constructor"){
        // reference vector
        ipps::vector<Ipp8s> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp8s>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp8s assignment operator"){
        std::vector<ipps::vector<Ipp8s>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp8s>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp16s copy constructor"){
        // reference vector
        ipps::vector<Ipp16s> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp16s>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp32s copy constructor"){
        // reference vector
        ipps::vector<Ipp32s> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp32s>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp32s assignment operator"){
        std::vector<ipps::vector<Ipp32s>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp32s>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp64s copy constructor"){
        // reference vector
        ipps::vector<Ipp64s> a(100, 1);
        // std vector of vectors
        std::vector<ipps::vector<Ipp64s>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
            REQUIRE(a.at(i) == v.at(0).at(i));
    }

    SECTION("ipp64s assignment operator"){
        std::vector<ipps::vector<Ipp64s>> v(4);
        // assign to the std vector of ipps vectors
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp64s>(100, 1);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
                REQUIRE(1 == v.at(i).at(j));
        }
    }

    SECTION("ipp8sc copy constructor"){
        // reference vector
        Ipp8sc c = {1, 1};
        ipps::vector<Ipp8sc> a(100, c);
        // std vector of vectors
        std::vector<ipps::vector<Ipp8sc>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
        {
            REQUIRE(a.at(i).re == v.at(0).at(i).re);
            REQUIRE(a.at(i).im == v.at(0).at(i).im);
        }
    }

    SECTION("ipp8sc assignment operator"){
        std::vector<ipps::vector<Ipp8sc>> v(4);
        // assign to the std vector of ipps vectors
        Ipp8sc c = {1, 1};
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp8sc>(100, c);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
            {
                REQUIRE(c.re == v.at(0).at(j).re);
                REQUIRE(c.im == v.at(0).at(j).im);
            }
        }
    }

    SECTION("ipp16sc copy constructor"){
        // reference vector
        Ipp16sc c = {1, 1};
        ipps::vector<Ipp16sc> a(100, c);
        // std vector of vectors
        std::vector<ipps::vector<Ipp16sc>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
        {
            REQUIRE(a.at(i).re == v.at(0).at(i).re);
            REQUIRE(a.at(i).im == v.at(0).at(i).im);
        }
    }

    SECTION("ipp16sc assignment operator"){
        std::vector<ipps::vector<Ipp16sc>> v(4);
        // assign to the std vector of ipps vectors
        Ipp16sc c = {1, 1};
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp16sc>(100, c);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
            {
                REQUIRE(c.re == v.at(0).at(j).re);
                REQUIRE(c.im == v.at(0).at(j).im);
            }
        }
    }

    SECTION("ipp32sc copy constructor"){
        // reference vector
        Ipp32sc c = {1, 1};
        ipps::vector<Ipp32sc> a(100, c);
        // std vector of vectors
        std::vector<ipps::vector<Ipp32sc>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
        {
            REQUIRE(a.at(i).re == v.at(0).at(i).re);
            REQUIRE(a.at(i).im == v.at(0).at(i).im);
        }
    }

    SECTION("ipp32sc assignment operator"){
        std::vector<ipps::vector<Ipp32sc>> v(4);
        // assign to the std vector of ipps vectors
        Ipp32sc c = {1, 1};
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp32sc>(100, c);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
            {
                REQUIRE(c.re == v.at(0).at(j).re);
                REQUIRE(c.im == v.at(0).at(j).im);
            }
        }
    }

    SECTION("ipp64sc copy constructor"){
        // reference vector
        Ipp64sc c = {1, 1};
        ipps::vector<Ipp64sc> a(100, c);
        // std vector of vectors
        std::vector<ipps::vector<Ipp64sc>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
        {
            REQUIRE(a.at(i).re == v.at(0).at(i).re);
            REQUIRE(a.at(i).im == v.at(0).at(i).im);
        }
    }

    SECTION("ipp64sc assignment operator"){
        std::vector<ipps::vector<Ipp64sc>> v(4);
        // assign to the std vector of ipps vectors
        Ipp64sc c = {1, 1};
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp64sc>(100, c);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
            {
                REQUIRE(c.re == v.at(0).at(j).re);
                REQUIRE(c.im == v.at(0).at(j).im);
            }
        }
    }

    SECTION("ipp32fc copy constructor"){
        // reference vector
        Ipp32fc c = {1.0, 1.0};
        ipps::vector<Ipp32fc> a(100, c);
        // std vector of vectors
        std::vector<ipps::vector<Ipp32fc>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
        {
            REQUIRE(a.at(i).re == v.at(0).at(i).re);
            REQUIRE(a.at(i).im == v.at(0).at(i).im);
        }
    }

    SECTION("ipp32fc assignment operator"){
        std::vector<ipps::vector<Ipp32fc>> v(4);
        // assign to the std vector of ipps vectors
        Ipp32fc c = {1.0, 1.0};
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp32fc>(100, c);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
            {
                REQUIRE(c.re == v.at(0).at(j).re);
                REQUIRE(c.im == v.at(0).at(j).im);
            }
        }
    }

    SECTION("ipp64fc copy constructor"){
        // reference vector
        Ipp64fc c = {1.0, 1.0};
        ipps::vector<Ipp64fc> a(100, c);
        // std vector of vectors
        std::vector<ipps::vector<Ipp64fc>> v;
        v.push_back(a);
        // should not be the same pointer
        REQUIRE(a.data()!= v.at(0).data());
        // should be same size
        REQUIRE(a.size() == v.at(0).size());
        // should be same data
        for (size_t i = 0; i < a.size(); i++)
        {
            REQUIRE(a.at(i).re == v.at(0).at(i).re);
            REQUIRE(a.at(i).im == v.at(0).at(i).im);
        }
    }

    SECTION("ipp64fc assignment operator"){
        std::vector<ipps::vector<Ipp64fc>> v(4);
        // assign to the std vector of ipps vectors
        Ipp64fc c = {1.0, 1.0};
        for (size_t i = 0; i < v.size(); i++){
            v.at(i) = ipps::vector<Ipp64fc>(100, c);
            // should be same size
            REQUIRE(100 == v.at(i).size());
            // should be same data
            for (int j = 0; j < 100; j++)
            {
                REQUIRE(c.re == v.at(0).at(j).re);
                REQUIRE(c.im == v.at(0).at(j).im);
            }
        }
    }

    
}

template <typename T>
void test_vector_iterators()
{
    ipps::vector<T> a(100);
    // Set with the iterators
    int i = 0;
    for (auto& v : a)
    {
        v = (T)i;
        i++;
    }
    // Read with the const iterators specifically
    i = 0;
    for (const auto& v : a)
    {
        REQUIRE(v == (T)i);
        i++;
    }
}

template <typename T>
void test_vector_iterators_cplx()
{
    ipps::vector<T> a(100);
    // Set with the iterators
    int i = 0;
    using realType = decltype(std::declval<T>().re);
    for (auto& v : a)
    {
        v.re = (realType)i;
        v.im = (realType)i;
        i++;
    }
    // Read with the const iterators specifically
    i = 0;
    for (const auto& v : a)
    {
        REQUIRE(v.re == i);
        REQUIRE(v.im == i);
        i++;
    }
}

TEST_CASE("ipps vector iterators", "[vector],[iterator]")
{
    // Real types
    SECTION("Ipp8u"){
        test_vector_iterators<Ipp8u>();
    }
    SECTION("Ipp8s"){
        test_vector_iterators<Ipp8s>();
    }
    SECTION("Ipp16u"){
        test_vector_iterators<Ipp16u>();
    }
    SECTION("Ipp16s"){
        test_vector_iterators<Ipp16s>();
    }
    SECTION("Ipp32s"){
        test_vector_iterators<Ipp32s>();
    }
    SECTION("Ipp32u"){
        test_vector_iterators<Ipp32u>();
    }
    SECTION("Ipp64s"){
        test_vector_iterators<Ipp64s>();
    }
    SECTION("Ipp64u"){
        test_vector_iterators<Ipp64u>();
    }
    SECTION("Ipp32f"){
        test_vector_iterators<Ipp32f>();
    }
    SECTION("Ipp64f"){
        test_vector_iterators<Ipp64f>();
    }

    // Complex types
    SECTION("Ipp8sc"){
        test_vector_iterators_cplx<Ipp8sc>();
    }
    SECTION("Ipp16sc"){
        test_vector_iterators_cplx<Ipp16sc>();
    }
    SECTION("Ipp32sc"){
        test_vector_iterators_cplx<Ipp32sc>();
    }
    SECTION("Ipp64sc"){
        test_vector_iterators_cplx<Ipp64sc>();
    }
    SECTION("Ipp32fc"){
        test_vector_iterators_cplx<Ipp32fc>();
    }
    SECTION("Ipp64fc"){
        test_vector_iterators_cplx<Ipp64fc>();
    }

}

	



