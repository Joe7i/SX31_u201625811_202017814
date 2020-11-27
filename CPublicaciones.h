#pragma once
#include "Arboles.h"
#include "ClasePubli.h"
class CPublicaciones {
	ArbolAVL<CPublicacion*>* arbolId;
	CPublicacion* _buscarPorID(ull id) {
		auto criterio = [](CPublicacion* a, CPublicacion* b) {return (a->getId() == b->getId()); };
		return arbolId->busquedaPorValor(new CPublicacion(id), criterio);
	}
public:
	CPublicaciones() {
		auto compararI = [](CPublicacion* a, CPublicacion* b)->bool {return a->getId() > b->getId(); };
		auto mostrar = [](CPublicacion* a)->void {cout << a->getId() << "  U: "; a->getUsuario()->toString(); };
		arbolId = new ArbolAVL<CPublicacion*>(compararI,mostrar);
	}
	CPublicacion* buscarPorID(ull id) {
		return _buscarPorID(id);
	}
	void insertar(CPublicacion* p) {
		arbolId->insertar(p);
	}
};