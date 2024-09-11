#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer el archivo y convertir cada línea en un vector de enteros
vector<vector<int>> leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);  // Abre el archivo para lectura
    vector<vector<int>> listas;       // Vector de vectores que contendrá las listas de números
    string linea;                     // Almacena cada línea del archivo
    
    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        vector<int> lista;            // Vector para cada lista individual de números
        stringstream ss(linea);       // Convierte la línea en un flujo de datos
        int numero;
        
        // Extrae los números de la línea y los almacena en la lista
        while (ss >> numero) {
            lista.push_back(numero);  // Agrega cada número a la lista
        }
        listas.push_back(lista);      // Agrega la lista al vector de listas
    }
    
    return listas;                    // Devuelve todas las listas leídas del archivo
}

// Función para fusionar dos sub-vectores en orden ascendente
void merge(vector<int>& arr, int left, int mid, int right) {
    // n1 es el tamaño del sub-vector izquierdo
    int n1 = mid - left + 1;
    // n2 es el tamaño del sub-vector derecho
    int n2 = right - mid;

    // Crea dos vectores temporales para almacenar los sub-vectores
    vector<int> L(n1), R(n2);

    // Copia los elementos al vector temporal izquierdo L
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    
    // Copia los elementos al vector temporal derecho R
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    // Fusiona los dos sub-vectores en el vector original
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];  // Copia el menor de L[i] o R[j]
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;  // Mueve el índice del vector original
    }

    // Si quedaron elementos en el sub-vector izquierdo, los copia
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Si quedaron elementos en el sub-vector derecho, los copia
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Algoritmo de ordenamiento Merge Sort
void mergeSort(vector<int>& arr, int left, int right) {
    // Si aún hay más de un elemento por ordenar
    if (left < right) {
        int mid = left + (right - left) / 2;  // Calcula el punto medio

        // Aplica MergeSort recursivamente a las dos mitades
        mergeSort(arr, left, mid);        // Ordena la mitad izquierda
        mergeSort(arr, mid + 1, right);   // Ordena la mitad derecha

        // Fusiona las dos mitades ordenadas
        merge(arr, left, mid, right);
    }
}

int main() {
    // Nombre del archivo que contiene las listas de números
    string nombreArchivo = "repeticion_10^5.txt";
    
    // Lee las listas de números desde el archivo
    vector<vector<int>> listas = leerArchivo(nombreArchivo);

    // Inicia la medición del tiempo de ejecución
    auto start = high_resolution_clock::now();

    // Aplica MergeSort a cada lista de números
    for (auto& lista : listas) {
        mergeSort(lista, 0, lista.size() - 1);  // Ordena cada lista con MergeSort
    }

    // Detiene la medición del tiempo de ejecución
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