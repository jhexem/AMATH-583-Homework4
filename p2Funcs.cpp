#include "p2Header.hpp"


template <typename T>
T threaded_function_length(T a, T b, const int numPoints, const int numThreads) {

   T dx = (b - a) / numPoints;
   T sum = 0.0;
   std::vector<std::thread> threads(numThreads);

   std::mutex sum_mutex;

   for (int i=0; i<numThreads; i++) {

      threads[i] = std::thread(threaded_partial_length<T>, std::ref(sum), std::ref(sum_mutex), a, dx, numPoints, numThreads, i);
   }

   for (int i=0; i<numThreads; i++) {
      threads[i].join();
   }

   return sum;
}

template <typename T>
void threaded_partial_length(T &sum, std::mutex &sum_mutex, T a, T dx, int numPoints, int numThreads, int i) {

   T partial_sum = 0.0;
   int start = (numPoints / numThreads) * i;
   int end = (i == numThreads - 1) ? numPoints : (numPoints / numThreads) * (i + 1);

   for (int j=start; j<end; j++) {

      T x = a + j * dx;
      partial_sum += (1 / x) + (x / 4);

   }

   partial_sum *= dx;

   sum_mutex.lock();
   sum += partial_sum;
   sum_mutex.unlock();
}

template double threaded_function_length(double a, double b, const int numPoints, const int numThreads);
template void threaded_partial_length(double &sum, std::mutex &sum_mutex, double a, double dx, int numPoints, int numThreads, int i);