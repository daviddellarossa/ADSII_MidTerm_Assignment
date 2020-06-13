//
// Created by deedeeaar on 07/06/2020.
//

#include "hashtable.h"
#include <algorithm>
#include <iostream>

Hashtable::Hashtable(size_t _rowSize) :
        Hashtable::Hashtable(1, 0, _rowSize * _rowSize) {
}

Hashtable::Hashtable(unsigned int a, unsigned int b, unsigned long mod) : m_a{a}, m_b{b}, m_mod{mod}{
    m_buckets.resize(mod);
}

Hashtable::~Hashtable() { }

void Hashtable::insert(unsigned int _value, unsigned int _rowIdx, unsigned int _colIdx) {
    unsigned int hashValue = hash(_value);

    std::shared_ptr<HashtableItem> newItem{new HashtableItem(_value, _rowIdx, _colIdx)};

    if(m_buckets[hashValue] != nullptr){
        newItem->next = m_buckets[hashValue];
    }
    m_buckets[hashValue] = newItem;

    m_itemCount++;
}

std::pair<unsigned int, unsigned int> Hashtable::find(unsigned int _value) {
    auto hashValue = hash(_value);

    auto ptr = m_buckets[hashValue];
    while(ptr != nullptr){
        if(ptr->getValue() == _value)
            return std::make_pair(ptr->getRowIndex(), ptr->getColIndex());
        ptr = ptr->next;
    }
    return std::make_pair(-1, -1);
}

unsigned int Hashtable::hash(unsigned int key){
    return (m_a*key+m_b) % (m_mod);
}

