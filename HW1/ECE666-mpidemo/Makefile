all: mpi-pi mm mm-debug functest

mpi-pi: mpi-pi.c Makefile
	mpicc -O2 mpi-pi.c -o mpi-pi

run:
	mpiexec -n 4 -f machinefile mpi-pi

clean: 
	rm mpi-pi mm mm-debug functest

mm:
	mpicc mpi_mmwrapper.c matmul.c -o mm

mm-debug:
	mpicc -D DEBUG mpi_mmwrapper.c matmul.c -o mm-debug

functest:
	mpicc outer.c inner.c -o functest

testrun:
	mpiexec -n 4 -f machinefile functest
