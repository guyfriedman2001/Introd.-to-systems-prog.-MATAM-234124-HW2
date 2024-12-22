#include "Matrix.h"
#include <cmath>


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
    return (this->is_traspose)?this->rows:this->cols;
}
int Matrix::getCols() const{
    return (this->is_traspose)?this->cols:this->rows;
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

/** 
//TODO check if maybe can delete Dis
int Matrix::calculateIndex(int i, int j){
    this->checkInput(i,j);
    int rotations = this->rotations % 4;
    int actualN = this->getRows();
    int actualM = this->getCols();
    int actualI = (this->is_traspose)?j:i;
    int actualJ = (this->is_traspose)?i:j;

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
*/

int Matrix::calculateIndex(int i, int j) const{
    this->checkInput(i,j);
    int rotations = this->rotations % 4;
    int actualN = this->getRows();
    int actualM = this->getCols();
    int actualI = (this->is_traspose)?j:i;
    int actualJ = (this->is_traspose)?i:j;

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

int* Matrix::operator()(int row, int coloum){ //TODO ADD CONST VERSION
    return &(this->data[this->calculateIndex(row,coloum)]);
}

int* Matrix::operator()(int row, int coloum) const{ //TODO ADD CONST VERSION
    return &(this->data[this->calculateIndex(row,coloum)]);
}

inline bool Matrix::sameDimensions(const Matrix& matrice) const{
    return (this->getCols() == matrice.getCols()) && (this->getRows() == matrice.getRows());
}

inline bool Matrix::canMultiply(const Matrix& matrice) const{
    return (this->getCols() == matrice.getRows());
}



Matrix Matrix::operator+=(const Matrix& other){
    if (!this->sameDimensions(other)){exitWithError(MatamErrorType::UnmatchedSizes);}
    int resRows = this->getRows();
    int resCols = this->getCols();
    for (int i = 0; i < resRows; ++i) {
        for (int j = 0; j < resCols; ++j) {
            *(*this)(i, j) = *(*this)(i, j) + *other(i, j);
        }
    }
    return *this;
    
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (!this->sameDimensions(other)){exitWithError(MatamErrorType::UnmatchedSizes);}
    int resRows = this->getRows();
    int resCols = this->getCols();
    Matrix result(resRows, resCols, 0);
    result += *this;
    result += other;

    //for (int i = 0; i < resRows; ++i) { //FIXME after debugging if everything is working, delete these commented lines
    //    for (int j = 0; j < resCols; ++j) {
    //        *result(i, j) = *(*this)(i, j) + *other(i, j);
    //    }
    //}

    return result;
}

/**
 * 
Matrix Matrix::operator+(const Matrix& left, const Matrix& right) {
    if (!this->sameDimensions(other)) {exitWithError(MatamErrorType::UnmatchedSizes);}

    Matrix result(this->rows, this->cols, 0);

    for (int i = 0; i < this->getRows(); ++i) {
        for (int j = 0; j < this->getCols(); ++j) {
            *result(i, j) = *(*this)(i, j) + *other(i, j);
        }
    }

    return result;
}
 */

void Matrix::checkInput(int row, int coloum) const{
    int thisRows = this->getRows();
    int thisCols = this->getCols();
    int actualI = (this->is_traspose)?row:coloum;
    int actualJ = (this->is_traspose)?row:coloum;
    if ((thisRows <= actualI)||(thisCols <= actualJ)){
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

int Matrix::CalcFrobeniusNorm(const Matrix& matrice){
    return matrice.CalcFrobeniusNorm();
}

int Matrix::CalcFrobeniusNorm()const{
    int sum = 0;
    int resRows = this->getRows();
    int resCols = this->getCols();
    for (int i = 0; i < resRows; ++i) {
        for (int j = 0; j < resCols; ++j) {
            int item = *(*this)(i, j);
            sum += sqrt((abs(item*item)));
        }
    }
    return sum;
}

Matrix Matrix::transpose() const{
    Matrix transposeMatrix(*this);
    transposeMatrix.is_traspose = !(this->is_traspose); 
    return transposeMatrix;
}

Matrix Matrix::rotateClockwise() const{
    Matrix clockwise(*this);
    clockwise.rotations += 1; 
    return clockwise;
}

Matrix Matrix::rotateCounterClockwise() const{
    Matrix counterClockwise(*this);
    counterClockwise.rotations -= 1; 
    return counterClockwise;
}

Matrix Matrix::operator*(int scalar){
     Matrix tempMatrix(*this);
     for(int i = 0; i<rows*cols; i++){
        tempMatrix.data[i] *= scalar;
     }
     return tempMatrix;
}


Matrix& Matrix::operator*=(int scalar){
    *this = *this * scalar;
    return *this;
}
Matrix Matrix::operator*(const Matrix& matrice){
    if(!(canMultiply(matrice))){
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix multpliedMatrix(this->getRows(), matrice.getCols(), 0);
    for (int i = 0; i <  matrice.getCols(); ++i) {
        for (int j = 0; j < this->getRows(); ++j) {
            for(int k=0; k< matrice.getRows(); k++){
                *(multpliedMatrix)(j,i) += *(*this)(j,k) * *(matrice)(k,i);
            } 
        }
    }
    return multpliedMatrix;

}
Matrix& Matrix::operator*=(const Matrix& matrice){
    *this = *this * matrice;
    return *this;
}

Matrix operator*(int scalar, const Matrix& matrice){
    Matrix tempMatrix(matrice);
    return (tempMatrix * scalar);
}

std::ostream &operator<<(std::ostream &os, const Matrix& matrice){
    for(int i = 0; i<matrice.getRows(); i++){
        for(int j = 0; j<matrice.getCols(); j++){
            os << "|" << matrice(i,j);
        }
        os << "|" << std::endl;
    }
    return os;
}
Matrix::~Matrix(){
    delete[] data;
}