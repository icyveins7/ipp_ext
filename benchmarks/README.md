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

### MSVC, Ryzen 5600X, /O2, /m:AVX2 

Notes:
1. The matmul implementation fully uses IPP only, but has separate implementations depending on the sizes of the matrix.
2. This favours the tall, thin matrices on the second matrix the most; ```A*B``` where B is tall and thin, or better still, just a column vector.
3. For the other cases, this can be up to 3x slower than Eigen, which isn't too bad.
4. Some of the test cases may not reflect the actual performance; Catch2 tends to perform copies if an object like a vector is returned, even if it's a reference.
5. Eigen is optimized well enough to be equivalent to IPP, at least on the vector operations.

```

-------------------------------------------------------------------------------
Benchmark with Eigen Vector
  Add, length 100000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(30)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Vector Add                               100             3     2.9535 ms
                                        12.0197 us     11.418 us    12.8663 us
                                        3.61992 us    2.82197 us    4.96243 us

IPP Vector Add                                 100             3     2.9643 ms
                                        11.1563 us    10.8527 us    11.7353 us
                                        2.06448 us    1.30594 us     3.8668 us

Raw Loop                                       100             1     3.6133 ms
                                         35.875 us     35.685 us     36.213 us
                                        1.25872 us    829.416 ns    2.01243 us


-------------------------------------------------------------------------------
Benchmark with Eigen Vector
  Add, length 1000000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(69)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Vector Add                               100             1    10.6233 ms
                                        115.006 us    109.396 us    134.423 us
                                          46.89 us    13.9629 us    105.428 us

IPP Vector Add                                 100             1    10.8597 ms
                                        117.709 us    113.424 us    129.193 us
                                        33.0088 us    15.4474 us    68.6478 us

Raw Loop                                       100             1    36.3201 ms
                                        364.557 us    360.502 us    383.149 us
                                        37.8588 us    3.97065 us    89.7761 us

Raw loop with explicit pointer cast            100             1    44.2088 ms
                                         440.98 us    438.216 us    447.889 us
                                        20.7609 us    7.86218 us    39.2606 us

Raw loop with explicit pointer cast
and explicit 4x UNROLL                         100             1    28.9216 ms
                                        288.622 us     285.95 us    300.322 us
                                        24.3777 us    3.41214 us    57.4255 us


-------------------------------------------------------------------------------
Benchmark with Eigen Array
  Element-wise multiply, length 100000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(146)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Array Multiply                           100             3      2.991 ms
                                         10.598 us    10.3433 us    10.9123 us
                                         1.4426 us    1.24141 us    1.64196 us

IPP Array Multiply                             100             3     2.9934 ms
                                         10.556 us    10.3543 us     10.807 us
                                        1.14843 us     997.48 ns    1.42483 us

Raw Loop                                       100             1     3.6127 ms
                                         35.681 us     35.599 us     35.852 us
                                        579.655 ns    339.816 ns    1.10919 us


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x1000, 1000x1
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(256)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             7      2.247 ms
                                          3.223 us    3.21186 us      3.246 us
                                        78.4545 ns    45.0859 ns     124.43 ns

IPP Matrix Multiply                            100           108     2.0304 ms
                                         243.12 ns    233.074 ns    252.963 ns
                                        50.9258 ns    49.2346 ns     55.736 ns

Raw loop                                       100             9      2.133 ms
                                        2.32767 us      2.323 us    2.33433 us
                                        28.0599 ns    19.6312 ns    42.5245 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x2, 2x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(261)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100          1050      1.995 ms
                                        19.0171 ns    18.9943 ns    19.0648 ns
                                       0.160868 ns  0.0711168 ns   0.273137 ns

IPP Matrix Multiply                            100           274     2.0276 ms
                                        70.1752 ns    69.8577 ns    71.2482 ns
                                        2.67369 ns   0.900033 ns    5.99165 ns

Raw loop                                       100           899     1.9778 ms
                                        22.4638 ns    22.4349 ns    22.5239 ns
                                       0.205119 ns  0.0988112 ns   0.344179 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x1000, 1000x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(266)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             3     2.1168 ms
                                          7.093 us      7.065 us    7.14567 us
                                        190.728 ns    117.195 ns    294.652 ns

IPP Matrix Multiply                            100            22     2.0636 ms
                                        943.864 ns      940.5 ns    955.182 ns
                                        27.8182 ns    8.33493 ns    62.1166 ns

Raw loop                                       100             3     2.1237 ms
                                        7.00833 us      6.963 us    7.16233 us
                                        374.739 ns    91.6582 ns    833.451 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x100, 100x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(271)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100            35     2.0895 ms
                                        598.057 ns    595.629 ns    606.686 ns
                                        20.6051 ns    5.91166 ns    46.4703 ns

IPP Matrix Multiply                            100            93      2.046 ms
                                        221.978 ns    220.785 ns    225.215 ns
                                        9.01388 ns    2.19363 ns     18.717 ns

Raw loop                                       100            27     2.0655 ms
                                        743.778 ns    742.852 ns    745.926 ns
                                        6.71781 ns    2.88675 ns    11.4623 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 3x10, 10x3
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(275)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100           534     2.0292 ms
                                         37.882 ns    37.5131 ns    38.8464 ns
                                        2.78044 ns   0.635866 ns    5.58849 ns

IPP Matrix Multiply                            100           134     2.0368 ms
                                        152.306 ns    151.701 ns    154.657 ns
                                        5.28544 ns    1.11781 ns    12.2156 ns

Raw loop                                       100           258     2.0382 ms
                                        77.6202 ns    77.3333 ns    78.8295 ns
                                        2.57708 ns   0.410194 ns    6.02931 ns


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 1000x3, 3x1000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(280)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             1    17.8916 ms
                                        179.896 us    178.889 us    183.607 us
                                        8.72944 us    2.15979 us    20.0513 us

IPP Matrix Multiply                            100             1    113.756 ms
                                        1.25755 ms    1.25047 ms     1.2674 ms
                                        42.3542 us    30.8873 us    58.4462 us

Raw loop                                       100             1    313.328 ms
                                        3.11445 ms    3.11128 ms    3.11789 ms
                                         16.829 us    14.1414 us    20.2533 us


-------------------------------------------------------------------------------
Benchmark with Eigen matrix multiplication
  Matmul Ipp32f, 1000x1000, 1000x1000
-------------------------------------------------------------------------------
E:\gitrepos\ipp_ext\benchmarks\compare_eigen.cpp(285)
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
Eigen Matrix Multiply                          100             1     1.64233 s
                                        16.3359 ms    16.3069 ms    16.3688 ms
                                        157.096 us    134.286 us    196.166 us

IPP Matrix Multiply                            100             1     5.61637 s
                                        56.1902 ms    56.0563 ms    56.3575 ms
                                        758.579 us    621.178 us    958.462 us

Raw loop                                       100             1     1.90362 m
                                         1.14816 s     1.14626 s     1.15107 s
                                        11.8863 ms    8.60212 ms    16.6594 ms


===============================================================================
test cases: 3 | 3 passed
assertions: - none -


```

