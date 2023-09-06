#include "p3Header.hpp"

int main(int argc, char **argv) {

   MPI_Init(&argc, &argv);

   int rank, size;
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);

   double a = 1.0, b = 6.0;
   const int numPoints = std::atoi(argv[1]);

   double start = MPI_Wtime();

   double local_a = a + rank * (b - a) / size;
   double local_b = a + (rank + 1) * (b - a) / size;
   int local_n = numPoints / size;

   double local_sum = sequential_riemann_sum(local_a, local_b, local_n);

   double global_sum;
   MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

   double end = MPI_Wtime();
   double time = end - start;

   if (rank == 0) {
      std::cout << "Result: " << a << " to " << b << " = " << global_sum << std::endl;
      std::cout << "Time taken to execute: " << time << std::endl;

      std::ofstream outfile1;
      outfile1.open("times.csv", std::ios::app);
      outfile1 << time << "," << std::endl;
      outfile1.close();
      /*
      double error = std::abs(global_sum - (std::log(6.0) + 35.0/8.0));
      std::ofstream outfile2;
      outfile2.open("errors.csv", std::ios::app);
      outfile2 << error << "," << std::endl;
      outfile2.close();

      std::cout << "Error: " << error << std::endl;
      */
   }

   MPI_Finalize();
   return 0;
}