CC = gcc

CFLAGS = -Wall

all : mynl mycat mycp pessoas

pessoas : pessoas.o

pessoas.o : pessoas.c

mynl : mynl.o

mynl.o : mynl.c

mycp : mycp.o

mycp.o : mycp.c

mycat : mycat.o

mycat.o : mycat.c

clean :
	@rm *.o
	@rm mynl
	@rm mycat
	@rm mycp
	@rm pessoas