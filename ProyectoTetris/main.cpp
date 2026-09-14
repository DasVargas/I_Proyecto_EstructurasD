#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Tablero.h"
#include "Pieza.h"
#include "ColaPiezas.h"
#include "Movimiento.h"
#include "Juego.h"
#include "ColaEventos.h"
#include "Puntaje.h"

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
			iniciarJuego();
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
				cout << "5. Caida automatica" << endl;
				cout << "6. prueba"<<endl;
				cout << "7. Guardar puntaje" << endl;
				cout << "8. Mostrar puntajes" << endl;
				cout << "9. Insertion Sort puntajes" << endl;
				cout << "10. Mostrar Top 10" << endl;
				cout << "11. Merge Sort puntajes" << endl;
				cout << "12. Comparar ordenamientos" << endl;
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
					system("cls");
					
					Tablero tablero;
					ColaPiezas cola;
					
					int puntaje = 0;
					
					cola.generarBolsa();
					
					char continuar = 's';
					
					while (continuar == 's' || continuar == 'S') {
						
						cola.mantenerCola();
						
						char tipo = cola.sacar();
						
						Pieza pieza(tipo);
						
						if (!puedeMover(pieza, tablero, pieza.getFila(), pieza.getColumna())) {
							cout << endl;
							cout << "======= GAME OVER =======" << endl;
							tablero.mostrarTablero();
							break;
						}
						
						char movimiento;
						
						cout << endl;
						cout << "Pieza actual: " << tipo << endl;
						
						do {
							
							cout << endl;
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
									//int lineas = tablero.limpiarFilas();
									movimiento = '0';
								}
							}
							
							if (movimiento == 'w' || movimiento == 'W') {
								rotarPieza(pieza, tablero);
							}
							
						} while (movimiento != '0');
						
						cout << endl;
						cout << "======= TABLERO =======" << endl;
						tablero.mostrarTablero();
						
						cout << endl;
						cout << "Siguiente pieza? (S/N): ";
						cin >> continuar;
					}
					
					system("pause");
					break;
				}
				case 5: {
					system("cls");
					
					Tablero tablero;
					ColaPiezas cola;
					
					cola.generarBolsa();
					
					char tipo = cola.sacar();
					Pieza pieza(tipo);
					
					sf::Clock relojCaida;
					
					cout << "======= CAIDA AUTOMATICA =======" << endl;
					cout << "Pieza: " << tipo << endl;
					cout << endl;
					
					while (true) {
						
						if (relojCaida.getElapsedTime().asSeconds() >= 0.8f) {
							
							if (!moverAbajo(pieza, tablero)) {
								colocarPieza(pieza, tablero);
								tablero.limpiarFilas();
								break;
							}
							
							cout << "Fila actual: " << pieza.getFila() << endl;
							
							relojCaida.restart();
						}
					}
					
					cout << endl;
					cout << "Pieza colocada." << endl;
					tablero.mostrarTablero();
					
					cout << endl;
					system("pause");
					break;
				}
				case 6:{
					ColaEventos eventos;
					
					eventos.insertar("PIEZA COLOCADA", 3);
					eventos.insertar("GAME OVER", 1);
					eventos.insertar("LINEA ELIMINADA", 2);
					
					eventos.mostrar();
					system("pause");
					break;
				}
				case 7:{
						string nombre;
						int puntaje;
						
						cout << "======= GUARDAR PUNTAJE =======" << endl;
						
						cout << "Nombre: ";
						cin >> nombre;
						
						cout << "Puntaje: ";
						cin >> puntaje;
						
						guardarPuntaje(nombre, puntaje);
						
						cout << endl;
						cout << "Puntaje guardado correctamente." << endl;
						
						system("pause");
						break;
					}
				case 8: {
							system("cls");
							
							cout << "======= PUNTAJES =======" << endl;
							
							mostrarPuntajes();
							
							cout << endl;
							system("pause");
							break;
						}
				case 9: {
					RegistroPuntaje puntajes[5] = {
						{"Das", 806},
					{"Pepe", 400},
						{"Ana", 1200},
					{"Luis", 250},
						{"Maria", 950}
					};
					
					insertionSort(puntajes, 5);
					
					cout << "======= INSERTION SORT =======" << endl;
					
					for (int i = 0; i < 5; i++) {
						cout << puntajes[i].nombre
							<< " - "
							<< puntajes[i].puntaje << endl;
					}
					
					cout << endl;
					system("pause");
					break;
				}
				case 10: {
					mostrarTop10();
					
					cout << endl;
					system("pause");
					break;
				}
				case 11: {
					system("cls");
					
					RegistroPuntaje puntajes[5] = {
						{"Das", 806},
					{"Pepe", 400},
						{"Ana", 1200},
					{"Luis", 250},
						{"Maria", 950}
					};
					
					mergeSort(puntajes, 0, 4);
					
					cout << "======= MERGE SORT =======" << endl;
					
					for (int i = 0; i < 5; i++) {
						cout << puntajes[i].nombre
							<< " - "
							<< puntajes[i].puntaje << endl;
					}
					
					cout << endl;
					
					system("pause");
					break;
				}
				case 12: {
					
					system("cls");
					
					compararOrdenamientos();
					
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
