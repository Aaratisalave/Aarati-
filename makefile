project: project.o
	cc project.o -o project
project.o: project.c project.h
	cc -Wall -c project.c
clean: 
	rm *.o
