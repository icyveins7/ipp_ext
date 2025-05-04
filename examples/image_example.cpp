#include "ipp_ext.h"
#include <iostream>

int main()
{
  // Instantiate simple image
  ippi::image<Ipp32s, ippi::channels::C1> img(64, 64);

  // Check some simple things
  printf("Image width: %zd\n", img.width());
  printf("Image height: %zd\n", img.height());
  printf("Image step bytes: %lld\n", img.stepBytes());

  // Set some values for a small img (width, height)
  ippi::image<Ipp32f, ippi::channels::C1> small_img(3, 4);
  printf("Small image dims: rows %zd x cols %zd\n", small_img.height(), small_img.width());
  printf("Small image step bytes: %lld\n", small_img.stepBytes());

  for (size_t i = 0; i < small_img.height(); ++i)
    for (size_t j = 0; j < small_img.width(); ++j)
      small_img.at(i, j) = (Ipp32f)(i * small_img.width() + j);

  // Print the small image
  for (size_t i = 0; i < small_img.height(); ++i)
  {
    for (size_t j = 0; j < small_img.width(); ++j)
      printf("%4.1f ", small_img.at(i, j));
    printf("\n");
  }

  // You can also have a single row image easily
  ippi::image<Ipp32f, ippi::channels::C1> row_img(3);
  printf("Single row image dims: %zd x %zd\n", row_img.width(), row_img.height());
  printf("Single row image step bytes: %lld\n", row_img.stepBytes());


  return 0;
}
