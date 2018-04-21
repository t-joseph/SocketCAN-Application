#
# Linux makefile
# Use with make 
#

.SUFFIXES: .o .asm .c

AS=as
ASFLAGS= -g -o
CFLAGS= -g 
CC=gcc
SRC=../src/
INC=../inc/


all: radar_rec

radar_rec : main.o modules.o  
	$(CC) $(CFLAGS) -o ../bin/radar_rec main.o modules.o -L/usr/local/lib -lm   

main.o : $(SRC)main.c $(INC)radar.h
	 $(CC) -c $(CFLAGS) $(SRC)main.c

modules.o : $(SRC)modules.c $(INC)radar.h
	$(CC) -c $(CFLAGS) $(SRC)modules.c

clean :
	rm *.o
	rm ../bin/radar_rec

debug :
	gdb ./Current -x gdb_command

