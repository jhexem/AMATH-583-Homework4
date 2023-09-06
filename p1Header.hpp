#ifndef P1HEADER_HPP
#define P1HEADER_HPP

#include <vector>
#include <fstream>
#include <iostream>
#include <random>
#include <string>

template <typename T>
void write_binary(std::string filename, const std::vector<T> &matrix);
template <typename T>
void read_binary(std::string filename, std::vector<T> &empty_matrix);
template <typename T>
std::vector<T> create_square_matrix(int size);
template <typename T>
void export_times_to_csv(std::vector<T> times);

#endif