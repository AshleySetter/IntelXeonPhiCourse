SRC=MD.f control.f util.f
OBJ=$(SRC:.f=.o)

FFLAGS= -g
FC=ifort

all: MD

test: test.ok

MD: $(OBJ)
	$(FC) $(FFLAGS)  -o $@  $(OBJ)

clean:
	rm -f MD $(OBJ)

$(OBJ): coord.inc Makefile

MD.o: MD.f
	$(FC) $(FFLAGS) -c MD.f

control.o: control.f
	$(FC) $(FFLAGS) -c control.f

util.o: util.f
	$(FC) $(FFLAGS) -c util.f

output.dat: MD input.dat
	./MD

test.ok: MD input.dat output.dat Makefile
	rm test.ok
	if ../Test/diff-output output.dat ../Test/good.dat; then touch test.ok; fi


