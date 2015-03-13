/*
 * mbanco.h
 *
 *  Creado Por: Carlos Enrique Peña Albarran
 *  Fecha: 24/03/2013
 */

class MBanco {

public:

	/**
	 *Identificador del Banco
	 */
	int oid;

	/**
	 * Nombre del Banco
	 */
	string nmbr;

	/**
	 * Estatus
	 */
	char tipo;

	/**
	 * Lista de Contratos
	 */
	vector<MContrato> Contrato;

	/**
	 * Lista de Personas
	 */
	vector<MPersona> Persona;

	/**
	 * Lista de Mensajes Cantidad, Suma y Posibles Errores
	 */

	vector<string> Mensaje;

	/**
	 * Base Datos Antigua (electron) t_cliente_creditos
	 *
	 * @param Banco
	 * @param Empresa
	 * @param Mes de Seleccion
	 * @param Periocidad
	 * @param Forma Contrato
	 * @param Nomina
	 * @param Nombre del Archivo
	 *
	 * @return string
	 */
	double MuchosContratosViejos(string _B, string _E, string _M, string _P,
			string _F, string _Fecha, string _N, string md5Archivo, int iPicar,
			string afiliacion, double dTope) {

		MYSQL_RES *result;
		MYSQL_ROW row;
		int estado;
		double iMesI = 0, iMesF = 0, iMesMax = 0; //Evaluar Por Periocidad

		double dSuma = 0, iMesVal = 0;
		double dAbono = 0, dPPagar = 0, dTotal = 0, dCuota = 0, dResta = 0; //Suma, Abono,Pendiente Por Pagar, Total, Cuota, Resta
		string Archivo = "";
		stringstream ssDia;
		string sDia;

		vector < string > sFecha;
		sFecha = this->Utilidad.Explode("-", _M);
		string sMes = sFecha[0] + "-" + sFecha[1];

		iMesI = atof(sFecha[1].c_str());
		double iMes = iMesI + 1;

		ssDia << iMes;
		sDia = ssDia.str();

		string sBanco; //Nombre de la entindad Bancaria
		string sCuentaBancaria; //Cuenta Bancaria

		//Cambiar a la variable del Mes por solicitud
		//iMesF = atoi(_Fecha.substr(6, 2).c_str());
		iMesF = atof(sFecha[2].c_str());

		switch (atoi(_P.c_str())) {
		case 0:
			iMesMax = 31;
			break;
		case 1:
			iMesMax = 14;
			break;
		case 2: // 15 - 30
			iMesMax = 30;
			break;
		case 3: // 10 - 25
			iMesMax = 25;
			break;
		case 4:
			iMesMax = 31;
			break;
		default:
			iMesMax = 31;
			break;
		}

		vector < string > sMonto;
		Archivo = md5Archivo + ".txt";

		string sEmpresa = " empresa = " + _E;
		//string sEmpresa = " empresa < 2 ";
		if (_E == "2") {
			sEmpresa = " empresa < 2 ";
		}
		string sNominaP = "nomina_procedencia";
		string sDistinct = " nomina_procedencia = '" + _N + "' ";
		if (_N == "VARIAS") {
			//sDistinct = " nomina_procedencia != '-------------' ";
			sDistinct = " nomina_procedencia != 'MINISTERIO DEL PODER POPULAR PARA LA EDUCACION' AND nomina_procedencia != 'MINISTERIO DEL PODER POPULAR PARA LA EDUCACION - JUBILADO' ";
			sNominaP = "'VARIAS'";
		}

		string sDelete = "DELETE FROM t_control_pagos WHERE " + sEmpresa
				+ " AND cobrado_en='" + _B + "' AND periocidad=" + _P
				+ " AND forma_contrato=" + _F + " AND " + sDistinct + ";";
		estado = mysql_query(this->MConexion, sDelete.c_str());
		//cout << sDelete << endl << endl;
		if (estado != 0) {
			printf(mysql_error(this->MConexion));
		}

		string sSet =
				"t_personas.documento_id, B.contrato_id, B.fecha_inicio_cobro, banco_1, cuenta_1, banco_2,cuenta_2, B.numero_cuotas,B.monto_cuota,B.monto,B.resta,B.cobrado_en,B.empresa,B.periocidad,B.forma_contrato,B.nomina_procedencia ";

		string sQuery =
				"INSERT INTO `t_control_pagos`(`documento_id`, `contrato_id`, `fecha_inicio_cobro`, `banco_1`, `cuenta_1`, `banco_2`, `cuenta_2`, `numero_cuotas`, `monto_cuota`, `monto`, ";

		/* forma contrato | 0 Unico | 1 Aguinaldo | 2 Vacaciones | 3 Extra | 4 Unico Extra | 5 Especial Extra */
		/* Periodicidad  | 4 Mensual | 3 Quincenal 10-25 | 2 Quincenal 15-30 */

		sQuery =
				sQuery
						+ "`resta`, `cobrado_en`, `empresa`, `periocidad`,forma_contrato, nomina_procedencia, nombre_completo, credito_id) "
						+ "SELECT " + sSet
						+ ", CONCAT(primer_apellido,' ', segundo_apellido,' ',primer_nombre,' ', segundo_nombre) AS nombre_completo, B.ID   FROM t_personas JOIN (SELECT * FROM (SELECT t_clientes_creditos.documento_id, contrato_id,"
						+ "t_clientes_creditos.fecha_inicio_cobro, t_clientes_creditos.numero_cuotas, t_clientes_creditos.monto_cuota,t_clientes_creditos.monto_total, "
						+ "IFNULL(sum( t_lista_cobros.monto ),0) AS monto, ( t_clientes_creditos.monto_total - IFNULL(sum( t_lista_cobros.monto ),0) ) AS resta,"
						+ "t_clientes_creditos.cobrado_en, t_clientes_creditos.empresa, periocidad, forma_contrato, nomina_procedencia, t_clientes_creditos.credito_id AS ID "
						+ "FROM t_clientes_creditos "
						+ "LEFT JOIN t_lista_cobros ON t_clientes_creditos.contrato_id = t_lista_cobros.credito_id "
						+ "WHERE t_clientes_creditos.cobrado_en = '" + _B
						+ "' AND " + sEmpresa + "  AND periocidad=" + _P
						+ " AND forma_contrato=" + _F + " AND " + sDistinct
						+ " AND marca_consulta != 6 AND cantidad != 0 "
						+ "GROUP BY t_clientes_creditos.contrato_id ) AS A WHERE A.monto != A.monto_total "
						+ "AND A.monto < A.monto_total AND A.fecha_inicio_cobro < '"
						+ sFecha[0] + "-" + sDia + "-01' "
						+ "ORDER BY A.fecha_inicio_cobro) AS B ON t_personas.documento_id=B.documento_id;";

		//cout << sQuery << endl << endl;

		estado = mysql_query(this->MConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(this->MConexion));
		}

