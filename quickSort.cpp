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

int partition(vector<int>& arr, int low, int high) {
  
    // Choose the pivot
    int pivot = arr[high];
  
    // Index of smaller element and indicates 
    // the right position of pivot found so far
    int i = low - 1;

    // Traverse arr[;ow..high] and move all smaller
    // elements on left side. Elements from low to 
    // i are smaller after every iteration
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    
    // Move pivot after smaller elements and
    // return its position
    swap(arr[i + 1], arr[high]);  
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {
  
    if (low < high) {
      
        // pi is the partition return index of pivot
        int pi = partition(arr, low, high);

        // Recursion calls for smaller elements
        // and greater or equals elements
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    vector<int> datos_aleatorio_1 = leerDataset("dataset_aleatorio_1.csv");
    vector<int> datos_aleatorio_2 = leerDataset("dataset_aleatorio_2.csv");
    vector<int> datos_aleatorio_3 = leerDataset("dataset_aleatorio_3.csv");
    vector<int> datos_peor_caso = leerDataset("dataset_peor_caso.csv");

    auto start = steady_clock::now();

    quickSort(datos_peor_caso, 0, 4999999)

    auto end = steady_clock::now();
    auto duration = duration_cast<milliseconds>(end - start).count(); // Calcula la duración en milisegundos
    cout << "Tiempo de ejecución: " << duration << " ms" << endl; // Imprime el tiempo de ejecución
    printArray(datos_peor_caso);
    
    return 0;
}