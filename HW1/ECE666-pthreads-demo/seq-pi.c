#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG

#ifdef DEBUG
#define N 4
#endif

#ifndef DEBUG
#define N (128*1024*1024)
#endif


int trial() {
   double x, y, dist;
   x = drand48();
   y = drand48();
   dist = x*x+y*y; //sqrt is unnecessary because we don't actually need the distance.
                   // We only need to know whether distance is less than one.
                   // It turns out that if dist < 1.0 ==> dist^2 < 1.0
                   // As such, we don't need it.

#ifdef DEBUG
   printf("Point (%5.3f,%5.3f) is %5.3f away from the origin.\n", x, y, dist);
#endif

   if (dist <1.0) return 1; 
   else return 0;
}

int main() {

   int i =0;
   int Cin = 0;

#ifndef DEBUG
   srand48(time(NULL)); // randomize seed
#endif

   printf("Number of Monte Carlo trials: %d\n", N);
   for(i=0; i<N; i++) {
	Cin += trial();
   };
   printf("Pi estimate : %5.6f\n", (double)Cin*4.0/N);

}
