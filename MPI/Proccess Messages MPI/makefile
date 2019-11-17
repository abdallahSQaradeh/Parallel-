CC=mpic++
CFLAGS= -I
LIBS=
DEPS =
OBJ = hello.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -O3 -o $@ $^ $(CFLAGS) 

test1:
	mpirun -np 4 ./main

clean:
	rm -f *.o *~ core
