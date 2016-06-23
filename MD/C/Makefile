SRC=MD.c control.c util.c
OBJ=$(SRC:.c=.o)
CFLAGS= -g 
CC= icc

all: MD

test: test.ok

MD: $(OBJ)
	$(CC) $(CFLAGS)  -o $@  $(OBJ) -lm


output.dat: MD input.dat
	./MD

test.ok: MD input.dat output.dat Makefile
	rm test.ok
	if ../Test/diff-output output.dat ../Test/good.dat; then touch test.ok; fi


clean:
	rm -f start MD $(OBJ) start.o

$(OBJ) start.o: coord.h Makefile


