project : project.o
	cc *.o -o project.c

project.o : project.c project.h
		cc -c project.c -wall

