#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <thread>

template <class Iterator>
Iterator partition(Iterator begin, Iterator end);

template <class Iterator>
void quicksort(Iterator begin, Iterator end);

template <class Container>
void quicksort(Container& vec){
    quicksort(vec.begin(), vec.end());
}


template <class Iterator>
void quicksort(Iterator begin, Iterator end){
    if(begin < end - 1){
        auto p = partition(begin, end);
        quicksort(begin, p);
        quicksort(p + 1, end);
    }
}

template <class Iterator>
Iterator partition(Iterator begin, Iterator end) {
    auto i = begin, j = i - 1;
    auto pivot = end - 1;
    for(; i < end - 1; i++){
        if(*i < *pivot){
            std::iter_swap(i, ++j);
        }
    }
    std::iter_swap(pivot, ++j);
    return j;
}


