#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//#define DEBUG

#ifdef DEBUG
#define N 3
#endif

#ifndef DEBUG
#define N 3
#endif

#define BLOCK_SIZE 2
double A[N][N] = {0};

typedef struct {
    int start, end, k;
} targ;



void * worker_function(void *args) {
    targ *arg = (targ *)args;

    for (int i = arg->start; i <= arg->end; ++i){
        for (int j = arg->k + 1; j < N; ++j){
            A[i][j] -= A[i][arg->k] * A[arg->k][j];
        }
        A[i][arg->k] = 0.0;
    }
}

void eliminate () {                                // *triangularizc the NxN matrix A*/
    int tid[N];
    

    tid[0] = 0;
    for (int k = 0; k < N; ++k){                       // Hoop over all diagonal ( pivot ) dements*/
        for (int j = k+1; j < N; ++j){                  // for all elements in row of, and to the right of the pivot element*/
            A[k][j] /= A[k][k];               // divide  by pivot element*/
        }
        A[k][k] = 1.0;

        int num_threads = ((N - k + 1) + BLOCK_SIZE - 1) / BLOCK_SIZE;
        pthread_t worker_threads[num_threads];
        targ args[num_threads];

        for (int i = 0; i < num_threads; ++i){                      // for all rows below the pivot row*/
            args[i].start = i * BLOCK_SIZE + k + 1;
            if (args[i].start + BLOCK_SIZE - 1 < N){
                args[i].end = args[i].start + BLOCK_SIZE - 1;
            }
            else {
                args[i].end = N - 1;
            }
            
            args[i].k = k;

            if(pthread_create(&worker_threads[i], NULL, worker_function, &args[i])) {
                fprintf(stderr, "Error creating thread %d\n",i);
            }
        }

        for (int i = 0; i < num_threads; ++i){
            pthread_join(worker_threads[i], NULL);
        }
    } 
}

void print_matrix() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%10.2f ", A[i][j]);
        }
        printf("\n");
    }
}


int main()
{
    // example matrix
    double data[N][N] = {
        {2, 1, -1},
        {-3, -1, 2},
        {-2, 1, 2}
    };

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            A[i][j] = data[i][j];

    printf("Original Matrix:\n");
    print_matrix(A);

    eliminate(A);

    printf("After Elimination:\n");
    print_matrix(A);

    return 0;
}

