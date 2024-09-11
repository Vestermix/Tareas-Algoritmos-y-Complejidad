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

void insertionSort(vector<int> &vec){
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

    vector<int> dataset = leerDataset("dataset_5.csv");

    auto start = steady_clock::now();

    insertionSort(dataset);
   
    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count();
    cout << "Tiempo de ejecución: " << duration << " ms" << endl;

    return 0;
}