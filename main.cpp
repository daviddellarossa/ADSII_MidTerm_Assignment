#include <iostream>
#include "radix_sort.h"
#include <random>
#include <algorithm>
#include <sstream>
#include "hashtable.h"
#include "common.h"
#include "constants.h"
#include <chrono>
#include <limits>

std::string printMatrix(const unsigned long* matrix, const size_t n){
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


unsigned long* createMatrix(const size_t n){
    auto m = new unsigned long[n * n];
    return m;
}

void populateMatrix(unsigned long* m, const size_t n){
    for(auto i = 0; i < n; i++){
        for(auto j = 0; j < n; j++) {
            m[i*n + j] = i*n + j;
        }
    }
//    std::cout << printMatrix(m, MATRIX_SIZE) << std::endl;
}

void destroyMatrix(unsigned long* m){
    delete[] m;
}


Hashtable createHashtable(){
    Hashtable ht(MATRIX_SIZE);
    return ht;
}

//void populateHashtable(Hashtable& ht){
//    std::default_random_engine ran(4);
//    std::uniform_int_distribution<>{MIN_VALUE, MAX_VALUE}(ran);
//    for(int i = 0; i < MATRIX_SIZE; i++){
//        for(int j = 0; j < MATRIX_SIZE; j++) {
//            unsigned int newVal = -1;
//            do {
//                newVal = std::uniform_int_distribution<>{MIN_VALUE, MAX_VALUE}(ran);
//
//            } while (ht.find(newVal).first != -1 && ht.find(newVal).second != -1);
////            std::cout << newVal << ", ";
//            ht.insert(newVal, i, j);
//        }
//    }
////    std::cout << std::endl;
//}

void process(unsigned long value){
    std::cout << "Searching for element " << value << " ... " << std::endl;
    auto matrix = createMatrix(MATRIX_SIZE);
    try {
        populateMatrix(matrix, MATRIX_SIZE);

        auto start = std::chrono::high_resolution_clock::now();
        auto pair = proposal2(matrix, MATRIX_SIZE, value);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "n: " << MATRIX_SIZE << ", Execution time(ms): " << duration.count() << std::endl;

        std::cout << "Found at (" << pair.first << ", " << pair.second << ")" << std::endl;
    } catch (const std::exception& e) {
        destroyMatrix(matrix);
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int main() {
    bool loop = true;
    while(loop){
        std::cout << "Insert a number or return to exit: " << std::endl;

        std::string line;

        std::getline(std::cin, line);
        std::stringstream ss{line};
        if(line.empty()) loop = false;
        unsigned long searchValue;
        try{
            searchValue = std::atol(line.c_str());
        } catch (...) {
            continue;
        }
        process(searchValue);
    }
    return 0;

//    auto a = tenPow(0);

//    const size_t matrixSize = MATRIX_SIZE;
    auto matrix = createMatrix(MATRIX_SIZE);
    try{
        populateMatrix(matrix, MATRIX_SIZE);


//    std::cout << "Searching for element " << SEARCH_VALUE << " ... " << std::endl;

//        auto pair1 = proposal1(matrix, matrixSize, searchForValue);
//        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair1.first << ", " << pair1.second << ")" << std::endl;

        auto start = std::chrono::high_resolution_clock::now();
        auto pair2 = proposal2(matrix, MATRIX_SIZE, SEARCH_VALUE);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "n: " << MATRIX_SIZE << ", Execution time(ms): " << duration.count() << std::endl;

        //std::cout << printMatrix(matrix, MATRIX_SIZE) << std::endl;
        std::cout << "Found at (" << pair2.first << ", " << pair2.second << ")" << std::endl;

//        auto pair3 = proposal3(matrix, matrixSize, searchForValue);
////        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair3.first << ", " << pair3.second << ")" << std::endl;


//        auto ht = createHashtable();
//        populateHashtable(ht);
//        std::cout << ht.toString() << std::endl;
//        std::cout << ht.toMatrixString() << std::endl;


//        auto pair4 = proposal4(ht, SEARCH_VALUE);
//        std::cout << "Found at (" << pair4.first << ", " << pair4.second << ")" << std::endl;
    }catch(std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
    destroyMatrix(matrix);
    return 0;
}
