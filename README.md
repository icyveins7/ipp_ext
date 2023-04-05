# ipp_ext
A bunch of C++ extensions to the Intel Performance Primitives C library. This repository is meant to be compiled directly with your own source code; it requires no separate compilation by itself.

See below for the available extensions. All individual extensions are under the namespace ```ippe```, and can be universally included with

```cpp
#include "ipp_ext.h"
```

# Extensions
## Extension 1: Vector

### Easy Compile Command

```bash
git clone https://github.com/icyveins7/ipp_ext.git
# In your project directory now...
cl mysource1.cpp mysource2.cpp ... -I"path/to/ipp_ext/include" ...
```


Individual header is contained in ```ipp_ext_vec.h```, but ```ipp_ext``` contains it.

The ```ippe::vector<>``` container is meant as a drop-in replacement for the ```std::vector<>``` container. It doesn't have all the features of the latter, but probably enough to get you going for most cases. 

This vector has templates for all the IPP types (```Ipp64fc``` all the way to ```Ipp8u```), but specifically excludes all non-IPP types (like ```float```, ```double``` etc).

Importantly, it utilises the ```ippsMalloc``` and ```ippsCopy``` functions to deal with memory allocation, so that IPP can properly utilise the 64-byte boundary of the arrays allocated.

See ```examples/vector_example.cpp``` for a simple example.