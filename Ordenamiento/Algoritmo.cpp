#include <iostream>    
#include <fstream>     
#include <vector>       
#include <sstream>     
#include <chrono>       
#include <algorithm>    

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

int main() {
    // Nombre del archivo que contiene las listas de números
    string nombreArchivo = "repeticion_10^5.txt";
    
    // Llama a la función para leer las listas del archivo
    vector<vector<int>> listas = leerArchivo(nombreArchivo);

    // Inicia la medición del tiempo de ejecución usando std::sort
    auto start = high_resolution_clock::now();

    // Ordena cada lista utilizando std::sort
    for (auto& lista : listas) {
        std::sort(lista.begin(), lista.end());  // Aplica std::sort a cada lista
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