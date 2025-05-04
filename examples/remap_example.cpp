#include "ipp_ext.h"

#include <iostream>
#include <array>

int main()
{
  try{
    // make an image
    ippi::image<Ipp32f, ippi::channels::C1> src(2, 2);

    // set the points incrementally
    for (int i = 0; i < src.height(); ++i)
      for (int j = 0; j < src.width(); ++j)
        src.at(i, j) = (Ipp32f)(i * src.width() + j + 1);

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
    const Ipp32f fixedInit = 9.9f;
    for (int i = 0; i < dst.height(); ++i)
      for (int j = 0; j < dst.width(); ++j)
        dst.at(i, j) = fixedInit;

    IppiRect srcRoi = { 0, 0, static_cast<int>(src.width()), static_cast<int>(src.height()) };

    {
      printf("Without smooth edge\n");
      ippi::Remap<ippi::channels::C1>(
        src.data(), src.size(), (int)src.stepBytes(), srcRoi,
        xmap.data(), (int)xmap.stepBytes(), ymap.data(), (int)ymap.stepBytes(),
        dst.data(), (int)dst.stepBytes(), dst.size(), IPPI_INTER_LINEAR);

      // print the result
      std::array<int, 4> cornersX;
      std::array<int, 4> cornersY;
      int k = 0;
      for (int i = 0; i < dst.height(); ++i)
      {
        for (int j = 0; j < dst.width(); ++j)
        {
          printf("%.1f ", dst.at(i, j));
          // Top left
          if (i > 0 && j > 0 && dst.at(i, j) != 9.9f && dst.at(i, j-1) == 9.9f && dst.at(i-1, j) == 9.9f)
          {
            cornersX.at(k) = j;
            cornersY.at(k) = i;
            k++;
          }
          // Btm left
          if (i > 0 && j > 0 && dst.at(i, j) != 9.9f && dst.at(i, j-1) == 9.9f && dst.at(i+1, j) == 9.9f)
          {
            cornersX.at(k) = j;
            cornersY.at(k) = i;
            k++;

          }
          // Top right
          if (i > 0 && j > 0 && dst.at(i, j-1) != 9.9f && dst.at(i, j) == 9.9f && dst.at(i-1, j-1) == 9.9f)
          {
            cornersX.at(k) = j-1;
            cornersY.at(k) = i;
            k++;
          }
          // Btm right
          if (i > 0 && j > 0 && dst.at(i, j-1) != 9.9f && dst.at(i, j) == 9.9f && dst.at(i+1, j-1) == 9.9f)
          {
            cornersX.at(k) = j-1;
            cornersY.at(k) = i;
            k++;
          }

        }
        printf("\n");
      }

      // Check corners
      for (int i = 0; i < k; ++i)
        printf(
          "(%d, %d) => %.1f, %.1f\n",
          cornersX.at(i), cornersY.at(i),
          xmap.at(cornersY.at(i), cornersX.at(i)), ymap.at(cornersY.at(i), cornersX.at(i))
        );

    }
    {
      printf("With smooth edge\n");
      ippi::Remap<ippi::channels::C1>(
        src.data(), src.size(), (int)src.stepBytes(), srcRoi,
        xmap.data(), (int)xmap.stepBytes(), ymap.data(), (int)ymap.stepBytes(),
        dst.data(), (int)dst.stepBytes(), dst.size(), IPPI_INTER_LINEAR | IPPI_SMOOTH_EDGE);

      // print the result
      std::array<int, 4> cornersX;
      std::array<int, 4> cornersY;
      int k = 0;
      for (int i = 0; i < dst.height(); ++i)
      {
        for (int j = 0; j < dst.width(); ++j)
        {
          printf("%.1f ", dst.at(i, j));
          // Top left
          if (i > 0 && j > 0 && dst.at(i, j) != 9.9f && dst.at(i, j-1) == 9.9f && dst.at(i-1, j) == 9.9f)
          {
            cornersX.at(k) = j;
            cornersY.at(k) = i;
            k++;
          }
          // Btm left
          if (i > 0 && j > 0 && dst.at(i, j) != 9.9f && dst.at(i, j-1) == 9.9f && dst.at(i+1, j) == 9.9f)
          {
            cornersX.at(k) = j;
            cornersY.at(k) = i;
            k++;

          }
          // Top right
          if (i > 0 && j > 0 && dst.at(i, j-1) != 9.9f && dst.at(i, j) == 9.9f && dst.at(i-1, j-1) == 9.9f)
          {
            cornersX.at(k) = j-1;
            cornersY.at(k) = i;
            k++;
          }
          // Btm right
          if (i > 0 && j > 0 && dst.at(i, j-1) != 9.9f && dst.at(i, j) == 9.9f && dst.at(i+1, j-1) == 9.9f)
          {
            cornersX.at(k) = j-1;
            cornersY.at(k) = i;
            k++;
          }

        }
        printf("\n");
      }

      // Check corners
      for (int i = 0; i < k; ++i)
        printf(
          "(%d, %d) => %.1f, %.1f\n",
          cornersX.at(i), cornersY.at(i),
          xmap.at(cornersY.at(i), cornersX.at(i)), ymap.at(cornersY.at(i), cornersX.at(i))
        );

    }
  }
  catch (std::exception& e){
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }


  return 0;
}
