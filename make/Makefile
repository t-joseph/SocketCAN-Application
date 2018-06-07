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
PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
#EXE = Gui


all: radar_rec

radar_rec : main.o modules.o  
	$(CC) $(CFLAGS) `pkg-config --cflags gtk+-3.0` -o ../bin/radar_rec main.o modules.o -L/usr/local/lib -lm `pkg-config --libs gtk+-3.0`

main.o : $(SRC)main.c $(INC)radar.h
	 $(CC) -c $(CFLAGS) `pkg-config --cflags gtk+-3.0`  $(SRC)main.c `pkg-config --libs gtk+-3.0`

modules.o : $(SRC)modules.c $(INC)radar.h
	$(CC) -c $(CFLAGS) $(SRC)modules.c

clean :
	rm *.o
	rm ../bin/radar_rec

debug :
	gdb ./Current -x gdb_command






