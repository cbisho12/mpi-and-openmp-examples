# mpi-scatterv.py
# run with:  mpiexec -n 4 python mpi-scatterv.py
#  example output with v_size = 24, n_pr = 4:
#  0 [ 0.  1.  2.  3.  4.  5.]
#  1 [  6.   7.   8.   9.  10.  11.]
#  2 [ 12.  13.  14.  15.  16.  17.]
#  3 [ 18.  19.  20.  21.  22.  23.]

from mpi4py import MPI
import numpy as np
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
v_size = 24 

n_pr = MPI.COMM_WORLD.Get_size() # get total # of processors
rank = MPI.COMM_WORLD.Get_rank() # get the process id #

my_size = v_size // n_pr     # split the vector into equal chucks for each
my_offset = comm.rank*my_size

A_vec = np.zeros(v_size)
B_vec = np.zeros(v_size)
local_vec = np.zeros(my_size) #local array

if rank == 0:    # initialize array with values 0 to v_size-1
	A_vec= np.linspace(0,v_size-1,v_size)

send_counts=np.full(n_pr,my_size)  #number of elements to send to each process
displ_vec = [x*my_size for x in range(n_pr)] # displacements from start to send to each process
comm.Scatterv([A_vec,send_counts,displ_vec,MPI.DOUBLE], local_vec, root=0) # scatter the vector to the other processes

# print out the process's rank and its local vector in order
for x in range(n_pr):
	if (rank==x):
		print rank, local_vec
	comm.Barrier()






