#include <iostream>
#include "radix_sort.h"
#include <random>
#include <algorithm>
#include <sstream>
#include "hashtable.h"
#include "common.h"
#include "constants.h"


int* createMatrix(size_t n){
    auto m = new int[n * n];
    return m;
}

void populateMatrix(int* m, size_t n){
    std::default_random_engine ran(4);
    std::uniform_int_distribution<>{MIN_VALUE, MAX_VALUE}(ran);
    std::generate(m, m + (n * n), [&ran](){ return std::uniform_int_distribution<>{MIN_VALUE, MAX_VALUE}(ran); });
}

void destroyMatrix(int* m){
    delete[] m;
}

std::string printMatrix(const int* matrix, size_t n){
    std::stringstream ss;
    for(auto i = 0; i < n; ++i){
        ss << "|";
        for(auto j = 0; j < n; ++j){
            if(j > 0) ss << " ";
            ss << matrix[i * n + j];
        }
        ss << "|" << std::endl;
    }
    return ss.str();
}

Hashtable createHashtable(){
    Hashtable ht(MATRIX_SIZE);
    return ht;
}

void populateHashtable(Hashtable& ht){
    std::default_random_engine ran(4);
    std::uniform_int_distribution<>{MIN_VALUE, MAX_VALUE}(ran);
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++) {
            unsigned int newVal = -1;
            do {
                newVal = std::uniform_int_distribution<>{MIN_VALUE, MAX_VALUE}(ran);

            } while (ht.find(newVal).first != -1 && ht.find(newVal).second != -1);
//            std::cout << newVal << ", ";
            ht.insert(newVal, i, j);
        }
    }
//    std::cout << std::endl;
}


int main() {

    auto a = tenPow(0);

    const size_t matrixSize = MATRIX_SIZE;
//    auto matrix = createMatrix(matrixSize);
    try{
//        populateMatrix(matrix, matrixSize);

    std::cout << "Searching for element " << SEARCH_VALUE << " ... " << std::endl;

//        auto pair1 = proposal1(matrix, matrixSize, searchForValue);
//        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair1.first << ", " << pair1.second << ")" << std::endl;


//        auto pair2 = proposal2(matrix, matrixSize, searchForValue);
//        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair2.first << ", " << pair2.second << ")" << std::endl;

//        auto pair3 = proposal3(matrix, matrixSize, searchForValue);
////        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair3.first << ", " << pair3.second << ")" << std::endl;


        auto ht = createHashtable();
        populateHashtable(ht);
//        std::cout << ht.toString() << std::endl;
//        std::cout << ht.toMatrixString() << std::endl;


        auto pair4 = proposal4(ht, SEARCH_VALUE);
        std::cout << "Found at (" << pair4.first << ", " << pair4.second << ")" << std::endl;
    }catch(std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
//    destroyMatrix(matrix);
    return 0;
}
