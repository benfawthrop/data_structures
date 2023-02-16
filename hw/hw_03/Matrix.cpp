//
// Created by Benjamin Fawthrop on 2/4/23.
//

#include "Matrix.h"
#include <iostream>

//TODO: Build get_column operation and quarter operator

// constructors
Matrix::Matrix(unsigned int rows, unsigned int columns, double fill_val) { // fill constructor
    height = rows; // sets height private var
    width = columns; // sets width private var
    matrix = create_matrix(rows, columns, fill_val);
}

// default constructor
Matrix::Matrix() {
    height = 0;
    width = 0;
    matrix = NULL;
}

Matrix::Matrix(const Matrix &other) { // copy constructor
    height = other.getHeight();
    width = other.getWidth();
    matrix = create_matrix(height, width, 0.0);
    // copies the given matrix into a separate memory location so that
    // both matrices can be edited without interference
    for (unsigned int y = 0; y < height; y++){
        for (unsigned int x = 0; x < width; x++){
            matrix[y][x] = other.getMatrix()[y][x];
        }
    }
}

// getters
bool Matrix::get(unsigned int row, unsigned int column, double& value){
    // evaluates whether or not the given coords are in the matrix
    // if so, the value at that point is stored in `value`
    bool in_bounds = ( (height > row && row >= 0) && (width > column && column >= 0) );
    if (in_bounds){
        value = matrix[row][column];
    }
    // returns if the point exists or not
    return in_bounds;
}

// returns a double* which points to the row at position row_num
double* Matrix::get_row(unsigned int row_num) {
    if (row_num > height || row_num < 0){
        double* r = NULL;
        return r; // null if out of bounds
    }
    double* final = new double[width];
    for (unsigned int x = 0; x < width; x++){
        final[x] = matrix[row_num][x]; // creates array
    }
    return final;
}

// returns a double* which pointer to a column and position column num
double* Matrix::get_col(unsigned int col_num) {
    if (col_num > width || col_num < 0){
        double* r = NULL;
        return r; // null if out of bounds
    }
    double* final; // allocates memory for our column array
    final = new double[height];
    for (unsigned int y = 0; y < height; y++){
        final[y] = matrix[y][col_num]; // creates array
    }
    return final; // returns the pointer to the array
}

// setters
// clears the current matrix and
void Matrix::clear(){
    if (matrix != NULL) {
        for (unsigned int i = 0; i < height; i++) {
            delete[] matrix[i]; // deletes each column in the matrix
        }
        delete[] matrix; // deletes the rows of the matrix
        matrix = NULL;
    }
    height = 0; // resets height
    width = 0; // resets width
}

// sets the val of the given point to `value` if the space is within the matrix
bool Matrix::set(unsigned int row, unsigned int column, double value){
    bool in_bounds = ( (height > row && row >= 0) && (width > column && column >= 0) );
    if (in_bounds){
        matrix[row][column] = value;
    }
    return in_bounds;
}

// private fxns
// this is a helper function that creates a 2d array on the heap
double** Matrix::create_matrix(unsigned int rows, unsigned int columns, double fill_val){
    double** m = new double*[height]; // allocates space on the heap for our matrix rows
    for (unsigned int i = 0; i < rows; i++){
        m[i] = new double[columns]; // creates columns within respective rows
        for (unsigned int j = 0; j < columns; j++){
            m[i][j] = fill_val; // fills in each space
        }
    }
    return m;
}

// multiplies all elements by a given coeff
void Matrix::multiply_by_coefficient(double coeff){
    for (unsigned int i = 0; i < height; i++) {
        for (unsigned int j = 0; j < width; j++) {
            //loops through all elements and multiplies each by coeff
            matrix[i][j] *= coeff;
        }
    }
}

// swaps two rows
bool Matrix::swap_row(unsigned int source, unsigned int target){
    // ensures that the indices are in bounds
    bool in_bounds = (source < height && source > -1) && (target < height && target > -1);
    // creates temp memory location and swaps the rows
    if (in_bounds) {
        double* temp;
        temp = matrix[source];
        matrix[source] = matrix[target];
        matrix[target] = temp;
        //deallocates memory
        delete[] temp;
    }
    return in_bounds;
}

// this function transposes the matrix
// essentially the same operation as flipping it over the line y = x
void Matrix::transpose(){
    // holds temp matrix
    double** temp = create_matrix(width, height, 0.0);
    // creates new width and height
    unsigned int _width = height;
    unsigned int _height = width;
    // loops through and transposes the matrix
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int j = 0; j < width; j++){
            temp[j][i] = matrix[i][j];
        }
    }
    // clears the current matrix and replaces it
    clear();
    matrix = temp;
    height = _height;
    width = _width;
    // deallocates memory
    for (unsigned int i = 0; i < height; i++){
        delete[] temp[i];
    }
    delete[] temp;

}

