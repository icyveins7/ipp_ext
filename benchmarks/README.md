# Running Benchmarks

Similar to tests, compile with the following

```
# Linux
mkdir build && cd build
cmake ..
make

# Windows
mkdir build && cd build
cmake ..
msbuild ALL_BUILD.vcproj -p:Configuration=Release # This is to enable optimisations like /O2
```

and then just run each benchmark individually.

```
./benchmark_dft
```

# Eigen Comparisons

There is a special benchmark that contains some comparisons between IPP function calls and the Eigen library. This benchmark will only be compiled if the environment variable ```EIGEN_DIR``` is set to the directory containing Eigen. 

# Sample Benchmarks

## DFTs

### Ryzen 5600X

1. Not an Intel chip, may not reflect performance accurately.
2. Actually slower for multithreading when <100M samples (memory/cache-bound before that).

```
Randomness seeded to: 382384178

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
benchmark_dft.exe is a Catch2 v3.3.2 host application.
Run with -? for options

-------------------------------------------------------------------------------
Benchmark DFT single-threaded
  ipp32fc, length 10000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(13)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd()                                          100             4      6.868 ms 
                                         17.121 us    17.0688 us    17.2967 us 
                                        427.842 ns     90.251 ns    946.565 ns 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT single-threaded
  ipp32fc, length 100000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(28)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd()                                          100             1    26.0329 ms 
                                        234.978 us    233.259 us    239.611 us 
                                        13.3756 us    6.11814 us    28.2528 us 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT single-threaded
  ipp32fc, length 1000000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(43)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd()                                          100             1    320.458 ms 
                                        3.43591 ms    3.32376 ms    3.61191 ms 
                                        705.682 us    502.165 us    1.01613 ms 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT single-threaded
  ipp32fc, length 10000000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(58)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd()                                          100             1     11.8822 s 
                                         101.63 ms     100.76 ms    102.853 ms 
                                        5.23519 ms    3.99747 ms     6.9596 ms 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT, 4 threads
  ipp32fc, length 10000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(99)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd(), should take benchmark time/4            100             1     15.513 ms 
                                        157.004 us    154.208 us     162.18 us 
                                        18.7436 us       12.5 us    33.5043 us 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT, 4 threads
  ipp32fc, length 100000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(118)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd(), should take benchmark time/4            100             1    39.7125 ms 
                                        418.639 us    408.531 us    438.554 us 
                                        69.7664 us    43.9915 us    127.585 us 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT, 4 threads
  ipp32fc, length 1000000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(138)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd(), should take benchmark time/4            100             1     1.72273 s 
                                        17.9305 ms    17.7101 ms    18.1906 ms 
                                        1.22371 ms    1.03216 ms    1.50758 ms 
                                                                               

-------------------------------------------------------------------------------
Benchmark DFT, 4 threads
  ipp32fc, length 10000000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\benchmark_dft.cpp(157)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
fwd(), should take benchmark time/4            100             1     28.1646 s 
                                        287.341 ms    285.582 ms    289.713 ms 
                                        10.3135 ms      8.275 ms    13.7681 ms 
                                                                               

===============================================================================
test cases: 2 | 2 passed
assertions: - none -
```


## Eigen Benchmark

### GCC, i7-8565UC, -O3 -mavx2

```
Randomness seeded to: 1502030075

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
compare_eigen is a Catch2 v3.3.2 host application.
Run with -? for options

-------------------------------------------------------------------------------
Benchmark with Eigen Vector
  Add, length 100000
-------------------------------------------------------------------------------
/home/seoxubuntu/gitrepos/ipp_ext/benchmarks/compare_eigen.cpp:19
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Vector Add                               100             1     3.0578 ms 
                                        30.7693 us     29.465 us    36.1006 us 
                                        10.9814 us    255.573 ns    25.6479 us 
                                                                               
IPP Vector Add                                 100             1     1.8323 ms 
                                        18.0329 us    17.9409 us     18.331 us 
                                        721.605 ns     53.565 ns    1.60573 us 
                                                                               
Raw Loop                                       100             1     3.3399 ms 
                                        32.7682 us    32.1941 us    34.1398 us 
                                        4.30973 us    2.15422 us    7.99879 us 
                                                                               

-------------------------------------------------------------------------------
Benchmark with Eigen Vector
  Add, length 1000000
-------------------------------------------------------------------------------
/home/seoxubuntu/gitrepos/ipp_ext/benchmarks/compare_eigen.cpp:59
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Vector Add                               100             1    86.4121 ms 
                                        860.113 us    840.069 us    921.139 us 
                                        161.027 us    58.6004 us    350.828 us 
                                                                               
IPP Vector Add                                 100             1    58.1658 ms 
                                        594.183 us    577.401 us    628.644 us 
                                        117.893 us    69.6488 us    226.894 us 
                                                                               
Raw Loop                                       100             1    114.686 ms 
                                        1.16465 ms    1.14504 ms    1.20911 ms 
                                        142.938 us    72.3016 us     276.94 us
```