		sQuery = "";

		if (afiliacion == "A") {
			sQuery =
					"SELECT t_control_pagos.documento_id, contrato_id, fecha_inicio_cobro,banco_1, cuenta_1,  "
							+ sQuery
							+ "numero_cuotas, monto_cuota, t_control_pagos.monto,resta, cobrado_en, empresa, forma_contrato, "
							+ "periocidad, IFNULL(A.Abono,0), A.fecha, nombre_completo, t_control_pagos.credito_id, t_afiliar_txt.detalle "
							+ "FROM t_control_pagos LEFT JOIN (SELECT credito_id, "
							+ "fecha, sum( monto ) AS Abono, banco_2,cuenta_2 FROM t_lista_cobros WHERE t_lista_cobros.fecha BETWEEN '"
							+ sMes + "-01' " + "AND '" + sMes
							+ "-31' GROUP BY t_lista_cobros.credito_id ) AS A ON t_control_pagos.contrato_id = A.credito_id  "
							+ "LEFT JOIN t_estadoejecucion ON t_control_pagos.contrato_id=t_estadoejecucion.oidc "
							+ "LEFT JOIN t_afiliar_txt ON t_afiliar_txt.cuenta=t_control_pagos.cuenta_1 "
							+ "WHERE ISNULL(t_afiliar_txt.detalle)  AND (t_estadoejecucion.oide > 3 OR ISNULL(t_estadoejecucion.oide) ) AND  cobrado_en='"
							+ _B + "' AND " + sEmpresa + " AND periocidad=" + _P
							+ " AND forma_contrato=" + _F + " AND " + sDistinct
							+ ";";
		} else {
			sQuery =
					"SELECT t_control_pagos.documento_id, contrato_id, fecha_inicio_cobro,banco_1, cuenta_1, "
							+ sQuery
							+ "numero_cuotas, monto_cuota, t_control_pagos.monto,resta, cobrado_en, empresa, forma_contrato, "
							+ "periocidad, IFNULL(A.Abono,0), A.fecha, nombre_completo, t_control_pagos.credito_id, banco_2,cuenta_2 FROM t_control_pagos LEFT JOIN (SELECT credito_id, "
							+ "fecha, sum( monto ) AS Abono FROM t_lista_cobros WHERE t_lista_cobros.fecha BETWEEN '"
							+ sMes + "-01' " + "AND '" + sMes
							+ "-31' GROUP BY t_lista_cobros.credito_id ) AS A ON t_control_pagos.contrato_id = A.credito_id  "
							+ "LEFT JOIN t_estadoejecucion ON t_control_pagos.contrato_id=t_estadoejecucion.oidc "
							+ "WHERE (t_estadoejecucion.oide > 3 OR ISNULL(t_estadoejecucion.oide) ) AND  cobrado_en='"
							+ _B + "' AND " + sEmpresa + " AND periocidad=" + _P
							+ " AND forma_contrato=" + _F + " AND " + sDistinct
							+ ";";

		}

