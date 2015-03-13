/*
 * 	marchivo.h
 *
 *  Created on: 20/03/2013
 *      Author: Carlos Enrique Peña Albarran
 *
 */

#include <fstream>

class LArchivo {
public:
	ofstream *salida;
	/**
	 * Contructor del Archivo
	 */
	LArchivo() {
		//Iniciando la Clases
		this->salida = new ofstream(); //instancia del Archivo
	}

	/**
	 * Destructor del Archivo
	 */
	~LArchivo() {
		//Saliendo de la Clase
		this->salida->close();
	}

	/*
	 *	Abrir Archivo de Texto
	 */
	void Abrir(const char *archivo) {
		this->salida->open(archivo); //Modo solo escritura
	}
	/*
	 * Escribir Linea del Archivo
	 */
	void Escribir(char *linea){
		this->salida->write(linea, strlen(linea)); //longitud de la linea
	}

	void EscribirSaltoLinea(char *linea){
		this->salida->write("\n",1);
		this->salida->write(linea, strlen(linea)); //longitud de la linea
	}

	/**
	 * Guadar y Cerrar Archivo
	 */
	void Salvar(){
		this->salida->close();
	}
	/*
	 * Leer Linea del Arvhico
	 */
	void Leer(){

	}



private:
	ifstream *entrada;


};
