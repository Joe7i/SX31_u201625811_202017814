/*#pragma once
#include "Arboles.h"
#include "User.h"
#include <fstream>
#include <sstream>
class CArchivo {
	ifstream cargarDatos;
	ofstream guardarDatos;
public:
	CArchivo() {}
	void cargarUsuarios(ArbolAVL<CUsuario*>* arbolID) {
		cargarDatos.open("users.tsv");
		string tmp;
		string nombre;
		string mail;
		ull id;
		short dia, mes;
		int año;
		getline(cargarDatos, tmp, '\n');
		while (getline(cargarDatos, tmp, '\n'))
		{
			stringstream text(tmp);
			getline(text, tmp, '	');
			id = stol(tmp);
			getline(text, tmp, '	');
			mail = tmp;
			getline(text, tmp, '	');
			nombre = tmp;
			getline(text, tmp, '	');
			stringstream fecha(tmp);
			getline(text, tmp, '-');
			año = stoi(tmp);
			getline(text, tmp, '-');
			mes = stoi(tmp);
			getline(text, tmp, '-');
			dia = stoi(tmp);
			arbolID->insertar(new CUsuario(id, mail, nombre, new CFecha(dia, mes, año)));
		}
	}
};*/