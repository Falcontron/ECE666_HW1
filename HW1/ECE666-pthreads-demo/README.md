# ECE666-pthreads-demo

This is a simple demo of working code that uses the pthreads library. Unlike the PARMACS-based code used in the ECE666 textbook, this code can be compiled and executed.

This repo contains three source files and a makefile. 
* `seq-pi.c` is the sequential version of the Monte Carlo method to estimate the value of **&pi;**. The code is hardcoded to run 128M  (where 1M = 1024x1024) trials. 
* `pthreads-pi.c` is the pthreads-based parallel version of `seq-pi.c`. It is functionally correct. No effort has been made to optimize its performance. It is hardcoded to use 8 threads.
* `pthreads-demo.c` is a simple program to highlight the `pthread_create` and `pthread_join` functionalities. Each thread prints some basic thread-information to illustrate the parallel execution. 

Each source file can be compiled with the `DEBUG` flag defined to (1) use repeatable random numbers, (2) use fewer threads and/or smaller problems, and (3) print additional diagnostic information.
