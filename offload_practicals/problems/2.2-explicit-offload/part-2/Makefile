CXX = icpc
CXXFLAGS = 

OBJECTS = offload.o worker.o

.SUFFIXES: .o .cpp

.cpp.o:
	$(CXX) -c $(CXXFLAGS) -o "$@" "$<"

all: runme

runme: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o runme $(OBJECTS)

clean: 
	rm -f *.o runme
