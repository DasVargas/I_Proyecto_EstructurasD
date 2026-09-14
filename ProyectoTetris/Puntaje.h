#ifndef PUNTAJE_H
#define PUNTAJE_H

#include <string>

using namespace std;

struct RegistroPuntaje {
	string nombre;
	int puntaje;
};

int calcularPuntos(int lineas);

void guardarPuntaje(string nombre, int puntaje);
void mostrarPuntajes();

void insertionSort(RegistroPuntaje puntajes[], int cantidad);

void mostrarTop10();

void merge(RegistroPuntaje puntajes[], int inicio, int medio, int fin);
void mergeSort(RegistroPuntaje puntajes[], int inicio, int fin);
void compararOrdenamientos();
#endif
