#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

void generarDatasetAleatorio(const string &filename, int n) {
    vector<int> datos(n);
    for (int i = 0; i < n; ++i) {
        datos[i] = i + 1;
    }
    shuffle(datos.begin(), datos.end(), mt19937(random_device()()));

    ofstream archivo(filename);
    if (archivo.is_open()) {
        for (int i = 0; i < n; ++i) {
            archivo << datos[i];
            if (i < n - 1) archivo << ",";
        }
        archivo.close();
        cout << "Dataset aleatorio guardado en: " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

void generarDatasetOrdenado(const string &filename, int n) {
    vector<int> datos(n);
    for (int i = 0; i < n; ++i) {
        datos[i] = i + 1;
    }

    ofstream archivo(filename);
    if (archivo.is_open()) {
        for (int i = 0; i < n; ++i) {
            archivo << datos[i];
            if (i < n - 1) archivo << ",";
        }
        archivo.close();
        cout << "Dataset ordenado guardado en: " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

void generarDatasetMedianamenteOrdenado(const string &filename, int n, double porcentajeOrdenado) {
    vector<int> datos(n);
    int limiteOrdenado = static_cast<int>(n * porcentajeOrdenado);

    for (int i = 0; i < limiteOrdenado; ++i) {
        datos[i] = i + 1;
    }

    random_device rd;
    mt19937 gen(rd());
    for (int i = limiteOrdenado; i < n; ++i) {
        datos[i] = limiteOrdenado + gen() % (n - limiteOrdenado + 1);
    }

    shuffle(datos.begin() + (limiteOrdenado / 2), datos.end(), gen);

    ofstream archivo(filename);
    if (archivo.is_open()) {
        for (int i = 0; i < n; ++i) {
            archivo << datos[i];
            if (i < n - 1) archivo << ",";
        }
        archivo.close();
        cout << "Dataset medianamente ordenado guardado en: " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

void generarYGuardarMatriz(int n, const string &filename, int minValor = 0, int maxValor = 100) {
    ofstream archivo(filename);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(minValor, maxValor);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int valor = distrib(gen);
            archivo << valor;
            if (j < n - 1) archivo << ",";
        }
        archivo << "\n";
    }
    
    archivo.close();
    cout << "Matriz guardada en: " << filename << endl;
}

int main() {

    // Generar datasets aleatorios
    generarDatasetAleatorio("dataset_1.csv", 10000);
    generarDatasetAleatorio("dataset_2.csv", 100000);
    generarDatasetAleatorio("dataset_3.csv", 1000000);
    generarDatasetMedianamenteOrdenado("dataset_4.csv", 100000, 0.3);
    generarDatasetMedianamenteOrdenado("dataset_5.csv", 100000, 0.6);

    // Generar y guardar dos matrices aleatorias
    generarYGuardarMatriz(8, "matriz_1.csv");
    generarYGuardarMatriz(128, "matriz_2.csv");
    generarYGuardarMatriz(1024, "matriz_3.csv");

    return 0;
}