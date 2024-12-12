#include <iostream>
#include <fstream>

using namespace std;

void inputMatrix(int** matrix, int size) {
    cout << "Введите элементы матрицы (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cin >> matrix[i][j];
        }
    }
}

void outputMatrix(int** matrix, int size) {
    cout << "Матрица (" << size << "x" << size << "):" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void editMatrix(int** matrix, int size) {
    char choice;
    do {
        int row, col, value;
        cout << "Введите индекс строки и столбца для редактирования (0-" << size - 1 << "): ";
        cin >> row >> col;
        if (row >= 0 && row < size && col >= 0 && col < size) {
            cout << "Введите новое значение: ";
            cin >> value;
            matrix[row][col] = value;
        } else {
            cout << "Неверный индекс!" << endl;
        }

        cout << "Хотите редактировать еще? (1. Да / 2. Нет): ";
        cin >> choice;
    } while (choice == '1');
}

void saveAllMatricesToFile(int** A, int** B, int** C, int size, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Матрица A:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file << A[i][j] << " ";
            }
            file << endl;
        }

        file << "\nМатрица B:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file << B[i][j] << " ";
            }
            file << endl;
        }

        file << "\nМатрица C:\n";
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file << C[i][j] << " ";
            }
            file << endl;
        }

        file.close();
        cout << "Все матрицы сохранены в файл: " << filename << endl;
    } else {
        cout << "Не удалось открыть файл для записи." << endl;
    }
}

void loadMatrixFromFile(int** matrix, int size, const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                file >> matrix[i][j];
            }
        }
        file.close();
        cout << "Матрица загружена из файла: " << filename << endl;
    } else {
        cout << "Не удалось открыть файл для чтения." << endl;
    }
}

int columnSum(int** matrix, int size, int col) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += matrix[i][col];
    }
    return sum;
}

void replaceColumns(int** C, int** A, int** B, int size) {
    for (int j = 0; j < size; j++) {
        int sumA = columnSum(A, size, j);
        int sumB = columnSum(B, size, j);
        if (sumA > sumB) {
            for (int i = 0; i < size; i++) {
                C[i][j] = A[i][j];
            }
        } else if (sumB > sumA) {
            for (int i = 0; i < size; i++) {
                C[i][j] = B[i][j];
            }
        }
    }
}

int main(int argc, char* argv[]) {
    bool isHuman = false;
    if (argc <= 1 || strcmp(argv[1], "false") != 0) {
        isHuman = true;
    }

    setlocale(LC_ALL, "Russian");

    int size;
    if (isHuman) {
        cout << "Введите размерность матриц (n x n): ";
    }
    cin >> size;

    int** A = new int*[size];
    int** B = new int*[size];
    int** C = new int*[size];
    for (int i = 0; i < size; i++) {
        A[i] = new int[size];
        B[i] = new int[size];
        C[i] = new int[size];
    }

    int choice;
    if (isHuman) {
        cout << "Выберите способ ввода данных:\n1. Консольный ввод\n2. Ввод из файла\nВаш выбор: ";
    }
    cin >> choice;

    if (choice == 1) {
        if (isHuman) {
            cout << "Матрица A:" << endl;
        }
        inputMatrix(A, size);
        if (isHuman) {
            cout << "Матрица B:" << endl;
        }
        inputMatrix(B, size);
        if (isHuman) {
            cout << "Матрица C:" << endl;
        }
        inputMatrix(C, size);
    } else if (choice == 2) {
        string filenameA, filenameB, filenameC;
        if (isHuman) {
            cout << "Введите имя файла для загрузки матрицы A: ";
        }
        cin >> filenameA;
        loadMatrixFromFile(A, size, filenameA);

        if (isHuman) {
            cout << "Введите имя файла для загрузки матрицы B: ";
        }
        cin >> filenameB;
        loadMatrixFromFile(B, size, filenameB);

        if (isHuman) {
            cout << "Введите имя файла для загрузки матрицы C: ";
        }
        cin >> filenameC;
        loadMatrixFromFile(C, size, filenameC);
    } else {
        if (isHuman) {
            cout << "Неверный выбор!" << endl;
        }
        return 1;
    }

    char editChoice;
    if (isHuman) {
        cout << "Хотите редактировать элементы матриц? (1. Да / 2. Нет): ";
    }
    cin >> editChoice;
    if (editChoice == '1') {
        char matrixChoice;
        do {
            if (isHuman) {
                cout << "Выберите матрицу для редактирования (1. A / 2. B / 3. Выход): ";
            }
            cin >> matrixChoice;
            if (matrixChoice == '1') {
                editMatrix(A, size);
            } else if (matrixChoice == '2') {
                editMatrix(B, size);
            } else if (matrixChoice == '3') {
                break;
            } else {
                if (isHuman) {
                    cout << "Неверный выбор матрицы!" << endl;
                }
            }
        } while (true);
    }

    replaceColumns(C, A, B, size);

    outputMatrix(A, size);
    outputMatrix(B, size);
    outputMatrix(C, size);

    char saveChoice;
    if (isHuman) {
        cout << "Хотите сохранить все матрицы в один файл? (1. Да / 2. Нет): ";
    }
    cin >> saveChoice;
    if (saveChoice == '1') {
        string filename;
        if (isHuman) {
            cout << "Введите имя файла для сохранения всех матриц: ";
        }
        cin >> filename;
        saveAllMatricesToFile(A, B, C, size, filename);
    }

    for (int i = 0; i < size; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C[i];
    }
    delete[] A;
    delete[] B;
    delete[] C;

    return 0;
}