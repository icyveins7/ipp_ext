/*
cl /EHsc /O2 dft_example.cpp ippcore.lib ipps.lib /I"../include/"
*/

#include "ipp_ext.h"

int main()
{
    // make the DFT object
    ippe::DFTCToC<Ipp32fc> dft(100);

    // some data
    ippe::vector<Ipp32fc> in(100);
    ippe::vector<Ipp32fc> out(100);

    // execute it
    dft.fwd(in.data(), out.data());

    return 0;
}