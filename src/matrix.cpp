#include "matrix.h"
#include <iostream>
#include <cmath>
#include <stdexcept>

Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) throw std::invalid_argument("Invalid matrix size");
    Matrix m;
    m.rows = rows;
    m.cols = cols;
    m.data = new double*[rows];
    for (int i = 0; i < rows; i++) {
        m.data[i] = new double[cols]{0};
    }
    return m;
}

void free_matrix(Matrix m) {
    if (!m.data) return;
    for (int i = 0; i < m.rows; i++) {
        delete[] m.data[i];
    }
    delete[] m.data;
}

Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols)
        throw std::invalid_argument("Matrix sizes must match for addition");

    Matrix res = create_matrix(a.rows, a.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            res.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return res;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows)
        throw std::invalid_argument("Matrix sizes are incompatible for multiplication");

    Matrix res = create_matrix(a.rows, b.cols);
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            double sum = 0;
            for (int k = 0; k < a.cols; k++) {
                sum += a.data[i][k] * b.data[k][j];
            }
            res.data[i][j] = sum;
        }
    }
    return res;
}

Matrix matrix_transpose(Matrix m) {
    Matrix res = create_matrix(m.cols, m.rows);
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            res.data[j][i] = m.data[i][j];
        }
    }
    return res;
}

void print_matrix(Matrix m) {
    for (int i = 0; i < m.rows; i++) {
        std::cout << " [";
        for (int j = 0; j < m.cols; j++) {
            std::cout << m.data[i][j];
            if (j < m.cols - 1) std::cout << "   ";
        }
        std::cout << "]\n";
    }
}

Matrix matrix_from_array(double* data, int rows, int cols) {
    Matrix m = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m.data[i][j] = data[i * cols + j];
        }
    }
    return m;
}

double matrix_average(Matrix m) {
    if (m.rows <= 0 || m.cols <= 0 || !m.data) {
        throw std::invalid_argument("Invalid matrix");
    }
    
    double sum = 0.0;
    int total_elements = m.rows * m.cols;
    
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            sum += m.data[i][j];
        }
    }
    
    return sum / total_elements;
}