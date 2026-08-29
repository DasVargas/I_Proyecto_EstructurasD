#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"

using namespace std;

int main() {
	
	srand(time(NULL));
	int opcion;
	
	do {
		cout << "========== TETRIS ==========" << endl;
		cout << "1. Iniciar juego" << endl;
		cout << "2. Pruebas" << endl;
		cout << "0. Salir" << endl;
		cout << "============================" << endl;
		cout << "Opcion: ";
		cin >> opcion;
		
		switch (opcion) {
			
		case 1: {
			system("cls");
			cout << "======= TETRIS =======" << endl;
			cout << "Juego pendiente..." << endl;
			cout << endl;
			system("pause");
			break;
		}
		
		case 2: {
			int prueba;
			do {
				system("cls");
				cout << "======= PRUEBAS =======" << endl;
				cout << "1. Tablero" << endl;
				cout << "2. Piezas" << endl;
				cout << "3. Cola de piezas" << endl;
				cout << "0. Volver" << endl;
				cout << "========================" << endl;
				cout << "Opcion: ";
				cin >> prueba;
	
				switch (prueba) {
					
				case 1: {
					system("cls");
					Tablero tablero;
					cout << "======= TABLERO =======" << endl;
					tablero.mostrarTablero();
					cout << endl;
					system("pause");
					break;
				}
				
				case 2: {
					system("cls");
					char tipo;
					cout << "======= PIEZAS =======" << endl;
					cout << "Pieza (I, O, T, S, Z, J, L): ";
					cin >> tipo;
					Pieza pieza(tipo);
					cout << endl;
					pieza.mostrarPieza();
					cout << endl;
					system("pause");
					break;
				}
				
				case 3: {
					system("cls");
					ColaPiezas cola;
					cola.generarBolsa();
					cout << "======= COLA DE PIEZAS =======" << endl;
					cout << "Cola completa:" << endl;
					cola.mostrar();
					cout << endl;
					cout << "Proximas 3:" << endl;
					cola.mostrarProximas3();
					cout << endl;
					system("pause");
					break;
				}
				
				case 0:
					break;
				default: {
					cout << "Opcion incorrecta." << endl;
					system("pause");
					
					break;
				}
				}
				
			} while (prueba != 0);
			
			break;
		}
		
		case 0:
			
			system("cls");
			cout << "Saliendo..." << endl;
			
			break;
			
		default: {
			
			cout << endl;
			cout << "Opcion incorrecta." << endl;
			
			system("pause");
			
			break;
		}
		}
		
	} while (opcion != 0);
	
	return 0;
}
