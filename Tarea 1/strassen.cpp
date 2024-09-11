#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

vector<vector<int>> leerMatriz(const string &filename) {
    vector<vector<int>> matriz;
    ifstream archivo(filename);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea)) { // Leer línea por línea
            vector<int> fila;
            stringstream ss(linea);
            string elemento;
            while (getline(ss, elemento, ',')) { // Leer cada elemento separado por coma
                fila.push_back(stoi(elemento)); // Convertir a entero y añadir a la fila
            }
            matriz.push_back(fila); // Añadir fila a la matriz
        }
        archivo.close();
        cout << "Matriz leída desde: " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para leer." << endl;
    }
    return matriz;
}

void sumarMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void restarMatrices(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int size) {
    if (size == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = size / 2;
    vector<int> inner(newSize);
    vector<vector<int>> A11(newSize, inner), A12(newSize, inner), A21(newSize, inner), A22(newSize, inner);
    vector<vector<int>> B11(newSize, inner), B12(newSize, inner), B21(newSize, inner), B22(newSize, inner);
    vector<vector<int>> C11(newSize, inner), C12(newSize, inner), C21(newSize, inner), C22(newSize, inner);
    vector<vector<int>> M1(newSize, inner), M2(newSize, inner), M3(newSize, inner), M4(newSize, inner), M5(newSize, inner), M6(newSize, inner), M7(newSize, inner);
    vector<vector<int>> AResult(newSize, inner), BResult(newSize, inner);

    // Dividir las matrices A y B en submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Calcular M1 a M7 según el algoritmo de Strassen
    sumarMatrices(A11, A22, AResult, newSize);
    sumarMatrices(B11, B22, BResult, newSize);
    strassen(AResult, BResult, M1, newSize);

    sumarMatrices(A21, A22, AResult, newSize);
    strassen(AResult, B11, M2, newSize);

    restarMatrices(B12, B22, BResult, newSize);
    strassen(A11, BResult, M3, newSize);

    restarMatrices(B21, B11, BResult, newSize);
    strassen(A22, BResult, M4, newSize);

    sumarMatrices(A11, A12, AResult, newSize);
    strassen(AResult, B22, M5, newSize);

    restarMatrices(A21, A11, AResult, newSize);
    sumarMatrices(B11, B12, BResult, newSize);
    strassen(AResult, BResult, M6, newSize);

    restarMatrices(A12, A22, AResult, newSize);
    sumarMatrices(B21, B22, BResult, newSize);
    strassen(AResult, BResult, M7, newSize);

    // Calcular C11, C12, C21, C22
    sumarMatrices(M1, M4, AResult, newSize);
    restarMatrices(M7, M5, BResult, newSize);
    sumarMatrices(AResult, BResult, C11, newSize);

    sumarMatrices(M3, M5, C12, newSize);
    sumarMatrices(M2, M4, C21, newSize);

    sumarMatrices(M1, M3, AResult, newSize);
    restarMatrices(M6, M2, BResult, newSize);
    sumarMatrices(AResult, BResult, C22, newSize);

    // Combinar las submatrices en la matriz C
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}

void imprimirMatriz(const vector<vector<int>> &matriz) {
    int rows = matriz.size();
    int cols = matriz[0].size();
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl; // Salto de línea después de cada fila
    }
}

int main() {

    vector<vector<int>> matriz = leerMatriz("matriz_1.csv");

    vector<vector<int>> resultado;

    auto start = steady_clock::now();

    strassen(matriz, matriz, resultado, 64);

    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); // Calcula la duración en milisegundos
    cout << "Tiempo de ejecución: " << duration << " ms" << endl; // Imprime el tiempo de ejecución
    imprimirMatriz(resultado);
    
    return 0;
}