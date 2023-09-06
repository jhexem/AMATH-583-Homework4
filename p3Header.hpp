#ifndef P3HEADER_HPP
#define P3HEADER_HPP

#include <mpi.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

double sequential_riemann_sum(double local_a, double local_b, int local_n);

#endif