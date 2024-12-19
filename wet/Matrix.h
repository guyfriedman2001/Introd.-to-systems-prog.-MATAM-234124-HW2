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
    int calculateIndex(int row, int coloum);
    int calculateIndex(int row, int coloum) const;
    ~Matrix();
    int* operator()(int row, int coloum);
    int* operator()(int row, int coloum) const;
    //int* operator()(int row, int coloum); //TODO ADD CONST
    bool sameDimensions(const Matrix& matrice) const;
    bool canMultiply(const Matrix& matrice) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator+=(const Matrix& other);
    //Matrix operator+(const Matrix& left, const Matrix& right);
    void checkInput(int row, int coloum) const;
    int CalcFrobeniusNorm(const Matrix& matrice);
    int CalcFrobeniusNorm()const;
};