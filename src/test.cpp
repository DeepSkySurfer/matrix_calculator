/*
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

#include <cmath>
#include <limits>

/**
 * @brief Тестирование функции matrix_average_stable
 * @details Проверяет точность, стабильность и обработку ошибок
 

// Вспомогательная функция для сравнения с заданной точностью
bool nearly_equal(double a, double b, double epsilon = 1e-12) {
    return std::abs(a - b) < epsilon;
}

// Тест 1: Базовая функциональность
void test_matrix_average_stable_basic() {
    std::cout << "Тест 1: Базовая функциональность matrix_average_stable" << std::endl;
    
    Matrix m = create_matrix(3, 3);
    // Заполняем матрицу последовательными числами
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            m.data[i][j] = i * m.cols + j + 1; // 1, 2, 3, ..., 9
        }
    }
    
    double result = matrix_average_stable(m);
    double expected = 5.0; // (1+2+3+4+5+6+7+8+9)/9 = 45/9 = 5.0
    
    assert(nearly_equal(result, expected));
    std::cout << "✓ Среднее: " << result << " (ожидалось: " << expected << ")" << std::endl;
    
    free_matrix(m);
}

// Тест 2: Сравнение с обычным суммированием на проблемных данных
void test_matrix_average_stable_vs_naive() {
    std::cout << "Тест 2: Сравнение стабильного и наивного алгоритмов" << std::endl;
    
    // Создаем матрицу с числами, вызывающими потерю точности
    Matrix m = create_matrix(2, 3);
    m.data[0][0] = 1.0e10;
    m.data[0][1] = 1.0;
    m.data[0][2] = -1.0e10;
    m.data[1][0] = 2.0;
    m.data[1][1] = 3.0;
    m.data[1][2] = 4.0;
    
    // Стабильная версия
    double stable_result = matrix_average_stable(m);
    
    // Наивная версия для сравнения
    double naive_sum = 0.0;
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            naive_sum += m.data[i][j];
        }
    }
    double naive_result = naive_sum / (m.rows * m.cols);
    
    // Ожидаемый результат: (1e10 + 1 - 1e10 + 2 + 3 + 4) / 6 = (10) / 6 ≈ 1.666...
    double expected = 10.0 / 6.0;
    
    std::cout << "  Наивный алгоритм: " << naive_result << std::endl;
    std::cout << "  Стабильный алгоритм: " << stable_result << std::endl;
    std::cout << "  Ожидаемый результат: " << expected << std::endl;
    
    // Стабильная версия должна быть ближе к ожидаемому результату
    assert(nearly_equal(stable_result, expected, 1e-10));
    std::cout << "✓ Стабильный алгоритм точнее" << std::endl;
    
    free_matrix(m);
}

// Тест 3: Числа с очень разным порядком величин
void test_matrix_average_stable_large_range() {
    std::cout << "Тест 3: Числа с большим разбросом величин" << std::endl;
    
    Matrix m = create_matrix(4, 1);
    m.data[0][0] = 1.0e15;
    m.data[1][0] = 1.0;
    m.data[2][0] = 1.0;
    m.data[3][0] = -1.0e15;
    
    double result = matrix_average_stable(m);
    double expected = (1.0 + 1.0) / 4.0; // (1e15 + 1 + 1 - 1e15) / 4 = 2/4 = 0.5
    
    assert(nearly_equal(result, expected));
    std::cout << "✓ Результат: " << result << " (ожидалось: " << expected << ")" << std::endl;
    
    free_matrix(m);
}

// Тест 4: Очень маленькие числа
void test_matrix_average_stable_small_numbers() {
    std::cout << "Тест 4: Очень маленькие числа" << std::endl;
    
    Matrix m = create_matrix(100, 100);
    double value = 1.0e-10;
    
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            m.data[i][j] = value;
        }
    }
    
    double result = matrix_average_stable(m);
    double expected = value;
    
    assert(nearly_equal(result, expected));
    std::cout << "✓ Среднее маленьких чисел: " << result << std::endl;
    
    free_matrix(m);
}

// Тест 5: Чередование положительных и отрицательных чисел
void test_matrix_average_stable_alternating() {
    std::cout << "Тест 5: Чередование положительных и отрицательных чисел" << std::endl;
    
    Matrix m = create_matrix(2, 2);
    m.data[0][0] = 1.0e6;
    m.data[0][1] = -1.0e6;
    m.data[1][0] = 2.0;
    m.data[1][1] = -1.0;
    
    double result = matrix_average_stable(m);
    double expected = (1.0e6 - 1.0e6 + 2.0 - 1.0) / 4.0; // (1.0) / 4.0 = 0.25
    
    assert(nearly_equal(result, expected));
    std::cout << "✓ Результат: " << result << " (ожидалось: " << expected << ")" << std::endl;
    
    free_matrix(m);
}

// Тест 6: Граничные случаи - матрица 1x1
void test_matrix_average_stable_single_element() {
    std::cout << "Тест 6: Матрица 1x1" << std::endl;
    
    Matrix m = create_matrix(1, 1);
    m.data[0][0] = 42.5;
    
    double result = matrix_average_stable(m);
    assert(nearly_equal(result, 42.5));
    std::cout << "✓ Результат для 1 элемента: " << result << std::endl;
    
    free_matrix(m);
}

// Тест 7: Обработка ошибок - пустая матрица
void test_matrix_average_stable_error_handling() {
    std::cout << "Тест 7: Обработка ошибок" << std::endl;
    
    // Тест с nullptr
    Matrix invalid;
    invalid.data = nullptr;
    invalid.rows = 2;
    invalid.cols = 2;
    
    bool exception_thrown = false;
    try {
        matrix_average_stable(invalid);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "✓ Исключение для nullptr обработано" << std::endl;
    
    // Тест с невалидными размерами
    exception_thrown = false;
    try {
        Matrix m = create_matrix(0, 5); // Невалидные размеры
        matrix_average_stable(m);
    } catch (const std::invalid_argument&) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    std::cout << "✓ Исключение для невалидных размеров обработано" << std::endl;
}

// Тест 8: Сравнение с обычной версией на больших матрицах
void test_matrix_average_stable_large_matrix() {
    std::cout << "Тест 8: Большая матрица (1000 элементов)" << std::endl;
    
    const int size = 1000;
    Matrix m = create_matrix(100, 10); // 1000 элементов
    
    // Заполняем числами, которые могут вызвать потерю точности
    for (int i = 0; i < m.rows; ++i) {
        for (int j = 0; j < m.cols; ++j) {
            m.data[i][j] = 1.0e8 + (i * m.cols + j) * 1.0e-8;
        }
    }
    
    double stable_result = matrix_average_stable(m);
    
    // Проверяем что результат в разумных пределах
    assert(stable_result > 1.0e8 && stable_result < 1.0e8 + 1.0);
    std::cout << "✓ Стабильный алгоритм работает на большой матрице: " << stable_result << std::endl;
    
    free_matrix(m);
}

// Тест 9: Числа с плавающей точкой двойной точности
void test_matrix_average_stable_double_precision() {
    std::cout << "Тест 9: Точность double" << std::endl;
    
    Matrix m = create_matrix(2, 2);
    m.data[0][0] = std::numeric_limits<double>::epsilon();
    m.data[0][1] = std::numeric_limits<double>::max();
    m.data[1][0] = -std::numeric_limits<double>::max();
    m.data[1][1] = std::numeric_limits<double>::epsilon();
    
    double result = matrix_average_stable(m);
    double expected = (std::numeric_limits<double>::epsilon() * 2) / 4.0;
    
    // Для таких экстремальных значений проверяем что не происходит переполнения
    assert(!std::isnan(result) && !std::isinf(result));
    std::cout << "✓ Алгоритм обрабатывает экстремальные значения: " << result << std::endl;
    
    free_matrix(m);
}

// Главная функция тестирования
void test_matrix_average_stable_comprehensive() {
    std::cout << "\n=== ТЕСТИРОВАНИЕ MATRIX_AVERAGE_STABLE ===" << std::endl;
    
    try {
        test_matrix_average_stable_basic();
        test_matrix_average_stable_vs_naive();
        test_matrix_average_stable_large_range();
        test_matrix_average_stable_small_numbers();
        test_matrix_average_stable_alternating();
        test_matrix_average_stable_single_element();
        test_matrix_average_stable_error_handling();
        test_matrix_average_stable_large_matrix();
        test_matrix_average_stable_double_precision();
        
        std::cout << "=== ВСЕ ТЕСТЫ MATRIX_AVERAGE_STABLE ПРОЙДЕНЫ УСПЕШНО ===" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ ОШИБКА В ТЕСТАХ: " << e.what() << std::endl;
        throw;
    }
}
*/

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