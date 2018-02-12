KULINA=/usr
#CC	=g++ -pthread
CC	=cc -pthread
sample1	: sample1.o sample1Callbacks.o main.o
	 $(CC) -o sample1 sample1.o sample1Callbacks.o main.o -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread -lz -lbz2 -lGL
sample1.o	: sample1.c 
	 $(CC) -c sample1.c
sample1Callbacks.o	: sample1Callbacks.c 
	 $(CC) -c sample1Callbacks.c
main.o	: main.c 
	 $(CC) -c main.c
clean	:  
	   rm -f *.o sample1
