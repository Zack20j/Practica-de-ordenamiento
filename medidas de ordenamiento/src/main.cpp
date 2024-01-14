#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "metodosDeOrdenamientos.hpp"

std::vector<int> generarArregloOrdenado(int tamano) {
    std::vector<int> arreglo(tamano);

    for (int i = 0; i < tamano; ++i) {
        arreglo[i] = i + 1;
    }
    return arreglo;
}

std::vector<int> generarArregloDesordenado(int tamano, const std::vector<int>& array) {
    std::vector<int> copia = array;

    //se usa un arreglo ordenada para generar el arreglo desordenado
    for (int i = tamano - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        swap(copia[i], copia[j]);
    }
    return copia;
}


std::vector<int> generarArregloOrdenadoInvertido(int tamano) {
    std::vector<int> arreglo(tamano);

    for (int i = tamano; i > 0; --i) {
        arreglo[tamano - i] = i;
    }
    return arreglo;
}

//mostrar el cuadro de informacion de los metodos de ordenamiento
void mostrarCuadro(const std::string& nombreMetodo,
                   const MetodoPorTipo& metodosPorTipo,
                   int tipoInformacion) {
    std::cout << std::setw(20) << nombreMetodo;

    //mostrar la informacion de los metodos
    for (const auto& parTipo : metodosPorTipo) {
        const MetodoOrdenamiento& metodo = parTipo.second;

        //determinar el tipo de informacion a mostrar
        if (tipoInformacion == 1) {
            std::cout << std::setw(20) << metodo.tiempo << "s";
        } else if (tipoInformacion == 2) {
            std::cout << std::setw(20) << metodo.comparaciones;
        } else if (tipoInformacion == 3) {
            std::cout << std::setw(20) << metodo.intercambios;
        }
    }

    std::cout << std::endl;
}

//mostrar la lista ordenada de mejor a peor
void mostrarLista(int tipoInformacion) {
    std::map<std::string, std::string> tipoArregloMap = {
        {"Desordenado", "Arreglo Desordenado"},
        {"Ordenado", "Arreglo Ordenado"},
        {"Invertido", "Arreglo Invertido"}};

    //mostrar los tipos de arreglos
    for (const auto& tipoArreglo : tipoArregloMap) {
        std::cout << tipoArreglo.second << std::endl;

        std::vector<std::pair<std::string, MetodoOrdenamiento>>
            resultadosFiltrados;

        //filtrar los resultados segun el tipo de arreglo
        for (const auto& par : metodos) {
            const std::string& nombreMetodo = par.first;
            const MetodoPorTipo& metodosPorTipo = par.second;

            const auto& metodo = metodosPorTipo.find(tipoArreglo.first);
            if (metodo != metodosPorTipo.end()) {
                resultadosFiltrados.push_back({nombreMetodo, metodo->second});
            }
        }

        //ordenar los resultados segun el tipo de informacion
        std::sort(resultadosFiltrados.begin(), resultadosFiltrados.end(),
                  [&tipoInformacion](const auto& a, const auto& b) {
                      if (tipoInformacion == 2) {
                          return a.second.comparaciones <
                                 b.second.comparaciones;
                      } else if (tipoInformacion == 3) {
                          return a.second.intercambios < b.second.intercambios;
                      } else {
                          return a.second.tiempo < b.second.tiempo;
                      }
                  });

        //mostrar los resultados
        int count = 1;
        for (const auto& par : resultadosFiltrados) {
            const std::string& nombreMetodo = par.first;
            const MetodoOrdenamiento& metodoOrdenado = par.second;

            std::cout << count << ".- " << nombreMetodo << " ";

            if (tipoInformacion == 1) {
                std::cout << metodoOrdenado.tiempo << "s";
            } else if (tipoInformacion == 2) {
                std::cout << metodoOrdenado.comparaciones;
            } else if (tipoInformacion == 3) {
                std::cout << metodoOrdenado.intercambios;
            }

            std::cout << std::endl;
            count++;
        }

        std::cout << std::endl;
    }
}

void ejecutarQuicksort(std::vector<int>& arreglo,
                       int tamano,
                       std::string& tipoArreglo) {

    //se hace la obtencion de la informacion fuera del metodo para
    //evitar errores debido a la recursividad
    std::vector<int> copia = arreglo;
    MetodoOrdenamiento quickSortMetodo;
    quickSortMetodo.nombre = "QuickSort";

    //se inicializa en 0
    quickSortMetodo.comparaciones = 0;
    quickSortMetodo.intercambios = 0;

    auto start = std::chrono::steady_clock::now();//inicia el cronometro

    quicksort(copia, 0, tamano - 1, tipoArreglo, quickSortMetodo);
    auto end = std::chrono::steady_clock::now();//termina el cronometro

    quickSortMetodo.tiempo =
        std::chrono::duration_cast<std::chrono::duration<double>>(end - start)
            .count();//guarda el tiempo de ejecucion

    //se agrega el metodo a la lista
    if (metodos.find(quickSortMetodo.nombre) == metodos.end()) {
        metodos[quickSortMetodo.nombre] = MetodoPorTipo();
    }
    //se agrega el tipo de arreglo al metodo
    metodos[quickSortMetodo.nombre][tipoArreglo] = quickSortMetodo;
}

