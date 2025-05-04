/*
cl /EHsc /O2 dft_example.cpp ippcore.lib ipps.lib /I"../include/"
*/

#include "ipp_ext.h"

int main()
{
    // some data
    ipps::vector<Ipp32fc> in(20);
    for (int i = 0; i < in.size(); i++)
    {
        in[i].re = (Ipp32f)i;
        in[i].im = (Ipp32f)i;
    }
    ipps::vector<Ipp32fc> out(in.size(), {0.0f, 0.0f});

    // make the DFT object
    ipps::DFTCToC<Ipp32fc> dft(out.size());

    // execute it
    dft.fwd(in.data(), out.data());

    for (int i = 0; i < out.size(); i++)
        printf("%f %f\n", out[i].re, out[i].im);
    printf("\n\n");

    // you can also reassign the dft object
    dft = ipps::DFTCToC<Ipp32fc>(out.size()/2);

    // execute it
    dft.fwd(in.data(), out.data());
    for (int i = 0; i < out.size()/2; i++)
    {
        printf("%f %f\n", out[i].re, out[i].im);
    }

    printf("End of DFT example\n");
    return 0;
}
