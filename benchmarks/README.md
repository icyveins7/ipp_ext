# Running Benchmarks

Similar to tests, compile with the following

```
mkdir build && cd build
cmake ..
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