/*
cl /EHsc /O2 dft_example.cpp ippcore.lib ipps.lib /I"../include/"
*/

#include "ipp_ext.h"

int main()
{
    // make the DFT object
    ippe::DFTCToC<Ipp32f> dft(100);

    return 0;
}