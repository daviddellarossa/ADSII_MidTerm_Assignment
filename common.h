//
// Created by deedeeaar on 08/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_COMMON_H
#define MID_TERM_ASSIGNMENT_COMMON_H

#include <iostream>
#include "hashtable.h"

std::pair<int, int> proposal1(const int* matrix, const size_t n, const int g);

std::pair<int, int> proposal2(int* matrix, size_t n, int g);

std::pair<int, int> proposal3(int* matrix, size_t n, int g);

std::pair<int, int> proposal4(Hashtable& ht, unsigned int g);


#endif //MID_TERM_ASSIGNMENT_COMMON_H
