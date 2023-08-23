/*
cl /EHsc /O2 dft_example.cpp ippcore.lib ipps.lib /I"../include/"
*/

#include "ipp_ext.h"

int main()
{
    // some data
    ippe::vector<Ipp32fc> in(10);
    for (int i = 0; i < in.size(); i++)
    {
        in[i].re = i;
        in[i].im = i;
    }
    ippe::vector<Ipp32fc> out(in.size(), {0.0f, 0.0f});

    // make the DFT object
    ippe::DFTCToC<Ipp32fc> dft(out.size());

    // execute it
    dft.fwd(in.data(), out.data());

    for (int i = 0; i < out.size(); i++)
        printf("%f %f\n", out[i].re, out[i].im);

    return 0;
}