		//cout << sQuery << endl << endl;
		estado = mysql_query(this->MConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(this->MConexion));
		}
		result = mysql_store_result(this->MConexion);
		while ((row = mysql_fetch_row(result)) != NULL) {
			stringstream sTotal;
			dResta = atof(row[8]); //Resta por pagar
			dAbono = atof(row[13]); //Abono
			dPPagar = atof(row[6]); //Monto de la cuota
			//Evaluar Contratos 10, 15, 25, 30, 1, 0
			iMesVal = 2;
			if (iMesI == 0 || iMesI == 1) {
				iMesVal = 1;
			} else {
				if (iMesF < iMesMax) {
					iMesVal = 1;
				}
			}
			//Si la cuota es menor que lo que resta
			if (dPPagar > atof(row[8])) {
				dPPagar = atof(row[8]) / iMesVal;
				dAbono = 0;
			}
			double sSumaTotalPru = 0; //Comparador para eliminar cobros excedidos en 10-25 y 15 y30
			sSumaTotalPru = dPPagar * iMesVal; // Verificar si la cuota es el final del pago

			dTotal = (dPPagar * iMesVal) - dAbono;
			if (atoi(_F.c_str()) > 0 && atoi(_F.c_str()) != 4) {
				dTotal = (atof(row[8]) * iMesVal);
			}
			// En los casos que el resto por pagar exceda a la cobranza
			if (sSumaTotalPru < dAbono) {
				dTotal = (dPPagar * 1) - dAbono;
			}

			if (sSumaTotalPru > dResta) {
				dTotal = dResta;
			}
			sBanco = row[3];
			sCuentaBancaria = row[4];
			if(_B != row[3]){
				sBanco = row[17];
				sCuentaBancaria = row[18];
				//cout << row[17] << " :: " << row[18] << endl;
			}

			sTotal << dTotal;
			//dCuota = dTotal / iPicar;
			dCuota = dTotal;
			//sCuota << dCuota;
			if (dTotal > 0) {
				//dCuota = dTotal - 500;
				while (dCuota > dTope) {
					stringstream sCuota;
					dCuota = dCuota - dTope;
					sCuota << dTope;
					MContrato lst = MContrato();
					lst.oid = row[0];
					lst.ncon = row[1];
					lst.icob = row[2]; //Inicio de Cobro
					lst.oidl = sBanco; //row[3]; //Banco 1
					lst.oidn = sCuentaBancaria; //row[4]; //Cuenta Bancaria
					lst.ncuo = row[5];
					lst.pagado = row[13]; //Abono
					lst.mcuo = sCuota.str(); //sTotal.str();
					lst.monto = row[7];
					lst.resta = row[8];
					lst.emp = row[9];
					lst.oidf = row[10]; //Cobrado En
					lst.perio = row[12];
					lst.nombre_completo = row[15];
					lst.credito_id = row[16];
					//cout << lst.ncon << " :::>>> " << dTope << endl;
					this->Contrato.push_back(lst);
				}

				if (dCuota != 0) {
					//cout <<  "XXXXX :::>>> " << dCuota << endl;
					stringstream sCuota;
					sCuota << dCuota;
					MContrato lst = MContrato();
					lst.oid = row[0];
					lst.ncon = row[1];
					lst.icob = row[2]; //Inicio de Cobro
					lst.oidl = sBanco; //row[3]; //Banco 1
					lst.oidn = sCuentaBancaria; //row[4]; //Cuenta Bancaria
					lst.ncuo = row[5];
					lst.pagado = row[13]; //Abono
					lst.mcuo = sCuota.str(); //sTotal.str();
					lst.monto = row[7];
					lst.resta = row[8];
					lst.emp = row[9];
					lst.oidf = row[10]; //Cobrado En
					lst.perio = row[12];
					lst.nombre_completo = row[15];
					lst.credito_id = row[16];
					this->Contrato.push_back(lst);
				}
				/**
				 for (int i = 0; i < iPicar; i++) {
				 MContrato lst = MContrato();
				 lst.oid = row[0];
				 lst.ncon = row[1];
				 lst.icob = row[2]; //Inicio de Cobro
				 lst.oidl = row[3]; //Banco 1
				 lst.oidn = row[4]; //Cuenta Bancaria
				 lst.ncuo = row[5];
				 lst.pagado = row[13]; //Abono
				 lst.mcuo = sCuota.str(); //sTotal.str();
				 lst.monto = row[7];
				 lst.resta = row[8];
				 lst.emp = row[9];
				 lst.oidf = row[10]; //Cobrado En
				 lst.perio = row[12];
				 lst.nombre_completo = row[15];
				 lst.credito_id = row[16];
				 this->Contrato.push_back(lst);
				 }
				 **/

				dSuma += dTotal;
			}
		}
		mysql_free_result(result);
		return dSuma;
	}

	/*
	 * Generar TXT verificar Contratos
	 */
	void MuchosContratos(string oid) {
		MYSQL_RES *result;
		MYSQL_ROW row;
		int estado;

		string sSet =
				"ncon,soli,icob,oidf,oidl,oidn,t_contrato.mont,mcuo,ncuo,t_abono.mont AS pago,(t_contrato.mont-t_abono.mont) AS rest";
		string sQuery =
				"SELECT " + sSet
						+ " FROM t_banco JOIN t_contrato ON t_contrato.oidl = t_banco.oid"
						+ " LEFT JOIN t_abono ON t_abono.oid = t_contrato.ncon"
						+ " WHERE t_banco.oid = " + oid
						+ " AND t_contrato.mont != t_abono.mont AND icob<'2013-04-01' "
						+ "AND form=0" + " AND tipo!=6";
		//Forma 0: Unico
		//Tipo 6: Distinto que Voucher
		estado = mysql_query(MConexion, sQuery.c_str());
		if (estado != 0) {
			printf(mysql_error(MConexion));
		}
		result = mysql_store_result(MConexion);
		while ((row = mysql_fetch_row(result)) != NULL) {
			MContrato lst = MContrato();
			lst.ncon = row[0];
			lst.soli = row[1];
			lst.icob = row[2];
			lst.oidf = row[3];
			lst.oidl = row[4];
			lst.oidn = row[5];
			lst.monto = row[6];
			lst.mcuo = row[7];
			lst.ncuo = row[8];
			lst.pagado = row[9];
			lst.resta = row[10];
			this->Contrato.push_back(lst);
		}
		mysql_free_result(result);

	}

	/**
	 * Muchas Cuentas Bancarias
	 * @param MYSQL Conexion
	 * @param Identificador del Banco
	 *
	 */
	void Generar_Cuentas(MYSQL *mConexion, string _B, string _E, string _M,
			string _P, string _F, string _Fecha, string _N, string md5Archivo,
			string afiliacion, double dDiv) {
		double dSuma = 0;
		int iPicar = 1;
		double dTope = 100;

		string Archivo = md5Archivo + ".txt";

		if (dDiv > 0) {
			dTope = dDiv;
		}
		//cout<< afiliacion << "\n";
		this->MConexion = mConexion;
		this->Mensaje.push_back("CREANDO ARCHIVO...");

		if (afiliacion == "A") {
			iPicar = 1;
		}

		if (_B == "BICENTENARIO") {
			_E = "2";
			//dTope = 100;
			dSuma = this->MuchosContratosViejos(_B, _E, _M, _P, _F, _Fecha, _N,
					md5Archivo, iPicar, afiliacion, dTope);
			if (afiliacion == "A") {
				this->_Esq_Bicentenario_Afiliacion(dSuma,
						"tmp/afiliacion/" + Archivo, _E, _Fecha);

			} else if (afiliacion == "C") {
				this->_Esq_Bicentenario_Cobranza(dSuma,
						"tmp/cobranza/" + Archivo, _E, _Fecha, _M);
			} else {
				this->_Esq_Bicentenario_Viejos(dSuma, "tmp/" + Archivo, _E,
						_Fecha);
			}

		};
		if (_B == "FONDO COMUN") {
			//dTope = 100;
			dSuma = this->MuchosContratosViejos(_B, _E, _M, _P, _F, _Fecha, _N,
					md5Archivo, iPicar, afiliacion, dTope);
			this->_Esq_Bfc(dSuma, "tmp/" + Archivo, _E, _Fecha);
		};

		if (_B == "CARONI") {
			//dTope = 100;
			dSuma = this->MuchosContratosViejos(_B, _E, _M, _P, _F, _Fecha, _N,
					md5Archivo, iPicar, afiliacion, dTope);
			this->_Esq_Caroni(dSuma, "tmp/cobranza/" + Archivo, _E, _Fecha);
		};

		if (_B == "DEL SUR") {
			//dTope = 100;
			dSuma = this->MuchosContratosViejos(_B, _E, _M, _P, _F, _Fecha, _N,
					md5Archivo, iPicar, afiliacion, dTope);
			//this->_Esq_Sur(dSuma, "tmp/" + Archivo, _E, _Fecha);
		};

		if (_B == "PROVINCIAL") {
			//dTope = 500;
			dSuma = this->MuchosContratosViejos(_B, _E, _M, _P, _F, _Fecha, _N,
					md5Archivo, iPicar, afiliacion, dTope);
			this->_Esq_Provincial(dSuma, "tmp/cobranza/" + Archivo, _E, _Fecha);
		};
	}

