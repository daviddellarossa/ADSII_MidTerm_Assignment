//
// Created by deedeeaar on 08/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_COMMON_H
#define MID_TERM_ASSIGNMENT_COMMON_H

#include <iostream>
#include "hashtable.h"

std::pair<int, int> proposal1(const unsigned long* matrix, size_t n, unsigned long g);

std::pair<int, int> proposal2(unsigned long* matrix, size_t n, unsigned long g);

std::pair<int, int> proposal3(unsigned long* matrix, size_t n, unsigned long g);

std::pair<int, int> proposal4(Hashtable& ht, unsigned int g);


#endif //MID_TERM_ASSIGNMENT_COMMON_H
