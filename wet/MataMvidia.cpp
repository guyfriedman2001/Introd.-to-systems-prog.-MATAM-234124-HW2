#include "MataMvidia.h"
#include "Utilities.h"
#include <string>
#include <iostream>

MataMvidia::MataMvidia(const std::string& movieName, const std::string& creator, Matrix* frames, int numberOfFrames): 
movieName(movieName), creator(creator),frames(new Matrix[numberOfFrames]), numberOfFrames(numberOfFrames) {
    if(numberOfFrames < 0){
        exitWithError(MatamErrorType::OutOfBounds); 
    }
    for(int i=0; i<numberOfFrames; i++){
        this->frames[i] =  frames[i];
    }
 }
MataMvidia::MataMvidia(const MataMvidia& other): movieName(other.movieName),
 creator(other.creator),frames(new Matrix[other.numberOfFrames]), numberOfFrames(other.numberOfFrames){
    for(int i=0; i<numberOfFrames; i++){
        this->frames[i] =  other.frames[i];
    }

}
MataMvidia& MataMvidia::operator=(const MataMvidia& other){
    if(this == &other)
    {
        return *this;
    }
    delete[] this->frames;
    movieName = other.movieName;
    creator = other.creator;
    numberOfFrames = other.numberOfFrames;
    frames = new Matrix[other.numberOfFrames];
    for(int i=0; i<numberOfFrames; i++){
        this->frames[i] =  other.frames[i];
    }
    return *this;
}

std::string MataMvidia::getMovieName() const{
    return this->movieName;
}
std::string MataMvidia::getcreatorName() const{
    return this->creator;
}
int MataMvidia::getNumberOfFrames() const{
    return this->numberOfFrames;
}

Matrix MataMvidia::operator[](int index){
    if(index < 0 || index > numberOfFrames){
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return this->frames[index];  
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& other){
    Matrix* newFrames = new Matrix[this->numberOfFrames + other.numberOfFrames];
    for(int i = 0; i< this->numberOfFrames; i++){
        newFrames[i] = this->frames[i];
    }
    for(int i = this->numberOfFrames; i < (this->numberOfFrames + other.numberOfFrames); i++){
        newFrames[i] = other.frames[i - this->numberOfFrames];
    }
    this->numberOfFrames += other.numberOfFrames;
    delete[] this->frames;
    this->frames = newFrames;
    return *this;
}

MataMvidia& MataMvidia::operator+=(const Matrix& newFrame){
    Matrix array[1];
    array[0] = newFrame;
    MataMvidia tempMovie("tempMovie","tempCreator", array, 1);
    return (*this += tempMovie);
}

MataMvidia operator+(const MataMvidia& leftMovie, const MataMvidia& rightMovie){
    return (MataMvidia(leftMovie) += rightMovie);
}

std::ostream &operator<<(std::ostream &os, const MataMvidia& movie){
    os << "Movie Name: " <<  movie.movieName << std::endl;
    os << "Author: " <<  movie.creator << std::endl;
    os << std::endl;
    for(int i = 0; i< movie.numberOfFrames; i++){
        os << "Frame " << i << ":" << std::endl;
        os << movie.frames[i] << std::endl;
    }
    os << "-----End of Movie-----" << std::endl;
    return os;
}

MataMvidia::~MataMvidia(){
    delete[] frames;
}