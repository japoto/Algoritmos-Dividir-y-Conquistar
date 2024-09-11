import random

def generate_random_dataset(array_size):
    return [random.randint(1, 100000) for _ in range(array_size)]

def generate_sorted_dataset(array_size):
    return list(range(1, array_size + 1))

def generate_reverse_sorted_dataset(array_size):
    return list(range(array_size, 0, -1))

def generate_shuffled_unique_dataset(array_size):
    array = list(range(1, array_size + 1))
    random.shuffle(array)
    return array

def save_dataset_to_file(dataset, file_name):
    with open(file_name, 'w') as f:
        for array in dataset:
            array_str = ' '.join(map(str, array))
            f.write(array_str + '\n')

def main():
    # Configura los parámetros
    num_arrays = 1  # Número de arreglos
    array_size = 100000  # Tamaño de cada arreglo

    # Menú de selección
    print("Seleccione una opción para generar el dataset:")
    print("1. Repeticion")
    print("2. Ordenado de menor a mayor")
    print("3. Ordenado de mayor a menor")
    print("4. Desordenado sin repetición")
    choice = input("Ingrese el número de la opción: ")

    if choice == '1':
        dataset = [generate_random_dataset(array_size) for _ in range(num_arrays)]
        file_name = 'dataset_repeticion.txt'
    elif choice == '2':
        dataset = [generate_sorted_dataset(array_size) for _ in range(num_arrays)]
        file_name = 'dataset_mejorcaso.txt'
    elif choice == '3':
        dataset = [generate_reverse_sorted_dataset(array_size) for _ in range(num_arrays)]
        file_name = 'dataset_peorcaso.txt'
    elif choice == '4':
        dataset = [generate_shuffled_unique_dataset(array_size) for _ in range(num_arrays)]
        file_name = 'dataset_sinrepeticion.txt'
    else:
        print("Opción no válida.")
        return

    save_dataset_to_file(dataset, file_name)
    print(f"Dataset creado y guardado en {file_name}")

main()