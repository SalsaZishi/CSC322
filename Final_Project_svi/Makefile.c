/* Makes the ./svi executable 

#    Makefile for the Modular program

svi:	svi.o parseCommands.o editCommands.o
	gcc -o svi svi.o parseCommands.o editCommands.o

svi.o:	svi.c
	gcc -c svi.o

parseCommands.o:	parseCommands.c parseCommands.h
	gcc -c parseCommands.c

editCommands.o:	editCommands.c editCommands.h
	gcc -c editCommands.c
