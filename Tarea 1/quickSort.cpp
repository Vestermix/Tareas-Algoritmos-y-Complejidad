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

// Función para encontrar la mediana de tres elementos
int medianOfThree(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    
    if (arr[low] > arr[mid])
        swap(arr[low], arr[mid]);
    if (arr[low] > arr[high])
        swap(arr[low], arr[high]);
    if (arr[mid] > arr[high])
        swap(arr[mid], arr[high]);
    
    // Mueve la mediana al final
    swap(arr[mid], arr[high]);
    return arr[high];
}

// Función de partición usando la mediana de tres elementos como pivote
int partition(vector<int>& arr, int low, int high) {
    int pivot = medianOfThree(arr, low, high);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// QuickSort usando mediana de tres elementos como pivote
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    vector<int> dataset = leerDataset("dataset_5.csv");

    auto start = steady_clock::now();

    quickSort(dataset, 0, 99999);

    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); // Calcula la duración en milisegundos
    cout << "Tiempo de ejecución: " << duration << " ms" << endl; // Imprime el tiempo de ejecución
    
    return 0;
}