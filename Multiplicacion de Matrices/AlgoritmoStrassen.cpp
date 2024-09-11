#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono> // Librería para medir el tiempo

using namespace std;
using namespace std::chrono; // Para facilitar el uso de las funciones de tiempo

// Función para leer la matriz desde un archivo
// Abre el archivo, lee sus contenidos línea por línea, y almacena los valores en una matriz 2D.
vector<vector<int>> leerMatriz(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo) {
        cerr << "Error al abrir el archivo " << nombreArchivo << endl;
        exit(1); // Sale del programa si ocurre un error al abrir el archivo
    }

    vector<vector<int>> matriz;
    string linea;
    // Lee cada línea del archivo
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        vector<int> fila;
        int numero;
        // Extrae los números de la línea y los agrega a la fila
        while (ss >> numero) {
            fila.push_back(numero);
        }
        matriz.push_back(fila); // Agrega la fila a la matriz
    }

    return matriz; // Devuelve la matriz completa
}

// Función auxiliar para sumar dos matrices A y B
vector<vector<int>> sumarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size(); // Tamaño de la matriz
    vector<vector<int>> C(n, vector<int>(n, 0)); // Matriz resultado de la misma dimensión
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j]; // Suma elemento a elemento
        }
    }
    return C; // Devuelve la matriz suma
}

// Función auxiliar para restar dos matrices A y B
vector<vector<int>> restarMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size(); // Tamaño de la matriz
    vector<vector<int>> C(n, vector<int>(n, 0)); // Matriz resultado de la misma dimensión
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j]; // Resta elemento a elemento
        }
    }
    return C; // Devuelve la matriz resta
}

// Función principal del algoritmo de Strassen para multiplicar dos matrices A y B
vector<vector<int>> multiplicarStrassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size(); // Tamaño de la matriz (n x n)

    // Caso base: si el tamaño de la matriz es 1x1, solo multiplicamos los elementos individuales
    if (n == 1) {
        return {{A[0][0] * B[0][0]}};
    }

    // Calculamos el nuevo tamaño de las submatrices (la mitad del tamaño original)
    int newSize = n / 2;
    vector<int> inner(newSize);
    
    // Inicializamos las submatrices para A y B
    vector<vector<int>> A11(newSize, inner), A12(newSize, inner), A21(newSize, inner), A22(newSize, inner);
    vector<vector<int>> B11(newSize, inner), B12(newSize, inner), B21(newSize, inner), B22(newSize, inner);

    // Dividimos las matrices A y B en sus respectivas submatrices
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            A11[i][j] = A[i][j]; // Parte superior izquierda
            A12[i][j] = A[i][j + newSize]; // Parte superior derecha
            A21[i][j] = A[i + newSize][j]; // Parte inferior izquierda
            A22[i][j] = A[i + newSize][j + newSize]; // Parte inferior derecha

            B11[i][j] = B[i][j]; // Parte superior izquierda
            B12[i][j] = B[i][j + newSize]; // Parte superior derecha
            B21[i][j] = B[i + newSize][j]; // Parte inferior izquierda
            B22[i][j] = B[i + newSize][j + newSize]; // Parte inferior derecha
        }
    }

    // Calculamos las 7 multiplicaciones intermedias usando recursión
    vector<vector<int>> M1 = multiplicarStrassen(sumarMatrices(A11, A22), sumarMatrices(B11, B22));
    vector<vector<int>> M2 = multiplicarStrassen(sumarMatrices(A21, A22), B11);
    vector<vector<int>> M3 = multiplicarStrassen(A11, restarMatrices(B12, B22));
    vector<vector<int>> M4 = multiplicarStrassen(A22, restarMatrices(B21, B11));
    vector<vector<int>> M5 = multiplicarStrassen(sumarMatrices(A11, A12), B22);
    vector<vector<int>> M6 = multiplicarStrassen(restarMatrices(A21, A11), sumarMatrices(B11, B12));
    vector<vector<int>> M7 = multiplicarStrassen(restarMatrices(A12, A22), sumarMatrices(B21, B22));

    // Calculamos las submatrices de la matriz resultado C usando los resultados M1 a M7
    vector<vector<int>> C11 = sumarMatrices(restarMatrices(sumarMatrices(M1, M4), M5), M7);
    vector<vector<int>> C12 = sumarMatrices(M3, M5);
    vector<vector<int>> C21 = sumarMatrices(M2, M4);
    vector<vector<int>> C22 = sumarMatrices(restarMatrices(sumarMatrices(M1, M3), M2), M6);

    // Combina las submatrices C11, C12, C21, C22 para formar la matriz completa C
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j]; // Parte superior izquierda
            C[i][j + newSize] = C12[i][j]; // Parte superior derecha
            C[i + newSize][j] = C21[i][j]; // Parte inferior izquierda
            C[i + newSize][j + newSize] = C22[i][j]; // Parte inferior derecha
        }
    }

    return C; // Devuelve la matriz resultado
}

// Función para imprimir una matriz (solo para depuración o visualización)
void imprimirMatriz(const vector<vector<int>>& matriz) {
    for (const auto& fila : matriz) {
        for (int elemento : fila) {
            cout << elemento << " ";
        }
        cout << endl;
    }
}

// Función principal
int main() {
    // Comienza a medir el tiempo de ejecución
    auto inicio = high_resolution_clock::now();

    // Especifica la ruta de los archivos de entrada que contienen las matrices A y B
    vector<vector<int>> A = leerMatriz("dataset/64x64_1.txt");
    vector<vector<int>> B = leerMatriz("dataset/64x64_2.txt");

    // Realiza la multiplicación de matrices usando el algoritmo de Strassen
    vector<vector<int>> C = multiplicarStrassen(A, B);
    
    // Termina la medición de tiempo
    auto fin = high_resolution_clock::now();
    
    // Calcula la duración total en milisegundos
    auto duracion = duration_cast<milliseconds>(fin - inicio).count();

    // Imprime el tiempo de ejecución
    cout << "Tiempo de ejecución: " << duracion << " ms" << endl;

    return 0;
}
