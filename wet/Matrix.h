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
    //int calculateIndex(int row, int coloum);
    int calculateIndex(int row, int coloum) const; //needs to move to private
    ~Matrix();
    int* operator()(int row, int coloum);
    int* operator()(int row, int coloum) const;
    //int* operator()(int row, int coloum); //TODO ADD CONST
    bool sameDimensions(const Matrix& matrice) const; //needs to move to private
    bool canMultiply(const Matrix& matrice) const; //needs to move to private
    Matrix operator+(const Matrix& other) const;
    Matrix operator+=(const Matrix& other);

    /**
     * check if a given input is within the matrix bounds
     * if it is - do nothing
     * if it is not - write appropriate message to cerr
     */
    void checkInput(int row, int coloum) const; //needs to move to private
    int CalcFrobeniusNorm(const Matrix& matrice);
    int CalcFrobeniusNorm()const;

    /**
     * return a copy the matrix rotated clockwise 90 degrees
     * 
     * @return - a copy of the called matrix, rotated 90 degrees clockwise
     */
    Matrix rotateClockwise() const;

    /**
     * return a copy the matrix rotated counter clockwise 90 degrees
     * 
     * @return - a copy of the called matrix, rotated 90 degrees counter clockwise
     */
    Matrix rotateCounterClockwise() const;

    /**
     * return a transposed copy the matrix
     * 
     * @return - a copy of the called matrix, transposed
     */
    Matrix transpose() const;

    Matrix operator*(int scalar);
    Matrix& operator*=(int scalar);
    Matrix operator*(const Matrix& matrice);
    Matrix& operator*=(const Matrix& matrice);
    friend std::ostream &operator<<(std::ostream &os, const Matrix& matrice);
    Matrix operator-(const Matrix& matrice);
    Matrix& operator-=(const Matrix& matrice);
    friend bool operator==(const Matrix& left, const Matrix& right);
};
Matrix operator*(int scalar, const Matrix& matrice);
bool operator!=(const Matrix& left, const Matrix& right);
//Matrix operator+(const Matrix& left, const Matrix& right);s