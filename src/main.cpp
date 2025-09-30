#include "matrix.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <cassert>

// ===== ТЕСТОВЫЕ ФУНКЦИИ =====

void test_create_and_free_matrix() {
    std::cout << "=== Testing create_matrix and free_matrix ===" << std::endl;
    
    // Тест 1: Создание обычной матрицы
    Matrix m1 = create_matrix(2, 3);
    assert(m1.rows == 2);
    assert(m1.cols == 3);
    assert(m1.data != nullptr);
    std::cout << "PASS: Normal matrix creation" << std::endl;
    
    // Тест 2: Проверка инициализации нулями
    for (int i = 0; i < m1.rows; i++) {
        for (int j = 0; j < m1.cols; j++) {
            assert(m1.data[i][j] == 0.0);
        }
    }
    std::cout << "PASS: Matrix initialized with zeros" << std::endl;
    
    // Тест 3: Освобождение памяти
    free_matrix(m1);
    std::cout << "PASS: Matrix memory freed" << std::endl;
    
    // Тест 4: Исключение при невалидных размерах
    try {
        Matrix m_invalid = create_matrix(0, 5);
        assert(false && "Should have thrown exception");
    } catch (const std::invalid_argument& e) {
        std::cout << "PASS: Correctly caught invalid size exception" << std::endl;
    }
}

void test_matrix_add() {
    std::cout << "\n=== Testing matrix_add ===" << std::endl;
    
    // Тест 1: Обычное сложение
    Matrix a = create_matrix(2, 2);
    Matrix b = create_matrix(2, 2);
    
    a.data[0][0] = 1.0; a.data[0][1] = 2.0;
    a.data[1][0] = 3.0; a.data[1][1] = 4.0;
    
    b.data[0][0] = 5.0; b.data[0][1] = 6.0;
    b.data[1][0] = 7.0; b.data[1][1] = 8.0;
    
    Matrix result = matrix_add(a, b);
    assert(result.rows == 2 && result.cols == 2);
    assert(result.data[0][0] == 6.0);
    assert(result.data[0][1] == 8.0);
    assert(result.data[1][0] == 10.0);
    assert(result.data[1][1] == 12.0);
    std::cout << "PASS: Normal matrix addition" << std::endl;
    
    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
    
    // Тест 2: Исключение при разных размерах
    Matrix c = create_matrix(2, 3);
    Matrix d = create_matrix(3, 2);
    
    try {
        matrix_add(c, d);
        assert(false && "Should have thrown exception");
    } catch (const std::invalid_argument& e) {
        std::cout << "PASS: Correctly caught size mismatch exception" << std::endl;
    }
    
    free_matrix(c);
    free_matrix(d);
}

void test_matrix_multiply() {
    std::cout << "\n=== Testing matrix_multiply ===" << std::endl;
    
    // Тест 1: Обычное умножение
    Matrix a = create_matrix(2, 3);
    Matrix b = create_matrix(3, 2);
    
    a.data[0][0] = 1; a.data[0][1] = 2; a.data[0][2] = 3;
    a.data[1][0] = 4; a.data[1][1] = 5; a.data[1][2] = 6;
    
    b.data[0][0] = 7; b.data[0][1] = 8;
    b.data[1][0] = 9; b.data[1][1] = 10;
    b.data[2][0] = 11; b.data[2][1] = 12;
    
    Matrix result = matrix_multiply(a, b);
    assert(result.rows == 2 && result.cols == 2);
    assert(result.data[0][0] == 58);  // 1*7 + 2*9 + 3*11
    assert(result.data[0][1] == 64);  // 1*8 + 2*10 + 3*12
    assert(result.data[1][0] == 139); // 4*7 + 5*9 + 6*11
    assert(result.data[1][1] == 154); // 4*8 + 5*10 + 6*12
    std::cout << "PASS: Normal matrix multiplication" << std::endl;
    
    free_matrix(a);
    free_matrix(b);
    free_matrix(result);
    
    // Тест 2: Исключение при несовместимых размерах
    Matrix c = create_matrix(2, 3);
    Matrix d = create_matrix(2, 3);
    
    try {
        matrix_multiply(c, d);
        assert(false && "Should have thrown exception");
    } catch (const std::invalid_argument& e) {
        std::cout << "PASS: Correctly caught incompatible sizes exception" << std::endl;
    }
    
    free_matrix(c);
    free_matrix(d);
}

void test_matrix_transpose() {
    std::cout << "\n=== Testing matrix_transpose ===" << std::endl;
    
    // Тест 1: Транспонирование прямоугольной матрицы
    Matrix m = create_matrix(2, 3);
    m.data[0][0] = 1; m.data[0][1] = 2; m.data[0][2] = 3;
    m.data[1][0] = 4; m.data[1][1] = 5; m.data[1][2] = 6;
    
    Matrix result = matrix_transpose(m);
    assert(result.rows == 3 && result.cols == 2);
    assert(result.data[0][0] == 1); assert(result.data[0][1] == 4);
    assert(result.data[1][0] == 2); assert(result.data[1][1] == 5);
    assert(result.data[2][0] == 3); assert(result.data[2][1] == 6);
    std::cout << "PASS: Rectangular matrix transpose" << std::endl;
    
    free_matrix(m);
    free_matrix(result);
    
    // Тест 2: Транспонирование квадратной матрицы
    Matrix square = create_matrix(2, 2);
    square.data[0][0] = 1; square.data[0][1] = 2;
    square.data[1][0] = 3; square.data[1][1] = 4;
    
    Matrix square_t = matrix_transpose(square);
    assert(square_t.data[0][0] == 1); assert(square_t.data[0][1] == 3);
    assert(square_t.data[1][0] == 2); assert(square_t.data[1][1] == 4);
    std::cout << "PASS: Square matrix transpose" << std::endl;
    
    free_matrix(square);
    free_matrix(square_t);
}

