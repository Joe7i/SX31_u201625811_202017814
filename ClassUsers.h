#pragma once
#include <functional>
#include "Arboles.h"
#include "User.h"
#include "ClaseArchi.h"
class DBUsuarios {
	//CArchivos* datos;
	ArbolAVL<CUsuario*>* arbolId;
	ArbolAVL<CUsuario*>* arbolNombre;
	ArbolAVL<CUsuario*>* arbolMail;
	CUsuario* _buscarPorNombre(string nombre) {
		auto criterio = [](CUsuario* a, CUsuario* b) {return a->getNombre() == b->getNombre(); };
		return arbolNombre->busquedaPorValor(new CUsuario("mail", nombre, new CFecha(1, 1, 1), 1), criterio);
	}
	CUsuario* _buscarPorID(ull id) {
		auto criterio = [](CUsuario* a, CUsuario* b) {return (a->getId() == b->getId()); };
		return arbolId->busquedaPorValor(new CUsuario("m","n",new CFecha(1,1,1),id), criterio);
	}
	CUsuario* _buscarPorMail(string mail) {
		auto criterio = [](CUsuario* a, CUsuario* b) {return (a->getMail() == b->getMail()); };
		return arbolMail ->busquedaPorValor(new CUsuario(mail, "nombre", new CFecha(1, 1, 1), 1), criterio);
	}
	bool _buscarNombre(string nombre) {
		CUsuario* tmp = new CUsuario("mail", "nombre", new CFecha(1, 1, 1), 1);
		tmp->setNombre(nombre);
		auto criterio = [](CUsuario* a, CUsuario* b) {return (a->getNombre() == b->getNombre()); };
		return this->arbolNombre->buscar(tmp, criterio);
	}
public:
	DBUsuarios() {
		auto compararI = [](CUsuario* a, CUsuario* b)->bool {return a->getId() > b->getId(); };
		auto compararN = [](CUsuario* a, CUsuario* b)->bool {return a->getNombre() > b->getNombre(); };
		auto compararM = [](CUsuario* a, CUsuario* b)->bool {return a->getMail() > b->getMail(); };
		auto mostrar = [](CUsuario* a)->void { a->toString(); };
		arbolId = new ArbolAVL<CUsuario*>(compararI,mostrar);
		arbolMail = new ArbolAVL<CUsuario*>(compararM, mostrar);
		arbolNombre = new ArbolAVL<CUsuario*>(compararN, mostrar);
	}
	ArbolAVL<CUsuario*>* getArbolId() { return arbolId; }
	ArbolAVL<CUsuario*>* getArbolNombre() { return arbolNombre; }
	ArbolAVL<CUsuario*>* getArbolMail() { return arbolMail; }
	~DBUsuarios() { delete arbolId; }
	void mostrarUsuariosDescendente() {
		arbolId->descendente();
	}
	void mostrarUsuariosAscendente() {
		arbolId->ascendente();
	}
	ull size() { return arbolId->size(); }
	CUsuario* buscarPorMail(string mail) {
		return _buscarPorMail(mail);
	}
	CUsuario* buscarPorNombre(string nombre) {
		return _buscarPorNombre(nombre);
	}
	CUsuario* buscarPorID(ull id) {
		return _buscarPorID(id);
	}
	bool buscarNombre(string name) {
		return this->_buscarNombre(name);
	}
	void registrar(CUsuario* nuevo) {
		arbolId->insertar(nuevo);
		arbolMail->insertar(nuevo);
		arbolNombre->insertar(nuevo);
		arbolId->incrementarSize();
		arbolMail->incrementarSize();
		arbolNombre->incrementarSize();
	}
};
