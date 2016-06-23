CXX = icpc
CXXFLAGS = -qopt-report=5

OBJECTS = worker.o main.o

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"

all: runme

runme: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o runme $(OBJECTS)

clean: 
	rm -f *.o runme
