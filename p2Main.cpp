#include "p2Header.hpp"
#include <chrono>

int main(int argc, char* argv[]) {

   if (argc!=3) {
      std::cerr << "Usage: " << argv[0] << " numPoints numThreads" << std::endl;
      return 1;
   }

   const int numPoints = std::atoi(argv[1]);
   const int numThreads = std::atoi(argv[2]);

   double a = 1.0;
   double b = 6.0;
   
   auto start = std::chrono::high_resolution_clock::now();
   double length = threaded_function_length<double>(a, b, numPoints, numThreads);
   auto stop = std::chrono::high_resolution_clock::now();
   auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
   long double time = (long double)duration.count() / (long double)1000000000.0;
   /*
   std::ofstream outfile1;
   outfile1.open("times.csv", std::ios::app);
   outfile1 << time << "," << std::endl;
   outfile1.close();
   */

   double error = std::abs(length - (std::log(6.0) + 35.0/8.0));
   std::ofstream outfile2;
   outfile2.open("errors.csv", std::ios::app);
   outfile2 << error << "," << std::endl;
   outfile2.close();

   return 0;
}