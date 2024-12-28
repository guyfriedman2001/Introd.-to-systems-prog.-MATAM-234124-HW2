#include "Matrix.h"

Matrix::Matrix(int rows, int cols, int initiale) : rows(rows), cols(cols), data(nullptr), is_traspose(false), rotations(0) {
    if(rows > 0 && cols > 0){
        data = new int[rows*cols]{initiale};
    }
}

Matrix::Matrix(const Matrix& other): rows(other.rows), cols(other.cols),
 data(new int[(other.rows * other.cols)]),is_traspose(other.is_traspose), rotations(other.rotations){
    for(int i=0; i< (other.rows * other.cols); i++){
        this->data[i] = other.data[i];
    }
}

int Matrix::getRows() const{
    if(this->is_traspose){
        if(this->rotations % 2 == 0){
            return this->cols;
        }
        return this->rows;
    }
    else if(this->rotations % 2 == 0){
        return this->rows;
    }
    return this->cols;
}
int Matrix::getCols() const{
        if(this->is_traspose){
        if(this->rotations % 2 == 0){
            return this->rows;
        }
        return this->cols;
    }
    else if(this->rotations % 2 == 0){
        return this->cols;
    }
    return this->rows;
}

Matrix& Matrix::operator=(const Matrix& other){
    if(this == &other)
    {
        return *this;
    }
    if(this->data != nullptr){
        delete[] this->data;
    }
     this->rows = other.rows;
     this->cols = other.cols;
     this->is_traspose = other.is_traspose;
     this->rotations = other.rotations;
     this->data = new int[(this->rows * this->cols)];
    for(int i=0; i<  (this->rows * this->cols) ; i++){
        this->data[i] = other.data[i];
    }
    return *this;
}

int Matrix::calculateIndex(int i, int j) const{
    this->checkInput(i,j);
    int actualRotations = this->rotations % 4;
    int actualCols = this->cols;
    int actualRows = this->rows;
    int actualI = (this->is_traspose)?j:i;
    int actualJ = (this->is_traspose)?i:j;
    int index = 0;
    switch(actualRotations){
        case(0):
            index = actualCols*actualI + actualJ;
            break;
        case(1):
            index = (actualRows - actualJ - 1)*actualCols + actualI;
            break;
        case(2):
            index = (actualRows - actualI - 1)*actualCols + actualCols - actualJ - 1;
            break;
        case(3):
            index = actualCols*actualJ + actualCols - actualI - 1;
            break;
        default:
            break;
    }
    return index;
}

int& Matrix::operator()(int row, int coloum){ //TODO ADD CONST VERSION
    int index = this->calculateIndex(row,coloum);
    return (this->data[index]);
}

int& Matrix::operator()(int row, int coloum) const{ //TODO ADD CONST VERSION
    int index = this->calculateIndex(row,coloum);
    return (this->data[index]);
}

inline bool Matrix::sameDimensions(const Matrix& matrice) const{
    return (this->getCols() == matrice.getCols()) && (this->getRows() == matrice.getRows());
}

inline bool Matrix::canMultiply(const Matrix& matrice) const{
    return (this->getCols() == matrice.getRows());
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (!this->sameDimensions(other)){
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    int resRows = other.getRows();
    int resCols = other.getCols();
    Matrix result(other);
    for (int i = 0; i < resRows; i++) { 
        for (int j = 0; j < resCols; j++) {
            result(i, j) = (*this)(i, j) + result(i, j);
        }
    }
    return result;
}

Matrix& Matrix::operator+=(const Matrix& other){
    if (!this->sameDimensions(other)){
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    *this = *this + other;
    return *this;    
}

void Matrix::checkInput(int row, int coloum) const{
    int thisRows = this->getRows();
    int thisCols = this->getCols();
    if ((thisRows <= row)||(thisCols <= coloum)){
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

double Matrix::CalcFrobeniusNorm(const Matrix& matrice){
    double sum = 0;
    int resRows = matrice.getRows();
    int resCols = matrice.getCols();
    for (int i = 0; i < resRows; ++i) {
        for (int j = 0; j < resCols; ++j) {
            int item = matrice(i, j);
            sum += abs(item*item);
        }
    }
    return sqrt(sum);
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
    counterClockwise.rotations += 3; 
    return counterClockwise;
}

Matrix Matrix::operator*(int scalar) const{
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

Matrix Matrix::operator*(const Matrix& matrice) const{
    if(!(canMultiply(matrice))){
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix multpliedMatrix(this->getRows(), matrice.getCols(), 0);
    for (int i = 0; i <  matrice.getCols(); i++) {
        for (int j = 0; j < this->getRows(); j++) {
            for(int k=0; k < matrice.getRows(); k++){
                (multpliedMatrix)(j,i) += (*this)(j,k) * (matrice)(k,i);
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
    if(matrice.getRows() == 0 || matrice.getCols() == 0){
        return os;
    }
    for(int i = 0; i < matrice.getRows(); i++){
        for(int j = 0; j < matrice.getCols(); j++){
            os << "|" << matrice(i,j);
        }
        os << "|" << std::endl;
    }
    return os;
}

bool operator==(const Matrix& left, const Matrix& right){
    if(!left.sameDimensions(right)){
        return false;
    }
    for(int i = 0; i < left.getRows(); i++){
        for(int j = 0; j < left.getCols(); j++){
            if(left(i,j) != right(i,j)){
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& left, const Matrix& right){
    return (!(left == right));
}

Matrix Matrix::operator-() const{
    Matrix tempMatrix(*this);
    return tempMatrix*(-1);
}

Matrix Matrix::operator-(const Matrix& matrice) const{
    Matrix tempMatrix(matrice);
    tempMatrix = -tempMatrix;
    return (*this + tempMatrix);
}

Matrix& Matrix::operator-=(const Matrix& matrice){
    *this = *this - matrice;
    return *this;    
}

Matrix::~Matrix(){
    delete[] data;
}