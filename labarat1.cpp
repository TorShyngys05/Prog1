#include <iostream>
#include <limits>

// ������������ ������ �������
const int MAX_SIZE = 100;

// �������� ������ � ������� �� �������� �������
int getIndex(int i, int j, int size) {
    return i > j ? i * (i + 1) / 2 + j : j * (j + 1) / 2 + i;
}

// ��������� �������� ��������, �������� ���������
void setElement(int* data, int i, int j, int value, int size) {
    data[getIndex(i, j, size)] = value;
}

// ��������� �������� ��������
int getElement(const int* data, int i, int j, int size) {
    return data[getIndex(i, j, size)];
}

// ����� ������������ �������
void printMatrix(const int* data, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << getElement(data, i, j, size) << " ";
        }
        std::cout << "\n";
    }
}

// ������� ��� ��������, �������� �� ����� ������ ������ �����
bool hasOnlyEvenDigits(int number) {
    while (number != 0) {
        int digit = number % 10;
        if (digit % 2 != 0) {
            return false;  // ������� �������� �����
        }
        number /= 10;
    }
    return true;  // ��� ����� ������
}

// ������� ��� ����������� ����� ������ ����� � ��������� �� ������������
int safeInput() {
    int value;
    while (true) {
        std::cin >> value;

        if (std::cin.fail()) {
            // ������ ������� �����, ������� ���� ������ � ������������� ��������� �������
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Input error. Try again: ";
        } else {
            break;  // ���� ���������, ������� �� �����
        }
    }
    return value;
}

int main() {
    try {
        int n;
        std::cout << "Vvedite razmernost matrix: ";
        n = safeInput();

        // �������� �� ���������� ������ �������
        if (n <= 0 || n > MAX_SIZE) {
            throw std::invalid_argument("Invalid matrix size");
        }

        // ����������� �������� ������������ �������
        int totalElements = n * (n + 1) / 2;

        // ������������� ����������� ������� ��� �������� �������� ������������ �������
        int symmetricMatrixData[MAX_SIZE * (MAX_SIZE + 1) / 2] = {0};

        // ���������� ������������ ������� �� �������� ������
        std::cout << "Vvedite elements matrix:\n";
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                std::cout << "Vvedite element [" << i << "][" << j << "]: ";
                int element = safeInput();
                setElement(symmetricMatrixData, i, j, element, n);
            }
        }

        // ����� ������������ �������
        std::cout << "Symmetric matrix:\n";
        printMatrix(symmetricMatrixData, n);

        // �������� ����� ������� �������� ��������� ���������
        int newMatrixData[MAX_SIZE * (MAX_SIZE + 1) / 2] = {0};
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int originalElement = getElement(symmetricMatrixData, i, j, n);
                if (hasOnlyEvenDigits(originalElement)) {
                    setElement(newMatrixData, i, j, originalElement, n);
                }
            }
        }

        // ����� ����� �������
        std::cout << "\n New matrix (only even numbers):\n";
        printMatrix(newMatrixData, n);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // ������� �� main ������������� �� ������
    }

    return 0; // ������� �� main ������������� �� �������� ����������
}
