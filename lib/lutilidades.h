/*
 * Herramientas de lectura de cadenas
 *
 * Creada Por: Judelvis Rivas
 * Comentado, Editado Por: Carlos Enrique Peña
 * Fecha : 21/03/2013
 *
 */
using namespace std;

#include <iostream>
#include <string.h>
#include <vector>
#include "iomanip"
#include "math.h"

typedef vector<string> VecString;

class LUtilidades {

public:

	/**
	 * Contructor
	 */
	LUtilidades() {

	}

	/**
	 * Parser de Parametros Picar Cadena en un Vector
	 *
	 * Creada Por: Judelvis Rivas
	 * Fecha : 21/03/2013
	 *
	 * @param dilimitador (:,;|)
	 * @param cadena (Cadena de Texto)
	 * @return vector
	 */
	vector<string> Explode(string delim, string cadena) {
		vector<string> arreglo_cadenas;
		string aux;
		int tam_cadena = cadena.length();
		int tam_del = delim.length();
		if (delim == "") {
			return arreglo_cadenas;
		}
		int i = 0;
		int k = 0;
		int j = 0;
		aux = cadena.substr(i, tam_cadena);
		k = aux.find(delim);
		while (k != string::npos) {
			arreglo_cadenas.push_back(aux.substr(j, k));
			aux = aux.substr(k + tam_del, aux.length() - k - tam_del);
			k = aux.find(delim);
		};
		arreglo_cadenas.push_back(aux);
		return arreglo_cadenas;
	}

	/**
	 * Agregar Ceros Derecha Izquierda
	 *
	 * Creada Por: Judelvis Rivas
	 * Fecha : 22/03/2013
	 *
	 * @param Cadena string
	 * @param Numero Integer
	 * @param Posicion (1: Derecha 0: Izquierda)
	 * @return string
	 */
	string Completar(string sCd,int iNum, int iPos){
		string sAux, sCero = "00000000000000000000000000000";
		sAux.assign(sCd);
		short int cant = iNum - sCd.length();
		(cant > 0 ) ? ((iPos == 1 ) ? sAux.insert(0,sCero,0,cant):sAux.insert(sCd.length(),sCero,0,cant)):sAux;
		return sAux;
	}


	/**
	 * Agregar Espacios en Blanco Derecha Izquierda
	 *
	 * Creada Por: Carlos Peña tomada de (Completar)
	 * Fecha : 28/11/2013
	 *
	 * @param Cadena string
	 * @param Numero Integer
	 * @param Posicion (1: Derecha 0: Izquierda)
	 * @return string
	 */
	string CompletarEspacios(string sCd,int iNum, int iPos){
		string sAux, sLimpiar = "                                        ";
		sAux.assign(sCd);
		short int cant = iNum - sCd.length();
		(cant > 0 ) ? ((iPos == 1 ) ? sAux.insert(0,sLimpiar,0,cant):sAux.insert(sCd.length(),sLimpiar,0,cant)):sAux;
		return sAux;
	}



};