### MSVC, Ryzen 5600X, /O2, /m:AVX2 (only matmul)

Notes:
1. The matmul implementation fully uses IPP only, but has separate implementations depending on the sizes of the matrix.
2. This favours the tall, thin matrices on the second matrix the most; ```A*B``` where B is tall and thin, or better still, just a column vector.
3. For the other cases, this can be up to 3x slower than Eigen, which isn't too bad.

```
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x1000, 1000x1
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(215)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             7     2.2736 ms
                                        3.23114 us    3.22343 us    3.25357 us
                                        61.1674 ns    22.8321 ns    131.197 ns

IPP Matrix Multiply                            100            89     2.0025 ms
                                        226.146 ns    225.045 ns    230.371 ns
                                        9.63993 ns    1.84253 ns    22.3668 ns

Raw loop                                       100             9     2.1762 ms
                                          2.374 us    2.36667 us    2.39044 us
                                        54.8933 ns    31.7786 ns    87.2824 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x2, 2x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(220)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100           334      2.004 ms
                                        58.5808 ns    58.3054 ns    59.3204 ns
                                        2.11301 ns   0.741131 ns    4.25792 ns

IPP Matrix Multiply                            100           164     2.0008 ms
                                        120.159 ns     119.22 ns    122.512 ns
                                        6.83763 ns    1.44515 ns    12.3972 ns

Raw loop                                       100           326     1.9886 ms
                                        60.9509 ns    60.7209 ns    61.8313 ns
                                        1.99405 ns   0.420357 ns    4.59838 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x1000, 1000x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(225)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             3     2.1234 ms
                                        7.80467 us    7.59967 us    8.24733 us
                                        1.46735 us    865.205 ns    2.91634 us

IPP Matrix Multiply                            100            21     2.0601 ms
                                        981.714 ns    976.143 ns    1.00452 us
                                        50.5273 ns    7.52486 ns    118.795 ns

Raw loop                                       100             3     2.1543 ms
                                          7.094 us      7.053 us      7.193 us
                                        322.059 ns     186.88 ns    514.374 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x100, 100x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(230)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100            32     2.0256 ms
                                        634.875 ns    633.531 ns    638.156 ns
                                        10.0524 ns    4.64554 ns    19.5282 ns

IPP Matrix Multiply                            100            77     2.0097 ms
                                        263.403 ns    259.065 ns    273.844 ns
                                         31.483 ns    14.3158 ns    59.4529 ns

Raw loop                                       100            25     2.0225 ms
                                            791 ns     788.04 ns     801.32 ns
                                        24.9275 ns    6.74282 ns    56.3665 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x10, 10x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(234)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100           256     1.9968 ms
                                        77.9727 ns    77.5352 ns    79.2383 ns
                                        3.44415 ns    1.30991 ns    7.33733 ns

IPP Matrix Multiply                            100           106      2.014 ms
                                        187.925 ns    187.075 ns     191.33 ns
                                        7.52815 ns     1.5292 ns    17.4355 ns

Raw loop                                       100           170      2.006 ms
                                        116.882 ns    116.471 ns    118.418 ns
                                        3.55568 ns   0.871284 ns    8.12944 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 1000x3, 3x1000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(239)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             1    98.6574 ms
                                        1.04931 ms    1.04564 ms    1.06373 ms
                                        32.8096 us    6.41253 us    76.7465 us

IPP Matrix Multiply                            100             1    210.377 ms
                                        2.00162 ms    1.96822 ms    2.05518 ms
                                        212.145 us    148.363 us    375.862 us

Raw loop                                       100             1    392.576 ms
                                          3.985 ms    3.96645 ms    4.00431 ms
                                        96.6704 us    84.2217 us    110.996 us


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 1000x1000, 1000x1000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(244)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             1     1.69859 s
                                        17.1672 ms    17.1137 ms    17.2512 ms
                                         336.86 us    241.731 us    539.114 us

IPP Matrix Multiply                            100             1      5.7703 s
                                        57.7854 ms    57.6533 ms     57.945 ms
                                        740.364 us    617.156 us    926.916 us

Raw loop                                       100             1      1.9176 m
                                         1.15157 s     1.15087 s     1.15288 s
                                        4.74635 ms    2.95273 ms    7.94557 ms
```

