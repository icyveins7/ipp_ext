#include "ipp_ext.h"
#include <iostream>

int main()
{
    // Instantiate simple image
    ippi::image<Ipp32s, ippi::channels::C1> img(64, 64);

    // Check some simple things
    printf("Image width: %zd\n", img.width());
    printf("Image height: %zd\n", img.height());
    printf("Image step bytes: %lld\n", img.stepBytes());

    // Make one specifying the step bytes
    ippi::image<Ipp32s, ippi::channels::C1> img2(64, 64, 512);
    printf("Image step bytes: %lld\n", img2.stepBytes());

    // Check again
    printf("Image width: %zd\n", img2.width());
    printf("Image height: %zd\n", img2.height());
    printf("Image step bytes: %lld\n", img2.stepBytes());


    return 0;
}
