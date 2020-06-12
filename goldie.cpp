//
// Created by deedeeaar on 08/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_GOLDIE_H
#define MID_TERM_ASSIGNMENT_GOLDIE_H

#include "constants.h"
#include <iostream>
#include "radix_sort.h"
#include "hashtable.h"


std::pair<int, int> proposal1(const unsigned long* matrix, size_t n, unsigned long g){
    for(auto i = 0; i < n; ++i){ //row
        for(auto j = 0; j < n; ++j){ //column
            if(matrix[i*n + j] == g){
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

#endif //MID_TERM_ASSIGNMENT_GOLDIE_H



int binary_search(unsigned long* array, size_t n, unsigned long g){
    unsigned long min=0, max = n-1;
    while(min <= max){
        auto mid = (max + min) / 2;
        if(array[mid] == g) return mid;
        else if(array[mid] > g) max = mid -1;
        else min = mid + 1;
    }
    return -1;
}

std::pair<int, int> proposal2(unsigned long* matrix, size_t n, unsigned long g){
    for(auto i = 0; i < n; ++i){
        radixSort(&matrix[i*n], n, MAX_LENGTH);
        auto bSearchResult = binary_search(&matrix[i*n], n, g);
        if(bSearchResult != -1){
            return std::make_pair(i, bSearchResult);
        }
    }
    return std::make_pair(-1, -1);
}

unsigned long binary_search_row(const unsigned long* array, size_t n, unsigned long g){
    unsigned long min = 0, max = n;
    while(min <= max){
        unsigned long mid = (max + min) / 2;
        /** If first element of the row is greater than g, then reset max and continue */
        if(array[mid*n] > g){
            max = mid - 1;
            continue;
        }else{ /** If first element of the row is less than g */
            /** If last element of the row is goe g, I found the row */
            if(array[mid*n + (n-1)] >= g){
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

std::pair<int, int> proposal3(unsigned long* matrix, size_t n, unsigned long g){
//    std::cout << printMatrix(matrix, n);
    radixSort(matrix, n * n, MAX_LENGTH);
//    std::cout << printMatrix(matrix, n);
    auto rowIndex = binary_search_row(matrix, n, g);
    if(rowIndex == -1) return std::make_pair(-1, -1);
    auto colIndex = binary_search(&matrix[rowIndex*n], n, g);
    if(colIndex == -1) return std::make_pair(-1, -1);
    return std::make_pair(rowIndex, colIndex);
}

std::pair<int, int> proposal4(Hashtable& ht, unsigned int g){
    return ht.find(g);
}
