#include "metodosDeOrdenamientos.hpp"
#include <chrono>

std::map<std::string, MetodoPorTipo> metodos;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void insercionDirecta(std::vector<int>& array,
                      int size,
                      std::string& tipoArreglo) {
    int i, j;
    std::vector<int> copia = array;

    MetodoOrdenamiento insercionDirectaMetodo;
    insercionDirectaMetodo.nombre = "Insercion Directa";

    insercionDirectaMetodo.comparaciones = 0;
    insercionDirectaMetodo.intercambios = 0;

    auto start = std::chrono::steady_clock::now();

    for (i = 1; i < size; i++) {
        int actual = copia[i];
        j = i - 1;
        insercionDirectaMetodo.comparaciones++;

        while (j >= 0 && copia[j] > actual) {
            copia[j + 1] = copia[j];
            j--;
            insercionDirectaMetodo.intercambios++;
            insercionDirectaMetodo.comparaciones++;
        }

        copia[j + 1] = actual;
    }
    auto end = std::chrono::steady_clock::now();
    insercionDirectaMetodo.tiempo =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count();

    if (metodos.find(insercionDirectaMetodo.nombre) == metodos.end()) {
        metodos[insercionDirectaMetodo.nombre] = MetodoPorTipo();
    }
    metodos[insercionDirectaMetodo.nombre][tipoArreglo] = insercionDirectaMetodo;
}

void seleccion(std::vector<int>& array, int size, std::string& tipoArreglo) {
    std::vector<int> copia = array;
    MetodoOrdenamiento seleccionMetodo;
    seleccionMetodo.nombre = "Seleccion";

    seleccionMetodo.comparaciones = 0;
    seleccionMetodo.intercambios = 0;

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < size - 1; i++) {
        int e = i;
        for (int j = i + 1; j < size; j++) {
            seleccionMetodo.comparaciones++;

            if (copia[e] > copia[j]) {
                e = j;
            }
        }

        if (i != e) {
            int t = copia[i];
            copia[i] = copia[e];
            copia[e] = t;
            seleccionMetodo.intercambios++;
        }
    }
    auto end = std::chrono::steady_clock::now();
    seleccionMetodo.tiempo =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count();

    if (metodos.find(seleccionMetodo.nombre) == metodos.end()) {
        metodos[seleccionMetodo.nombre] = MetodoPorTipo();
    }
    metodos[seleccionMetodo.nombre][tipoArreglo] = seleccionMetodo;
}

void burbuja(std::vector<int>& array, int size, std::string& tipoArreglo) {
    std::vector<int> copia = array;
    MetodoOrdenamiento burbujaMetodo;
    burbujaMetodo.nombre = "Burbuja";

    burbujaMetodo.comparaciones = 0;
    burbujaMetodo.intercambios = 0;

    auto start = std::chrono::steady_clock::now();

    for (int i = 1; i < size; i++) {
        for (int j = size - 1; j >= i; --j) {
            burbujaMetodo.comparaciones++;

            if (copia[j - 1] > copia[j]) {
                int t = copia[j - 1];
                copia[j - 1] = copia[j];
                copia[j] = t;
                burbujaMetodo.intercambios++;
            }
        }
    }

    auto end = std::chrono::steady_clock::now();
    burbujaMetodo.tiempo =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count();

    if (metodos.find(burbujaMetodo.nombre) == metodos.end()) {
        metodos[burbujaMetodo.nombre] = MetodoPorTipo();
    }
    metodos[burbujaMetodo.nombre][tipoArreglo] = burbujaMetodo;
}

void burbujaMejorado(std::vector<int>& array,
                     int size,
                     std::string& tipoArreglo) {
    std::vector<int> copia = array;

    MetodoOrdenamiento burbujaMejoradoMetodo;
    burbujaMejoradoMetodo.nombre = "Burbuja Mejorado";

    burbujaMejoradoMetodo.comparaciones = 0;
    burbujaMejoradoMetodo.intercambios = 0;

    bool bandera;

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < size - 1; i++) {
        bandera = false;
        for (int j = 0; j < size - i - 1; j++) {
            burbujaMejoradoMetodo.comparaciones++;
            if (copia[j] > copia[j + 1]) {
                swap(copia[j], copia[j + 1]);
                bandera = true;
                burbujaMejoradoMetodo.intercambios++;
            }
        }
        if (!bandera) {
            break;
        }
    }
    auto end = std::chrono::steady_clock::now();
    burbujaMejoradoMetodo.tiempo =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count();

    if (metodos.find(burbujaMejoradoMetodo.nombre) == metodos.end()) {
        metodos[burbujaMejoradoMetodo.nombre] = MetodoPorTipo();
    }
    metodos[burbujaMejoradoMetodo.nombre][tipoArreglo] = burbujaMejoradoMetodo;
}

void shellsort(std::vector<int>& array, int size, std::string& tipoArreglo) {
    std::vector<int> copia = array;

    MetodoOrdenamiento shellSortMetodo;
    shellSortMetodo.nombre = "ShellSort";

    shellSortMetodo.comparaciones = 0;
    shellSortMetodo.intercambios = 0;

    auto start = std::chrono::steady_clock::now();

    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = copia[i];
            int j;

            for (j = i; j >= gap && copia[j - gap] > temp; j -= gap) {
                copia[j] = copia[j - gap];
                shellSortMetodo.comparaciones++;
                shellSortMetodo.intercambios++;
            }

            copia[j] = temp;
            shellSortMetodo.intercambios++;
        }
    }

    auto end = std::chrono::steady_clock::now();
    shellSortMetodo.tiempo =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count();

    if (metodos.find(shellSortMetodo.nombre) == metodos.end()) {
        metodos[shellSortMetodo.nombre] = MetodoPorTipo();
    }
    metodos[shellSortMetodo.nombre][tipoArreglo] = shellSortMetodo;
}

int partition(std::vector<int>& array,
              int inicio,
              int fin,
              MetodoOrdenamiento& metodo,
              std::string& tipoArreglo) {
    int medio = (fin - inicio) / 2;
    int pivote = array[medio];

    if (tipoArreglo == "Desordenado") {
        pivote = array[fin];
    }

    int i = inicio - 1;

    for (int j = inicio; j < fin; j++) {
        metodo.comparaciones++;
        if (array[j] <= pivote) {
            i++;
            swap(array[i], array[j]);
            metodo.intercambios++;
        }
    }
    swap(array[i + 1], array[fin]);
    metodo.intercambios++;
    return i + 1;
}

void quicksort(std::vector<int>& array,
               int inicio,
               int fin,
               std::string& tipoArreglo,
               MetodoOrdenamiento& quickSortMetodo) {
    if (inicio < fin) {
        int pivotIndex =
            partition(array, inicio, fin, quickSortMetodo, tipoArreglo);

        quicksort(array, inicio, pivotIndex - 1, tipoArreglo, quickSortMetodo);
        quicksort(array, pivotIndex + 1, fin, tipoArreglo, quickSortMetodo);
    }
}
