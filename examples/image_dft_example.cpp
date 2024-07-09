#include "ipp_ext.h"

#include <iostream>

int main()
{
  try{
    // make an image
    ippi::image<Ipp32f, ippi::channels::C1> img(32, 32);

    // make a DFT object
    ippi::DFT_RToPack<Ipp32f> dft(img.size());

    // get hint of output size (which should be the same)
    ippi::image<Ipp32f, ippi::channels::C1> out(
      dft.fwdOutputSize()
    );
    printf("Output size: %zdx%zd\n", out.width(), out.height());

    // run the forward transform on the image
    dft.fwd<ippi::channels::C1>(
      img.data(),
      static_cast<int>(img.stepBytes()),
      out.data(),
      static_cast<int>(out.stepBytes())
    );

  }
  catch (std::exception& e){
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }


  return 0;
}
