#include <iostream>
#include <cstdlib>
#include <ctime>
#include "ColaPiezas.h"

using namespace std;

int main() {
	
	srand(time(NULL));
	
	ColaPiezas cola;
	
	cola.generarBolsa();
	
	cout << "COLA INICIAL:" << endl;
	cola.mostrar();
	
	cout << endl;
	
	cout << "Sacamos 5 piezas:" << endl;
	
	for (int i = 0; i < 5; i++) {
		cout << cola.sacar() << " ";
	}
	
	cout << endl << endl;
	
	cout << "COLA RESTANTE:" << endl;
	cola.mostrar();
	
	cout << endl;
	
	cout << "Cantidad restante: " << cola.contar() << endl;
	
	cola.mantenerCola();
	
	cout << endl;
	
	cout << "COLA DESPUES DE MANTENER:" << endl;
	cola.mostrar();
	
	cout << endl;
	
	cout << "Cantidad ahora: " << cola.contar() << endl;
	
	cout << endl;
	
	cout << "PROXIMAS 3:" << endl;
	cola.mostrarProximas3();
	
	return 0;
}
