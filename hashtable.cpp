//
// Created by deedeeaar on 07/06/2020.
//

#include "hashtable.h"
#include <algorithm>
#include <iostream>

Hashtable::Hashtable(size_t _rowSize) : m_rowSize{_rowSize}, m_Size{_rowSize * _rowSize} {
    m_Buckets = new HashtableItem[size_t(m_Size * m_extendFactor)];
}

Hashtable::~Hashtable() {
    delete [] m_Buckets;
}

void Hashtable::insert(unsigned int _value, unsigned int _rowIdx, unsigned int _colIdx) {
    if(loadFactor() >= m_extendThreshold)
        extend();
    insert(m_Buckets, m_Size, _value, _rowIdx, _colIdx);
    m_itemCount++;
}

std::pair<unsigned int, unsigned int> Hashtable::find(unsigned int _value) {
    auto hashValue = hash(_value);

    if(m_Buckets[hashValue].getValue() == _value)
        return std::make_pair(m_Buckets[hashValue].getRowIndex(), m_Buckets[hashValue].getColIndex());

    int counter = 0;
    while(counter < m_Size && m_Buckets[hash(hashValue + counter)].getValue() != _value){
        counter ++;
    }
    if(counter == m_Size){
        return std::make_pair(-1, -1);
    }else{
        auto item = m_Buckets[hash(hashValue + counter)];
        return std::make_pair(item.getRowIndex(), item.getColIndex());
    }
}

void Hashtable::extend() {
    if(loadFactor() < m_extendThreshold)
        return;

    size_t newRowSize = m_rowSize * m_extendFactor;
    size_t newSize = newRowSize * newRowSize;
    std::cout << "Extending hashtable " << std::endl;
    HashtableItem* newBuckets = new HashtableItem[newSize];

    try{
        std::for_each(
                m_Buckets,
                m_Buckets + m_Size,
                [&](HashtableItem& x){
                    if(x.isNull()) return;
                    insert(newBuckets, newSize, x.getValue(), x.getRowIndex(), x.getColIndex());
                }
        );

    } catch(...){
        delete [] newBuckets;
        throw;
    }
    //swap buckets
    std::swap(m_Buckets, newBuckets);
    delete[] newBuckets;

    //reset m
    m_rowSize = newRowSize;
    m_Size = newSize;
}

void Hashtable::insert(
        HashtableItem* _buckets,
        size_t _Size,
        unsigned int _value,
        unsigned int _rowIdx,
        unsigned int _colIdx) {

    unsigned int hashValue = hash(_Size, _value);
    unsigned int counter = 0;
    //find the position in the array where to store key
    while( counter < _Size && _buckets[hash(_Size, (hashValue + counter))].isNull() == false ){
//        std::cout << "collision at " << hash(m_Size, (hashValue + counter)) << std::endl;
        counter ++;
    }
    _buckets[hash(_Size, (hashValue + counter))].set(_value, _rowIdx, _colIdx);
}

std::string Hashtable::toString() {
    std::stringstream ss;

    for (auto i = 0; i < m_rowSize; i++){
        ss << "|";
        for(auto j = 0; j < m_rowSize; j++){
            ss << m_Buckets[i * m_rowSize + j].getValue() << ", ";
        }
        ss<< "|" << std::endl;
    }

    return ss.str();
}

std::string Hashtable::toMatrixString() {
    std::stringstream ss;
    int* matrix = new int[m_Size];
    std::for_each(matrix, matrix + m_Size, [](auto& x){ x = -1; });

    for(auto i = 0; i < m_Size; ++i){
        if(!m_Buckets[i].isNull()){
            matrix[m_Buckets[i].getRowIndex()*m_rowSize + m_Buckets[i].getColIndex()] = m_Buckets[i].getValue();
        }
    }
    for(auto i = 0; i < m_rowSize; ++i){
        ss << "|";
        for(auto j = 0; j < m_rowSize; ++j){
            ss << matrix[i*m_rowSize +j] << " ";
        }
        ss<< "|" << std::endl;
    }
    delete [] matrix;
    return ss.str();
}

double Hashtable::loadFactor() {
    return m_itemCount / double(m_Size);
}

unsigned int Hashtable::hash( unsigned int key){
    return hash(m_Size, key);
}
unsigned int Hashtable::hash(unsigned  int size, unsigned int key){
    return key % (size);
}
