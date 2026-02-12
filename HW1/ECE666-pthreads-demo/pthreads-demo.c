#include <pthread.h>
#include <stdio.h>



#define NUM_THREADS 32 

void * worker_function(void *tid) {
  printf("Worker thread id: %d got here\n", *((int *) tid));
}


int main()
{
  int i, tid[NUM_THREADS-1];

  /* 'worker_threads' points to all threads other than thread-0 */
  pthread_t worker_threads[NUM_THREADS-1];
  printf("Only thread zero exists at this point\n");

  for(i=0; i< NUM_THREADS-1; i++) {
    tid[i] = i+1;
    if(pthread_create(&worker_threads[i], NULL, worker_function, &tid[i])) {
      fprintf(stderr, "Error creating thread %d\n",i);
    }
  }
  printf("Only thread 0 gets here and waits for other threads\n");
  for(i=0; i< NUM_THREADS-1; i++) {
    pthread_join(worker_threads[i], NULL); 
  }
  printf("All threads have rejoined. Thread 0 exiting...\n");
}
