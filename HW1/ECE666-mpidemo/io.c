#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#ifdef DEBUG
#define NUM_ELEMENTS (4*4)
#else
#define NUM_ELEMENTS (512*512)
#endif

double *a, *b;

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

main() {
   int i;
   int write_success=0;
   int read_success=0;
   srand48(time(NULL));
   a = malloc(NUM_ELEMENTS*sizeof(double));
   b = malloc(NUM_ELEMENTS*sizeof(double));
   for(i = 0; i<NUM_ELEMENTS; i++) {
	*(a+i) = drand48();

#ifdef DEBUG
	printf("%6.4f\n", a[i]);
#endif

   }
   write_success = write_to_file("a.bin",a,NUM_ELEMENTS);
   if(write_success ==1) printf("Successfully written.\n");
   read_success = read_from_file("a.bin",b,NUM_ELEMENTS);
   if(read_success == 1) {
	for(i=0; i<NUM_ELEMENTS; i++) {
	   if (b[i] != a[i]) break;
#ifdef DEBUG
	   printf("%6.4f\n", b[i]);
#endif
	}
	if(i==NUM_ELEMENTS) {
	  printf("integrity verified. All %d elements match.\n", NUM_ELEMENTS);
	} else {
	  printf("Mismatch at element %d (a[%d] = %6.4f; b[%d] = %6.4f;)\n",
		i, i, a[i], i, b[i]);
	}
   }
   free(a);
   free(b);
}


