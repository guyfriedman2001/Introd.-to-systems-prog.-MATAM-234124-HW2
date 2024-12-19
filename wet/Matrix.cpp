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

int Matrix::calculateIndex(int i, int j){
    int rotations = this->rotations % 4;
    int actualN = (is_traspose)?rows:cols;
    int actualM = (is_traspose)?cols:rows;
    int actualI = (is_traspose)?j:i;
    int actualJ = (is_traspose)?i:j;

    int temp = actualI;
    int temp2 = actualJ;
    switch(rotations){
        case(1):
            actualI = actualJ;
            actualJ = actualN - 1 - temp;
            break;
        case(2):
            actualI = actualN - 1 - temp;
            actualJ = actualM - 1 - temp2;
            break;
        case(3):
            actualI = actualM - 1 - actualJ;
            actualJ = temp;
            break;
        default:
            break;
    }
    return actualI*actualN + actualJ;

}

Matrix::~Matrix(){
    delete[] data;
}