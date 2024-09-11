#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


// Función para leer el archivo y convertir cada línea en un vector de enteros
vector<vector<int>> leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);  // Abre el archivo de texto para lectura
    vector<vector<int>> listas;       // Contendrá todas las listas leídas
    string linea;                     // Almacena cada línea del archivo
    
    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        vector<int> lista;            // Almacena los números de cada línea
        stringstream ss(linea);       // Convierte la línea en un flujo de datos
        int numero;
        
        // Extrae los números de la línea y los guarda en el vector lista
        while (ss >> numero) {
            lista.push_back(numero);  // Agrega cada número al vector lista
        }
        listas.push_back(lista);      // Agrega la lista al vector de listas
    }
    
    return listas;                    // Devuelve todas las listas
}

// Función para encontrar la mediana de tres elementos como pivote
int medianOfThree(vector<int>& arr, int low, int mid, int high) {
    // Compara y ordena tres elementos: el primero, el del medio y el último
    if (arr[mid] < arr[low])
        swap(arr[low], arr[mid]);
    if (arr[high] < arr[low])
        swap(arr[low], arr[high]);
    if (arr[high] < arr[mid])
        swap(arr[mid], arr[high]);
    
    // Devuelve el elemento del medio como pivote
    return arr[mid];
}

// Función para particionar el vector según el pivote
int partition(vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;  // Encuentra el índice del medio
    int pivot = medianOfThree(arr, low, mid, high);  // Encuentra el pivote con la mediana de tres
    int i = low, j = high;

    // Bucle para reorganizar los elementos alrededor del pivote
    while (true) {
        // Avanza el puntero i mientras el elemento sea menor que el pivote
        while (arr[i] < pivot) i++;
        
        // Retrocede el puntero j mientras el elemento sea mayor que el pivote
        while (arr[j] > pivot) j--;
        
        // Si los punteros se cruzan, retorna la posición del pivote
        if (i >= j) return j;
        
        // Si no se cruzan, intercambia los elementos en i y j
        swap(arr[i], arr[j]);
        i++;  // Avanza i
        j--;  // Retrocede j
    }
}

// Algoritmo de ordenamiento QuickSort
void quickSort(vector<int>& arr, int low, int high) {
    // Si aún hay elementos por ordenar
    if (low < high) {
        // Particiona el vector y obtiene la posición del pivote
        int pi = partition(arr, low, high);
        
        // Aplica QuickSort recursivamente a las dos mitades
        quickSort(arr, low, pi);        // Mitad izquierda
        quickSort(arr, pi + 1, high);   // Mitad derecha
    }
}

int main() {
    // Nombre del archivo que contiene las listas de números
    string nombreArchivo = "repeticion_10^5.txt";
    
    // Lee las listas de números del archivo y las guarda en un vector de vectores
    vector<vector<int>> listas = leerArchivo(nombreArchivo);

    // Inicia la medición del tiempo de ejecución
    auto start = high_resolution_clock::now();

    // Aplica QuickSort a cada una de las listas
    for (auto& lista : listas) {
        quickSort(lista, 0, lista.size() - 1);  // Ordena la lista con QuickSort
    }

    // Detiene la medición del tiempo
    auto stop = high_resolution_clock::now();

    // Calcula la duración total en milisegundos
    auto duration = duration_cast<milliseconds>(stop - start);

    // Muestra el tiempo de ejecución total
    cout << "Tiempo de ejecución total: " << duration.count() << " milisegundos" << endl;
        
    // Puedes descomentar este bloque si deseas mostrar las listas ordenadas
    // for (const auto& lista : listas) {
    //     for (int num : lista) {
    //         cout << num << " ";
    //     }
    //     cout << endl;
    // }

    return 0; 
}