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
    int calculateIndex(int row, int coloum) const; //needs to move to private
    bool sameDimensions(const Matrix& matrice) const; //needs to move to private
    bool canMultiply(const Matrix& matrice) const; //needs to move to private
    /**
     * check if a given input is within the matrix bounds
     * if it is - do nothing
     * if it is not - write appropriate message to cerr
     */
    void checkInput(int row, int coloum) const; //needs to move to private
    
    public:
    Matrix(int rows = 0, int cols = 0, int initiale = 0);
    Matrix(const Matrix& other);
    int getRows() const;
    int getCols() const;
    Matrix& operator=(const Matrix& other);
    int& operator()(int row, int coloum);
    int& operator()(int row, int coloum) const;
    Matrix operator+(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    static double CalcFrobeniusNorm(const Matrix& matrice);
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
    Matrix operator*(int scalar) const;
    Matrix& operator*=(int scalar);
    Matrix operator*(const Matrix& matrice) const;
    Matrix& operator*=(const Matrix& matrice);
    Matrix operator-(const Matrix& matrice) const;
    friend std::ostream &operator<<(std::ostream &os, const Matrix& matrice);
    Matrix& operator-=(const Matrix& matrice);
    friend bool operator==(const Matrix& left, const Matrix& right);
    Matrix operator-() const;
    ~Matrix();
};
Matrix operator*(int scalar, const Matrix& matrice);
bool operator!=(const Matrix& left, const Matrix& right);

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