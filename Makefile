dimag-ka-dahi:
	mkdir -p bin
	gcc main.c -o bin/dimag-ka-dahi
debug:
	mkdir -p bin
	gcc main.c -o bin/dimag-ka-dahi -g -static -Wall
clean:
	rm -r bin
