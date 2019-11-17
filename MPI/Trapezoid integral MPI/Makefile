	
CC=mpic++
CFLAGS= 
DEPS = 
sOBJ = integrate.o  func.o mpi_integrate_v1.o mpi_integrate_v2.o mpi_integrate_v3.o


%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

integrate: integrate.o func.o
	g++ -o $@ $^ $(CFLAGS)

mpi_integrate_v1: mpi_integrate_v1.o func.o
	mpic++ -o $@ $^ $(CFLAGS)

mpi_integrate_v2: mpi_integrate_v2.o func.o
	$(CC)  -o $@ $^ $(CFLAGS)
			
mpi_integrate_v3: mpi_integrate_v3.o func.o
	$(CC)  -o $@ $^ $(CFLAGS)	

test1: integrate
			./integrate 1 4 100

test2: mpi_integrate_v1
			mpirun  -np 4 ./mpi_integrate_v1 1 4 100

test3: mpi_integrate_v2
			mpirun  -np 4 ./mpi_integrate_v2 1 4 100

test4: mpi_integrate_v3
			mpirun  -np 4 ./mpi_integrate_v3 1 4 100

clean:
			rm -f *.o *~ core
