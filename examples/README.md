# Compiling Examples

Most of the examples can be compiled with your favourite compiler just by specifying the ```include``` folder appropriately. However, you can compile all of them using CMake if you'd like.

## Unix Makefiles

Unix Makefiles are single configuration generators, so you must specify the Debug/Release at the cmake step. See this [link](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#build-configurations) for details.

```bash
mkdir Debug
mkdir Release
# This prints some extra debug information to track memory allocations.
cmake -DCMAKE_BUILD_TYPE=Debug -B Debug . 
cmake -DCMAKE_BUILD_TYPE=Release -B Release .
# Note that failing to specify the CMAKE_BUILD_TYPE defaults to Debug

# Enter either folder and make
cd Debug
make
cd ../Release
make

```