#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "Movimiento.h"

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
			
			Tablero tablero;
			
			cout << "======= TABLERO =======" << endl;
			
			tablero.setCelda(5, 3, 1);
			
			cout << "Valor de la celda [5][3]: ";
			cout << tablero.getCelda(5, 3) << endl;
			
			cout << endl;
			tablero.mostrarTablero();
			
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
				cout << "4. Movimiento y colisiones" << endl;
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
				case 4: {
				
					
					Tablero tablero;
					Pieza pieza('T');
					
					
					char movimiento;
					
					do {
						
						
						cout << "======= MOVIMIENTO =======" << endl;
						cout << "A = Izquierda" << endl;
						cout << "D = Derecha" << endl;
						cout << "S = Abajo" << endl;
						cout << "W = Rotar" << endl;
						cout << "0 = Salir" << endl;
						
						cout << endl;
						cout << "Fila actual: " << pieza.getFila() << endl;
						cout << "Columna actual: " << pieza.getColumna() << endl;
						cout << "Orientacion actual: " << pieza.getOrientacion() << endl;
						cout << endl;
						cout << "Movimiento: ";
						cin >> movimiento;
						
						if (movimiento == 'a' || movimiento == 'A') {
							moverIzquierda(pieza, tablero);
						}
						
						if (movimiento == 'd' || movimiento == 'D') {
							moverDerecha(pieza, tablero);
						}
						
						if (movimiento == 's' || movimiento == 'S') {
							
							if (!moverAbajo(pieza, tablero)) {
								colocarPieza(pieza, tablero);
								movimiento = '0';
							}
						}
						if (movimiento == 'w' || movimiento == 'W') {
							rotarPieza(pieza, tablero);
						}
					} while (movimiento != '0');
					
					
					cout << endl;
					cout << "======= TABLERO CON PIEZA =======" << endl;
					tablero.mostrarTablero();
					
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
