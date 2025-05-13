#include "ipp_ext.h"
#include <cstdlib>
#include <iostream>

int main()
{
    // Make an image
    ippi::image<Ipp16s, ippi::channels::C1> img(5, 5);
    // Make a filter median object
    IppiSize maskSize = {3, 3};
    ippi::FilterMedianBorder<Ipp16s, ippi::channels::C1> filter(img.size(), maskSize);

    // Set some data
    for (int i = 0; i < img.size().height; i++){
        for (int j = 0; j < img.size().width; j++){
            img.at(i, j) = (Ipp16s)(std::rand() % 100);
            printf("%3hd ", img.at(i, j));
        }
        printf("\n");
    }

    // Make an output image
    ippi::image<Ipp16s, ippi::channels::C1> out(img.size());

    // Run the filter
    filter.filter(img.data(), (int)img.stepBytes(), out.data(), (int)out.stepBytes(), ippBorderRepl, nullptr);

    // Print the output
    for (int i = 0; i < out.size().height; i++){
        for (int j = 0; j < out.size().width; j++)
            printf("%3hd ", out.at(i, j));
        printf("\n");
    }


    return 0;
}
