#include "ipp_ext.h"
#include <iostream>

int main()
{
    printf("Creating filter object...\n");
    ippe::filter::FIRSR<Ipp32f, Ipp32fc> filter(
        ippe::filter::generateLowpassTaps<Ipp32f>(0.5/2.0, 8, ippWinHamming, ippTrue)
    );
    // Copy elision should happen for the above statement so you won't see the move ctor.

    // You could also hold the filter taps separately, though this is unnecessary since the filter object copies it..
    printf("Unnecessary taps storage, not recommended\n");
    ippe::vector<Ipp32f> unnecessaryTaps = ippe::filter::generateLowpassTaps<Ipp32f>(0.5/2.0, 8, ippWinHamming, ippTrue);
    ippe::filter::FIRSR<Ipp32f, Ipp32fc> filter2(unnecessaryTaps);

    printf("Checking filter coefficients...\n");
    for (int i = 0; i < filter.getTaps().size(); i++)
        printf("%f ", filter.getTaps()[i]);

    printf("\nCreating some data...\n");
    ippe::vector<Ipp32fc> data(10);
    ippe::generator::Slope<Ipp32f>(
        (Ipp32f*)data.data(), data.size()*2, 0.0f, 1.0f
    );
    for (int i = 0; i < data.size(); i++)
        printf("%f %f\n", data[i].re, data[i].im);

    printf("\nChecking filter delay...\n");
    for (int i = 0; i < filter.getDelayVector().size(); i++)
        printf("%f %f\n", filter.getDelayVector()[i].re, filter.getDelayVector()[i].im);

    printf("\nRunning the filter...\n");
    ippe::vector<Ipp32fc> out(data.size());
    filter.filter(data.data(), out.data(), data.size());

    printf("\nChecking the output...\n");
    for (int i = 0; i < out.size(); i++)
    {
        printf("%f %f\n", out[i].re, out[i].im);
    }

    printf("\nChecking the delay again...\n");
    for (int i = 0; i < filter.getDelayVector().size(); i++)
    {
        printf("%f %f\n", filter.getDelayVector()[i].re, filter.getDelayVector()[i].im);
    }


    return 0;
}