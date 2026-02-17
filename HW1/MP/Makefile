all: blocked 

debug: 
	gcc -O2 gaussian-blocked.c -o gaussian-blocked -D DEBUG -lpthread

blocked: gaussian-blocked.c Makefile
	mpicc -O2 gaussian-blocked.c -o gaussian-blocked
	mpicc -O2 gaussian-asynch.c -o gaussian-asynch
	mpicc -O2 gaussian-interleaved.c -o gaussian-interleaved

asynch: 
	mpiexec -n 16 -f machinefile gaussian-asynch

interleaved:
	mpiexec -n 16 -f machinefile gaussian-interleaved

run:
	mpiexec -n 16 -f machinefile gaussian-blocked

time:
	time mpiexec -n 1 -f machinefile gaussian-blocked

clean:
	rm gaussian-blocked

# export PATH=/opt/gcc/6.1.0/bin:/home/yara/mithuna2/mpich-install/bin:$PATH
# export LD_LIBRARY_PATH=/opt/gcc/6.1.0/lib64:/package/intel_alt/12.0.0/x86_64-Linux/composerxe-2011.0.084/compiler/lib/intel64:/home/yara/mithuna2/mpich-install/lib:$LD_LIBRARY_PATH

