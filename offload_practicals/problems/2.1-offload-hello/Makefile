CC=icpc

COPT=-g -openmp -xHost

pi: pi.c mytime.c mytime.h
	$(CC) -o pi $(COPT) pi.c mytime.c

clean:
	rm -f *.o pi pi
