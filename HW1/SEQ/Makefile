all: seq

debug: 
	gcc -O2 gaussian-seq.c -o gaussian-seq -D DEBUG 

seq: gaussian-seq.c 
	gcc gaussian-seq.c -o gaussian-seq 

clean:
	rm gaussian-seq