void iniciarOrdenamiento(std::vector<int>& arreglo,
                         int tamano,
                         std::string& tipoArreglo) {
    insercionDirecta(arreglo, tamano, tipoArreglo);
    seleccion(arreglo, tamano, tipoArreglo);
    burbuja(arreglo, tamano, tipoArreglo);
    burbujaMejorado(arreglo, tamano, tipoArreglo);
    shellsort(arreglo, tamano, tipoArreglo);
    ejecutarQuicksort(arreglo, tamano, tipoArreglo);
}

//metodo para daler a escoger al usuario que tipo de ordenamiento completo o parcial
void realizarOrdenamiento(int tamano) {
    int opcionOrdenamiento,subArreglo = 1000;

    std::cout << "Bienvenido,seleccione una opcion de ordenamiento:" << std::endl;
    std::cout << "1. Ordenamiento completo" << std::endl;
    std::cout << "2. Ordenamiento parcial (primeros 1000 elementos)" << std::endl;
    std::cin >> opcionOrdenamiento;
    system("cls");

    std::cout << "Porfavor sea paciente!" << std::endl;

    std::vector<int> arregloOrdenado = generarArregloOrdenado(tamano);//generar un arreglo ordenado
    std::vector<int> arregloDesordenado = generarArregloDesordenado(tamano, arregloOrdenado);//generar un arreglo desordenado
    std::vector<int> arregloOrdenadoInvertido = generarArregloOrdenadoInvertido(tamano);//generar un arreglo ordenado invertido

    std::string tipoArregloDesordenado = "Desordenado";
    std::string tipoArregloOrdenado = "Ordenado";
    std::string tipoArregloInvertido = "Invertido";

    switch (opcionOrdenamiento) {
        case 1:
            std::cout << "Iniciando ordenamiento con arreglo desordenado." << std::endl;
            iniciarOrdenamiento(arregloDesordenado, tamano, tipoArregloDesordenado);
            std::cout << "Iniciando ordenamiento con arreglo ordenado." << std::endl;
            iniciarOrdenamiento(arregloOrdenado, tamano, tipoArregloOrdenado);
            std::cout << "Iniciando ordenamiento con arreglo ordenado invertido." << std::endl;
            iniciarOrdenamiento(arregloOrdenadoInvertido, tamano, tipoArregloInvertido);
            break;
        case 2:
            std::cout << "Iniciando ordenamiento parcial con arreglo desordenado." << std::endl;
            seleccion(arregloDesordenado,subArreglo,tipoArregloDesordenado);
            insercionDirecta(arregloDesordenado, tamano, tipoArregloDesordenado);
            burbuja(arregloDesordenado, tamano, tipoArregloDesordenado);
            burbujaMejorado(arregloDesordenado, tamano, tipoArregloDesordenado);
            shellsort(arregloDesordenado, tamano, tipoArregloDesordenado);
            ejecutarQuicksort(arregloDesordenado, tamano, tipoArregloDesordenado);

            break;
        default:
            std::cout << "Opcion invalida. Iniciando ordenamiento completo por defecto." << std::endl;
            iniciarOrdenamiento(arregloDesordenado, tamano, tipoArregloDesordenado);
            iniciarOrdenamiento(arregloOrdenado, tamano, tipoArregloOrdenado);
            iniciarOrdenamiento(arregloOrdenadoInvertido, tamano, tipoArregloInvertido);
            break;
    }
    std::cout << "Ordenamiento completado." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
}

void pausarYLimpiarPantalla() {
    std::cout << "Presiona una tecla para continuar...";
    std::cin.ignore();
    std::cin.get();
    system("cls");
}

int main() {
    int opcion,tipoInformacion;

    realizarOrdenamiento(30000);// tamano del arreglo

    do {
        std::cout << "Seleccione una opcion:" << std::endl;
        std::cout
            << "1. Mostrar cuadro de informacion de metodos de ordenamiento"
            << std::endl;
        std::cout << "2. Mostrar lista ordenada de mejor a peor" << std::endl;
        std::cout << "3. Salir" << std::endl;

        std::cin >> opcion;
        system("cls");

        if (opcion == 1 || opcion == 2) {
            std::cout << "Seleccione el cuadro a mostrar:" << std::endl;
            std::cout << "1. Cuadro de Tiempo" << std::endl;
            std::cout << "2. Cuadro de Comparaciones" << std::endl;
            std::cout << "3. Cuadro de Intercambios" << std::endl;
            std::cin >> tipoInformacion;
        }

        switch (opcion) {
            case 1:
                std::cout << std::setw(20) << "Nombre del Método";
                for (const auto& parTipo : metodos.begin()->second) {
                    const std::string& tipoArreglo = parTipo.first;
                    std::cout << std::setw(20) << tipoArreglo;
                }
                std::cout << std::endl;

                for (const auto& par : metodos) {
                    const std::string& nombreMetodo = par.first;
                    const MetodoPorTipo& metodosPorTipo = par.second;
                    mostrarCuadro(nombreMetodo, metodosPorTipo,
                                  tipoInformacion);
                }
                pausarYLimpiarPantalla();
                break;
            case 2:
                mostrarLista(tipoInformacion);
                pausarYLimpiarPantalla();

                break;
            case 3:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida. Intente de nuevo." << std::endl;
        }

    } while (opcion != 3);

    return 0;
}
