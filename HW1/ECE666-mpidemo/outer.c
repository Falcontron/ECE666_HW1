#include<stdio.h>
#include<stdlib.h>
#include<time.h>

extern void foo(int argc, char *argv[]);


main(int argc, char *argv[]) {
   printf("pre mpi\n");    // Because MPI uses the SPMD programming model, 
			   // the code executes in each process. 
			   // So you'll see this print execute multiple times.
   foo(argc,argv);         // All MPI is contained inside this function

   printf("post mpi\n");   // Same here. This code, which occurs after MPI_FINALIZE
			   // will execute multiple times
}


