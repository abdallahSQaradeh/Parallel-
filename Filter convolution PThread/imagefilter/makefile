CC=g++
CFLAGS=-I
forMyComputer=--hostfile hostfile
all:	serial_edge serial_blur serial_sharpen  parallel_edge  parallel_blur parallel_sharpen

c1:
	g++ -o serial serialimage.cpp $^ 
c2: 
	$(CC) -o parallel parallelimagefilter.cpp -lpthread
serial_edge:	c1
	@./serial oimage.txt edge.txt serialedge.txt
parallel_edge:	c2
	@./parallel oimage.txt edge.txt paralleledge.txt

serial_blur:	c1
	@./serial oimage.txt blur.txt serialblur.txt
parallel_blur:	c2
	@./parallel oimage.txt blur.txt parallelblur.txt
serial_sharpen:	c1
	@./serial oimage.txt sharpen.txt serialsharpen.txt
parallel_sharpen:	c2
	@./parallel oimage.txt sharpen.txt parallelsharpen.txt	
clean:
	rm -f *.o *~ core
	rm serialp
	rm parallelp
	rm text2.txt
	rm new.txt