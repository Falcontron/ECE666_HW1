#include<stdio.h>
#include<mpi.h>

void foo(int argc, char*argv[]) {
    int myid, useless_counter=0;                       //holds process's rank id
    double starttime, endtime;
    
    MPI_Init(&argc, &argv);                 //Start MPI
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);           //get rank of node's process

    if(myid == 0) {starttime = MPI_Wtime();}
 
    printf("printing from %d\n", myid);
    for(int i = 0; i++; i< 100000) {
	useless_counter += i*i;
    }
              
    MPI_Barrier(MPI_COMM_WORLD);
    if(myid == 0) {
       endtime = MPI_Wtime();
       printf("Elapsed time : %8.4f\n", endtime-starttime);
    }
    MPI_Finalize();                     //Close the MPI instance
}

