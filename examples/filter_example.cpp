#include "ipp_ext.h"
#include <iostream>

void FIRSR_example()
{
    printf("Creating filter object...\n");
    ipps::filter::FIRSR<Ipp32fc, Ipp32fc> filter(
        ipps::filter::generateLowpassTaps<Ipp32fc>(0.5/2.0, 8, ippWinHamming, ippTrue)
    );
    // Copy elision should happen for the above statement so you won't see the move ctor.

    // You could also hold the filter taps separately, though this is unnecessary since the filter object copies it..
    printf("Unnecessary taps storage, not recommended\n");
    ipps::vector<Ipp32fc> unnecessaryTaps = ipps::filter::generateLowpassTaps<Ipp32fc>(0.5/2.0, 8, ippWinHamming, ippTrue);
    ipps::filter::FIRSR<Ipp32fc, Ipp32fc> filter2(unnecessaryTaps);

    printf("Checking filter coefficients...\n");
    for (int i = 0; i < filter.getTaps().size(); i++)
        printf("%f %f", filter.getTaps()[i].re, filter.getTaps()[i].im);

    printf("\nCreating some data...\n");
    ipps::vector<Ipp32fc> data(10);
    ipps::generator::Slope<Ipp32f>(
        (Ipp32f*)data.data(), (int)data.size()*2, 0.0f, 1.0f
    );
    for (int i = 0; i < data.size(); i++)
        printf("%f %f\n", data[i].re, data[i].im);

    printf("\nChecking filter delay...\n");
    for (int i = 0; i < filter.getDelayVector().size(); i++)
        printf("%f %f\n", filter.getDelayVector()[i].re, filter.getDelayVector()[i].im);

    printf("\nRunning the filter...\n");
    ipps::vector<Ipp32fc> out(data.size());
    filter.filter(data.data(), out.data(), (int)data.size());

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
}

void FIRMR_example()
{
    printf("Creating filter object...\n");
    int up = 5, down = 3;
    ipps::filter::FIRMR<Ipp32fc, Ipp32fc> filter(
        ipps::filter::generateLowpassTaps<Ipp32fc>(0.2/2.0, 8, ippWinHamming, ippTrue),
        up, 0, down, 0
    );
    
    printf("Creating some data...\n");
    ipps::vector<Ipp32fc> data(30);
    ipps::generator::Slope<Ipp32f>(
        (Ipp32f*)data.data(), (int)data.size()*2, 10.0f, 1.0f
    );

    printf("\nRunning the filter...\n");
    ipps::vector<Ipp32fc> out(data.size()*up/down);
    filter.filter(data.data(), out.data(), (int)data.size(), (int)out.size());

    printf("\nChecking the output...\n");
    for (int i = 0; i < out.size(); i++)
    {
        printf("%d: %f %f\n", i, out[i].re, out[i].im);
    }

}

int main()
{
    
    try{
        printf("============ FIRSR Example =================\n");
        FIRSR_example();
        printf("============ FIRMR Example =================\n");
        FIRMR_example();
    }
    catch(std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }


    return 0;
}
