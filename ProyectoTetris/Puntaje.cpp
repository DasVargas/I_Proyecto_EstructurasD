#include "Puntaje.h"

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
