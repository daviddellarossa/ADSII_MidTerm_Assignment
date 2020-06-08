//
// Created by deedeeaar on 06/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_RADIX_SORT_H
#define MID_TERM_ASSIGNMENT_RADIX_SORT_H
#include <vector>
#include <cmath>

unsigned int tenPow(unsigned int pow);

void countingSortbyDigit(int* array, size_t n, int k);

void radixSort(int* vecA, size_t n, int numOfDigits);


#endif //MID_TERM_ASSIGNMENT_RADIX_SORT_H
