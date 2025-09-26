/*
 * @file main.cpp
 * @brief Основное приложение матричного калькулятора
 * @details Демонстрирует работу всех функций библиотеки матричных операций
 

#include "matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @brief Демонстрация создания и освобождения матриц
 
void demo_create_and_free() {
    cout << "=== ДЕМОНСТРАЦИЯ: СОЗДАНИЕ И ОСВОБОЖДЕНИЕ МАТРИЦ ===" << endl;
    
    // Создание матрицы 3x4
    Matrix A = create_matrix(3, 4);
    cout << "Создана матрица A размером " << A.rows << "x" << A.cols << endl;
    
    // Заполнение матрицы значениями
    int counter = 1;
    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            A.data[i][j] = counter++;
        }
    }
    
    cout << "Матрица A после заполнения:" << endl;
    print_matrix(A);
    
    // Освобождение памяти
    free_matrix(A);
    cout << "Память матрицы A освобождена" << endl << endl;
}

/**
 * @brief Демонстрация сложения матриц
 
void demo_matrix_addition() {
    cout << "=== ДЕМОНСТРАЦИЯ: СЛОЖЕНИЕ МАТРИЦ ===" << endl;
    
    // Создание двух матриц 2x2
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    
    // Заполнение матрицы A: [[1, 2], [3, 4]]
    A.data[0][0] = 1.0; A.data[0][1] = 2.0;
    A.data[1][0] = 3.0; A.data[1][1] = 4.0;
    
    // Заполнение матрицы B: [[5, 6], [7, 8]]
    B.data[0][0] = 5.0; B.data[0][1] = 6.0;
    B.data[1][0] = 7.0; B.data[1][1] = 8.0;
    
    cout << "Матрица A:" << endl;
    print_matrix(A);
    
    cout << "Матрица B:" << endl;
    print_matrix(B);
    
    // Сложение матриц
    Matrix C = matrix_add(A, B);
    cout << "Результат сложения A + B:" << endl;
    print_matrix(C);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    cout << endl;
}

/**
 * @brief Демонстрация умножения матриц
 
void demo_matrix_multiplication() {
    cout << "=== ДЕМОНСТРАЦИЯ: УМНОЖЕНИЕ МАТРИЦ ===" << endl;
    
    // Матрица A: 2x3
    Matrix A = create_matrix(2, 3);
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;
    
    // Матрица B: 3x2
    Matrix B = create_matrix(3, 2);
    B.data[0][0] = 7;  B.data[0][1] = 8;
    B.data[1][0] = 9;  B.data[1][1] = 10;
    B.data[2][0] = 11; B.data[2][1] = 12;
    
    cout << "Матрица A (2x3):" << endl;
    print_matrix(A);
    
    cout << "Матрица B (3x2):" << endl;
    print_matrix(B);
    
    // Умножение матриц
    Matrix C = matrix_multiply(A, B);
    cout << "Результат умножения A × B:" << endl;
    print_matrix(C);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    cout << endl;
}

/**
 * @brief Демонстрация транспонирования матрицы
 
void demo_matrix_transpose() {
    cout << "=== ДЕМОНСТРАЦИЯ: ТРАНСПОНИРОВАНИЕ МАТРИЦЫ ===" << endl;
    
    // Матрица 3x2
    Matrix A = create_matrix(3, 2);
    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    A.data[2][0] = 5; A.data[2][1] = 6;
    
    cout << "Исходная матрица A (3x2):" << endl;
    print_matrix(A);
    
    // Транспонирование
    Matrix B = matrix_transpose(A);
    cout << "Транспонированная матрица A^T (2x3):" << endl;
    print_matrix(B);
    
    free_matrix(A);
    free_matrix(B);
    cout << endl;
}

/**
 * @brief Демонстрация создания матрицы из массива
 
void demo_matrix_from_array() {
    cout << "=== ДЕМОНСТРАЦИЯ: СОЗДАНИЕ МАТРИЦЫ ИЗ МАССИВА ===" << endl;
    
    // Одномерный массив данных
    double data[] = {
        1.5, 2.5, 3.5,
        4.5, 5.5, 6.5,
        7.5, 8.5, 9.5
    };
    
    // Создание матрицы 3x3 из массива
    Matrix A = matrix_from_array(data, 3, 3);
    
    cout << "Матрица созданная из массива:" << endl;
    print_matrix(A);
    
    free_matrix(A);
    cout << endl;
}

/**
 * @brief Демонстрация обработки ошибок
 
void demo_error_handling() {
    cout << "=== ДЕМОНСТРАЦИЯ: ОБРАБОТКА ОШИБОК ===" << endl;
    
    cout << "1. Попытка создания матрицы с невалидными размерами:" << endl;
    try {
        Matrix A = create_matrix(-1, 5);
        cout << "ОШИБКА: Должно было быть исключение!" << endl;
        free_matrix(A);
    } catch (const exception& e) {
        cout << "✓ Перехвачено исключение: " << e.what() << endl;
    }
    
    cout << "2. Попытка сложения матриц разных размеров:" << endl;
    try {
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(3, 3);
        Matrix C = matrix_add(A, B);
        cout << "ОШИБКА: Должно было быть исключение!" << endl;
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    } catch (const exception& e) {
        cout << "✓ Перехвачено исключение: " << e.what() << endl;
    }
    
    cout << "3. Попытка умножения несовместимых матриц:" << endl;
    try {
        Matrix A = create_matrix(2, 3);
        Matrix B = create_matrix(2, 3); // Несовместимые размеры
        Matrix C = matrix_multiply(A, B);
        cout << "ОШИБКА: Должно было быть исключение!" << endl;
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
    } catch (const exception& e) {
        cout << "✓ Перехвачено исключение: " << e.what() << endl;
    }
    
    cout << endl;
}

/**
 * @brief Демонстрация работы с большой матрицей
 
void demo_large_matrix() {
    cout << "=== ДЕМОНСТРАЦИЯ: РАБОТА С БОЛЬШОЙ МАТРИЦЕЙ ===" << endl;
    
    // Создание большой матрицы
    Matrix large = create_matrix(15, 12);
    
    // Заполнение значениями
    for (int i = 0; i < large.rows; i++) {
        for (int j = 0; j < large.cols; j++) {
            large.data[i][j] = (i + 1) * 0.1 + (j + 1) * 0.01;
        }
    }
    
    cout << "Большая матрица 15x12 (сокращенный вывод):" << endl;
    print_matrix(large);
    
    free_matrix(large);
    cout << endl;
}

/**
 * @brief Комплексный пример использования
 
void demo_complex_example() {
    cout << "=== КОМПЛЕКСНЫЙ ПРИМЕР ===" << endl;
    
    // Создание матриц для системы уравнений
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    
    // Заполнение
    A.data[0][0] = 2; A.data[0][1] = 1;
    A.data[1][0] = 1; A.data[1][1] = 3;
    
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;
    
    cout << "Матрица коэффициентов A:" << endl;
    print_matrix(A);
    
    cout << "Матрица B:" << endl;
    print_matrix(B);
    
    // Выполнение операций
    Matrix sum = matrix_add(A, B);
    Matrix product = matrix_multiply(A, B);
    Matrix A_transposed = matrix_transpose(A);
    
    cout << "Сумма A + B:" << endl;
    print_matrix(sum);
    
    cout << "Произведение A × B:" << endl;
    print_matrix(product);
    
    cout << "Транспонированная A:" << endl;
    print_matrix(A_transposed);
    
    // Освобождение памяти
    free_matrix(A);
    free_matrix(B);
    free_matrix(sum);
    free_matrix(product);
    free_matrix(A_transposed);
    
    cout << endl;
}

/**
 * @brief Главная функция приложения
 * @return int Код возврата (0 - успех, 1 - ошибка)
 
int main() {
    cout << "🎯 МАТРИЧНЫЙ КАЛЬКУЛЯТОР" << endl;
    cout << "================================" << endl;
    
    try {
        // Демонстрация всех возможностей
        demo_create_and_free();
        demo_matrix_addition();
        demo_matrix_multiplication();
        demo_matrix_transpose();
        demo_matrix_from_array();
        demo_large_matrix();
        demo_complex_example();
        demo_error_handling();
        
        cout << "✅ ВСЕ ДЕМОНСТРАЦИИ УСПЕШНО ЗАВЕРШЕНЫ!" << endl;
        cout << "📚 Для подробной документации запустите: doxygen Doxyfile" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "❌ ОШИБКА В ПРОГРАММЕ: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "❌ НЕИЗВЕСТНАЯ ОШИБКА В ПРОГРАММЕ" << endl;
        return 1;
    }
}
*/
/**
 * @file main.cpp
 * @brief Основное приложение матричного калькулятора
 * @details Демонстрирует работу всех функций библиотеки матричных операций
 */

