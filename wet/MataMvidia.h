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
    /**
     * Constructor to create a MataMvidia object.
     * 
     * @param movieName - the name of the movie.
     * @param creator - the name of the creator of the movie.
     * @param frames - an array of Matrix objects representing the frames of the movie.
     * @param numberOfFrames - the number of frames in the movie.
     */
    MataMvidia(const std::string& movieName, const std::string& creator, Matrix* frames, int numberOfFrames);

    /**
     * Copy constructor to create a deep copy of a MataMvidia object.
     * 
     * @param other - the MataMvidia object to copy.
     */
    MataMvidia(const MataMvidia& other);

    /**
     * Assignment operator to perform a deep copy of another MataMvidia object.
     * 
     * @param other - the MataMvidia object to copy.
     * 
     * @return - a reference to this MataMvidia object after copying.
     */
    MataMvidia& operator=(const MataMvidia& other);

    //do we need to delete this??
    // std::string getMovieName() const;
    // std::string getcreatorName() const;
    // int getNumberOfFrames() const;

    /**
     * Overload of the subscript operator to access a specific frame of the movie.
     * 
     * @param index - the index of the desired frame (0-based).
     * 
     * @return - a reference to the Matrix object representing the frame at the given index.
     *           If the index is out of bounds, behavior is undefined.
     */
    Matrix& operator[](int index);

    /**
     * Overload of the addition-assignment operator to append the frames of another movie.
     * 
     * @param other - the MataMvidia object whose frames are to be appended.
     * 
     * @return - a reference to this MataMvidia object after the operation.
     */
    MataMvidia& operator+=(const MataMvidia& other);

    /**
     * Overload of the addition-assignment operator to append a new frame to the movie.
     * 
     * @param newFrame - the Matrix object representing the new frame to be added.
     * 
     * @return - a reference to this MataMvidia object after the operation.
     */
    MataMvidia& operator+=(const Matrix& newFrame); 

    /**
     * Overload of the stream insertion operator to output the MataMvidia object.
     * 
     * @param os - the output stream.
     * @param movie - the MataMvidia object to output.
     * 
     * @return - the output stream with the MataMvidia object's content.
     */
    friend std::ostream &operator<<(std::ostream &os, const MataMvidia &movie);

    /**
     * Destructor to free allocated memory for the frames of the movie.
     */
    ~MataMvidia();
};

/**
 * Overload of the addition operator to combine two MataMvidia objects into a new movie.
 * 
 * @param leftMovie - the first MataMvidia object.
 * @param rightMovie - the second MataMvidia object.
 * 
 * @return - a new MataMvidia object containing the frames of both movies concatenated.
 */
MataMvidia operator+(const MataMvidia& leftMovie, const MataMvidia& rightMovie);