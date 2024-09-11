import matplotlib.pyplot as plt
import numpy as np

# Datos
scenarios = ['Menor a Mayor', 'Mayor a Menor', 'Repetición', 'Sin Repetición', 'Sin Repetición 20 Listas', 'Con Repetición 20 Listas']
bubble_sort = [14939, 48338, 44668, 44449, None, None]
merge_sort = [29, 30, 36, 42, 800, 811]
quick_sort = [4, 5, 16, 16, 310, 318]
algoritmo = [11, 8, 20, 21, 410, 414]  # None para valores que no se aplican

# Graficar
plt.figure(figsize=(10, 6))
plt.plot(scenarios, bubble_sort, marker='o', label='BubbleSort')
plt.plot(scenarios, merge_sort, marker='o', label='MergeSort')
plt.plot(scenarios, quick_sort, marker='o', label='QuickSort')
plt.plot(scenarios, algoritmo, marker='o', label='Algoritmo')

# Etiquetas y título
plt.xlabel('Escenario')
plt.ylabel('Tiempo (ms)')
plt.title('Comparación de Algoritmos de Ordenamiento')

# Añadir cuadrícula y leyenda
plt.grid(True)
plt.legend()

# Mostrar gráfica
plt.show()
