/*
 * mfactura.h
 *
 *  Created on: 27/03/2013
 *      Author: crash
 */


class MFactura{

public:
	/*
	 * Identificador
	 */
	char *oid;

	/*
	 * Una Persona
	 */
	MPersona Persona;

	/*
	 * Tiene Muchos Contratos
	 */
	vector<MContrato> Contrato;

	/*
	 * Tiene Un Linaje
	 */
	string Linaje;

	/*
	 * Tiene Muchos Cheques
	 */

	/*
	 * Tiene Muchos Productos
	 */


	/**
	 * Una Persona
	 * @param MYSQL Conexion
	 * @param Identificador de Factura
	 * @param Identificador del Banco
	 */
	void UnaPersona(MYSQL *conexion, string oidf, string oidb){
		MYSQL_RES *result;
		MYSQL_ROW row;
		int estado;
		string sSet = "t_persona.oid,ced,pnmb,snmb,pape,sape,_r_personabanco.cuenta";
		string sQuery =
				"SELECT " + sSet
						+ " FROM t_factura JOIN t_persona ON t_factura.oidp = t_persona.oid"
						+ " JOIN _r_personabanco ON _r_personabanco.oidp = t_persona.oid"
						+ " JOIN t_banco ON t_banco.oid = _r_personabanco.oidb"
						+ " WHERE t_factura.oid = " + oidf + " LIMIT 1";
		// AND _r_personabanco.oidb= " + oidb + "

		estado = mysql_query(conexion, sQuery.c_str());
		if (estado != 0) {
			cout << mysql_error(conexion);
		}
		result = mysql_store_result(conexion);
		while ((row = mysql_fetch_row(result)) != NULL) {
			this->Persona.oid = row[0];
			this->Persona.ced = row[1];
			this->Persona.pnmb = row[2];
			this->Persona.snmb = row[3];
			this->Persona.pape = row[4];
			this->Persona.sape = row[5];
			this->Persona.Banco.cuenta = row[6];
		}
		mysql_free_result(result);
	}


};
