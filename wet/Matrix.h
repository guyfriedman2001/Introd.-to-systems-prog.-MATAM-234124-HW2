#pragma once
#include "Utilities.h"
#include <iostream>
#include <cmath>

class Matrix {
    private:
    int rows;
    int cols;
    int* data; 
    bool is_traspose;
    int rotations;

    /**
     * Calculate the index in the underlying data array for a given row and column.
     * 
     * @param row - the row index.
     * @param coloum - the column index.
     * 
     * @return - the calculated index in the data array.
     */
    int calculateIndex(int row, int coloum) const;

    /**
     * Check if the dimensions of this matrix match the dimensions of another matrix.
     * 
     * @param matrice - the matrix to compare dimensions with.
     * 
     * @return - true if the dimensions match, false otherwise.
     */
    bool sameDimensions(const Matrix& matrice) const;

    /**
     * Check if this matrix can be multiplied by another matrix.
     * 
     * @param this - the left matrix in the multiplication.
     * @param matrice - the matrix to check compatibility for multiplication.
     * 
     * @return - true if the matrices can be multiplied, false otherwise.
     */
    bool canMultiply(const Matrix& matrice) const;

    /**
     * check if a given input is within the matrix bounds
     * 
     * @param row - the row of the given input.
     * @param coloum - the coloum of the given input.
     */
    void checkInput(int row, int coloum) const;
    
    public:

    /**
     * A matrice creation constructor,
     * deside how many rows and coloums will the
     * new matrice have, and the initial value for each number
     * in the matrice.
     * 
     * @param rows - how many rows would the new matrice have.
     * @param cols - how many coloums would the new matrice have.
     * @param initiale - the value of the initial values in the matrice.
     * 
     * @return - a new matrice with the above specified values.
     */
    Matrix(int rows = 0, int cols = 0, int initiale = 0);

    /**
     * A copy constructor, to copy a given matrice.
     * 
     * @param other - the matrice to be copied.
     * 
     * @return - a (deep) copy of the given matrice.
     */
    Matrix(const Matrix& other);

    /**
     * return the number of rows that a given matrix has.
     * 
     * @param this - the matrix for which the number of rows should be given.
     * 
     * @return - the number of rows for the matrix.
     */
    int getRows() const;

    /**
     * return the number of coloums that a given matrix has.
     * 
     * @param this - the matrix for which the number of coloums should be given.
     * 
     * @return - the number of coloums for the matrix.
     */
    int getCols() const;

    /**
     * Assignment operator for deep copying another matrix.
     * 
     * @param other - the matrix to copy.
     * @param this - the matrix that the result is going to be assigned to
     * 
     * @return - a reference to @param this matrix after copying.
     */
    Matrix& operator=(const Matrix& other);

    /**
     * the () allows acces and modifications to the numbers of the
     * matrix at the specified row and coloum.
     * 
     * @param row - the row of the desired number.
     * @param coloum - the coloum of the desired number.
     * 
     * @return - a non const (modifiable) reference to the number itself inside the matrix.
     */
    int& operator()(int row, int coloum);

    /**
     * the () allows acces to the numbers of a const
     * matrix at the specified row and coloum.
     * 
     * @param row - the row of the desired number.
     * @param coloum - the coloum of the desired number.
     * 
     * @return - a reference to the number itself inside the const matrix.
     */
    int& operator()(int row, int coloum) const;

    /**
     * operator + allows adding two matrices to one another to get a
     * new matrix with the result of their addition.
     * 
     * @param this - the first matrix to add.
     * @param other - the second matrix to add.
     * 
     * @return - the result of the addition of the two matrices.
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * addition assignment operator - add a matrix to
     * a matrix.
     * 
     * @param this - the matrix that will contain the result of the addition
     * @param other - the matrix to add to @param this
     * 
     * @return - a reference to @param this
     */
    Matrix& operator+=(const Matrix& other);

    /**
     * Calculate the Frobenius norm of a given matrix.
     * 
     * @param matrice - the matrix for which the Frobenius norm is calculated.
     * 
     * @return - the Frobenius norm as a double.
     */
    static double CalcFrobeniusNorm(const Matrix& matrice);

    /**
     * Calculate the Frobenius norm of this matrix.
     * 
     * @return - the Frobenius norm as a double.
     */
    double CalcFrobeniusNorm()const;

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

