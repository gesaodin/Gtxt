/*
 * mbanco.h
 *
 *  Creado Por: Carlos Enrique Peña Albarran
 *  Fecha: 24/03/2013
 */


class MBanco {

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
	 * Lista de Contratos
	 */
	vector<MContrato> Contrato;

	/*
	 * Lista de Personas
	 */
	vector<MPersona> Persona;

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
		cout << "---------------------------------------<br>\n";
		cout << ">>> Por favor Espere Generando Consulta<br>\n";
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
		cout << "<<< Fin de La Consulta<br>\n";
		cout << "---------------------------------------<br>\n\n";

	}

	/**
	 * Muchas Cuentas Bancarias
	 * @param MYSQL Conexion
	 * @param Identificador del Banco
	 *
	 */
	void Generar_Cuentas(MYSQL *mConexion, int iOid) {
		stringstream sOid;
		sOid << iOid;
		this->MConexion = mConexion;
		this->MuchosContratos(sOid.str());
		switch (iOid) {
		case 5:
			this->_Esq_Bicentenario();
			break;
		case 13:
			this->_Esq_Bfc();
			break;
		case 18:
			this->_Esq_Provincial();
			break;
		default:
			break;
		}
	}

private:
	string _BFC;

	string _PROVINCIAL;

	string _BICENTENARIO;

	string _VENEZUELA;

	string _BANESCO;

	string _BOD;

	string _INDUSTRIAL;

	MYSQL *MConexion;

	LUtilidades Utilidad;

	vector<string> Monto;

	/**
	 *	Generar Linea Esquema para banco Bicentenario
	 *
	 */
	void _Esq_Bicentenario() {

		LArchivo Archivo = LArchivo();
		Archivo.Abrir("Bicentenario.txt"); //Creando el archivo
		int iMax = this->Contrato.size();
		int iMin = iMax - 1;
		double dSuma = 0;
		string sLinea, sCed, sNom, sMon, sMonT, sCue;
		cout << "**************************<br>\n";
		cout << "Creando Archivo Bicentenario<br>\n";

		for (int i = 0; i < iMax; i++) {
			MFactura Factura = MFactura();
			Factura.UnaPersona(MConexion, Contrato[i].oidf, Contrato[i].oidl);

			sCed = Utilidad.Completar(Factura.Persona.ced, 10, 1);
			Monto = Utilidad.Explode(".", Contrato[i].mcuo);
			dSuma += atof(Contrato[i].mcuo.c_str());
			sMonT = Monto[0] + Monto[1];
			sMon = Utilidad.Completar(sMonT, 10, 1);
			sNom = Factura.Persona.pnmb + " " + Factura.Persona.snmb + " "
					+ Factura.Persona.pape + " " + Factura.Persona.sape;

			sLinea = "327500" + sMon + Factura.Persona.Banco.cuenta + sCed
					+ "00000100";
			Archivo.Escribir((char *) sLinea.c_str());

		}
		Archivo.Salvar();
		cout << "Pendiente por Cobrar: " << dSuma << "<br>\n";
		cout << "Proceso Exitoso<br>\n";
		cout << "**************************<br>\n";
	}

	/*
	 * Generar Archivo Banco Fondo Comun
	 */
	void _Esq_Bfc() {
		LArchivo Archivo = LArchivo();
		Archivo.Abrir("BFC.txt"); //Creando el archivo
		int iMax = this->Contrato.size();
		int iMin = iMax - 1;
		double dSuma = 0;
		string sLinea, sCed, sNom, sMon, sMonT, sCue, sCan;
		cout << "***************************<br>\n";
		cout << "Creando Archivo Fondo Comun<br>\n";
		string hrs = "080100"; //Hora Minutos Segundo
		string fch = "20130401"; //Año Mes Dia
		string sCab =
				"000000" + fch + hrs + fch + hrs
						+ "00000000000000000000000001 CC0001510138528138022782 CC0001510138528138022782000000000000000000000000000000000000000000000000000000000000";
		Archivo.Escribir((char *) sCab.c_str()); //Creando la Cabezera

		for (int i = 0; i < iMax; i++) {
			MFactura Factura = MFactura();
			stringstream sC;
			Factura.UnaPersona(MConexion, Contrato[i].oidf, Contrato[i].oidl);
			sC << i;
			sCan = Utilidad.Completar(sC.str(), 6, 1);
			sCed = Utilidad.Completar(Factura.Persona.ced, 10, 1);
			Monto = Utilidad.Explode(".", Contrato[i].mcuo);
			sMonT = Monto[0] + Monto[1];
			sMon = Utilidad.Completar(sMonT, 15, 1);
			dSuma += atof(Contrato[i].mcuo.c_str());
			sNom = Factura.Persona.pnmb + " " + Factura.Persona.snmb + " "
					+ Factura.Persona.pape + " " + Factura.Persona.sape;

			sLinea =
					sCan + " LS" + Factura.Persona.Banco.cuenta + "V" + sCed
							+ "00001000000000000000" + sMon
							+ "D0ABONO A EMPRESA ELECTRON                0000                                        000000000 ";
			Archivo.Escribir((char *) sLinea.c_str());
		}
		stringstream sC, sM;
		sC << iMin;
		sCan = Utilidad.Completar(sC.str(), 6, 1);
		sM << dSuma;
		sMon = Utilidad.Completar(sM.str(), 15, 1);

		string sPie =
				"999999GRUPO ELECTRON CA                       " + sCan + sMon
						+ "000000000000000" + sCan
						+ "0000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		Archivo.Escribir((char *) sPie.c_str());
		Archivo.Salvar();
		cout << "Pendiente por Cobrar: " << dSuma << "<br>\n";
		cout << "Proceso Exitoso<br>\n";
		cout << "***************************<br>\n";
	}

	/**
	 *	Generar Linea Esquema para banco Provincia
	 *
	 */
	void _Esq_Provincial() {

		LArchivo Archivo = LArchivo();
		Archivo.Abrir("Provincial.txt"); //Creando el archivo
		int iMax = this->Contrato.size();
		int iMin = iMax - 1;
		double dSuma = 0;
		string sLinea, sCed, sNom, sMon, sMonT, sCue;
		cout << "**************************<br>\n";
		cout << "Creando Archivo Provincial<br>\n";

		for (int i = 0; i < iMax; i++) {
			MFactura Factura = MFactura();
			Factura.UnaPersona(MConexion, Contrato[i].oidf, Contrato[i].oidl);
			sCue = Utilidad.Completar(Factura.Persona.ced, 10, 1);
			sCed = Utilidad.Completar(Factura.Persona.ced, 10, 1);
			Monto = Utilidad.Explode(".", Contrato[i].mcuo);
			dSuma += atof(Contrato[i].mcuo.c_str());
			sMonT = Monto[0] + Monto[1];
			sMon = Utilidad.Completar(sMonT, 15, 1);
			sNom = Factura.Persona.pnmb + " " + Factura.Persona.snmb + " "
					+ Factura.Persona.pape + " " + Factura.Persona.sape;

			sLinea = Factura.Persona.Banco.cuenta + " " + "V" + sCed + " "
					+ sMon + " " + sNom;
			Archivo.Escribir((char *) sLinea.c_str());

		}
		Archivo.Salvar();
		cout << "Pendiente por Cobrar: " << dSuma << "<br>\n";
		cout << "Proceso Exitoso<br>\n";
		cout << "**************************<br>\n";
	}
};

