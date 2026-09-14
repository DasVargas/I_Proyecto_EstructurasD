#ifndef PIEZA_H
#define PIEZA_H

class Pieza {
private:
	
	char tipo;
	int forma[4][4][4];
	
	int orientacion;
	int fila;
	int columna;
	
public:
	
	Pieza(char tipoPieza);
	
	void mostrarPieza();
	void rotar();
	
	int getFila();
	int getColumna();
	int getOrientacion();
	
	void setFila(int nuevaFila);
	void setColumna(int nuevaColumna);
	
	int getCelda(int f, int c);
	
	void setOrientacion(int nuevaOrientacion);
	
	char getTipo();
};

#endif
