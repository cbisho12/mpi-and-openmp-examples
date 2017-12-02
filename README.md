# mpi-and-openmp-examples

In the python folder:

mpi-scatterv.py - This code is an example of the mpi-scatterv function.
It uses the mpi4py package in python to utilize MPI. It creates an array on the root process
and then distributes pieces to the other processes. Then each process prints out its ID # and 
its local arrray.

In the C++ folder:

main.cpp - This code uses both MPI processes and openMP threads.
Each MPI process calculates out the same code and launches its own threads.
It uses openMP reduction to add elements of an array. Then each MPI process
prints out its results. 

Makefile- make file to compile main.cpp (use make all to compile)
