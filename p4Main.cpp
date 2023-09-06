#include <mpi.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

template <typename T>
void my_broadcast(T* data, int count, int root, MPI_Comm comm) {

   int rank, size;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   if (rank == root) {
      for (int i=0; i<size; i++) {
         if (i != root) {
            MPI_Send(data, count, MPI_BYTE, i, 0, comm);
         }
      }
   }
   else {
      MPI_Recv(data, count, MPI_BYTE, root, 0, comm, MPI_STATUS_IGNORE);
   }
   MPI_Barrier(comm);
}


int main(int argc, char **argv) {

   MPI_Init(&argc, &argv);

   int rank, size;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   const int numBytes = std::atoi(argv[1]);
   int numDoubles = numBytes / sizeof(double);

   std::vector<double>vec(numDoubles);

   if (rank == 0) {
      for (int i=0; i<numDoubles; i++) {
         vec[i] = i+1;
      }
   }

   double start = MPI_Wtime();

   my_broadcast<double>(vec.data(), numBytes, 0, MPI_COMM_WORLD);

   double end = MPI_Wtime();
   double time = end - start;

   if (rank == 0) {
      std::ofstream outfile1;
      outfile1.open("p4times.csv", std::ios::app);
      outfile1 << time << "," << std::endl;
      outfile1.close();
   }

   MPI_Finalize();
   return 0;
}