import matplotlib.pyplot as plt
import numpy as np

# Datos
matrix_sizes = ['64x64', '128x128', '256x256', '512x512', '1024x1024', '2048x2048']
cubico = [6, 23, 155, 1187, 8669, 72969]
traspuesto = [5, 23, 146, 1097, 8506, 68715]
strassen = [199, 1376, 9475, 67198, 464929, None]  # None para el valor faltante

# Convertir los tamaños de las matrices a enteros para la gráfica
matrix_sizes_int = [64, 128, 256, 512, 1024, 2048]

# Graficar
plt.figure(figsize=(10, 6))
plt.plot(matrix_sizes_int, cubico, marker='o', label='Cúbico')
plt.plot(matrix_sizes_int, traspuesto, marker='o', label='Traspuesto')
plt.plot(matrix_sizes_int, strassen, marker='o', label='Strassen')

# Etiquetas y título
plt.xlabel('Tamaño de la matriz (n x n)')
plt.ylabel('Tiempo (ms)')
plt.title('Comparación de algoritmos de multiplicación de matrices')

# Personalizar las etiquetas del eje X
plt.xticks(matrix_sizes_int, matrix_sizes)

# Añadir cuadrícula y leyenda
plt.grid(True)
plt.legend()

# Mostrar gráfica
plt.show()