private:
	string _BFC;

	string _PROVINCIAL;

	string _BICENTENARIO;

	string _VENEZUELA;

	string _BANESCO;

	string _MERCANTIL;

	string _DELSUR;

	string _CARONI;

	string _BOD;

	string _INDUSTRIAL;

	MYSQL *MConexion;

	LUtilidades Utilidad;

	vector<string> Monto;

	/**
	 * Base de datos Antigua electron
	 * Generar Linea Esquema para banco Bicentenario
	 *
	 * @param Sumatoria Total
	 * @param Nombre del Archivo
	 * @param Empresa
	 * @param Nombre del Archivo En Formato MD5
	 *
	 */
	void _Esq_Bicentenario_Viejos(double dSum, string sNTxt, string _E,
			string _Fecha) {

		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo

		int iMax = this->Contrato.size();
		//int iMin = iMax - 1;
		vector < string > vMon;
		string sCuenta, sClave;
		stringstream sSuma;
		stringstream sMax;

		sCuenta = "01750541650071150460";
		sClave = "3275";
		if (_E == "0") { //Si es Cooperativa
			sCuenta = "01750011250000034702";
			sClave = "0661";
		}
		string sLinea, sCed, sNom, sMon, sMonT, sCue, sDec;
		sSuma.precision(2);
		sSuma << fixed;
		sSuma << dSum;
		sMax << iMax;
		sLinea = "EJHMADEDRGKB";

		this->Mensaje.push_back(sMax.str());
		this->Mensaje.push_back(sSuma.str());

		Archivo.Escribir((char *) sLinea.c_str());

		vMon = Utilidad.Explode(".", sSuma.str());
		if (vMon.size() > 1) {
			if (vMon[1].length() == 1) {
				sDec = vMon[1] + "0";
			} else {
				sDec = vMon[1];
			}
		} else {
			sDec = "00";
		}
		sMon = Utilidad.Completar(vMon[0], 15, 1);

		sLinea = sCuenta + _Fecha + Utilidad.Completar(sMon, 15, 1) + sDec
				+ Utilidad.Completar(sMax.str(), 4, 1);

		Archivo.EscribirSaltoLinea((char *) sLinea.c_str());
		sDec = "";
		sMon = "";
		for (int i = 0; i < iMax; i++) {
			sCed = Utilidad.Completar(this->Contrato[i].oid, 10, 1);
			vMon = Utilidad.Explode(".", this->Contrato[i].mcuo);
			if (vMon.size() > 1) {

				if (vMon[1].length() == 1) {
					sDec = vMon[1] + "0";
				} else {
					sDec = vMon[1];
				}
			} else {
				sDec = "00";
			}
			sMon = Utilidad.Completar(vMon[0], 10, 1);
			sLinea = sClave + sMon + sDec + Contrato[i].oidn + sCed
					+ "00000100";
			Archivo.EscribirSaltoLinea((char *) sLinea.c_str());

		}
		Archivo.Salvar();
	}

	/**
	 * Base de datos Antigua electron
	 * Generar Linea Esquema para banco Bicentenario
	 *
	 * @param Sumatoria Total
	 * @param Nombre del Archivo
	 * @param Empresa
	 * @param Nombre del Archivo En Formato MD5
	 *
	 */
	void _Esq_Bicentenario_Afiliacion(double dSum, string sNTxt, string _E,
			string _Fecha) {
		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo
		string sFecha, sCed, sNombre, sCuenta, sCredito; 	  //20130902
		string sCantidad; //0000000002
		stringstream sMax;
		string sRif;
		int iMax = this->Contrato.size();
		sMax << iMax;
		sRif = "2983784680";
		string sRegistro = Utilidad.Completar(sMax.str(), 10, 1);
		string sCabezera =
				"1BICENTENARIO000000000000001J" + sRif + "DOMIC" + _Fecha
						+ sRegistro
						+ " 0000000000000                                                                                                                                                                                    ";
		Archivo.Escribir((char *) sCabezera.c_str());
		string sLinea;
		this->Mensaje.push_back(sRegistro);
		this->Mensaje.push_back(":D");
		for (int i = 0; i < iMax; i++) {
			stringstream sID;
			sCredito = Utilidad.Completar(this->Contrato[i].credito_id, 16, 1);
			sCed = Utilidad.Completar(this->Contrato[i].oid, 10, 1); // 10 Caracteres
			sNombre = Utilidad.CompletarEspacios(
					this->Contrato[i].nombre_completo, 30, 0); // 30 Caracteres
			//cout << sNombre << "\n";
			sCuenta = this->Contrato[i].oidn; //0175-04-5681-0061208997: 20 Caracteres
			//2AV0007066998YSMIR JOSEFINA DOMINGUEZ DE FR0017504568100612089970007066998036512         0007066998036512 200000000000000000000000000000000000000
			sLinea =
					"2AV" + sCed + sNombre + "0" + sCuenta + sCredito
							+ "         " + sCredito
							+ " 200000000000000000000000000000000000000                                                                                                               ";
			Archivo.EscribirSaltoLinea((char *) sLinea.c_str());

		}
		Archivo.Salvar();
	}

	/**
	 * Base de datos Antigua electron
	 * Generar Linea Esquema para banco Bicentenario
	 *
	 * @param Sumatoria Total
	 * @param Nombre del Archivo
	 * @param Empresa
	 * @param Nombre del Archivo En Formato MD5
	 *
	 */
	void _Esq_Bicentenario_Cobranza(double dSum, string sNTxt, string _E,
			string _Fecha, string _M) {
		vector < string > vMon;
		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo
		string sCed, sNombre, sCuenta, sCredito, sInequivoca, sIrrCliente; //20130902
		string sMon, sDec, sCantidad; //0000000002
		string sIrrepetible;
		string sContrato;
		string sRif;
		stringstream sMax;
		stringstream sSuma; //00000000000133400 17 Digitos

		string sContar;
		string sFin;
		vector < string > sFecha;

		int j = 0;
		sFecha = this->Utilidad.Explode("-", _M);
		sFin = "30";
		if (sFecha[2] == "02") {
			sFin = "28";
		}
		string sMes = sFecha[0] + sFecha[1] + sFin;

		sSuma.precision(2);
		sSuma << fixed;
		sSuma << dSum;
		vMon = Utilidad.Explode(".", sSuma.str());
		if (vMon.size() > 1) {
			if (vMon[1].length() == 1) {
				sDec = vMon[1] + "0";
			} else {
				sDec = vMon[1];
			}
		} else {
			sDec = "00";
		}
		sMon = Utilidad.Completar(vMon[0], 15, 1);

		sIrrepetible = "000000000000001"; // 15 Digitos Numericos
		sRif = "2983784680";
		int iMax = this->Contrato.size();
		sMax << iMax;
		string sRegistro = Utilidad.Completar(sMax.str(), 8, 1);
		//cout << sRegistro + "\r\n";
		string sCuentaBancaria = "01750541650071150460"; //Grupo Electron
		string sCabezera =
				"1BICENTENARIOC1" + sIrrepetible + "000000DOMICJ" + sRif
						+ sRegistro + sMon + sDec + _Fecha + sCuentaBancaria
						+ "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000                                                ";
		Archivo.Escribir((char *) sCabezera.c_str());
		string sLinea;
		this->Mensaje.push_back(sMax.str());
		this->Mensaje.push_back(sSuma.str());

		string sEContrato = this->Contrato[0].credito_id;

		for (int i = 0; i < iMax; i++) {
			stringstream sID;
			stringstream ssCon;

			if (this->Contrato[i].credito_id != sEContrato) { //sEContrato Evaluar Contrato
				sEContrato = this->Contrato[i].credito_id;
				j = 1;
			}
			j++;

			ssCon << j;

			sContar = Utilidad.Completar(ssCon.str(), 2, 1);

			sContrato = Utilidad.Completar(this->Contrato[i].credito_id, 16, 1);

			sCredito = Utilidad.Completar(this->Contrato[i].credito_id, 13, 1)
					+ sContar; //0007066998036512 16 Caracteres

			sInequivoca = Utilidad.Completar(this->Contrato[i].credito_id, 15,
					1); //0007066998036512 16 Caracteres
			sIrrCliente = Utilidad.Completar(this->Contrato[i].credito_id, 6, 1)
					+ sContar; //0007066998036512 16 Caracteres
			sCed = Utilidad.Completar(this->Contrato[i].oid, 10, 1); // 10 Caracteres

			sCuenta = this->Contrato[i].oidn; //0175-04-5681-0061208997: 20 Caracteres
			vMon = Utilidad.Explode(".", this->Contrato[i].mcuo);
			if (vMon.size() > 1) {

				if (vMon[1].length() == 1) {
					sDec = vMon[1] + "0";
				} else {
					sDec = vMon[1];
				}
			} else {
				sDec = "00";
			}
			sMon = Utilidad.Completar(vMon[0], 15, 1);

			//2V0007066998001750456810061208997          0007066998036512         00000000000066700                              0007066998036512 0000000000000010000000000000                              0000000000000012013090220130930ELCTRON 465
			sLinea = "2V" + sCed + "0" + sCuenta + "          " + sContrato
					+ "         " + sMon + sDec
					+ "                              " + sContrato + " "
					+ sCredito
					+ "0000000000000                              0000000"
					+ sIrrCliente + _Fecha + sMes
					+ "ELCTRON 465                        ";
			Archivo.EscribirSaltoLinea((char *) sLinea.c_str());

		}
		Archivo.Salvar();
	}

	/*
	 * Generar Archivo Banco Fondo Comun
	 * @param Suma total de Contratos Double
	 * @param Nombre del Archivo String
	 * @param Empresa
	 * @param Fecha en formato texto
	 */
	void _Esq_Bfc(double dSum, string sNTxt, string _E, string _Fecha) {
		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo
		int iMax = this->Contrato.size();
		int iMin = iMax - 1;
		double dSuma = 0;
		stringstream sSuma;
		stringstream sMax;
		vector < string > vMon; //Monto de la cuota
		vector < string > vTot; //Total
		string sLinea, sCed, sNom, sMon, sMonT, sCue, sCan, sDec;
		sSuma.precision(2);
		sSuma << fixed;
		sSuma << dSum;
		sMax << iMax;

		this->Mensaje.push_back(sMax.str());
		this->Mensaje.push_back(sSuma.str());

		string hrs = "080100"; //Hora Minutos Segundo
		string fch = _Fecha; //Año Mes Dia
		string sCab =
				"000000" + fch + hrs + fch + hrs
						+ "00000000000000000000000001 CC0001510138528138022782 CC0001510138528138022782000000000000000000000000000000000000000000000000000000000000";
		Archivo.Escribir((char *) sCab.c_str()); //Creando la Cabezera
		int j = 0;
		for (int i = 0; i < iMax; i++) {
			MPersona Persona = MPersona();
			Persona.getPersona(this->MConexion, this->Contrato[i].oid);
			stringstream sC;
			j++;
			sC << j;
			sCan = Utilidad.Completar(sC.str(), 6, 1);
			sCed = Utilidad.Completar(this->Contrato[i].oid, 10, 1);
			sNom = Persona.pnmb + " " + Persona.snmb + " " + Persona.pape + " "
					+ Persona.sape;
			vMon = Utilidad.Explode(".", this->Contrato[i].mcuo);
			if (vMon.size() > 1) {
				if (vMon[1].length() == 1) {
					sDec = vMon[1] + "0";
				} else {
					sDec = vMon[1];
				}
			} else {
				sDec = "00";
			}
			sMon = Utilidad.Completar(vMon[0], 13, 1);
			sLinea =
					sCan + " LS" + this->Contrato[i].oidn + "V" + sCed
							+ "00001000000000000000" + sMon + sDec
							+ "D0ABONO A EMPRESA ELECTRON                0000                                        000000000 ";
			Archivo.EscribirSaltoLinea((char *) sLinea.c_str());
		}
		stringstream sC, sM;
		sC << iMax;
		sCan = Utilidad.Completar(sC.str(), 6, 1);
		sM << dSum;
		vTot = Utilidad.Explode(".", sM.str());
		if (vTot.size() > 1) {
			if (vTot[1].length() == 1) {
				sDec = vTot[1] + "0";
			} else {
				sDec = vTot[1];
			}
		} else {
			sDec = "00";
		}

		sMon = Utilidad.Completar(vTot[0], 13, 1);

		string sPie =
				"999999GRUPO ELECTRON CA                       " + sCan + sMon
						+ sDec + "000000000000000" + sCan
						+ "0000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		Archivo.EscribirSaltoLinea((char *) sPie.c_str());
		Archivo.Salvar();
	}

	/**
	 * Generar Linea Esquema para banco Provincia
	 *
	 * @param Suma total de Contratos Double
	 * @param Nombre del Archivo String
	 * @param Empresa
	 * @param Fecha en formato texto
	 */
	void _Esq_Provincial(double dSum, string sNTxt, string _E, string _Fecha) {
		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo
		int iMax = this->Contrato.size();
		int iMin = iMax - 1;
		double dSuma = 0;
		vector < string > vMon;
		string sLinea, sCed, sNom, sMon, sMonT, sCue, sDec;
		stringstream sSuma;
		stringstream sMax;
		sSuma << dSum;
		sMax << iMax;

		this->Mensaje.push_back(sMax.str());
		this->Mensaje.push_back(sSuma.str());

		for (int i = 0; i < iMax; i++) {
			MPersona Persona = MPersona();
			Persona.getPersona(this->MConexion, this->Contrato[i].oid);
			sCue = Utilidad.Completar(this->Contrato[i].oidn, 20, 1);
			sCed = Utilidad.Completar(this->Contrato[i].oid, 10, 1);
			vMon = Utilidad.Explode(".", this->Contrato[i].mcuo);
			if (vMon.size() > 1) {
				if (vMon[1].length() == 1) {
					sDec = vMon[1] + "0";
				} else {
					sDec = vMon[1];
				}
			} else {
				sDec = "00";
			}
			sMon = Utilidad.Completar(vMon[0], 13, 1);
			sNom = Persona.pnmb + " " + Persona.snmb + " " + Persona.pape + " "
					+ Persona.sape;
			sLinea = this->Contrato[i].oidn + " " + "V" + sCed + " " + sMon
					+ sDec + " " + sNom;
			if (i > 0) {
				Archivo.EscribirSaltoLinea((char *) sLinea.c_str());
			} else {
				Archivo.Escribir((char *) sLinea.c_str());
			}

		}
		Archivo.Salvar();
	}

	/**
	 * Base de datos Antigua electron
	 * Generar Linea Esquema para Banco Mercantil
	 *
	 * @param Sumatoria Total
	 * @param Nombre del Archivo
	 * @param Empresa
	 * @param Nombre del Archivo En Formato MD5
	 *
	 */
	void _Esq_Mercantil_Cobranza(double dSum, string sNTxt, string _E,
			string _Fecha, string _M) {
		vector < string > vMon;
		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo
		string sCed, sNombre, sCuenta, sCredito, sInequivoca, sIrrCliente; //20130902
		string sMon, sDec, sCantidad; //0000000002
		string sIrrepetible;
		string sContrato;
		string sRif;
		stringstream sMax;
		stringstream sSuma; //00000000000133400 17 Digitos

		string sContar;
		string sFin;
		vector < string > sFecha;

		int j = 0;
		sFecha = this->Utilidad.Explode("-", _M);
		sFin = "30";
		if (sFecha[2] == "02") {
			sFin = "28";
		}
		string sMes = sFecha[0] + sFecha[1] + sFin;

		sSuma.precision(2);
		sSuma << fixed;
		sSuma << dSum;
		vMon = Utilidad.Explode(".", sSuma.str());
		if (vMon.size() > 1) {
			if (vMon[1].length() == 1) {
				sDec = vMon[1] + "0";
			} else {
				sDec = vMon[1];
			}
		} else {
			sDec = "00";
		}
		sMon = Utilidad.Completar(vMon[0], 15, 1);

		sIrrepetible = "000000000000001"; // 15 Digitos Numericos
		sRif = "2983784680";
		int iMax = this->Contrato.size();
		sMax << iMax;
		string sRegistro = Utilidad.Completar(sMax.str(), 8, 1);
		//cout << sRegistro + "\r\n";
		string sCuentaBancaria = "01750541650071150460"; //Grupo Electron
		string sCabezera =
				"1BICENTENARIOC1" + sIrrepetible + "000000DOMICJ" + sRif
						+ sRegistro + sMon + sDec + _Fecha + sCuentaBancaria
						+ "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000                                                ";
		Archivo.Escribir((char *) sCabezera.c_str());
		string sLinea;
		this->Mensaje.push_back(sMax.str());
		this->Mensaje.push_back(sSuma.str());
		for (int i = 0; i < iMax; i++) {
			stringstream sID;
			stringstream ssCon;

			j++;
			if (j == 11) {
				j = 1;
			}
			ssCon << j;

			sContar = Utilidad.Completar(ssCon.str(), 2, 1);

			sContrato = Utilidad.Completar(this->Contrato[i].credito_id, 16, 1);

			sCredito = Utilidad.Completar(this->Contrato[i].credito_id, 13, 1)
					+ sContar; //0007066998036512 16 Caracteres

			sInequivoca = Utilidad.Completar(this->Contrato[i].credito_id, 15,
					1); //0007066998036512 16 Caracteres
			sIrrCliente = Utilidad.Completar(this->Contrato[i].credito_id, 6, 1)
					+ sContar; //0007066998036512 16 Caracteres
			sCed = Utilidad.Completar(this->Contrato[i].oid, 10, 1); // 10 Caracteres

			sCuenta = this->Contrato[i].oidn; //0175-04-5681-0061208997: 20 Caracteres
			vMon = Utilidad.Explode(".", this->Contrato[i].mcuo);
			if (vMon.size() > 1) {

				if (vMon[1].length() == 1) {
					sDec = vMon[1] + "0";
				} else {
					sDec = vMon[1];
				}
			} else {
				sDec = "00";
			}
			sMon = Utilidad.Completar(vMon[0], 15, 1);

			//2V0007066998001750456810061208997          0007066998036512         00000000000066700                              0007066998036512 0000000000000010000000000000                              0000000000000012013090220130930ELCTRON 465
			sLinea = "2V" + sCed + "0" + sCuenta + "          " + sContrato
					+ "         " + sMon + sDec
					+ "                              " + sContrato + " "
					+ sCredito
					+ "0000000000000                              0000000"
					+ sIrrCliente + _Fecha + sMes
					+ "ELCTRON 465                        ";
			Archivo.EscribirSaltoLinea((char *) sLinea.c_str());

		}
		Archivo.Salvar();
	}

	/*
	 * Generar Archivo Banco Fondo Comun
	 * @param Suma total de Contratos Double
	 * @param Nombre del Archivo String
	 * @param Empresa
	 * @param Fecha en formato texto
	 */
	void _Esq_Caroni(double dSum, string sNTxt, string _E, string _Fecha) {
		LArchivo Archivo = LArchivo();
		Archivo.Abrir(sNTxt.c_str()); //Creando el archivo
		int iMax = this->Contrato.size();
		int iMin = iMax - 1;
		double dSuma = 0;
		stringstream sSuma;
		stringstream sMax;
		vector < string > vMon; //Monto de la cuota
		vector < string > vTot; //Total
		string sLinea, sCed, sNom, sMon, sNombreCompletado, sMonT, sCue, sCan,
				sDec;
		sSuma.precision(2);
		sSuma << fixed;
		sSuma << dSum;
		sMax << iMax;

		this->Mensaje.push_back(sMax.str());
		this->Mensaje.push_back(sSuma.str());

		string sRegistro = Utilidad.Completar(sMax.str(), 5, 1); //CANTIDAD DE REGISTROS

		vMon = Utilidad.Explode(".", sSuma.str());
		if (vMon.size() > 1) {
			if (vMon[1].length() == 1) {
				sDec = vMon[1] + "0";
			} else {
				sDec = vMon[1];
			}
		} else {
			sDec = "00";
		}
		sMon = Utilidad.Completar(vMon[0], 11, 1);

		string sCab =
				"01COOPERATIVA ELECTRON                    01280072047200668106"
						+ sRegistro + sMon + sDec + "                    ";
		Archivo.Escribir((char *) sCab.c_str()); //Creando la Cabezera
		int j = 0;
		for (int i = 0; i < iMax; i++) {
			MPersona Persona = MPersona();
			Persona.getPersona(this->MConexion, this->Contrato[i].oid);
			stringstream sC;
			j++;
			sC << j;
			sCan = "02"; //VALOR FIJO
			sCed = Utilidad.Completar(this->Contrato[i].oid, 8, 1); //CEDUKA DE 8 DIGIYOS
			//sNom =  Persona.pape + Persona.sape + Persona.pnmb + Persona.snmb; //APELLIDOS Y NOMBRES TODO PEGADO 40 DIGITOS
			sNom = Persona.pape + Persona.pnmb; //APELLIDOS Y NOMBRES TODO PEGADO 40 DIGITOS
			sNombreCompletado = Utilidad.CompletarEspacios(sNom, 40, 0);
			vMon = Utilidad.Explode(".", this->Contrato[i].mcuo);
			if (vMon.size() > 1) {
				if (vMon[1].length() == 1) {
					sDec = vMon[1] + "0";
				} else {
					sDec = vMon[1];
				}
			} else {
				sDec = "00";
			}
			sMon = Utilidad.Completar(vMon[0], 10, 1);
			sLinea = sCan + this->Contrato[i].oidn + sMon + sDec
					+ sNombreCompletado + sCed + "                    ";
			Archivo.EscribirSaltoLinea((char *) sLinea.c_str());
		}

		Archivo.Salvar();
	}

};

