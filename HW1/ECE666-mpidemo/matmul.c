
void matmul(double* a, double *b, double *c, int n, int argc, char*argv[]) {
	// Sequential code shown. SPAWN MPI PROCESSES HERE.
	int i, j, k;
	for(i = 0; i<n; i++) {
		for(j = 0; j<n; j++) {
			double tmp = 0;
			for(k = 0; k<n; k++) {
				tmp += *(a+i*n+k) * *(b+k*n+j);	 	
			}
			*(c+i*n+j) = tmp;
		}
	}
	// JOIN ALL MPI PROCESSES HERE
	return;
}

