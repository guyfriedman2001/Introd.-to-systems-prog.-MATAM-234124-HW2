#include "Utilities.h"
#include <iostream>

class Matrix {
    private:
    int rows;
    int cols;
    int* data; 
    bool is_traspose;
    int rotations;

    public:
    Matrix(int rows = 0, int cols = 0, int initiale = 0);
    Matrix(const Matrix& other);
    int getRows() const;
    int getCols() const;
    Matrix& operator=(const Matrix& other);
    int calculateIndex(int i, int j);
    ~Matrix();
};