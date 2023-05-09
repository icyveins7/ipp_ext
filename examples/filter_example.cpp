/*
cl /EHsc /O2 filter_example.cpp ippcore.lib ipps.lib /I"../include/"
*/

#include "ipp_ext.h"

int main()
{
    // make the filter object
    // here we make a lowpass filter equivalent to scipy.signal.firwin(64, 0.5)
    ippe::FIRSRLowpass<Ipp32fc> lowpass(0.5, 64, ippWinHamming, ippTrue);

    // make some data and output
    ippe::vector<Ipp32fc> data(1000, Ipp32fc{1.0, 2.0});
    ippe::vector<Ipp32fc> output(1000);

    // filter the data
    lowpass.filter(data.data(), output.data(), output.size());

    // reset the delay vector and run (here we just re-use the vector) if needed
    lowpass.reset();
    lowpass.filter(data.data(), output.data(), output.size());

    return 0;
}