//
// Created by deedeeaar on 07/06/2020.
//

#ifndef MID_TERM_ASSIGNMENT_HASHTABLE_H
#define MID_TERM_ASSIGNMENT_HASHTABLE_H

#include <cstddef>
#include <utility>
#include <memory>
#include <string>
#include <sstream>
#include "constants.h"
#include "vector"
#include "iostream"

class HashtableItem{
public:
    HashtableItem() : m_isNull{true}{}
    HashtableItem(unsigned int value, unsigned int rowIndex, unsigned int colIndex):
        m_isNull{false}, m_value{value}, m_rowIndex{rowIndex}, m_colIndex{colIndex}{}
    ~HashtableItem(){
//        std::cout << "hti desctructor" << std::endl;
    }
    bool isNull() const{ return m_isNull; }

    void setNull() { m_isNull = true; }

    unsigned int getValue() const {
        return m_value;
    }

    void set(unsigned int value, unsigned int rowIndex, unsigned int colIndex) {
        m_value = value;
        m_rowIndex = rowIndex;
        m_colIndex = colIndex;
        m_isNull = false;
    }

    unsigned int getRowIndex() const {
        return m_rowIndex;
    }

    unsigned int getColIndex() const {
        return m_colIndex;
    }

//    std::unique_ptr<HashtableItem> prev = nullptr;
    std::shared_ptr<HashtableItem> next = nullptr;

private:
    bool m_isNull;
    unsigned int m_value;
    unsigned int m_rowIndex;
    unsigned int m_colIndex;


};


class Hashtable {
public:
    Hashtable(const size_t _rowSize);
    Hashtable(const size_t _rowSize, unsigned int a, unsigned int b, unsigned long mod);
    ~Hashtable();
    std::pair<unsigned int, unsigned int> find(unsigned int _value);
    void insert(unsigned int _value, unsigned int _rowIdx, unsigned int _colIdx);

    double loadFactor();

    std::vector<std::shared_ptr<HashtableItem>> m_buckets;
private:
    unsigned int hash(unsigned int);


    size_t m_Size{0};
    size_t m_rowSize{0};
    size_t m_itemCount{0};
    unsigned int m_a = 1;
    unsigned int m_b = 0;
    unsigned long m_mod;
};


#endif //MID_TERM_ASSIGNMENT_HASHTABLE_H
