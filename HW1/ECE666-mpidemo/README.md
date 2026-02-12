# Demo MPI code: Monte Carlo &pi; estimation example

This code is similar in functionality to the `pthreads` code used in the previous assignment; it performs 128M Monte Carlo trials to estimate the value of **&pi;**. The parallel implementation uses message passing as the programming model. As with the shared-memory example code, this code is provided with the accompanying Makefile. After you setup your environment to use MPI (described below), use `make` to compile the code and `make run` to launch a run with 4 processes. 

## MPI installation
You are welcome to download and install your own MPI implementation -- it's fairly straightforward and can be done with user permissions alone. However, one installation is made available to you at `/home/yara/mithuna2/mpich-install`. The installed version is the MPICH implementation (version 3.4.1) and it includes the MPI compiler (`mpicc`) and a utility to launch MPI programs (`mpi-exec`). To access these scripts, your environment variables must point to the relevant directories as follows.

* `$PATH` must include `/opt/gcc/6.1.0/bin:/home/yara/mithuna2/mpich-install/bin`.
* `$LD_LIBRARY_PATH` must include `/opt/gcc/6.1.0/lib64:/package/intel_alt/12.0.0/x86_64-Linux/composerxe-2011.0.084/compiler/lib/intel64:/home/yara/mithuna2/mpich-install/lib`.

## Launching MPI Execution
There are a few key differences in the MPI version (as compared to the shared memory programming model of `pthreads`). 

Under `pthreads,` the operating system (OS) works under the hood to take care of scheduling the threads on multiple cores on the same machine. In contrast, MPI orchestration requires the launching of multiple threads across _different_ machines, each running its own independent OS. Effectively, the MPI runtime performs the equivalent tasks by launching parallel processes on other machines; but this requires you to take some steps to ensure that the MPI runtime _can_ launch jobs on other machines. 

This entails three tasks.
1. You use a special command `mpiexec` to launch the binary (as opposed to directly running the binary at the command-line.)
2. The runtime must be given a list of machine names where the processes may be launched. This is straightforward; (1) you create a file with a list of machine names (one name per line), and (2) you pass the file name as a command-line argument when launching the MPI executable using `mpiexec`. 
```
mpiexec -n <num-threads> -f <path-to-machinefile> <executable-binary>
```
3. You must set-up passwordless ssh connections so that the MPI runtime can launch tasks on other machines without needing authentication for each machine. This involves SSH key generation and running an SSH agent. Please consult external resources on how to set this up. Here's one such resource to get you started: https://www.open-mpi.org/faq/?category=rsh 

-------------
## Added on 3/1/2022
The program `mpi_mmwrapper.c` and `matmul.c` is a demonstration of the wrapper code that should be linked to your parallel matrix multiplication implementation. The file provides file I/O routines that allow saving/retrieving data to/from the filesystem. These routines will be used for grading.  

The example format is a binary format that holds an arbitrary number of double-precision numbers. The format will be used directly for the matrix-multiplication problem. 

1. `int read_from_file(char * filename, double *data, int num-elements)` populates a buffer (pointed to by `data`) of `num-elements` double precision numbers by reading the values from file `filename`. It is important that the data be pre-allocated using malloc. 
2. `int write_to_file(char * filename, double *data, int num-elements)` writes out the contents of a buffer (pointed to by `data`) that holds `num-elements` double precision numbers to file `filename` in binary format. 

Because it is flat format (a linear sequence of numbers), any richer structure must be imposed by convention. A matrix of `NxN` dimensions is stored as flat sequence of N^2 numbers in row-major order. 

### Error checking
Because double-precision arithmetic is not precise, there can be small errors arising from executing operations in a different order than the sequential implementation. The wrapper includes code to measure and report the error. If the error is small, your code does not need further debugging.

### Compiling the code
The makefile includes targets to compile the wrapper with a simple sequential implementation. Your implementation must entirely be in `matmul.c`.

### Data files
You are provided two sets of data files for testing: `{a,b,c}.{4,512}.bin` 
The `a` and `b` files are the input matrices to be multiplied. the `c` files contain the matrix product. The two sets correspond to 4x4 and 512x512 matrix sizes respectively. Use the 4x4 set for debugging.

For any given `<size>`, copy the corresponding input files `{a,b}.<size>.bin` to `{a,b}.bin`. Further, copy `c.<size>.bin` to `golden.bin`. 

### Running the program
After the input files have been copied to `a.bin, b.bin`, and `golden.bin`, run the binary without any command line parameters as you would run any other MPI binary. (See the instructions for &pi; example.)

--------
### CHANGELOG 3/2/2022
Some changes and additional examples have been pushed. Here's a summary of changes. 
1. Two new files (`outer.c` and `inner.c`) have been added to illustrate how MPI behaves. To compile them, use `make functest`. To run it, use `make testrun`. This example highlights three key functionalities. 
    1. It shows SPMD (single program multiple data) behavior of the MPI runtime. The exact same code runs on all nodes. Even the code before `MPI_Init` and the code after `MPI_Finalize` is executed everywhere (see the pre-mpi and post-mpi printed statements). 
    2. It shows that MPI_Init can be called from within an external function. It doesn't have to be in `main()`.
    3. It shows how `MPI_Wtime` can be used to selectively measure time within the MPI code sections. 
  
2. There are other minor corrections. The matmul prototype now takes in `argc` and `argv` parameters as they're needed for `MPI_Init`.