    /**
     * Perform scalar multiplication on this matrix.
     * 
     * @param scalar - the scalar to multiply with.
     * 
     * @return - a new matrix with the result of the scalar multiplication.
     */
    Matrix operator*(int scalar) const;

    /**
     * Perform scalar multiplication on this matrix and update it.
     * 
     * @param scalar - the scalar to multiply with.
     * 
     * @return - a reference to this matrix after the operation.
     */
    Matrix& operator*=(int scalar);

    /**
     * Perform matrix multiplication with another matrix.
     * 
     * @param matrice - the matrix to multiply with.
     * 
     * @return - a new matrix with the result of the multiplication.
     */
    Matrix operator*(const Matrix& matrice) const;

    /**
     * Perform matrix multiplication with another matrix and update this matrix.
     * 
     * @param matrice - the matrix to multiply with.
     * 
     * @return - a reference to this matrix after the operation.
     */
    Matrix& operator*=(const Matrix& matrice);

    /**
     * Perform subtraction of another matrix from this matrix.
     * 
     * @param matrice - the matrix to subtract.
     * 
     * @return - a new matrix with the result of the subtraction.
     */
    Matrix operator-(const Matrix& matrice) const;

    /**
     * Overload of the stream insertion operator to output the matrix.
     * 
     * @param os - the output stream.
     * @param matrice - the matrix to output.
     * 
     * @return - the output stream with the matrix's content.
     */
    friend std::ostream &operator<<(std::ostream &os, const Matrix& matrice);

    /**
     * Perform subtraction of another matrix from this matrix and update it.
     * 
     * @param matrice - the matrix to subtract.
     * 
     * @return - a reference to this matrix after the operation.
     */
    Matrix& operator-=(const Matrix& matrice);

    /**
     * Overload of the equality operator to compare two matrices.
     * 
     * @param left - the first matrix to compare.
     * @param right - the second matrix to compare.
     * 
     * @return - true if the matrices are equal, false otherwise.
     */
    friend bool operator==(const Matrix& left, const Matrix& right);

    /**
     * Negate this matrix (unary minus operator).
     * 
     * @return - a new matrix with all elements negated.
     */
    Matrix operator-() const;

    /**
     * Destructor to free allocated memory.
     */
    ~Matrix();
};

/**
 * Overload of the scalar multiplication operator to allow scalar multiplication
 * with a matrix on the left-hand side.
 * 
 * @param scalar - the scalar to multiply.
 * @param matrice - the matrix to multiply with.
 * 
 * @return - a new matrix with the result of the multiplication.
 */
Matrix operator*(int scalar, const Matrix& matrice);

/**
 * Overload of the inequality operator to compare two matrices.
 * 
 * @param left - the first matrix to compare.
 * @param right - the second matrix to compare.
 * 
 * @return - true if the matrices are not equal, false otherwise.
 */
bool operator!=(const Matrix& left, const Matrix& right);

/**
 * Calculate the determinant of a square matrix.
 * 
 * @param matrice - the matrix to calculate the determinant of.
 * 
 * @return - the determinant of the matrix. If the matrix is not square,
 *           exits with an error and returns 0.
 */
static int CalcDeterminant(const Matrix& matrice){
    if(matrice.getRows() != matrice.getCols()){
        exitWithError(MatamErrorType::NotSquareMatrix);
        return 0;        
    }
    if(matrice.getRows() == 0){
        return 0;
    }
    if(matrice.getRows() == 1){
        return matrice(0,0);
    }
    if(matrice.getRows() == 2){
        return ((matrice(0,0) * matrice(1,1)) - (matrice(0,1) * matrice(1,0)));
    }
    int det = 0;
    Matrix temp((matrice.getRows() - 1), (matrice.getCols() - 1));
    for(int i = 0; i< matrice.getRows(); i++){
        for(int j=0; j<matrice.getRows(); j++){
            if(i>j){
                for(int k=0; k < temp.getCols(); k++){
                    temp(j,k) = matrice(j,k+1);
                }
            }
            if(i<j){
                for(int k=0; k < temp.getCols(); k++){
                    temp(j-1,k) = matrice(j,k+1);
                }
            }

        }
        det += pow(-1,i) * (matrice(i,0)) * CalcDeterminant(temp);
    }
    return det;
}