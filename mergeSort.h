//
// Created by deedeeaar on 30/05/2020.
//
#include <vector>
#include <algorithm>
#include <cmath>

template<typename Iterator>
void mergeSort(Iterator begin, Iterator end);

template<typename Iterator>
void merge(Iterator begin, Iterator mid, Iterator end);

template<typename Container>
void mergeSort(Container& cont){
    mergeSort(cont.begin(), cont.end());
}

template<typename Iterator>
void mergeSort(Iterator begin, Iterator end){
    if(begin >= end - 1) return;
    auto mid = begin + floor((end - begin)/2);
    mergeSort(begin, mid);
    mergeSort(mid, end);
    merge(begin, mid, end);
}

template<typename Iterator>
void merge(Iterator begin, Iterator mid, Iterator end){
    std::vector<typename Iterator::value_type> vec;
    auto leftPtr = begin;
    auto rightPtr = mid;

    while((leftPtr < mid) && (rightPtr < end)){
        if(*leftPtr <= *rightPtr){
            vec.push_back(*leftPtr);
            ++leftPtr;
        }else{
            vec.push_back(*rightPtr);
            ++rightPtr;
        }
    }
    while((leftPtr < mid)){
        vec.push_back(*leftPtr);
        ++leftPtr;
    }
    while((rightPtr < end)){
        vec.push_back(*rightPtr);
        ++rightPtr;
    }
    std::copy(vec.begin(), vec.end(), begin);
}