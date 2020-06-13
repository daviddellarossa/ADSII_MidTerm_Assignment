#include <iostream>
#include "radix_sort.h"
#include <random>
#include <algorithm>
#include <sstream>
#include "hashtable.h"
#include "goldie.h"
#include "constants.h"
#include <chrono>
#include <limits>

std::string printMatrix(const std::vector<unsigned long>& matrix, const size_t n){
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

void process(std::vector<unsigned long>& matrix, Hashtable& ht, unsigned long value){
    std::cout << "Searching for element " << value << " ... " << std::endl;
//    std::cout << printMatrix(matrix, MATRIX_SIZE) << std::endl;
    try {

        auto start = std::chrono::high_resolution_clock::now();
//         auto pair = proposal3(matrix, value);
       auto pair = proposal4(ht, value);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
        std::cout << "n: " << MATRIX_SIZE << ", Execution time(ms): " << duration.count() << std::endl;
        std::cout << "Found at (" << pair.first << ", " << pair.second << ")" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception: " << e.what() << std::endl;
    }
}

int main() {
    std::vector<unsigned long> matrix(MATRIX_SIZE * MATRIX_SIZE, 0);
    std::generate(matrix.begin(), matrix.end(), []() {
        static unsigned long counter = MATRIX_SIZE * MATRIX_SIZE - 1;
        return counter--;
    });

    Hashtable ht(MATRIX_SIZE, 1, 0, MATRIX_SIZE);
    unsigned int counter = MATRIX_SIZE*MATRIX_SIZE - 1;
    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++) {
            ht.insert(counter--, i, j);
        }
    }
    std::cout << "Size of ht:" << ht.m_buckets.size() << std::endl;

    bool loop = true;
    while (loop) {
        std::cout << "Insert a number or return to exit: " << std::endl;

        std::string line;

        std::getline(std::cin, line);
        std::stringstream ss{line};
        if (line.empty()) loop = false;
        unsigned long searchValue;
        try {
            searchValue = std::atol(line.c_str());
        } catch (...) {
            continue;
        }
        process(matrix, ht, searchValue);
    }
    return 0;
}
//    auto a = tenPow(0);

//    const size_t matrixSize = MATRIX_SIZE;
//    auto matrix = createMatrix(MATRIX_SIZE);
//    try{
//        populateMatrix(matrix, MATRIX_SIZE);


//    std::cout << "Searching for element " << SEARCH_VALUE << " ... " << std::endl;

//        auto pair1 = proposal1(matrix, matrixSize, searchForValue);
//        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair1.first << ", " << pair1.second << ")" << std::endl;

//        auto start = std::chrono::high_resolution_clock::now();
//        auto pair2 = proposal2(matrix, MATRIX_SIZE, SEARCH_VALUE);
//        auto stop = std::chrono::high_resolution_clock::now();
//        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
//        std::cout << "n: " << MATRIX_SIZE << ", Execution time(ms): " << duration.count() << std::endl;

        //std::cout << printMatrix(matrix, MATRIX_SIZE) << std::endl;
//        std::cout << "Found at (" << pair2.first << ", " << pair2.second << ")" << std::endl;

//        auto pair3 = proposal3(matrix, matrixSize, searchForValue);
////        std::cout << printMatrix(matrix, matrixSize) << std::endl;
//        std::cout << "Found at (" << pair3.first << ", " << pair3.second << ")" << std::endl;


//        auto ht = createHashtable();
//        populateHashtable(ht);
//        std::cout << ht.toString() << std::endl;
//        std::cout << ht.toMatrixString() << std::endl;


//        auto pair4 = proposal4(ht, SEARCH_VALUE);
//        std::cout << "Found at (" << pair4.first << ", " << pair4.second << ")" << std::endl;
//    }catch(std::exception& ex){
//        std::cout << ex.what() << std::endl;
//    }
//    destroyMatrix(matrix);
//    return 0;
//}
