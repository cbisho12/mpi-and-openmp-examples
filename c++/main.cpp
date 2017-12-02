/* ***************************************************
 *  Authors:Chris Bishop 
 *  Data:Nov 10, 2017
 *  Platform: linux
 *  Language: C++
 *  -- Testing MPI with openMP --  
 * -- compile with: make all
 * -- run with: mpiexec -n # ./main N
 * -- where above # is the number of mpi processes and N is the size of the array
 * example output for np=2, openMP threads=2, N=1000000 on i7 5820K:
   rank  sum (= 0)  time in sec
   0        0       29.3929
   1        0       29.3797
 *****************************************************/
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <mpi.h>
#include <omp.h>
using namespace std;

int main(int argc, char *argv[]) {

  int rank;
  int ierr;
  int np, N=1, sumA=0;
  vector<int> A; 
    N = stoi(argv[1]);
  // initialize the MPI context
   ierr = MPI_Init ( &argc, &argv );
  // get the number of MPI processes
   ierr = MPI_Comm_size ( MPI_COMM_WORLD, &np );
  // get the id (rank) of each MPI process
   ierr = MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
   omp_set_num_threads(2);
   A.resize(N);
   std::fill(A.begin(),A.end(),1);
   double start_time = omp_get_wtime();
   // the point of these loops is to take up time and test reduction loop using openMP
   // by adding 1 many times and reseting back to zero
   #pragma omp parallel for reduction(+ : sumA) 
   for (int i=0;i<N;i++) {                     
      for (int j=0;j<N;j++) {
       sumA += A[i];  // just adding 1 to sum N times
      }
      sumA -= N;   // subtract off N to reset back to zero 
   }
   double time = omp_get_wtime() - start_time;
   if (rank == 0) {
       cout<<"rank  "<<"sum (= 0)"<<"  "<<"time in sec"<<endl;
   }
   MPI_Barrier( MPI_COMM_WORLD );
   cout<<rank<<"        "<<sumA<<"       "<<time<<endl;
   // Finalize the MPI environment
   MPI_Finalize();

    return 0;
} // main
