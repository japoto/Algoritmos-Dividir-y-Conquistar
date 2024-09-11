import numpy as np

def generar_matriz_aleatoria(n, rango=(1, 32)):
    return np.random.randint(rango[0], rango[1], size=(n, n))

def guardar_matriz(matriz, nombre, indice):
    np.savetxt(f'{nombre}_{indice}.txt', matriz, fmt='%d')
    print(f"Matriz guardada como {nombre}_{indice}.txt")

def menu():
    print("Selecciona el tipo de matriz a generar:")
    print("1. Matriz Aleatoria")
    print("0. Salir")

def main():
    while True:
        menu()
        opcion = int(input("Opción: "))
        if opcion == 0:
            break
        
        n = 2048
        num_matrices = 2
        
        for i in range(num_matrices):
            if opcion == 1:
                matriz = generar_matriz_aleatoria(n)
                guardar_matriz(matriz, "matriz_aleatoria", i+1)
            else:
                print("Opción no válida. Intenta de nuevo.")

if __name__ == "__main__":
    main()
