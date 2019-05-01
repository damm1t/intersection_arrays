#ifndef ARRAY_CHECKER_H
#define ARRAY_CHECKER_H

#include <vector>
#include <iostream>


using std::vector;

const size_t SMALL_SIZE = 1024;
const size_t TINY_SIZE = 10;

size_t intersection(const vector<int> &lhs, const vector<int> &rhs);

#endif // ARRAY_CHECKER_H
