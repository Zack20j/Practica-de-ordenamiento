#ifndef METODOS_DE_ORDENAMIENTOS_HPP
#define METODOS_DE_ORDENAMIENTOS_HPP

#include <vector>
#include <map>
#include <string>
#include <iomanip>

struct MetodoOrdenamiento {
    std::string nombre;
    double tiempo;
    int comparaciones;
    int intercambios;
};

using MetodoPorTipo = std::map<std::string, MetodoOrdenamiento>;
extern std::map<std::string, MetodoPorTipo> metodos;

void swap(int& a, int& b);
void insercionDirecta(std::vector<int>& array,int size,std::string& tipoArreglo);
void seleccion(std::vector<int>& array, int size,std::string& tipoArreglo);
void burbuja(std::vector<int>& array, int size,std::string& tipoArreglo);
void burbujaMejorado(std::vector<int>& array, int size,std::string& tipoArreglo);
void shellsort(std::vector<int>& array, int size,std::string& tipoArreglo);
int particion(std::vector<int>& array, int inicio, int fin, MetodoOrdenamiento &metodo);
void quicksort(std::vector<int>& array, int inicio, int fin,std::string& tipoArreglo,MetodoOrdenamiento &quickSortMetodo);


#endif
