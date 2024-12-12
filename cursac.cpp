#include <iostream>
#include <fstream>

using namespace std;

// Функция для ввода элементов матрицы с клавиатуры
void inputMatrix(int** matrix, int size) {
    cout << "Введите элементы матрицы (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
}

// Функция для вывода матрицы на экран
void outputMatrix(int** matrix, int size) {
    cout << "Матрица (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для редактирования элементов матрицы
void editMatrix(int** matrix, int size) {
    char choice;
    do {
        int row, col, value;
        cout << "Введите индекс строки и столбца для редактирования (0-" << size - 1 << "): ";
        cin >> row >> col;
        if (row >= 0 && row < size && col >= 0 && col < size) {
            cout << "Введите новое значение: ";
            cin >> value;
            matrix[row][col] = value; // Обновление значения в матрице
        }
        else {
            cout << "Неверный индекс!" << endl;
        }

        cout << "Хотите редактировать еще? (1. Да / 2. Нет): ";
        cin >> choice;
    } while (choice == '1'); // Продолжать редактирование, пока пользователь не решит выйти
}

// Функция для сохранения матрицы в файл
void saveMatrixToFile(const string& filename, int** matrix, int size) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file << matrix[i][j] << " ";
            }
            file << endl;
        }
        file.close();
        cout << "Матрица сохранена в файл: " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

// Функция для загрузки матрицы из файла
void loadMatrixFromFile(int** matrix, int size, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> matrix[i][j]; // Считывание значений из файла
            }
        }
        file.close();
        cout << "Матрица загружена из файла: " << filename << endl;
    }
    else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

// Функция для вычисления суммы элементов указанного столбца матрицы
int columnSum(int** matrix, int size, int col) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += matrix[i][col]; // Суммирование элементов столбца
    }
    return sum;
}

// Функция для замены столбцов в матрице C на основе сумм столбцов матриц A и B
void replaceColumns(int** C, int** A, int** B, int size) {
    for (int j = 0; j < size; j++) {
        int sumA = columnSum(A, size, j);
        int sumB = columnSum(B, size, j);
        if (sumA > sumB) {
            for (int i = 0; i < size; i++) {
                C[i][j] = A[i][j]; // Замена столбца C на столбец A
            }
        }
        else if (sumB > sumA) {
            for (int i = 0; i < size; i++) {
                C[i][j] = B[i][j]; // Замена столбца C на столбец B
            }
        }
    }
}

// Функция для освобождения памяти матрицы
void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

// Основная функция
int main() {
    setlocale(LC_ALL, "Russian");

    int size;
    cout << "Введите размерность матриц (n x n): ";
    cin >> size;

    // Динамическое выделение памяти для трех матриц
    int** A = new int* [size];
    int** B = new int* [size];
    int** C = new int* [size];
    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }

    // Основное меню программы
    int choice;
    do {
        cout << "\nМеню:\n";
        cout << "1. Ввод матрицы A с консоли\n";
        cout << "2. Ввод матрицы B с консоли\n";
        cout << "3. Ввод матрицы C с консоли\n";
        cout << "4. Загрузка матрицы A из файла\n";
        cout << "5. Загрузка матрицы B из файла\n";
        cout << "6. Загрузка матрицы C из файла\n";
        cout << "7. Редактирование матриц\n";
        cout << "8. Замена столбцов в матрице C\n";
        cout << "9. Вывод матриц\n";
        cout << "10. Сохранение матрицы A в файл\n";
        cout << "11. Сохранение матрицы B в файл\n";
        cout << "12. Сохранение матрицы C в файл\n";
        cout << "13. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Матрица A:" << endl;
            inputMatrix(A, size);
            break;
        }
        case 2: {
            cout << "Матрица B:" << endl;
            inputMatrix(B, size);
            break;
        }
        case 3: {
            cout << "Матрица C:" << endl;
            inputMatrix(C, size);
            break;
        }
        case 4: {
            loadMatrixFromFile(A, size, "A.txt");
            break;
        }
        case 5: {
            loadMatrixFromFile(B, size, "B.txt");
            break;
        }
        case 6: {
            loadMatrixFromFile(C, size, "C.txt");
            break;
        }
        case 7: {
            char matrixChoice;
            do {
                cout << "Выберите матрицу для редактирования (1. A / 2. B / 3. C / 4. Выход): ";
                cin >> matrixChoice;
                if (matrixChoice == '1') {
                    editMatrix(A, size);
                }
                else if (matrixChoice == '2') {
                    editMatrix(B, size);
                }
                else if (matrixChoice == '3') {
                    editMatrix(C, size);
                }
                else if (matrixChoice == '4') {
                    break;
                }
                else {
                    cout << "Неверный выбор матрицы!" << endl;
                }
            } while (true);
            break;
        }
        case 8: {
            replaceColumns(C, A, B, size);
            cout << "Столбцы в матрице C заменены на основе сумм столбцов A и B." << endl;
            break;
        }
        case 9: {
            outputMatrix(A, size);
            outputMatrix(B, size);
            outputMatrix(C, size);
            break;
        }
        case 10: {
            saveMatrixToFile("A.txt", A, size);
            break;
        }
        case 11: {
            saveMatrixToFile("B.txt", B, size);
            break;
        }
        case 12: {
            saveMatrixToFile("C.txt", C, size);
            break;
        }
        case 13: {
            cout << "Выход из программы." << endl;
            break;
        }
        default:
            cout << "Неверный выбор! Пожалуйста, попробуйте еще раз." << endl;
        }
    } while (choice != 13);

    // Освобождение выделенной памяти с помощью функции deleteMatrix
    deleteMatrix(A, size);
    deleteMatrix(B, size);
    deleteMatrix(C, size);

    return 0;
}