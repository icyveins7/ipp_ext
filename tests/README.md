# Prerequisites
We will be using Catch2 for the unit tests. Install it by following the link [here](https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md). You can probably use the git repository installation if you're on Linux and the vcpkg one if you're on Windows. If you're using vcpkg, ensure you install the correct version of vcpkg (usually the 64-bit version, the default installs the 32-bit x86-windows version) i.e.

```bash
vcpkg install catch2:x64-windows
```

# Easy Testing

Set up your environment variable to point ```VCPKG_DIR``` to your vcpkg directory.
CMake should automatically detect and set the necessary prefixes to find Catch2 installed there.

Then just run 

```bash
mkdir build
cd build
cmake ..
msbuild ALL_BUILD.vcxproj # you can add /m:4 for multithread building
```

# Running with CMake (as an example on a Windows machine using vcpkg)
```bash
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH=%VCPKG_DIR%\\installed\\x64-windows\\share ..
msbuild ALL_BUILD.vcxproj # you can add /m:4 for multithread building
```

There are then two ways to run the tests:

```bash
# Run ctest directly
ctest
# Or run the executable produced
Debug\tests.exe # For example, this is where msvc will compile to
```

