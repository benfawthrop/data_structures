//
// Created by Benjamin Fawthrop on 2/4/23.
//

#ifndef _ds_Matrix_
#define _ds_Matrix_
#include <iostream>


class Matrix {
public:
    // constructors
    Matrix();
    Matrix(unsigned int rows, unsigned int columns, double fill_val = 0.0); // fill constructor
    Matrix(const Matrix& other); // copy constructor
    ~Matrix() { clear(); } // destructor

    // getters
    unsigned int num_rows() const { return height; } //returns num rows
    unsigned int num_cols() const { return width; } // returns num cols
    bool get(unsigned int row, unsigned int column, double& value);
    double** getMatrix() const { return matrix; }
    unsigned int getHeight() const { return height; }
    unsigned int getWidth() const { return width; }
    double* get_row(unsigned int row_num);
    double* get_col(unsigned int col_num);


    // setters
    void clear();
    bool set(unsigned int row, unsigned int column, double value);
    void multiply_by_coefficient(double coeff);
    bool swap_row(unsigned int source, unsigned int target);
    void transpose();
    bool add(const Matrix& m);
    bool subtract(const Matrix& m);
    Matrix* quarter();
    Matrix& operator= (const Matrix& other);
private:
    // allocates mem for a matrix on the heap.  used by the fill constructor
    double** create_matrix(unsigned int rows, unsigned int columns, double fill_val);
    Matrix makeOneQuarter(unsigned int y_start, unsigned int y_stop,
                          unsigned int x_start, unsigned int x_stop);
    double** matrix;
    unsigned int height;
    unsigned int width;


};

std::ostream& operator<< (std::ostream& out, const Matrix& m);
bool operator== (const Matrix& m1, const Matrix& m2);
bool operator!= (const Matrix& m1, const Matrix& m2);


#endif //_ds_Matrix_

