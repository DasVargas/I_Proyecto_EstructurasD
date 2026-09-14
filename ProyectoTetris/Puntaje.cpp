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
