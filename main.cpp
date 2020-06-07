#include <iostream>
#include "radix_sort.h"
#include <random>
#include <algorithm>
#include <sstream>
#include "hashtable.h"

#define MAX_LENGTH (trunc(log10(MAX_VALUE)) + 1)
#define MIN_VALUE 0
#define MAX_VALUE 500000000
#define MATRIX_SIZE 3000

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


std::pair<int, int> proposal1(const int* matrix, const size_t n, const int g){
    for(auto i = 0; i < n; ++i){ //row
        for(auto j = 0; j < n; ++j){ //column
            if(matrix[i*n + j] == g){
                return std::make_pair(i, j);
            }
        }
    }
    return std::make_pair(-1, -1);
}

int binary_search(int* array, size_t n, int g){
    int min=0, max = n;
    while(min <= max){
        auto mid = (max + min) / 2;
        if(array[mid] == g) return mid;
        else if(array[mid] > g) max = mid -1;
        else min = mid + 1;
    }
    return -1;
}

std::pair<int, int> proposal2(int* matrix, size_t n, int g){
    for(auto i = 0; i < n; ++i){
        radixSort(&matrix[i*n], n, MAX_LENGTH);
        auto bSearchResult = binary_search(&matrix[i*n], n, g);
        if(bSearchResult != -1){
            return std::make_pair(i, bSearchResult);
        }
    }
    return std::make_pair(-1, -1);
}

int binary_search_row(const int* array, size_t n, int g){
    int min = 0, max = n;
    while(min <= max){
        int mid = (max + min) / 2;
        /** If first element of the row is greater than g, then reset max and continue */
        if(array[mid*n] > g){
            max = mid - 1;
            continue;
        }else{ /** If first element of the row is less than g */
            /** If last element of the row is goe g, I found the row */
            if(array[mid*n + (n-1)] >= g){
                /** Return the row index */
                return mid;
            }else{
                /** Reset min and continue */
                min = mid+1;
            }
        }
    }
    /** Row not found */
    return -1;
}

std::pair<int, int> proposal3(int* matrix, size_t n, int g){
//    std::cout << printMatrix(matrix, n);
    radixSort(matrix, n * n, MAX_LENGTH);
//    std::cout << printMatrix(matrix, n);
    auto rowIndex = binary_search_row(matrix, n, g);
    if(rowIndex == -1) return std::make_pair(-1, -1);
    auto colIndex = binary_search(&matrix[rowIndex*n], n, g);
    if(colIndex == -1) return std::make_pair(-1, -1);
    return std::make_pair(rowIndex, colIndex);
}

std::pair<int, int> proposal4(Hashtable& ht, unsigned int g){
    return ht.find(g);
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
        const int searchForValue = 1272;
        std::cout << "Searching for element " << searchForValue << " ... " << std::endl;

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


        auto pair4 = proposal4(ht, searchForValue);
        std::cout << "Found at (" << pair4.first << ", " << pair4.second << ")" << std::endl;
    }catch(std::exception& ex){
        std::cout << ex.what() << std::endl;
    }
//    destroyMatrix(matrix);
    return 0;
}
