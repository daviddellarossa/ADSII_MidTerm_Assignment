//
// Created by deedeeaar on 08/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_GOLDIE_H
#define MID_TERM_ASSIGNMENT_GOLDIE_H

#include "constants.h"
#include <iostream>
#include "radix_sort.h"
#include "hashtable.h"
#include "algorithm"
#include "mergeSort.h"
#include "quickSort.h"


std::pair<int, int> proposal1(const std::vector<unsigned long>& matrix, unsigned long g){
    for(auto i = 0; i < MATRIX_SIZE; ++i){ //row
        for(auto j = 0; j < MATRIX_SIZE; ++j){ //column
            if(matrix[i*MATRIX_SIZE + j] == g){
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

#endif //MID_TERM_ASSIGNMENT_GOLDIE_H

std::pair<int, int> proposal2(std::vector<unsigned long>& matrix, unsigned long g){
    for(auto i = 0; i < MATRIX_SIZE; ++i){
        auto begin = matrix.begin() +(i*MATRIX_SIZE);
        auto end = begin + MATRIX_SIZE;
//       radixSort(begin, end, MAX_LENGTH);
//         mergeSort(begin, end);
//        quicksort(begin, end);
        std::sort(begin, end);
        auto bSearchResult = std::lower_bound(begin, end, g);
        if(*bSearchResult == g){
            return std::make_pair(i, bSearchResult-begin);
        }
    }
    return std::make_pair(-1, -1);
}

unsigned long binary_search_row(std::vector<unsigned long>::iterator begin, std::vector<unsigned long>::iterator end, unsigned long g){
    unsigned long min = 0, max = MATRIX_SIZE;
    while(min <= max){
        unsigned long mid = (max + min) / 2;
        /** If first element of the row is greater than g, then reset max and continue */
        if(*(begin + mid*MATRIX_SIZE) > g){
            max = mid - 1;
            continue;
        }else{ /** If first element of the row is less than g */
            /** If last element of the row is goe g, I found the row */
            if(*(begin + mid*MATRIX_SIZE + (MATRIX_SIZE-1)) >= g){
                /** Return the row index */
                return mid;
            }else{
                /** Reset min and continue */
                min = mid+1;
            }
        }
    }
    /** Row not found */
    return -1;
}

std::pair<int, int> proposal3(std::vector<unsigned long>& matrix, unsigned long g){
//    radixSort(matrix.begin(), matrix.end(), MAX_LENGTH);
//  mergeSort(matrix.begin(), matrix.end());
//  quicksort(matrix.begin(), matrix.end());
  std::sort(matrix.begin(), matrix.end());
    auto rowIndex = binary_search_row(matrix.begin(), matrix.end(), g);
    if(rowIndex == -1) return std::make_pair(-1, -1);
    auto begin = matrix.begin()+(rowIndex*MATRIX_SIZE);
    auto end = begin + MATRIX_SIZE;
    auto itemIndex = std::lower_bound(begin, end, g);
    if(*itemIndex == g){
        return std::make_pair(rowIndex, (itemIndex-begin)%MATRIX_SIZE);
    }
    return std::make_pair(-1, -1);
}

std::pair<int, int> proposal4(Hashtable& ht, unsigned int g){
    return ht.find(g);
}