// adds two matrices together
bool Matrix::add(const Matrix& m){
    // ensures they are the same size
    bool same_size = (height == m.getHeight() && width == m.getWidth());
    // loops through each element of each matrix and performs the add operation
    if (same_size){
        for (unsigned int y = 0; y < height; y++){
            for (unsigned int x = 0; x < width; x++){
                matrix[y][x] += m.getMatrix()[y][x];
            }
        }
    }
    return same_size;
}
// subtracts m from `matrix`
bool Matrix::subtract(const Matrix& m){
    // ensures they are the same size
    bool same_size = (height == m.getHeight() && width == m.getWidth());
    // loops through each element of each matrix and performs the subtract operation
    if (same_size){
        for (unsigned int y = 0; y < height; y++){
            for (unsigned int x = 0; x < width; x++){
                matrix[y][x] -= m.getMatrix()[y][x];
            }
        }
    }
    return same_size;
}


// overloads the << operator in order to print your matrix
std::ostream& operator<< (std::ostream& out, const Matrix& m){
    out << m.getHeight() << " x " << m.getWidth() << " matrix:" << std::endl;
    out << '[';
    // loops through all of our matrix and prints out each element accordingly
    for (unsigned int y = 0; y < m.getHeight(); y++){
        for (unsigned int x = 0; x < m.getWidth(); x++){
            out << " " << m.getMatrix()[y][x];
        }
        if (y < m.getHeight() - 1){
            out << std::endl;
        }
    }
    out << " ]" << std::endl;
    return out;
}

// compares two matrices for equality
bool operator== (const Matrix& m1, const Matrix& m2){
    // makes sure both Matrices are identical in size
    bool same_size = (m1.getHeight() == m2.getHeight() &&
            m1.getWidth() == m2.getWidth());
    // loops through each element of both matrices to see if there are any inequalities
    // if there are, the fxn returns false
    if (same_size){
        for (unsigned int y = 0; y < m1.getHeight(); y++){
            for (unsigned int x = 0; x < m1.getWidth(); x++){
                if (m1.getMatrix()[y][x] != m2.getMatrix()[y][x]){
                    return false;
                }
            }
        }
    }
    return same_size;
}

// compares two matrices for inequality
bool operator!= (const Matrix& m1, const Matrix& m2){
    //uses our predefined == operator and just return the opposite
    return !(operator==(m1, m2));
}

// this is a helper function that is responsible for creating a single matrix
// object for use in the quarter function
// it takes arguments for starting and stopping values of x and y which it uses to create a
// partial matrix
Matrix Matrix::makeOneQuarter(unsigned int y_start, unsigned int y_stop,
                              unsigned int x_start, unsigned int x_stop) {
    unsigned int _width = x_stop - x_start;
    unsigned int _height = y_stop - y_start;
    Matrix newMat(_height, _width, 0.0);
    for (unsigned int y = 0; y < _height; y++){
        for (unsigned int x = 0; x < _width; x++){
            newMat.set(y, x, matrix[y + y_start][x + x_start]);
        }
    }
    return newMat;
}



// function responsible for quartering our matrix
// utilizes our makeOneQuarter function to do most of the heavy lifting
Matrix* Matrix::quarter() {
    unsigned int height_quotient = height / 2 + (height % 2 != 0);
    unsigned int width_quotient = width / 2 + (width % 2 != 0);
    // allocates memory
    Matrix* final = new Matrix[4];
    // adds the quarters

    final[0] = makeOneQuarter(0, height_quotient, 0, width_quotient);
    final[1] = makeOneQuarter(0, height_quotient, width_quotient, width);
    final[2] = makeOneQuarter(height_quotient - 1, height, 0, width_quotient);
    final[3] = makeOneQuarter(height_quotient - 1, height, width_quotient, width);

    return final; // returns our array
}

// overloads the = operator
Matrix& Matrix::operator=(const Matrix &other) {
    // essentially the same logic as the copy constructor
    // checks to see if the array has already been cleared
    if (this == &other){
        return *this;
    }
    clear();
    height = other.getHeight();
    width = other.getWidth();
    matrix = create_matrix(height, width, 0.0);
    // copies the given matrix into a separate memory location so that
    // both matrices can be edited without interference
    for (unsigned int y = 0; y < height; y++){
        for (unsigned int x = 0; x < width; x++){
            matrix[y][x] = other.getMatrix()[y][x];
        }
    }
    return *this;
}




