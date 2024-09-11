#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono> // Librería para medir el tiempo

using namespace std;
using namespace std::chrono; // Para facilitar el uso de las funciones de tiempo

// Función para leer una matriz desde un archivo
vector<vector<int>> leerMatriz(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);  // Abre el archivo
    if (!archivo) {  // Verifica si el archivo se abrió correctamente
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        exit(1);  // Si no se abre, termina el programa
    }

    vector<vector<int>> matriz;  // Matriz que almacenará los datos del archivo
    string linea;
    
    // Leer línea por línea del archivo
    while (getline(archivo, linea)) {
        stringstream ss(linea);  // Convierte la línea en un flujo de datos
        vector<int> fila;        // Vector para almacenar los elementos de una fila
        int numero;

        // Leer los números de la línea y agregarlos a la fila
        while (ss >> numero) {
            fila.push_back(numero);
        }
        
        matriz.push_back(fila);  // Agregar la fila a la matriz
    }

    return matriz;  // Devuelve la matriz leída
}

// Función para multiplicar dos matrices utilizando el algoritmo cúbico tradicional
vector<vector<int>> multiplicarMatricesCubo(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();  // Suponemos que las matrices son cuadradas de tamaño n x n
    vector<vector<int>> C(n, vector<int>(n, 0));  // Matriz de resultado inicializada en 0

    // Tres bucles anidados para realizar la multiplicación cúbica tradicional
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                // Multiplica el elemento de la fila i de A con el elemento de la columna j de B y lo suma en C[i][j]
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;  // Devuelve la matriz resultado
}

// Función para imprimir una matriz (opcional para verificar resultados)
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {  // Recorre cada fila de la matriz
        for (int elemento : fila) {    // Recorre cada elemento de la fila
            cout << elemento << " ";   // Imprime cada elemento con un espacio
        }
        cout << endl;  // Nueva línea al final de cada fila
    }
}

// Función principal
int main() {
    // Iniciar el cronómetro para medir el tiempo de ejecución
    auto inicio = high_resolution_clock::now();

    // Especificar la ruta de los archivos en la carpeta "datasets" y leer las matrices
    vector<vector<int>> A = leerMatriz("dataset/64x64_1.txt");  // Leer matriz A
    vector<vector<int>> B = leerMatriz("dataset/64x64_2.txt");  // Leer matriz B

    // Descomentar si deseas imprimir las matrices leídas
    //cout << "Matriz A:" << endl;
    //imprimirMatriz(A);

    //cout << "Matriz B:" << endl;
    //imprimirMatriz(B);

    // Multiplicar las matrices A y B
    vector<vector<int>> C = multiplicarMatricesCubo(A, B);

    // Descomentar si deseas imprimir la matriz resultado
    //cout << "Matriz resultado (C = A * B):" << endl;
    //imprimirMatriz(C);
    
    // Detener el cronómetro al finalizar la multiplicación
    auto fin = high_resolution_clock::now();
    
    // Calcular la duración en milisegundos
    auto duracion = duration_cast<milliseconds>(fin - inicio).count();

    // Imprimir el tiempo de ejecución
    cout << "Tiempo de ejecución: " << duracion << " ms" << endl;

    return 0;  // Fin del programa
}
