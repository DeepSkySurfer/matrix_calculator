FROM gcc:12.2.0

# Установка зависимостей
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    && rm -rf /var/lib/apt/lists/*

# Рабочая директория
WORKDIR /app

# Копирование всех необходимых файлов
COPY src/ ./src/
COPY Makefile ./
COPY Doxyfile ./  

# Сборка
RUN make all

# Генерация документации
RUN doxygen Doxyfile

# Точка входа
CMD ["./test_app"]

RUN doxygen Doxyfile 2>/dev/null || echo "Documentation generated with warnings"