# Prerequisites
We will be using Catch2 for the unit tests. Install it by following the link [here](https://github.com/catchorg/Catch2/blob/devel/docs/cmake-integration.md). 

We will be using the git repository installation if you're on Linux and the vcpkg one if you're on Windows. If you're using vcpkg, ensure you install the correct version of vcpkg (usually the 64-bit version, the default installs the 32-bit x86-windows version) i.e.

```bash
vcpkg install catch2:x64-windows
```

# Easy Testing

Set up your environment variable to point ```VCPKG_DIR``` to your vcpkg directory if you're using it.
CMake should automatically detect and set the necessary prefixes to find Catch2 installed there.

Then just run 

```bash
mkdir build
cd build
cmake ..
# For windows
msbuild ALL_BUILD.vcxproj # you can add /m:4 for multithread building
# For unix
make # you can add -j4 for multithread building
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

# Note for MacOS with Apple Silicon

You will need to build Catch2 with x86_64 targets. To do that, when building Catch2 run the normal cmake command with

```bash
-DCMAKE_OSX_ARCHITECTURES=x86_64
```

The CMakeLists.txt should handle the rest. This command is used internally in the ```ipp_ext``` cmake as well.