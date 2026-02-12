#include<stdio.h>
#include<stdlib.h>
#include<time.h>

extern void matmul(double*, double*, double*, int, int,char*[]);

#ifdef DEBUG
#define NUM_ELEMENTS (4*4)
#define AFILE "a.4.bin"
#define BFILE "b.4.bin"
#define CFILE "c.4.bin"
#define LEADING_DIM 4
#else
#define AFILE "a.512.bin"
#define BFILE "b.512.bin"
#define CFILE "c.512.bin"
#define NUM_ELEMENTS (512*512)
#define LEADING_DIM 512
#endif

double *a, *b, *c;

int write_to_file(char * filename, double *data, int num) {
    FILE * fp;
    int write_count;
    fp = fopen(filename, "w");
    if (fp ==NULL) {
	printf("file not found: %s\n", filename);
	exit(-1);
    }
    write_count = fwrite( (const void*) data, sizeof(double),num,fp);
    if (write_count == num) {
	fclose(fp);
	return 1;
    } else {
	fclose(fp);
	return -1;
    }
} 

int read_from_file(char * filename, double *data, int num) {
    FILE * fp;
    int read_count;
    fp = fopen(filename, "rb");
    if (fp ==NULL) {
	printf("file not found: %s\n", filename);
	exit(-1);
    }
    read_count = fread( (void*) data, sizeof(double),num,fp);
    if (read_count == num) {
	fclose(fp);
	return 1;
    } else {
	printf("%d\n", read_count);
	fclose(fp);
	return -1;
    }
} 

main(int argc, char*argv[]) {
   int i;
   int write_success=0;
   int read_success=0;
   a = malloc(NUM_ELEMENTS*sizeof(double));
   b = malloc(NUM_ELEMENTS*sizeof(double));
   c = malloc(NUM_ELEMENTS*sizeof(double));

   read_success = read_from_file("a.bin", a, NUM_ELEMENTS);
   if(read_success == 1) {
	read_success = read_from_file("b.bin", b, NUM_ELEMENTS);
	if (read_success == 1) {
	   matmul(a, b, c, LEADING_DIM,argc,argv);
	}
   }
   read_success = read_from_file("golden.bin", a, NUM_ELEMENTS);
   if(read_success == 1) {
        double diff = 0; 
	for(int p=0; p<LEADING_DIM; p++) {
	   for(int q=0; q<LEADING_DIM; q++) {
	         diff += abs(*(c + p*LEADING_DIM + q) - *(a+p*LEADING_DIM+q));	
	   }
	}
	printf("Absolute error: %e\n",diff);
   }
//   write_success = write_to_file("c.bin", c, NUM_ELEMENTS);
#ifdef DEBUG
   for(i=0; i<NUM_ELEMENTS; i++) {
	printf("Computed: %6.4f; Golden: %6.4f\n",c[i],a[i]);
   }
#endif
   free(a);
   free(b);
   free(c);
    
}


