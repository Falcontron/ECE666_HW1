all: blocked

debug: 
	gcc -O2 gaussian-blocked.c -o gaussian-blocked -D DEBUG -lpthread

blocked: gaussian-blocked.c 
	gcc gaussian-blocked.c -o gaussian-blocked -lpthread

clean:
	rm gaussian-blocked
