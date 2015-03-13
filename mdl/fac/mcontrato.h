/*
 * mcontrato.h
 *
 *  Created on: 27/03/2013
 *      Author: crash
 */
#include "mpagado.h"

class MContrato : public MPagado {
public:
	/*
	 * Identificador
	 */
	string oid;

	/*
	 * Numero de Contrato
	 */
	string ncon;

	/*
	 * Fecha de Solicitud
	 */
	string soli;

	/*
	 * Inicio de Cobro Fecha
	 */
	string icob;

	/*
	 * Motivo
	 */
	string motv;

	/*
	 * Condicion
	 */
	string cond;

	/*
	 * Empresa
	 */
	string emp;

	/*
	 * Periocidad
	 */
	string perio;
	/*
	 * Numero de Cuotas
	 */
	string ncuo;

	/*
	 * Monto de la Cuota
	 */
	string mcuo;

	/*
	 * Cantidad
	 */
	string cant;

	/*
	 * Monto Por Pagar
	 */
	string monto;

	/**
	 * Pagado a la Fecha
	 */
	string pagado;

	/**
	 * Pendiente Por Pagar
	 */
	string resta;

	/*
	 * Tiene un Linaje   | Viejo Sistema : Banco
	 */
	string oidl;


	/*
	 * Tiene una Nomina | Viejo Sistema : Numero Cuenta
	 */
	string oidn;

	/*
	 * Tiene Una Factura | Viejo Sistema : Cobrado En
	 */
	string oidf;



	/*
	 * Tiene Una Factura | Viejo Sistema : Cobrado En
	 */
	string nombre_completo;

	string credito_id;

	/**
	 * Verificar Que Banco y Formato de Reglas
	 *
	 * @param MYSQL Conexion
	 * @param ibnc Identificador del Banco ref (banco_id)
	 *
	 * @return char Cadena de valores
	 */
	string Verificar_Banco(MYSQL *conexion, int ibnc) {
		string sAux;
		sAux = "PROVINCIAL";

		return sAux;
	}

	/**
	 * Verificar Que un Cliente no Tenga saldo pendiente
	 *
	 *
	 * @param MYSQL Conexion
	 * @param ced Documento de Identificacion
	 * @param cnt Contrato del Cliente
	 *
	 * @return (0 : Solvente, 1 : Pendiente)
	 */
	int Verificar_Solvente(MYSQL *conexion, char *ced, char *cnt) {

		return 1;
	}



};

