#include <iostream>
#include <limits>

// Максимальный размер матрицы
const int MAX_SIZE = 100;

// Получить индекс в массиве по индексам матрицы
int getIndex(int i, int j, int size) {
    return i > j ? i * (i + 1) / 2 + j : j * (j + 1) / 2 + i;
}

// Установка значения элемента, учитывая симметрию
void setElement(int* data, int i, int j, int value, int size) {
    data[getIndex(i, j, size)] = value;
}

// Получение значения элемента
int getElement(const int* data, int i, int j, int size) {
    return data[getIndex(i, j, size)];
}

// Вывод симметричной матрицы
void printMatrix(const int* data, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << getElement(data, i, j, size) << " ";
        }
        std::cout << "\n";
    }
}

// Функция для проверки, содержит ли число только четные цифры
bool hasOnlyEvenDigits(int number) {
    while (number != 0) {
        int digit = number % 10;
        if (digit % 2 != 0) {
            return false;  // Найдена нечетная цифра
        }
        number /= 10;
    }
    return true;  // Все цифры четные
}

// Функция для безопасного ввода целого числа с проверкой на корректность
int safeInput() {
    int value;
    while (true) {
        std::cin >> value;

        if (std::cin.fail()) {
            // Ошибка формата ввода, очистим флаг ошибки и проигнорируем введенные символы
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Input error. Try again: ";
        } else {
            break;  // Ввод корректен, выходим из цикла
        }
    }
    return value;
}

int main() {
    try {
        int n;
        std::cout << "Vvedite razmernost matrix: ";
        n = safeInput();

        // Проверка на допустимый размер матрицы
        if (n <= 0 || n > MAX_SIZE) {
            throw std::invalid_argument("Invalid matrix size");
        }

        // Размерность верхнего треугольника матрицы
        int totalElements = n * (n + 1) / 2;

        // Инициализация одномерного массива для хранения верхнего треугольника матрицы
        int symmetricMatrixData[MAX_SIZE * (MAX_SIZE + 1) / 2] = {0};

        // Считывание симметричной матрицы из входного потока
        std::cout << "Vvedite elements matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                std::cout << "Vvedite element [" << i << "][" << j << "]: ";
                int element = safeInput();
                setElement(symmetricMatrixData, i, j, element, n);
            }
        }

        // Вывод симметричной матрицы
        std::cout << "Symmetric matrix:\n";
        printMatrix(symmetricMatrixData, n);

        // Создание новой матрицы согласно указанным критериям
        int newMatrixData[MAX_SIZE * (MAX_SIZE + 1) / 2] = {0};
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int originalElement = getElement(symmetricMatrixData, i, j, n);
                if (hasOnlyEvenDigits(originalElement)) {
                    setElement(newMatrixData, i, j, originalElement, n);
                }
            }
        }

        // Вывод новой матрицы
        std::cout << "\n New matrix (only even numbers):\n";
        printMatrix(newMatrixData, n);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Возврат из main сигнализирует об ошибке
    }

    return 0; // Возврат из main сигнализирует об успешном завершении
}
