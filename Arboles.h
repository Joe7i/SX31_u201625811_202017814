#pragma once
#include <iostream>
#include <functional>
#include <fstream>
using namespace std;
typedef unsigned long long ull;
template<typename T>
struct ANodo {
	T elemento;
	ANodo* izquierdo;
	ANodo* derecho;
	ANodo* padre;
	ull altura;
	ANodo(T e, ANodo* p = nullptr, ANodo* i = nullptr, ANodo* d = nullptr, ull a = 0) : elemento(e), padre(p), izquierdo(i), derecho(d),altura(a) {}
};
template<class T>
class ArbolAVL {
	ANodo<T>* raiz;
	size_t cantidad;
	function<bool(T, T)> comparar;
	function<void(T)> mostrar;
	ull altura(ANodo<T>* nodo) {
		if (nodo == nullptr) return 0;
		return nodo->altura;
	}
	void rotarDerecha(ANodo<T>*& nodo) {
		ANodo<T>* p = nodo->izquierdo;
		nodo->izquierdo = p->derecho;
		p->derecho = nodo;
		nodo = p;
	}
	void rotarIzquierda(ANodo<T>*& nodo) {
		ANodo<T>* p = nodo->derecho;
		nodo->derecho = p->izquierdo;
		p->izquierdo = nodo;
		nodo = p;
	}
	void balanceo(ANodo<T>*& nodo) {
		int diferencia = (altura(nodo->derecho)- altura(nodo->izquierdo));
		if (diferencia > 1) {
			int hhizq = altura(nodo->derecho->izquierdo);
			int hhder = altura(nodo->derecho->derecho);
			if (hhizq > hhder) {
				rotarDerecha(nodo->derecho);
			}
			rotarIzquierda(nodo);
		}
		if (diferencia < -1) {
			int hhizq = altura(nodo->izquierdo->izquierdo);
			int hhder = altura(nodo->izquierdo->derecho);
			if (hhizq < hhder) {
				rotarIzquierda(nodo->izquierdo);
			}
			rotarDerecha(nodo);
		}
		int hizq = altura(nodo->izquierdo);
		int hder = altura(nodo->derecho);
		nodo->altura = 1 + ((hizq > hder) ? hizq : hder);
	}
	void insertar(ANodo<T>*& nodo, T elemento) {
		if (nodo == nullptr) {
			nodo = new ANodo<T>(elemento);
			++cantidad;
		}
		else {
			if (comparar(nodo->elemento, elemento))
				insertar(nodo->izquierdo, elemento), nodo->izquierdo->padre = nodo;
			else insertar(nodo->derecho, elemento), nodo->derecho->padre = nodo;
			balanceo(nodo);
			
		}
	}
	T mayor(ANodo<T>* nodo) {
		if (nodo->derecho == nullptr)
			return nodo->elemento;
		else return mayor(nodo->derecho);
	}
	T menor(ANodo<T>* nodo) {
		if (nodo->izquierdo == nullptr)
			return nodo->elemento;
		else return menor(nodo->izquierdo);
	}
	bool buscar(ANodo<T>* nodo, T e, function<bool(T, T)> criterioBusqueda) {
		if (nodo == nullptr)return false;
		else {
			if (criterioBusqueda(nodo->elemento, e))
				return true;
			else if (comparar(nodo->elemento, e))
				return buscar(nodo->izquierdo, e, criterioBusqueda);
			else return buscar(nodo->derecho, e, criterioBusqueda);
		}
	}

	T busquedaPorValor(ANodo<T>* nodo, T e, function<bool(T, T)> criterioBusqueda) {
		if (nodo == nullptr)return NULL;
		else {
			if (criterioBusqueda(nodo->elemento, e))
				return nodo->elemento;
			else if (comparar(nodo->elemento, e))
				return busquedaPorValor(nodo->izquierdo, e, criterioBusqueda);
			else return busquedaPorValor(nodo->derecho, e, criterioBusqueda);
		}
	}
	void ascendente(ANodo<T>* nodo) {
		if (nodo == nullptr) return;
		ascendente(nodo->izquierdo);
		mostrar(nodo->elemento);
		ascendente(nodo->derecho);
	}
	void descendente(ANodo<T>* nodo) {
		if (nodo == nullptr) return;
		descendente(nodo->derecho);
		mostrar(nodo->elemento);
		descendente(nodo->izquierdo);
	}
	void guardarDatos(ANodo<T>* nodo, ofstream& archivo, function<string(T)> criterio) {
		if (nodo == nullptr) return;
		guardarDatos(nodo->izquierdo,archivo,criterio);
		archivo << criterio(nodo->elemento) << endl;
		guardarDatos(nodo->derecho,archivo,criterio);
	}
public:
	ArbolAVL(function<bool(T, T)> comparar, function<void(T)> mostrar) {
		raiz = nullptr;
		this->comparar = comparar;
		this->mostrar = mostrar;
		cantidad = 0;
	}
	void insertar(T e) {this->insertar(raiz, e); }
	T mayor() { return mayor(raiz); }
	T menor() { return menor(raiz); }
	bool buscar(T e, function<bool(T, T)> criterioBusqueda) { return buscar(raiz, e, criterioBusqueda); }
	size_t size() { return cantidad; }
	void ascendente() { this->ascendente(raiz); }
	void descendente() { this->descendente(raiz); }
	T busquedaPorValor(T e, function<bool(T, T)>criterioBusqueda) { return busquedaPorValor(raiz, e, criterioBusqueda); };
	void guardarNodos(ofstream& archivo, function<string(T)>criterio) { this->guardarDatos(raiz, archivo, criterio); }
	void incrementarSize() { ++cantidad; }
};