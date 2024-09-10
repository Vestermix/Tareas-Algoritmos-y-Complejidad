#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

// Función para generar un dataset aleatorio.
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

// Función para generar un dataset en el peor caso para Insertion Sort.
void generarDatasetPeorCaso(const string &filename, int n) {
    vector<int> datos(n);
    for (int i = 0; i < n; ++i) {
        datos[i] = n - i;  // Orden descendente para el peor caso de Insertion Sort.
    }

    ofstream archivo(filename);
    if (archivo.is_open()) {
        for (int i = 0; i < n; ++i) {
            archivo << datos[i];
            if (i < n - 1) archivo << ",";
        }
        archivo.close();
        cout << "Dataset peor caso guardado en: " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
    }
}

int main() {
    int n = 5000000; // Ajustar según la velocidad de tu máquina para que el peor caso de Insertion Sort tarde unos 5 minutos.

    // Generar datasets aleatorios
    generarDatasetAleatorio("dataset_aleatorio_1.csv", n);
    generarDatasetAleatorio("dataset_aleatorio_2.csv", n);
    generarDatasetAleatorio("dataset_aleatorio_3.csv", n);

    // Generar dataset en el peor caso para Insertion Sort
    generarDatasetPeorCaso("dataset_peor_caso.csv", n);

    return 0;
}