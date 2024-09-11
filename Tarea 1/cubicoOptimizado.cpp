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

void transponerMatriz(vector<vector<int>> &mat) {
    int n = mat.size();
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            swap(mat[i][j], mat[j][i]);
        }
    }
}

void multiplicacionOptimizada(const vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C) {
    int n = A.size();
    int m = B[0].size();
    int p = B.size();

    C.assign(n, vector<int>(m, 0));
    // Transponer la matriz B
    transponerMatriz(B);
    
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * B[j][k]; // Acceso más secuencial a los elementos de B
            }
        }
    }

    // Restaurar la matriz B a su forma original si es necesario
    transponerMatriz(C);
}

int main() {

    vector<vector<int>> matriz = leerMatriz("matriz_1.csv");

    vector<vector<int>> resultado;

    auto start = steady_clock::now();

    multiplicacionOptimizada(matriz, matriz, resultado);

    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); // Calcula la duración en milisegundos
    cout << "Tiempo de ejecución: " << duration << " ms" << endl; // Imprime el tiempo de ejecución
    imprimirMatriz(resultado);
    return 0;
}