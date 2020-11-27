#pragma once
#include <iostream>
#include "User.h"
#include "Arboles.h"
#include<fstream>
#include "CPublicaciones.h"
using namespace std;
class CArchivos {
	ifstream cargar;
	ofstream guardar;
public:
	CArchivos() {}
	~CArchivos(){}
	void leerUsuarios(ArbolAVL<CUsuario*>* arbolI,ArbolAVL<CUsuario*>* arbolN, ArbolAVL<CUsuario*>* arbolM) {
		ull id;
		short dia, mes;
		int año;
		string date;
		string name;
		string mail;
		string texto;
		cargar.open("users.csv");
		getline(cargar, texto, '\n');
		while (getline(cargar, texto, '\n'))
		{
			stringstream cadena(texto);
			getline(cadena, texto, ',');
			getline(cadena, texto, ',');
			id = stoi(texto);
			getline(cadena, mail, ',');
			for (int i = 0; i < mail.size(); i++)
				if (mail[i] == 34)
					mail = mail.substr(1, mail.size() - 2);
			getline(cadena, name, ',');
			for (int i = 0; i < name.size(); i++)
				if (name[i] == 34)
					name = name.substr(1, name.size()-2);
			getline(cadena, date, ',');
			stringstream fecha(date);
			getline(fecha, date, '-');
			dia = stoi(date);
			getline(fecha, date, '-');
			mes = stoi(date);
			getline(fecha, date, '-');
			año = stoi(date);
			arbolN->insertar(new CUsuario(mail, name, new CFecha(dia, mes, año), id));
			arbolI->insertar(new CUsuario(mail, name, new CFecha(dia, mes, año), id));
			arbolM->insertar(new CUsuario(mail, name, new CFecha(dia, mes, año), id));
		}
		cargar.close();
	}
	void guardarUsuarios(ArbolAVL<CUsuario*>* arbol) {
		guardar.open("users.csv");
		guardar << "id,mail,name,date" << endl;
		auto criterio = [](CUsuario* a)->string {return a->getString(); };
		arbol->guardarNodos(guardar, criterio);
		guardar.close();
	}
	void cargarSolicitudes(ArbolAVL<CUsuario*>* arbolI) {
		ull id, idU, idF;
		string texto;
		cargar.open("followers.csv");
		getline(cargar, texto, '\n');
		auto compararI = [](CUsuario* a, CUsuario* b)->bool {return a->getId() == b->getId(); };
		while (getline(cargar, texto, '\n')) {
			stringstream s(texto);
			getline(s, texto, ',');
			getline(s, texto, ',');
			id = stoi(texto);
			getline(s, texto, ',');
			idU = stoi(texto);
			getline(s, texto, ',');
			idF = stoi(texto);
			arbolI->busquedaPorValor(new CUsuario("m", "n", new CFecha(1, 1, 1), idU), compararI)->agregarSeguidor(arbolI->busquedaPorValor(new CUsuario("m", "n", new CFecha(1, 1, 1), idF), compararI));
		}
		cargar.close();
	}
	void cargarPublicaciones(CPublicaciones* pub, ArbolAVL<CUsuario*>* arbolI) {
		cargar.open("publications.csv");
		string txt;
		ull id, idU, idP, likes;
		string descripcion, titulo;
		short dia, mes;
		int año;
		auto compararI = [](CUsuario* a, CUsuario* b)->bool {return a->getId() == b->getId(); };
		getline(cargar, txt, '\n');
		while (getline(cargar,txt,'\n')){
			stringstream text(txt);
			getline(text, txt, ',');
			getline(text, txt, ',');
			id = stoi(txt);
			getline(text, txt, ',');
			idU = stoi(txt);
			getline(text, txt, ',');
			titulo = txt;
			getline(text, txt, ',');
			descripcion = txt;
			getline(text, txt, ',');
			stringstream fecha(txt);
			getline(fecha, txt, '-');
			dia = stoi(txt);
			getline(fecha, txt, '-');
			mes = stoi(txt);
			getline(fecha, txt, '-');
			año = stoi(txt);
			cout << txt << "  |";
			getline(text, txt, ',');
			likes = stoi(txt);
			arbolI->busquedaPorValor(new CUsuario("m", "n", new CFecha(1, 1, 1), idU), compararI)->toString();

			cout << "Likes: " << likes << "USUARIO: "; 
			cout << "Descripcion: " << endl;
			cout << descripcion << endl;
			cout << "TITULO: " << titulo << endl;
			cout << "IDPUB: " << idP << "   idU : " << idU << "   id: " << id << endl;
			CPublicacion* p = new CPublicacion(id, titulo, descripcion, new CFecha(dia, mes, año), arbolI->busquedaPorValor(new CUsuario("m", "n", new CFecha(1, 1, 1), idU), compararI),likes);
			pub->insertar(p);
			p->toString();
		}
	}
};
