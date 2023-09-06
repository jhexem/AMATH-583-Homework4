#ifndef P2HEADER_HPP
#define P2HEADER_HPP

#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <fstream>
#include <cmath>

template <typename T>
T threaded_function_length(T a, T b, const int numPoints, const int numThreads);
template <typename T>
void threaded_partial_length(T &sum, std::mutex &sum_mutex, T a, T dx, int numPoints, int numThreads, int i);

#endif