void test_matrix_from_array() {
    std::cout << "\n=== Testing matrix_from_array ===" << std::endl;
    
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix m = matrix_from_array(data, 2, 3);
    
    assert(m.rows == 2 && m.cols == 3);
    assert(m.data[0][0] == 1.0); assert(m.data[0][1] == 2.0); assert(m.data[0][2] == 3.0);
    assert(m.data[1][0] == 4.0); assert(m.data[1][1] == 5.0); assert(m.data[1][2] == 6.0);
    std::cout << "PASS: Matrix from array creation" << std::endl;
    
    free_matrix(m);
}

void test_matrix_average() {
    std::cout << "\n=== Testing matrix_average ===" << std::endl;
    
    // Тест 1: Обычная матрица
    Matrix m1 = create_matrix(2, 3);
    m1.data[0][0] = 1.0; m1.data[0][1] = 2.0; m1.data[0][2] = 3.0;
    m1.data[1][0] = 4.0; m1.data[1][1] = 5.0; m1.data[1][2] = 6.0;
    
    double avg1 = matrix_average(m1);
    assert(std::fabs(avg1 - 3.5) < 1e-9); // (1+2+3+4+5+6)/6 = 3.5
    std::cout << "PASS: Normal matrix average" << std::endl;
    free_matrix(m1);
    
    // Тест 2: Один элемент
    Matrix m2 = create_matrix(1, 1);
    m2.data[0][0] = 42.0;
    double avg2 = matrix_average(m2);
    assert(std::fabs(avg2 - 42.0) < 1e-9);
    std::cout << "PASS: Single element average" << std::endl;
    free_matrix(m2);
    
    // Тест 3: Отрицательные числа
    Matrix m3 = create_matrix(2, 2);
    m3.data[0][0] = -1.0; m3.data[0][1] = 2.0;
    m3.data[1][0] = 3.0; m3.data[1][1] = -4.0;
    double avg3 = matrix_average(m3);
    assert(std::fabs(avg3 - 0.0) < 1e-9); // (-1+2+3-4)/4 = 0
    std::cout << "PASS: Negative numbers average" << std::endl;
    free_matrix(m3);
    
    // Тест 4: Исключение для невалидной матрицы
    Matrix invalid;
    invalid.rows = 0;
    invalid.cols = 0;
    invalid.data = nullptr;
    
    try {
        matrix_average(invalid);
        assert(false && "Should have thrown exception");
    } catch (const std::invalid_argument& e) {
        std::cout << "PASS: Correctly caught invalid matrix exception" << std::endl;
    }
}

void test_print_matrix() {
    std::cout << "\n=== Testing print_matrix ===" << std::endl;
    
    Matrix m = create_matrix(2, 2);
    m.data[0][0] = 1.5; m.data[0][1] = 2.5;
    m.data[1][0] = 3.5; m.data[1][1] = 4.5;
    
    std::cout << "Matrix output (visual check):" << std::endl;
    print_matrix(m);
    std::cout << "PASS: Matrix printed without errors" << std::endl;
    
    free_matrix(m);
}

void run_all_tests() {
    std::cout << "🚀 Starting comprehensive matrix tests...\n" << std::endl;
    
    test_create_and_free_matrix();
    test_matrix_add();
    test_matrix_multiply();
    test_matrix_transpose();
    test_matrix_from_array();
    test_matrix_average();
    test_print_matrix();
    
    std::cout << "\n🎉 All tests completed successfully!" << std::endl;
}

// ===== ОСНОВНАЯ ФУНКЦИЯ =====

int main() {
    try {
        run_all_tests();
        
        // Демонстрация работы
        std::cout << "\n=== Demonstration ===" << std::endl;
        
        // Создаем матрицы для демонстрации
        double data1[] = {1, 2, 3, 4, 5, 6};
        double data2[] = {7, 8, 9, 10, 11, 12};
        
        Matrix A = matrix_from_array(data1, 2, 3);
        Matrix B = matrix_from_array(data2, 2, 3);
        
        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);
        
        std::cout << "Matrix B:" << std::endl;
        print_matrix(B);
        
        std::cout << "A + B:" << std::endl;
        Matrix C = matrix_add(A, B);
        print_matrix(C);
        
        std::cout << "Average of A: " << matrix_average(A) << std::endl;
        std::cout << "Average of B: " << matrix_average(B) << std::endl;
        
        // Освобождаем память
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}