#include "ipp_ext.h"

int main()
{
  // Example 1: should allocate 200 bytes = 64 + 8 + 64*2
  // {
  //   printf("Example 1\n");
  //   ippi::image<Ipp32f, ippi::channels::C1> colImg(1, 2);
  //
  //   colImg[0][0] = 1.0f;
  //   colImg[1][0] = 2.0f;
  //
  //   colImg[4][0] = 3.0f; // this will be out of bounds
  // }

  // // Example 2: should allocate 64 + 8 + 128*2 = 328 bytes
  // {
  //   printf("Example 2\n");
  //   ippi::image<Ipp32f, ippi::channels::C1> colImg(17, 2); // needs 68 bytes per row, so padded to 128
  //
  //   colImg[0][0] = 1.0f;
  //   colImg[1][0] = 2.0f;
  //
  //   colImg[4][0] = 3.0f; // this will be out of bounds
  // }

  // Example 3: should also allocate 328 bytes
  {
    printf("Example 3\n");
    ippi::image<Ipp32f, ippi::channels::C1> colImg(32, 2);

    colImg[0][0] = 1.0f;
    colImg[1][0] = 2.0f;

    colImg[4][0] = 3.0f; // this will be out of bounds
  }

  return 0;
}
