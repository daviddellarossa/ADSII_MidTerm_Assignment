//
// Created by deedeeaar on 08/06/2020.
//

#include "radix_sort.h"
unsigned int tenPow(unsigned int pow){
    if(pow > 0)
        return 10 * tenPow(--pow);
    return 1;
}

void countingSortbyDigit(std::vector<unsigned long>::iterator begin, std::vector<unsigned long>::iterator end, unsigned int k){
    std::vector<int> vecC(10, 0);
    unsigned int divisor = tenPow(k) ;
    for(auto b = begin, e = end; b < e; ++b){
        ++vecC[(unsigned(*b / divisor)) % 10];
    }
    for(auto i = 1; i < vecC.size(); i++){
        vecC[i] += vecC[i-1];
    }
    std::vector<long> vecB(end - begin, 0);
    for(auto b = begin, e = end-1 ; e >= b; --e ){
        auto value = (unsigned(*e / divisor)) % 10;
        vecB[vecC[value]-1] = *e;
        --vecC[value];
    }
    std::copy(vecB.cbegin(), vecB.cend(), begin);
}

void radixSort(std::vector<unsigned long>::iterator begin, std::vector<unsigned long>::iterator end, unsigned int numOfDigits){
    --numOfDigits;
    if(numOfDigits > 0){
        radixSort(begin, end, numOfDigits);
    }
    countingSortbyDigit( begin,  end, numOfDigits);
}
