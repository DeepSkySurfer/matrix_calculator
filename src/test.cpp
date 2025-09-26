#include "matrix.h"
#include <cassert>
#include <iostream>
#include <cmath>

const double EPSILON = 1e-10;

bool matrices_equal(Matrix a, Matrix b, double tolerance = EPSILON) {
    if (a.rows != b.rows || a.cols != b.cols) {
        return false;
    }
    
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            if (fabs(a.data[i][j] - b.data[i][j]) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

void test_create_and_free_matrix() {
    std::cout << "Тест 1: Создание и освобождение матрицы" << std::endl;
    
    Matrix m = create_matrix(3, 4);
    assert(m.rows == 3);
    assert(m.cols == 4);
    assert(m.data != nullptr);
    
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            assert(m.data[i][j] == 0.0);
        }
    }
    
    free_matrix(m);
    std::cout << "✓ Успешно" << std::endl;
}

void test_matrix_addition() {
    std::cout << "Тест 2: Сложение матриц" << std::endl;
    
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    
    A.data[0][0] = 1.0; A.data[0][1] = 2.0;
    A.data[1][0] = 3.0; A.data[1][1] = 4.0;
    
    B.data[0][0] = 5.0; B.data[0][1] = 6.0;
    B.data[1][0] = 7.0; B.data[1][1] = 8.0;
    
    Matrix result = matrix_add(A, B);
    
    assert(result.rows == 2);
    assert(result.cols == 2);
    assert(result.data[0][0] == 6.0);
    assert(result.data[0][1] == 8.0);
    assert(result.data[1][0] == 10.0);
    assert(result.data[1][1] == 12.0);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
    std::cout << "✓ Успешно" << std::endl;
}

int main() {
    std::cout << "=== ЗАПУСК ТЕСТОВ ===" << std::endl;
    
    try {
        test_create_and_free_matrix();
        test_matrix_addition();
        
        std::cout << "=== ВСЕ ТЕСТЫ ПРОЙДЕНЫ ===" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
}