#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Función para leer el archivo y convertir cada línea en un vector de enteros
vector<vector<int>> leerArchivo(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);  // Abre el archivo de texto
    vector<vector<int>> listas;       // Vector de vectores para almacenar listas de enteros
    string linea;                     // Almacena cada línea del archivo

    // Lee el archivo línea por línea
    while (getline(archivo, linea)) {
        vector<int> lista;            // Vector que almacenará los enteros de cada línea
        stringstream ss(linea);       // Convierte la línea en un flujo de datos
        int numero;

        // Extrae los números de la línea y los agrega a la lista
        while (ss >> numero) {
            lista.push_back(numero);
        }
        listas.push_back(lista);  // Agrega la lista al vector de listas
    }

    return listas;  // Devuelve todas las listas leídas del archivo
}

// Algoritmo de ordenamiento Bubble Sort
void bubbleSort(vector<int>& arr) {
    int n = arr.size();  // Obtiene el tamaño del vector

    // Recorre el vector n-1 veces
    for (int i = 0; i < n - 1; ++i) {
        // En cada iteración, recorre el vector hasta el último elemento no ordenado
        for (int j = 0; j < n - 1 - i; ++j) {
            // Si el elemento actual es mayor que el siguiente, se intercambian
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);  // Intercambia los elementos
            }
        }
    }
}

int main() {
    // Nombre del archivo que contiene las listas de números
    string nombreArchivo = "repeticion_101^5.txt";
    
    // Llama a la función para leer las listas del archivo
    vector<vector<int>> listas = leerArchivo(nombreArchivo);

    // Inicia la medición del tiempo de ejecución del algoritmo Bubble Sort
    auto start = high_resolution_clock::now();

    // Ordena cada lista utilizando el algoritmo Bubble Sort
    for (auto& lista : listas) {
        bubbleSort(lista);
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

    return 0;  // Fin del programa
}