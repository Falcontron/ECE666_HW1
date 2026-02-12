#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


//#define DEBUG

#ifdef DEBUG
#define N 8
#define NUM_THREADS 2 
#endif

#ifndef DEBUG
#define N (128*1024*1024)
#define NUM_THREADS 8 
#endif

int Cin[NUM_THREADS] = {0};

#define TRIALS_PER_THREAD (N/NUM_THREADS)

int trial(struct drand48_data *rbuf) {
   double x, y, dist;
   drand48_r(rbuf, &x);
   drand48_r(rbuf, &y);
   dist = x*x+y*y;

#ifdef DEBUG
   printf("Point (%5.3f,%5.3f) is %5.3f away from the origin.\n", x, y, dist);
#endif

   if (dist <1.0) return 1; 
   else return 0;
}

void * worker_function(void *tid) {
   int i,local_sum=0;
   int bound = TRIALS_PER_THREAD;
   struct drand48_data rbuf;
   srand48_r(time(NULL) + (*(int *)tid), &rbuf); // private randomize seed
   for(i=0; i<bound; i++) {
     local_sum += trial(&rbuf);
   };
   Cin[*(int *) tid] += local_sum;
}

int main() {

   int i =0;
   int tid[NUM_THREADS];
   pthread_t worker_threads[NUM_THREADS-1];
   
   printf("Number of Monte Carlo trials: %d\n", N);
#ifdef DEBUG 
   printf("Launching %d threads with %d trials each.\n",NUM_THREADS,TRIALS_PER_THREAD);
#endif

   tid[0] = 0;
   for(i=1; i< NUM_THREADS; i++) {
     tid[i] = i;
     if(pthread_create(&worker_threads[i-1], NULL, worker_function, &tid[i])) {
       fprintf(stderr, "Error creating thread %d\n",i);
     }
   }

   worker_function(&tid[0]);
   for(i=0; i< NUM_THREADS-1; i++) {
     pthread_join(worker_threads[i], NULL); 
   }
   for(i=0; i< NUM_THREADS-1; i++) {
     Cin[0]+= Cin[i+1];
   }

   printf("Pi estimate : %5.6f\n", (double)Cin[0]*4.0/N);

}


