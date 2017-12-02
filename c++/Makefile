#### Makefile for MPI-OpenMP example

EXENAME  = main
CXX     = mpiicpc # this is using the intel compiler
CPPFLAGS = -std=c++11  -O3 -qopenmp 

$(EXENAME): clean main.o 
	$(CXX) $(CPPFLAGS) -o $(EXENAME)  main.o 

all: $(EXENAME)
	 
clean:
	rm -f $(EXENAME) *.o

######## End of Makefile ########

