# ipp_ext
A bunch of C++ extensions to the Intel Performance Primitives C library. This repository is meant to be compiled directly with your own source code; it requires no separate compilation by itself.

See below for the available extensions. All individual extensions are under the namespace ```ippe```, and can be universally included with

```cpp
#include "ipp_ext.h"
```

## Easy Compile Command (Example for MSVC)

```bash
git clone https://github.com/icyveins7/ipp_ext.git
# In your project directory now...
cl mysource1.cpp mysource2.cpp ... -I"path/to/ipp_ext/include" ...
```

# Extensions
## Extension 1: Vector
### Description
Individual header is contained in ```ipp_ext_vec.h```, but ```ipp_ext``` contains it.

The ```ippe::vector<>``` container is meant as a drop-in replacement for the ```std::vector<>``` container. It doesn't have all the features of the latter, but probably enough to get you going for most cases. 

This vector has templates for all the IPP types (```Ipp64fc``` all the way to ```Ipp8u```), but specifically excludes all non-IPP types (like ```float```, ```double``` etc).

Importantly, it utilises the ```ippsMalloc``` and ```ippsCopy``` functions to deal with memory allocation, so that IPP can properly utilise the 64-byte boundary of the arrays allocated.

See ```examples/vector_example.cpp``` for a simple example.

### Comparison with std::vector
The ```ippe::vector<>``` container was designed primarily as a memory management container, and as such does not replicate all of the ```std::vector<>``` features.

1. Constructor does not set values to 'default-insertable'. This means that the underlying array elements for ```ippe::vector<>``` are undefined by default, whereas ```std::vector<>``` instead usually sets this to 0.
2. We bridge over this zero-ing functionality to the other constructor which ```std::vector<>``` also has, of the form ```vector(count, value)```, and invoke the ```ippsSet``` and ```ippsZero``` functions appropriately. Hence, to achieve the same 0-valued array, use ```ippe::vector<>(count, zeroval)``` (where ```zeroval``` may need to be defined beforehand for complex IPP types).
3. Instead of ```std::vector```'s ```assign```, we instead have ```set``` (and ```zero```), which does not mutate the array size. The call structure uses integers to mark the index of the element to start, and the length of the array to use, which corresponds to the IPP function structure. There is also a convenience overload with no arguments for both, which will simply ```set```/```zero``` the entire vector.


## Extension 2: DFT
### Description
Individual header is contained in ```ipp_ext_dft.h```. This ```ippe::DFTCToC``` class wraps the available flavours for ```DFTCToC``` functions, which are the most common DFT/FFT use-case in IPP, as they are not limited to powers of 2.

The class takes care of internal workspace allocation and deallocation, and allows you to simply call ```fwd()``` or ```bwd()``` which are the equivalent of FFT/IFFT functions. See the ```dft_example.cpp``` for the simplest example.

## Extension 3: FIRSR
### Description
Individual header is contained in ```ipp_ext_filter.h```. The parent class ```ippe::FIRSR``` is not meant to be instantiated directly; instead, use the derived classes with the below currently implemented flavours:

1. ```ippe::FIRSRLowpass``` creates a lowpass filter.

These classes take care of internal taps generation, memory allocation and de-allocation, and all workspace requirements, including a delay vector that properly accounts for repeated ```filter()``` invocations. See ```filter_example.cpp``` for a simple example.