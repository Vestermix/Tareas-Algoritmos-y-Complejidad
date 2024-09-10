#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

vector<int> leerDataset(const string &filename){
    vector<int> datos;
    ifstream archivo(filename);
    if (archivo.is_open()) {
        string linea;
        while (getline(archivo, linea, ',')) {
            datos.push_back(stoi(linea));
        }
        archivo.close();
        cout << "Datos leídos desde: " << filename << endl;
    } else {
        cerr << "No se pudo abrir el archivo para leer." << endl;
    }
    return datos;
}

void printArray(const vector<int> &vec){
    for (int i = 0; i < 12; ++i)
        cout << vec[i] << " ";
    cout << endl;
}

void insertionSort(vector<int> &vec){//geeksforgeeks con modificación a vectores
    int n = vec.size();

    for (int i = 1; i < n; ++i) {
        int key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
}

int main() {

    vector<int> datos_aleatorio_1 = leerDataset("dataset_aleatorio_1.csv");
    vector<int> datos_aleatorio_2 = leerDataset("dataset_aleatorio_2.csv");
    vector<int> datos_aleatorio_3 = leerDataset("dataset_aleatorio_3.csv");
    vector<int> datos_peor_caso = leerDataset("dataset_peor_caso.csv");

    auto start = steady_clock::now();

    insertionSort(datos_peor_caso);
   
    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); // Calcula la duración en milisegundos
    cout << "Tiempo de ejecución: " << duration << " ms" << endl; // Imprime el tiempo de ejecución
    printArray(datos_peor_caso);

    return 0;
}