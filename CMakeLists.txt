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

// Тест создания и освобождения матрицы
void test_create_and_free_matrix() {
    std::cout << "Тест 1: Создание и освобождение матрицы" << std::endl;
    
    // Тест создания нормальной матрицы
    Matrix m = create_matrix(3, 4);
    assert(m.rows == 3);
    assert(m.cols == 4);
    assert(m.data != nullptr);
    
    // Проверка инициализации нулями
    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            assert(m.data[i][j] == 0.0);
        }
    }
    
    free_matrix(m);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест обработки ошибок при создании матрицы
void test_invalid_matrix_creation() {
    std::cout << "Тест 2: Обработка невалидных размеров матрицы" << std::endl;
    
    bool exception_thrown = false;
    
    // Тест отрицательных размеров
    try {
        Matrix m = create_matrix(-1, 5);
    } catch (const std::invalid_argument& e) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    
    exception_thrown = false;
    try {
        Matrix m = create_matrix(2, 0);
    } catch (const std::invalid_argument& e) {
        exception_thrown = true;
    }
    assert(exception_thrown);
    
    std::cout << "✓ Успешно" << std::endl;
}

// Тест сложения матриц
void test_matrix_addition() {
    std::cout << "Тест 3: Сложение матриц" << std::endl;
    
    // Создание тестовых матриц 2x2
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    
    // Заполнение матрицы A: [[1, 2], [3, 4]]
    A.data[0][0] = 1.0; A.data[0][1] = 2.0;
    A.data[1][0] = 3.0; A.data[1][1] = 4.0;
    
    // Заполнение матрицы B: [[5, 6], [7, 8]]
    B.data[0][0] = 5.0; B.data[0][1] = 6.0;
    B.data[1][0] = 7.0; B.data[1][1] = 8.0;
    
    Matrix result = matrix_add(A, B);
    
    // Проверка результата: [[6, 8], [10, 12]]
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

// Тест сложения матриц с несовпадающими размерами
void test_matrix_addition_invalid() {
    std::cout << "Тест 4: Сложение матриц с несовпадающими размерами" << std::endl;
    
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);
    
    bool exception_thrown = false;
    try {
        Matrix result = matrix_add(A, B);
    } catch (const std::invalid_argument& e) {
        exception_thrown = true;
    }
    
    assert(exception_thrown);
    
    free_matrix(A);
    free_matrix(B);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест умножения матриц
void test_matrix_multiplication() {
    std::cout << "Тест 5: Умножение матриц" << std::endl;
    
    // Матрица A: 2x3
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;
    
    // Матрица B: 3x2
    Matrix B = create_matrix(3, 2);
    B.data[0][0] = 7; B.data[0][1] = 8;
    B.data[1][0] = 9; B.data[1][1] = 10;
    B.data[2][0] = 11; B.data[2][1] = 12;
    
    Matrix result = matrix_multiply(A, B);
    
    // Ожидаемый результат: 2x2
    // [1*7 + 2*9 + 3*11, 1*8 + 2*10 + 3*12] = [58, 64]
    // [4*7 + 5*9 + 6*11, 4*8 + 5*10 + 6*12] = [139, 154]
    assert(result.rows == 2);
    assert(result.cols == 2);
    assert(fabs(result.data[0][0] - 58.0) < EPSILON);
    assert(fabs(result.data[0][1] - 64.0) < EPSILON);
    assert(fabs(result.data[1][0] - 139.0) < EPSILON);
    assert(fabs(result.data[1][1] - 154.0) < EPSILON);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(result);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест умножения матриц с несовпадающими размерами
void test_matrix_multiplication_invalid() {
    std::cout << "Тест 6: Умножение матриц с несовпадающими размерами" << std::endl;
    
    Matrix A = create_matrix(2, 3);
    Matrix B = create_matrix(2, 3); // Несовместимые размеры
    
    bool exception_thrown = false;
    try {
        Matrix result = matrix_multiply(A, B);
    } catch (const std::invalid_argument& e) {
        exception_thrown = true;
    }
    
    assert(exception_thrown);
    
    free_matrix(A);
    free_matrix(B);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест транспонирования матрицы
void test_matrix_transpose() {
    std::cout << "Тест 7: Транспонирование матрицы" << std::endl;
    
    // Матрица 2x3
    Matrix m = create_matrix(2, 3);
    m.data[0][0] = 1; m.data[0][1] = 2; m.data[0][2] = 3;
    m.data[1][0] = 4; m.data[1][1] = 5; m.data[1][2] = 6;
    
    Matrix result = matrix_transpose(m);
    
    // Ожидаемый результат: 3x2
    // [[1, 4], [2, 5], [3, 6]]
    assert(result.rows == 3);
    assert(result.cols == 2);
    assert(result.data[0][0] == 1.0);
    assert(result.data[0][1] == 4.0);
    assert(result.data[1][0] == 2.0);
    assert(result.data[1][1] == 5.0);
    assert(result.data[2][0] == 3.0);
    assert(result.data[2][1] == 6.0);
    
    free_matrix(m);
    free_matrix(result);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест создания матрицы из массива
void test_matrix_from_array() {
    std::cout << "Тест 8: Создание матрицы из массива" << std::endl;
    
    double data[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};
    Matrix m = matrix_from_array(data, 2, 3);
    
    assert(m.rows == 2);
    assert(m.cols == 3);
    assert(m.data[0][0] == 1.0);
    assert(m.data[0][1] == 2.0);
    assert(m.data[0][2] == 3.0);
    assert(m.data[1][0] == 4.0);
    assert(m.data[1][1] == 5.0);
    assert(m.data[1][2] == 6.0);
    
    free_matrix(m);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест вывода матрицы (проверка что не падает)
void test_print_matrix() {
    std::cout << "Тест 9: Вывод матрицы (проверка отсутствия падений)" << std::endl;
    
    Matrix m = create_matrix(2, 2);
    m.data[0][0] = 1.5; m.data[0][1] = 2.25;
    m.data[1][0] = 3.75; m.data[1][1] = 4.1;
    
    // Просто проверяем что функция не падает
    print_matrix(m);
    
    // Тест с пустой матрицей
    Matrix empty;
    empty.data = nullptr;
    empty.rows = 0;
    empty.cols = 0;
    print_matrix(empty);
    
    free_matrix(m);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест с большой матрицей для проверки сокращенного вывода
void test_print_large_matrix() {
    std::cout << "Тест 10: Вывод большой матрицы" << std::endl;
    
    Matrix large = create_matrix(15, 12);
    // Заполняем некоторыми значениями
    for (int i = 0; i < large.rows; i++) {
        for (int j = 0; j < large.cols; j++) {
            large.data[i][j] = i + j * 0.1;
        }
    }
    
    print_matrix(large);
    free_matrix(large);
    std::cout << "✓ Успешно" << std::endl;
}

// Тест на утечки памяти
void test_memory_management() {
    std::cout << "Тест 11: Проверка управления памятью" << std::endl;
    
    // Создаем и освобождаем несколько матриц
    for (int i = 0; i < 100; i++) {
        Matrix m = create_matrix(10, 10);
        free_matrix(m);
    }
    
    // Тест вложенных операций
    Matrix A = create_matrix(3, 3);
    Matrix B = create_matrix(3, 3);
    
    Matrix sum = matrix_add(A, B);
    Matrix product = matrix_multiply(A, B);
    Matrix transposed = matrix_transpose(A);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(sum);
    free_matrix(product);
    free_matrix(transposed);
    
    std::cout << "✓ Успешно" << std::endl;
}

// Тест двойного освобождения (должно обрабатываться корректно)
void test_double_free() {
    std::cout << "Тест 12: Проверка двойного освобождения" << std::endl;
    
    Matrix m = create_matrix(2, 2);
    free_matrix(m);
    free_matrix(m); // Должно обработаться корректно без падения
    
    std::cout << "✓ Успешно" << std::endl;
}

// Главная функция запуска тестов
int main() {
    std::cout << "=== ЗАПУСК ТЕСТОВ МАТРИЧНОГО КАЛЬКУЛЯТОРА ===" << std::endl;
    std::cout << std::endl;
    
    try {
        test_create_and_free_matrix();
        test_invalid_matrix_creation();
        test_matrix_addition();
        test_matrix_addition_invalid();
        test_matrix_multiplication();
        test_matrix_multiplication_invalid();
        test_matrix_transpose();
        test_matrix_from_array();
        test_print_matrix();
        test_print_large_matrix();
        test_memory_management();
        test_double_free();
        
        std::cout << std::endl;
        std::cout << "=== ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ! ===" << std::endl;
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "ОШИБКА: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "НЕИЗВЕСТНАЯ ОШИБКА" << std::endl;
        return 1;
    }
}