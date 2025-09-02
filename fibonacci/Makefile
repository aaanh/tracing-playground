default: build run

build:
	gcc main.c -o main.o -lm -finstrument-functions

build_no_inst:
	gcc main.c -o main.o

run:
	chmod +x main.o
	./main.o

