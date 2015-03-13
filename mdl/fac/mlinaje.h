/*
 * mlinaje.h
 *
 *  Creado Por: Carlos Enrique Peña Albarran
 *  Fecha: 24/03/2013
 */


class MLinaje{

public:
	/*
	 *Identificador del Banco
	 */
	int oid;

	/*
	 * Nombre del Banco
	 */
	string nmbr;

	/*
	 * Estatus
	 */
	char tipo;

	/*
	 * Lista de Linajes
	 */
	vector<MLinaje> Lista;

	/*
	 * Tiene Muchos Contratos
	 */
	vector<MContrato> Contratos;


};



