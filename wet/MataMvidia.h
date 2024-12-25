#pragma once
#include "Matrix.h"
#include <string>
#include <iostream>

class MataMvidia{
    private: 
    std::string movieName;
    std::string creator;
    Matrix* frames; 
    int numberOfFrames;

    public:
    MataMvidia(const std::string& movieName, const std::string& creator, Matrix* frames, int numberOfFrames);
    MataMvidia(const MataMvidia& other);
    MataMvidia& operator=(const MataMvidia& other);
    std::string getMovieName() const;
    std::string getcreatorName() const;
    int getNumberOfFrames() const;
    Matrix operator[](int index);
    MataMvidia& operator+=(const MataMvidia& other);
    MataMvidia& operator+=(const Matrix& newFrame); 
    friend std::ostream &operator<<(std::ostream &os, const MataMvidia &movie);
    ~MataMvidia();
};

MataMvidia operator+(const MataMvidia& leftMovie, const MataMvidia& rightMovie);