/*
 * 	mpersona.h
 *
 *  Creado Por: Carlos Enrique Peña Albarran
 *  Fecha: 18/03/2013
 *
 */


#include "mrbanco.h"


class MPersona {
public:
	/*
	 * Indentificador de la Persona
	 */
	string oid;

	/*
	 * Cedula de Indentidad
	 */
	string ced;

	/*
	 * Primer Nombre
	 */
	string pnmb;

	/*
	 * Segundo Nombre
	 */
	string snmb;

	/*
	 * Primer Apellido
	 */
	string pape;

	/*
	 * Segundo Apellido
	 */
	string sape;

	/**
	 * Cuenta Bancaria Principal
	 */
	MRBanco Banco;


	/*
	 * Tiene Mucho Numeros de Cuentas
	 */
	vector<MRBanco> LBanco;

	/*
	 * Constructor
	 *
	 * @param Cedula
	 */
	MPersona() {

	}

	/*
	 * Obtener una Persona Completo
	 *
	 * @param Conexion a MySql
	 * @param Cedula de Identidad
	 * @return MPersona
	 *
	 */
	void getPersona( MYSQL *conexion, string sCed) {
		MYSQL_RES *result;
		MYSQL_ROW row;
		int estado;

		// string sSet = "oid,ced,pnmb,snmb,pape,sape"; //Verdadero Modelo (t_personas)
		string sSet = "nro_documento,documento_id,primer_nombre,segundo_nombre,primer_apellido,segundo_apellido";
		string sQuery = "SELECT " + sSet + " FROM t_personas WHERE documento_id='" + sCed	+ "' LIMIT 1";

		estado =
				mysql_query(
						conexion,
						sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(conexion));
		}
		result = mysql_store_result(conexion);

		while ((row = mysql_fetch_row(result)) != NULL) {
			this->oid = row[0];
			this->ced = row[1];
			this->pnmb = row[2];
			this->snmb = row[3];
			this->pape = row[4];
			this->sape = row[5];
		}

		mysql_free_result(result);
	}

	/**
	 *
	 */
	void MuchosBanco(MYSQL *conexion, string oid) {
		MYSQL_RES *result;
		MYSQL_ROW row;
		int estado;

		string sQuery = "SELECT cuenta,tipo,t_banco.nmbr FROM _r_personabanco INNER JOIN t_banco ON _r_personabanco.oidb=t_banco.oid WHERE oidp=" + oid;

		estado = mysql_query(conexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(conexion));
		}
		result = mysql_store_result(conexion);
		while ((row = mysql_fetch_row(result)) != NULL) {
			MRBanco lst_banco = MRBanco();
			lst_banco.cuenta = row[0];
			lst_banco.tipo = row[1];
			lst_banco.nmbr = row[2];
			this->LBanco.push_back(lst_banco);
		}
		mysql_free_result(result);

	}

	/**
	 * Destructor
	 */
	~MPersona() {

	}

};

