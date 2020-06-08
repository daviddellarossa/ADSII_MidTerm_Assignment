//
// Created by deedeeaar on 08/06/2020.
//

#include "radix_sort.h"
unsigned int tenPow(unsigned int pow){
    if(pow > 0)
        return 10 * tenPow(--pow);
    return 1;
}

void countingSortbyDigit(int* array, size_t n, int k){
    std::vector<int> vecC(10, 0);
    unsigned int divisor = tenPow(k) ;

    for(auto i = 0; i < n; ++i){
        ++vecC[(unsigned(array[i] / divisor)) % 10];
    }

    for(auto i = 1; i < vecC.size(); i++){
        vecC[i] += vecC[i-1];
    }

    std::vector<int> vecB(n, 0);
    for(int i = n - 1; i >= 0; i--){
        auto value = (unsigned(array[i] / divisor)) % 10;
        vecB[vecC[value]-1] = array[i];
        --vecC[value];
    }

    std::copy(vecB.cbegin(), vecB.cend(), array);
}

void radixSort(int* vecA, size_t n, int numOfDigits){
    --numOfDigits;
    if(numOfDigits > 0){
        radixSort(vecA, n, numOfDigits);
    }
    countingSortbyDigit(vecA, n, numOfDigits);
}
