CC=icpc

COPT=-g -openmp

pi: pi.c mytime.c mytime.h
	$(CC) -o pi $(COPT) -xhost pi.c mytime.c

clean:
	rm -f *.o pi pi
