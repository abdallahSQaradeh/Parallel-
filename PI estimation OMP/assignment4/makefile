CC=g++
CFLAGS=-I
forMyComputer=--hostfile hostfile
all:	parallelpi

c1:
	 g++ -std=c++11  -fopenmp -o pi pi.cpp $^ 

parallelpi:	c1
	@./pi