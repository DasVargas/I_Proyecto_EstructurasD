#include "Puntaje.h"
#include <fstream>
#include <iostream>

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
	RegistroPuntaje auxiliar[10000];
	
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
