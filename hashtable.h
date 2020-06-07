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

template<typename T>
class Nullable{
public:
    Nullable() : m_IsNull{true}{}
    Nullable(T value): m_IsNull{false}, m_Value{value}{}
    ~Nullable() = default;
    bool isNull() const{ return m_IsNull; }
    T value() const { return m_Value; }
    void value(T value) { m_Value = value; m_IsNull = false; }
    void setNull() { m_IsNull = true; }
private:
    bool m_IsNull;
    T m_Value;

};

class HashtableItem{
public:
    HashtableItem() : m_isNull{true}{}
    HashtableItem(unsigned int value, unsigned int rowIndex, unsigned int colIndex):
        m_isNull{false}, m_value{value}, m_rowIndex{rowIndex}, m_colIndex{colIndex}{}
    ~HashtableItem() = default;
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

private:
    bool m_isNull;
    unsigned int m_value;
    unsigned int m_rowIndex;
    unsigned int m_colIndex;

};


class Hashtable {
public:
    Hashtable(const size_t _rowSize);
    ~Hashtable();
    std::pair<unsigned int, unsigned int> find(unsigned int _value);
    void extend();
    void insert(unsigned int _value, unsigned int _rowIdx, unsigned int _colIdx);
    std::string toString();
    std::string toMatrixString();
    double loadFactor();

private:
//    void insert(std::shared_ptr<HashtableItem[]> buckets, size_t size, const Hashtable& element);
    unsigned int hash(unsigned int);
    unsigned int hash(unsigned int, unsigned int);

    void insert(HashtableItem* buckets, size_t size, unsigned int _value, unsigned int _rowIdx, unsigned int _colIdx);
    HashtableItem* m_Buckets;
    size_t m_Size{0};
    size_t m_rowSize{0};
    size_t m_itemCount{0};
    const double m_extendThreshold{0.5};
    const double m_extendFactor{1.5};
};


#endif //MID_TERM_ASSIGNMENT_HASHTABLE_H
