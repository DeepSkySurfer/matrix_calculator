#include "matrix.h"
#include <cassert>
#include <iostream>
#include <cmath>

// Константа для сравнения чисел с плавающей точкой
const double EPSILON = 1e-10;

// Вспомогательная функция для сравнения матриц
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

// Существующие тесты...
void test_create_and_free_matrix() { /* ... */ }
void test_matrix_addition() { /* ... */ }

// Новые тесты для matrix_average_stable
void test_matrix_average_stable_comprehensive() { /* ... */ }

/**
 * @brief Главная функция тестов
 * @return int Код возврата (0 - успех, 1 - ошибка)
 */
int main() {
    std::cout << "=== ЗАПУСК ТЕСТОВ МАТРИЧНОГО КАЛЬКУЛЯТОРА ===" << std::endl;
    
    try {
        // Существующие тесты...
        test_create_and_free_matrix();
        test_matrix_addition();
        // ... другие тесты ...
        
        // Новые тесты для matrix_average_stable
        test_matrix_average_stable_comprehensive();
        
        std::cout << "=== ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ ОШИБКА: " << e.what() << std::endl;
        return 1;
    }
    
    
}
bool test_matrix_average_comprehensive() {
    bool all_passed = true;
    
    try {
        // Тест на нормальную работу
        Matrix m1 = create_matrix(2, 2);
        m1.data[0][0] = 1.0; m1.data[0][1] = 2.0;
        m1.data[1][0] = 3.0; m1.data[1][1] = 4.0;
        
        double result = matrix_average(m1);
        if (fabs(result - 2.5) > 1e-9) {
            std::cout << "FAIL: Expected 2.5, got " << result << std::endl;
            all_passed = false;
        }
        free_matrix(m1);
        
        // Тест на пустую матрицу (должно бросить исключение)
        Matrix m2;
        m2.rows = 0;
        m2.cols = 0;
        m2.data = nullptr;
        
        try {
            matrix_average(m2);
            std::cout << "FAIL: Expected exception for empty matrix" << std::endl;
            all_passed = false;
        } catch (const std::invalid_argument& e) {
            // Ожидаемое поведение
        }
        
    } catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
        all_passed = false;
    }
    
    return all_passed;
}
    void test_matrix_average() {
    std::cout << "=== Testing matrix_average function ===" << std::endl;
    
    // Тест 1: Обычная матрица 2x3
    Matrix m1 = create_matrix(2, 3);
    m1.data[0][0] = 1.0; m1.data[0][1] = 2.0; m1.data[0][2] = 3.0;
    m1.data[1][0] = 4.0; m1.data[1][1] = 5.0; m1.data[1][2] = 6.0;
    
    double avg1 = matrix_average(m1);
    double expected1 = 3.5; // (1+2+3+4+5+6)/6 = 21/6 = 3.5
    std::cout << "Test 1 - Normal 2x3 matrix: " << avg1;
    if (std::fabs(avg1 - expected1) < 1e-9) {
        std::cout << " ✓ PASS" << std::endl;
    } else {
        std::cout << " ✗ FAIL (expected " << expected1 << ")" << std::endl;
    }
    free_matrix(m1);
    
    // Тест 2: Матрица 1x1 (один элемент)
    Matrix m2 = create_matrix(1, 1);
    m2.data[0][0] = 42.5;
    
    double avg2 = matrix_average(m2);
    double expected2 = 42.5;
    std::cout << "Test 2 - Single element: " << avg2;
    if (std::fabs(avg2 - expected2) < 1e-9) {
        std::cout << " ✓ PASS" << std::endl;
    } else {
        std::cout << " ✗ FAIL (expected " << expected2 << ")" << std::endl;
    }
    free_matrix(m2);
    
    // Тест 3: Матрица с отрицательными числами
    Matrix m3 = create_matrix(2, 2);
    m3.data[0][0] = -1.0; m3.data[0][1] = 2.0;
    m3.data[1][0] = 3.0; m3.data[1][1] = -4.0;
    
    double avg3 = matrix_average(m3);
    double expected3 = 0.0; // (-1+2+3-4)/4 = 0
    std::cout << "Test 3 - Negative numbers: " << avg3;
    if (std::fabs(avg3 - expected3) < 1e-9) {
        std::cout << " ✓ PASS" << std::endl;
    } else {
        std::cout << " ✗ FAIL (expected " << expected3 << ")" << std::endl;
    }
    free_matrix(m3);
    
    // Тест 4: Нулевая матрица
    Matrix m4 = create_matrix(3, 2);
    // Все элементы уже инициализированы нулями
    
    double avg4 = matrix_average(m4);
    double expected4 = 0.0;
    std::cout << "Test 4 - Zero matrix: " << avg4;
    if (std::fabs(avg4 - expected4) < 1e-9) {
        std::cout << " ✓ PASS" << std::endl;
    } else {
        std::cout << " ✗ FAIL (expected " << expected4 << ")" << std::endl;
    }
    free_matrix(m4);
    
    // Тест 5: Дробные числа
    Matrix m5 = create_matrix(1, 4);
    m5.data[0][0] = 0.1; m5.data[0][1] = 0.2; 
    m5.data[0][2] = 0.3; m5.data[0][3] = 0.4;
    
    double avg5 = matrix_average(m5);
    double expected5 = 0.25; // (0.1+0.2+0.3+0.4)/4 = 1.0/4 = 0.25
    std::cout << "Test 5 - Fractional numbers: " << avg5;
    if (std::fabs(avg5 - expected5) < 1e-9) {
        std::cout << " ✓ PASS" << std::endl;
    } else {
        std::cout << " ✗ FAIL (expected " << expected5 << ")" << std::endl;
    }
    free_matrix(m5);
    
    std::cout << "=== Matrix average tests completed ===" << std::endl;
}

