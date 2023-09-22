#include "ipp_ext.h"
#include <iostream>

int main()
{
    printf("Creating filter object...\n");
    ippe::filter::FIRSR<Ipp32f, Ipp32fc> filter(
        ippe::filter::generateLowpassTaps<Ipp32f>(0.5, 8, ippWinHamming, ippTrue)
    );

    printf("Checking filter coefficients...\n");
    for (int i = 0; i < filter.getTaps().size(); i++)
        printf("%f ", filter.getTaps()[i]);


    return 0;
}