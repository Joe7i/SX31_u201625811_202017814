#pragma once
#include <iostream>
#include<vector>
#include <sstream>
#include<fstream>
#include "ClassUsers.h"
#include"ClassList.h"
using namespace std;
typedef unsigned long long ull;
class CFecha {
	short dia;
	short mes;
	int año;
public:
	CFecha(short d, short m, short a) : dia(d), mes(m), año(a) {}
	short getDia() { return dia; }
	void setDia(short dia) { this->dia = dia; }
	short getMes() { return mes; }
	void setMes(short mes) { this->mes = mes; }
	int getAño() { return año; }
	void setAño(short anio) { this->año = anio; }
	string getString() {
		string txt = to_string(dia) + "-" + to_string(mes) + "-" + to_string(año);
		return txt;
	}
};
class CUsuario {
	string nombre;
	string mail;
	CFecha* registro;
	ull id;
	ListaDoble<CUsuario*>* seguidores;
	bool estado;
public:
	CUsuario(string m, string n, CFecha* r, ull i) : nombre(n), mail(m), registro(r), id(i) {
		auto mostrar = [](CUsuario* u) {u->toString(); };
		seguidores = new ListaDoble<CUsuario*>(mostrar); 
		auto compararI = [](CUsuario* a, CUsuario* b)->bool {return a->getId() == b->getId(); };
		seguidores->setBuscar(compararI);
	}
	string getNombre() { return nombre; }
	string getMail() { return mail; }
	ull getId() { return id; }
	CFecha* getFecha() { return registro; }
	void toString() {
		cout << nombre << "  " << mail << "  " << registro->getDia() << "/" << registro->getMes() << "/" << registro->getAño() << "  id: " << id << endl;
	}
	string getString() {
		string txt = to_string(id) + "," + to_string(id) + "," + mail + "," + nombre + "," + registro->getString();
		return txt;
	}
	void setMail(string mail) { this->mail = mail; }
	void setId(unsigned long long id) { this->id = id; }
	void setNombre(string nombre) { this->nombre = nombre; }
	void agregarSeguidor(CUsuario* nuevo) {
		if (seguidores->busqueda(nuevo))return;
		this->seguidores->insertar(nuevo);
	}
	void eliminarSeguidor(CUsuario* e) {
		auto buscar = [](CUsuario* a, CUsuario* b) {return a->getNombre() == b->getNombre(); };
		seguidores->setBuscar(buscar);
		this->seguidores->eliminarV(e);
	}
	size_t getCantSeguidores() { return seguidores->size(); }
	ListaDoble<CUsuario*>* getListaSeguidores() { return seguidores; }
	void SeguidoresNew() {
		seguidores->mostrarI();
	}
	string show() { string tx = nombre + "   " + mail; return tx; }
	void setEstado(bool estado) { this->estado = estado; }
};