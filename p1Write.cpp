#include "p1Header.hpp"
#include <chrono>

int main() {

   int n_start = 32;
   int n_end = 16384;

   std::vector<long double> write_times;

   for (int n=n_start; n<=n_end; n*=2) {

      long int numBytes = n * n * sizeof(double);
      std::vector<double> matrix = create_square_matrix<double>(n);
      std::string filename = "matrix" + std::to_string(n) + ".bin";

      auto start = std::chrono::high_resolution_clock::now();
      write_binary<double>(filename, matrix);
      auto stop = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
      long double time = (long double)numBytes / ((long double)duration.count() / (long double)1000000000.0);
      write_times.push_back(time);
   }
   export_times_to_csv<long double>(write_times);

   return 0;
}