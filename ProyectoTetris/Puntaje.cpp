#include "Puntaje.h"
#include <fstream>
#include <iostream>
#include <chrono>
#include <cstdlib>

int calcularPuntos(int lineas) {
	
	if (lineas == 1)
		return 100;
	
	if (lineas == 2)
		return 300;
	
	if (lineas == 3)
		return 500;
	
	if (lineas == 4)
		return 800;
	
	return 0;
}

void guardarPuntaje(string nombre, int puntaje) {
	ofstream archivo("puntajes.txt", ios::app);
	
	if (archivo.is_open()) {
		archivo << nombre << " " << puntaje << endl;
		archivo.close();
	}
}
void mostrarPuntajes() {
	ifstream archivo("puntajes.txt");
	
	string nombre;
	int puntaje;
	
	if (archivo.is_open()) {
		while (archivo >> nombre >> puntaje) {
			cout << nombre << " - " << puntaje << endl;
		}
		archivo.close();
	}
}
void insertionSort(RegistroPuntaje puntajes[], int cantidad) {
	for (int i = 1; i < cantidad; i++) {
		RegistroPuntaje aux = puntajes[i];
		int j = i - 1;
		
		while (j >= 0 && puntajes[j].puntaje < aux.puntaje) {
			puntajes[j + 1] = puntajes[j];
			j--;
		}
		
		puntajes[j + 1] = aux;
	}
}

void mostrarTop10() {
	ifstream archivo("puntajes.txt");
	
	RegistroPuntaje puntajes[100];
	int cantidad = 0;
	
	if (archivo.is_open()) {
		while (cantidad < 100 && archivo >> puntajes[cantidad].nombre>> puntajes[cantidad].puntaje) {
			cantidad++;
		}
		archivo.close();
	}
	
	insertionSort(puntajes, cantidad);
	
	cout << "======= TOP 10 =======" << endl;
	
	int limite = cantidad;
	
	if (limite > 10) {
		limite = 10;
	}
	
	for (int i = 0; i < limite; i++) {
		cout << i + 1 << ". "
		<< puntajes[i].nombre
		<< " - "
		<< puntajes[i].puntaje
		<< endl;
	}
}

void mergeSort(RegistroPuntaje puntajes[], int inicio, int fin) {
	if (inicio < fin) {
		int medio = (inicio + fin) / 2;
		
		mergeSort(puntajes, inicio, medio);
		mergeSort(puntajes, medio + 1, fin);
		
		merge(puntajes, inicio, medio, fin);
	}
}

void merge(RegistroPuntaje puntajes[], int inicio, int medio, int fin) {
	static RegistroPuntaje auxiliar[10000];
	int i = inicio;
	int j = medio + 1;
	int k = inicio;
	
	while (i <= medio && j <= fin) {
		if (puntajes[i].puntaje >= puntajes[j].puntaje) {
			auxiliar[k] = puntajes[i];
			i++;
		}
		else {
			auxiliar[k] = puntajes[j];
			j++;
		}
		
		k++;
	}
	
	while (i <= medio) {
		auxiliar[k] = puntajes[i];
		i++;
		k++;
	}
	
	while (j <= fin) {
		auxiliar[k] = puntajes[j];
		j++;
		k++;
	}
	
	for (int x = inicio; x <= fin; x++) {
		puntajes[x] = auxiliar[x];
	}
}

void compararOrdenamientos() {
	int tamanos[4] = {10, 100, 1000, 10000};
	
	cout << "======= COMPARACION DE ORDENAMIENTOS =======" << endl;
	cout << endl;
	
	for (int t = 0; t < 4; t++) {
		
		int cantidad = tamanos[t];
		
		RegistroPuntaje* datos = new RegistroPuntaje[cantidad];
		RegistroPuntaje* datosInsertion = new RegistroPuntaje[cantidad];
		RegistroPuntaje* datosMerge = new RegistroPuntaje[cantidad];
		
		// Generamos los mismos datos para ambos algoritmos
		for (int i = 0; i < cantidad; i++) {
			
			datos[i].nombre = "Jugador";
			datos[i].puntaje = rand() % 100000;
			
			datosInsertion[i] = datos[i];
			datosMerge[i] = datos[i];
		}
		
		// INSERTION SORT
		auto inicioInsertion = chrono::high_resolution_clock::now();
		
		insertionSort(datosInsertion, cantidad);
		
		auto finInsertion = chrono::high_resolution_clock::now();
		
		chrono::duration<double, milli> tiempoInsertion = finInsertion - inicioInsertion;
		
		// MERGE SORT
		auto inicioMerge = chrono::high_resolution_clock::now();
		
		mergeSort(datosMerge, 0, cantidad - 1);
		
		auto finMerge = chrono::high_resolution_clock::now();
		
		chrono::duration<double, milli> tiempoMerge = finMerge - inicioMerge;
		
		// Mostrar resultados
		cout << "Cantidad: " << cantidad << endl;
		
		cout << "Insertion Sort: "<< tiempoInsertion.count()<< " ms" << endl;
		cout << "Merge Sort: "<< tiempoMerge.count() << " ms" << endl;
		
		delete[] datos;
		delete[] datosInsertion;
		delete[] datosMerge;
	}
}
