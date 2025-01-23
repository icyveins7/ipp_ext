#include "ipp_ext.h"

#include <iostream>

int main()
{
  try{
    // make an image
    ippi::image<Ipp32f, ippi::channels::C1> src(2, 2);

    // set the points incrementally
    for (int i = 0; i < src.height(); ++i)
      for (int j = 0; j < src.width(); ++j)
        src.at(i, j) = i * src.width() + j + 1;

    // set some request values
    ippi::image<Ipp32f, ippi::channels::C1> xmap(31, 31);
    ippi::image<Ipp32f, ippi::channels::C1> ymap(xmap.size());
    // make a grid spanning -1.0f to 1.0f
    for (int i = 0; i < xmap.height(); ++i)
      for (int j = 0; j < xmap.width(); ++j)
        xmap.at(i, j) = j * 0.1f - 1.0f;

    for (int i = 0; i < ymap.height(); ++i)
      for (int j = 0; j < ymap.width(); ++j)
        ymap.at(i, j) = i * 0.1f - 1.0f;

    // call the remap
    ippi::image<Ipp32f, ippi::channels::C1> dst(xmap.size());
    // initialize all destination to a larger number so we can see the effect
    for (int i = 0; i < dst.height(); ++i)
      for (int j = 0; j < dst.width(); ++j)
        dst.at(i, j) = 9.9f;

    IppiRect srcRoi = { 0, 0, static_cast<int>(src.width()), static_cast<int>(src.height()) };

    ippi::Remap<ippi::channels::C1>(
      src.data(), src.size(), src.stepBytes(), srcRoi, xmap.data(), xmap.stepBytes(), ymap.data(), ymap.stepBytes(),
      dst.data(), dst.stepBytes(), dst.size(), IPPI_INTER_LINEAR);

    // print the result
    for (int i = 0; i < dst.height(); ++i)
    {
      for (int j = 0; j < dst.width(); ++j)
      {
        printf("%.1f ", dst.at(i, j));
      }
      printf("\n");
    }


  }
  catch (std::exception& e){
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }


  return 0;
}
