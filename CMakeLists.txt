cmake_minimum_required(VERSION 3.10)
project(matrix_calculator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл из двух исходников
add_executable(matrix_calculator 
    src/main.cpp 
    src/matrix.cpp
)

# Включаем директорию с заголовками
target_include_directories(matrix_calculator PRIVATE src)