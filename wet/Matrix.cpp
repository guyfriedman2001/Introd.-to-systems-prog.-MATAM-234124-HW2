#include "Matrix.h"

Matrix::Matrix(int rows, int cols, int initiale) : rows(rows), cols(cols),
 data(new int[rows*cols]{initiale}),is_traspose(false), rotations(0) {
}

Matrix::Matrix(const Matrix& other): rows(other.rows), cols(other.cols),
 data(new int[other.rows*other.cols]),is_traspose(other.is_traspose), rotations(other.rotations){
    for(int i=0; i< rows*cols; i++){
        this->data[i] = other.data[i];
    }
}

int Matrix::getRows() const{
    return this->rows;
}
int Matrix::getCols() const{
    return this->cols;
}

Matrix& Matrix::operator=(const Matrix& other){
    if(this == &other)
    {
        return *this;
    }
    delete this->data;
    rows = other.rows;
    cols = other.cols;
    is_traspose = other.is_traspose;
    rotations = other.rotations;
    data = new int[rows*cols];
    for(int i=0; i< rows*cols; i++){
        this->data[i] = other.data[i];
    }
    return *this;
}

Matrix::~Matrix(){
    delete[] data;
}