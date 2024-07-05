#include "ipp_ext.h"
#include <iostream>

int main()
{
    // Instantiate simple image
    ippi::image<Ipp8u, ippi::channels::C1> img(8, 8);

    // Check some simple things
    printf("Image width: %zd\n", img.width());
    printf("Image height: %zd\n", img.height());

    return 0;
}
