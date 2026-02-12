all: seq-pi pthreads-demo pthreads-pi

debug: 
	gcc -O2 seq-pi.c -o seq-pi -D DEBUG 
	gcc pthreads-demo.c -o pthreads-demo -D DEBUG -lpthread
	gcc pthreads-pi.c -o pthreads-pi -D DEBUG -lpthread

seq-pi: seq-pi.c 
	gcc seq-pi.c -o seq-pi 

pthreads-pi: pthreads-pi.c 
	gcc pthreads-pi.c -o pthreads-pi -lpthread

pthreads-demo: pthreads-demo.c
	gcc pthreads-demo.c -o pthreads-demo -lpthread

clean:
	rm pthreads-demo seq-pi pthreads-pi
