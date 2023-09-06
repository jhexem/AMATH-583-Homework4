#include "p1Header.hpp"

template <typename T>
void write_binary(std::string filename, const std::vector<T> &matrix) {

   std::ofstream out(filename, std::ios::binary);

   int numEntries = matrix.size();
   for (int i=0; i<numEntries; i++) {

      out.write(reinterpret_cast<const char*>(&matrix[i]), sizeof(double));

   }
   out.close();
}

template <typename T>
void read_binary(std::string filename, std::vector<T> &empty_matrix) {

   std::ifstream in(filename, std::ios::binary);

   int numEntries = empty_matrix.size();
   for (int i=0; i<numEntries; i++) {

      in.read((char*) (&empty_matrix[i]), sizeof(double));

   }
   in.close();
}

template <typename T>
std::vector<T> create_square_matrix(int size) {

   int numEntries = size * size;
   std::vector<T>matrix(numEntries);

   std::random_device dev;
   std::mt19937 rng(dev());
   std::uniform_real_distribution<T> dist(0,1);

   for (int i=0; i<numEntries; i++) {
      T rNum = dist(rng);
      matrix[i] = rNum;
   }
   return matrix;
}

template <typename T>
void export_times_to_csv(std::vector<T> times) {
   std::ofstream file;
   file.open("times.csv");
   for (int i=0; i<times.size(); i++) {
      file << times[i] << "," << std::endl;
   }
   file.close();
}

template void write_binary(std::string filename, const std::vector<double> &matrix);
template void write_binary(std::string filename, const std::vector<long double> &matrix);
template void read_binary(std::string filename, std::vector<double> &empty_matrix);
template void read_binary(std::string filename, std::vector<long double> &empty_matrix);
template std::vector<double> create_square_matrix(int size);
template std::vector<long double> create_square_matrix(int size);
template void export_times_to_csv(std::vector<double> times);
template void export_times_to_csv(std::vector<long double> times);