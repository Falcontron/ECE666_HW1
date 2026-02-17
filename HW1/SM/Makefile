all: blocked

debug: 
	gcc -O2 gaussian-blocked.c -o gaussian-blocked -D DEBUG -lpthread

blocked: gaussian-blocked.c 
	gcc gaussian-blocked.c -o gaussian-blocked -lpthread
	gcc gaussian-interleaved.c -o gaussian-interleaved -lpthread

interleaved: 
	./gaussian-interleaved 16

run: gaussian-blocked 
	./gaussian-blocked 16

time: gaussian-blocked 
	time ./gaussian-blocked 8

clean:
	rm gaussian-blocked
