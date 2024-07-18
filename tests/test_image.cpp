#include "ipp_ext.h"

#include <catch2/catch_test_macros.hpp>

/*
  All types:
  8u, 16u, 16s, 32s, 32f, 32sc, 32fc

  All channels:
  C1, C2, C3, C4, AC4
*/

template <typename T, ippi::channels U>
void test_simple_image()
{
  // Create a small simple image
  IppiSize smallsize = { 3, 4 };
  ippi::image<T, U> smallimg(smallsize);

  // Check properties
  REQUIRE(smallimg.size().width == smallsize.width);
  REQUIRE(smallimg.size().height == smallsize.height);
  REQUIRE(smallimg.width() == smallsize.width);
  REQUIRE(smallimg.height() == smallsize.height);
  REQUIRE(smallimg.data() != nullptr);
  REQUIRE(smallimg.capacity() == smallsize.width * smallsize.height);
  REQUIRE(smallimg.empty() != true);

  // Clear and re-check
  smallimg.clear();
  REQUIRE(smallimg.empty() == true);
  REQUIRE(smallimg.size().width == 0);
  REQUIRE(smallimg.size().height == 0);

}

TEST_CASE("ippi image simple", "[image],[simple]")
{
  SECTION("8u C1") { test_simple_image<Ipp8u, ippi::channels::C1>(); }
  SECTION("16u C1") { test_simple_image<Ipp16u, ippi::channels::C1>(); }
  SECTION("16s C1") { test_simple_image<Ipp16s, ippi::channels::C1>(); }
  SECTION("32s C1") { test_simple_image<Ipp32s, ippi::channels::C1>(); }
  SECTION("32f C1") { test_simple_image<Ipp32f, ippi::channels::C1>(); }
  SECTION("32sc C1") { test_simple_image<Ipp32sc, ippi::channels::C1>(); }
  SECTION("32fc C1") { test_simple_image<Ipp32fc, ippi::channels::C1>(); }

  SECTION("8u C2") { test_simple_image<Ipp8u, ippi::channels::C2>(); }
  SECTION("16u C2") { test_simple_image<Ipp16u, ippi::channels::C2>(); }
  SECTION("16s C2") { test_simple_image<Ipp16s, ippi::channels::C2>(); }
  SECTION("32s C2") { test_simple_image<Ipp32s, ippi::channels::C2>(); }
  SECTION("32f C2") { test_simple_image<Ipp32f, ippi::channels::C2>(); }
  SECTION("32sc C2") { test_simple_image<Ipp32sc, ippi::channels::C2>(); }
  SECTION("32fc C2") { test_simple_image<Ipp32fc, ippi::channels::C2>(); }

  SECTION("8u C3") { test_simple_image<Ipp8u, ippi::channels::C3>(); }
  SECTION("16u C3") { test_simple_image<Ipp16u, ippi::channels::C3>(); }
  SECTION("16s C3") { test_simple_image<Ipp16s, ippi::channels::C3>(); }
  SECTION("32s C3") { test_simple_image<Ipp32s, ippi::channels::C3>(); }
  SECTION("32f C3") { test_simple_image<Ipp32f, ippi::channels::C3>(); }
  SECTION("32sc C3") { test_simple_image<Ipp32sc, ippi::channels::C3>(); }
  SECTION("32fc C3") { test_simple_image<Ipp32fc, ippi::channels::C3>(); }

  SECTION("8u C4") { test_simple_image<Ipp8u, ippi::channels::C4>(); }
  SECTION("16u C4") { test_simple_image<Ipp16u, ippi::channels::C4>(); }
  SECTION("16s C4") { test_simple_image<Ipp16s, ippi::channels::C4>(); }
  SECTION("32s C4") { test_simple_image<Ipp32s, ippi::channels::C4>(); }
  SECTION("32f C4") { test_simple_image<Ipp32f, ippi::channels::C4>(); }
  SECTION("32sc C4") { test_simple_image<Ipp32sc, ippi::channels::C4>(); }
  SECTION("32fc C4") { test_simple_image<Ipp32fc, ippi::channels::C4>(); }

  SECTION("8u AC4") { test_simple_image<Ipp8u, ippi::channels::AC4>(); }
  SECTION("16u AC4") { test_simple_image<Ipp16u, ippi::channels::AC4>(); }
  SECTION("16s AC4") { test_simple_image<Ipp16s, ippi::channels::AC4>(); }
  SECTION("32s AC4") { test_simple_image<Ipp32s, ippi::channels::AC4>(); }
  SECTION("32f AC4") { test_simple_image<Ipp32f, ippi::channels::AC4>(); }
  SECTION("32sc AC4") { test_simple_image<Ipp32sc, ippi::channels::AC4>(); }
  SECTION("32fc AC4") { test_simple_image<Ipp32fc, ippi::channels::AC4>(); }
}