#include "matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

// Все demo-функции остаются как есть...
void demo_create_and_free() { /* ... */ }
void demo_matrix_addition() { /* ... */ }
void demo_matrix_multiplication() { /* ... */ }
void demo_matrix_transpose() { /* ... */ }
void demo_matrix_from_array() { /* ... */ }
void demo_error_handling() { /* ... */ }
void demo_large_matrix() { /* ... */ }
void demo_complex_example() { /* ... */ }

/**
 * @brief Главная функция приложения
 * @return int Код возврата (0 - успех, 1 - ошибка)
 */
int main() {
    cout << "🎯 МАТРИЧНЫЙ КАЛЬКУЛЯТОР" << endl;
    cout << "================================" << endl;
    
    try {
        // Демонстрация всех возможностей
        demo_create_and_free();
        demo_matrix_addition();
        demo_matrix_multiplication();
        demo_matrix_transpose();
        demo_matrix_from_array();
        demo_large_matrix();
        demo_complex_example();
        demo_error_handling();
        
        cout << "✅ ВСЕ ДЕМОНСТРАЦИИ УСПЕШНО ЗАВЕРШЕНЫ!" << endl;
        cout << "📚 Для подробной документации запустите: doxygen Doxyfile" << endl;
        
        return 0;
        
    } catch (const exception& e) {
        cerr << "❌ ОШИБКА В ПРОГРАММЕ: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "❌ НЕИЗВЕСТНАЯ ОШИБКА В ПРОГРАММЕ" << endl;
        return 1;
    }
}