//
// Created by deedeeaar on 06/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_RADIX_SORT_H
#define MID_TERM_ASSIGNMENT_RADIX_SORT_H
#include <vector>
#include <cmath>

unsigned int tenPow(unsigned int pow);

void countingSortbyDigit(std::vector<unsigned long>::iterator begin, std::vector<unsigned long>::iterator end, unsigned int k);

void radixSort(std::vector<unsigned long>::iterator begin, std::vector<unsigned long>::iterator end, unsigned int numOfDigits);


#endif //MID_TERM_ASSIGNMENT_RADIX_SORT_H
