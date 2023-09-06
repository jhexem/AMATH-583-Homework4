#include "p3Header.hpp"


double sequential_riemann_sum(double local_a, double local_b, int local_n) {

   double dx = (local_b - local_a) / local_n;
   double sum = 0.0;

   for (int i=0; i<local_n; i++) {

      double x = local_a + i * dx;
      sum += ((1/x) + (x/4)) * dx;
   }
   
   return sum;
}