#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"
#include<time.h>

#define N (128*1024*1024)
#define NUM_PROCESSES 4
 
/* The code for each trial is identical to the sequential version **/
int trial() {
   double x, y, dist;
   x = drand48();
   y = drand48();
   dist = x*x+y*y;

   if (dist <1.0) return 1; 
   else return 0;
}

int main(int argc, char* argv[])
{
    int niter = N/NUM_PROCESSES;
    int myid;                       //holds process's rank id
    double x,y;                     //x,y value for the random coordinate
    int i;
    int Cin=0;                //Count holds all the number of how many good coordinates
    double pi;                      //holds approx value of pi
    int reduced_Cin;                   //total number of "good" points from all nodes
    int reduced_niter;                   //total number of ALL points from all nodes
 
    srand48(time(NULL));                //Give drand48() a seed value
    MPI_Init(&argc, &argv);                 //Start MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           //get rank of node's process
 
    for (i=0; i<niter; ++i) {                 //main loop
       Cin+= trial();
    }
 
    MPI_Reduce(&Cin,                     // scalar value at each process being reduced
                   &reduced_Cin,         // variable that holds the reduced (summed) Cin
                   1,                    // count of number data items sent
                   MPI_INT,		 // datatype of communicated value
                   MPI_SUM,              // type of reduction
                   0,                    // This means that the reduced value will be available
					 // at the Rank-0 process 
                   MPI_COMM_WORLD);      // Ignore this for now. 

    /* This reduction is not really necessary because we know the total number of trials.
         By construction this reduction will always yield 128M. 
     */
    MPI_Reduce(&niter,
                   &reduced_niter,
                   1,
                   MPI_INT,
                   MPI_SUM,
                   0,
                   MPI_COMM_WORLD);
 
    if (myid == 0)                      //if root process
    {
        pi = ((double)reduced_Cin/(double)reduced_niter)*4.0;               //p = 4(m/n)
        printf("Pi: %5.6f\n%i\n%d\n", pi, reduced_Cin, reduced_niter);
        //Print the calculated value of pi
         
    }
              
    MPI_Finalize();                     //Close the MPI instance
    return 0;
}


