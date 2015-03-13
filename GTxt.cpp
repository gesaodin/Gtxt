//============================================================================
// Name        : grupo.cpp
// Autor       : Carlos Peña
// Version     :
// Copyright   : GenProg C.A
// Description : Generador De Txt
//============================================================================

using namespace std;

#include <stdio.h>
#include <sys/time.h>
#include <mysql.h>

#include "lib/lutilidades.h"
#include "lib/larchivo.h"

#include <sstream>
#include "mdl/prs/mpersona.h"
#include "mdl/fac/mcontrato.h"
#include "mdl/fac/mfactura.h"
#include "mdl/fac/mlinaje.h"
#include "mdl/fac/mnomina.h"
#include <stdlib.h>
#include "mdl/bnc/mbanco.h" // Listado de cuentas Bancarias
/**
 * Inicio del Sistema
 *
 * @param Banco (oid) t_banco
 * @param Tipo (0: Unico,  1:Aguinaldos, 2: Vacaciones)
 * @param Fecha (Y-m-d) : (2013-04-01)
 *
 */
int main(int argc, char *argv[]) {
	MYSQL *mConexion, mysql;
	int state;
	MBanco Banco = MBanco();

	mysql_init(&mysql);
	mConexion = mysql_real_connect(&mysql, "localhost", "root", "za63qj2p",
			"electron", 0, 0, 0);
	if (mConexion == NULL) {
		printf(mysql_error(&mysql));
		return 1;
	}
	//cout << "----------------------------------- <br><br>" << endl << endl;
//	cout << "Iniciando Programa <br><br>" << endl << endl;
    
	stringstream B; // Banco
	B << argv[1];
	string _B = B.str();
	stringstream E; //Empresa
	E << argv[2];
	string _E = E.str();
	stringstream M; // Mes ( YYYY-MM )
	M << argv[3];
	string _M = M.str();
	stringstream P; // Periodos
	P << argv[4];
	string _P = P.str();
	stringstream F; // Forma del Contrato
	F << argv[5];
	string _F = F.str();
	stringstream Fecha; // Forma del Contrato
	Fecha << argv[6];
	string _Fecha = Fecha.str();
	stringstream Nomina; // Forma del Contrato
	Nomina << argv[7];
	string _Nomina = Nomina.str();
	stringstream archivo; // Nombre del Archivo en Md5
	archivo << argv[8];
	string md5Archivo = archivo.str();
	stringstream afil; // Nombre del Archivo en Md5
	afil << argv[9];
	string afiliacion = afil.str();
	stringstream ssDiv; // Nombre del Archivo en Md5
	ssDiv << argv[10];
	string sDiv = ssDiv.str();
	double dDiv = atof(argv[10]);

	//cout << _B << " " << _E << " " << _M << " " << _P << " " << _F << endl;
	//Banco.Generar_Cuentas(mConexion, oidb);
	/* Empresa  * 0 Cooperativa * 1 Grupo */
	/* Periodicidad * 4 Mensual * 3 Quincenal 10-25 * 2 Quincenal 15-30 * 0 Semanal * 1 Catorcenal */
	/* forma contrato * 0 Unico * 1 Aguinaldo * 2 Vacaciones * 3 Extra * 4 Unico Extra * 5 Especial Extra */

	//Banco.MuchosContratosViejos(mConexion, _B, _E, _M, _P, _F, _Fecha, _Nomina,md5Archivo);
	Banco.Generar_Cuentas(mConexion, _B, _E, _M, _P, _F, _Fecha, _Nomina,
			md5Archivo, afiliacion, dDiv);
	string sJson;
//	vector<string> sMsj;
//
//	sMsj = Banco.Mensaje;
	cout.precision(9);

	sJson = Banco.Mensaje[0] + ";" + Banco.Mensaje[1] + ";" + Banco.Mensaje[2]
			+ ";";

	sJson += "{\"mensaje\":\"" + Banco.Mensaje[0] + "\",\"cantidad\":\""
			+ Banco.Mensaje[1] + "\",\"total\":\"" + Banco.Mensaje[2] + "\"}";
	cout << sJson;

	mysql_close(mConexion);
//	cout << ">>> Saliendo del Sistema <br>\n";
//	cout << "***********************************************<br>\n";

	return 0;
}

