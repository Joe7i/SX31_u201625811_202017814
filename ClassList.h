#pragma once
#include<functional>
#include<iostream>
using namespace std;
typedef unsigned long long ull;
template<typename T>
struct LNodo {
	T elemento;
	LNodo* siguiente;
	LNodo* anterior;
	LNodo(T e, LNodo* s = nullptr, LNodo* a = nullptr) : elemento(e), siguiente(s), anterior(a) {}
};
template<class T>
class ListaDoble {
	LNodo<T>* inicio;
	LNodo<T>* fin;
	size_t cantidad;
	function<bool(T, T)>buscar;
	function<void(T)>mostrar;
public:
	ListaDoble(function<void(T)>mostrar) {
		this->mostrar = mostrar;
		inicio = fin = nullptr;
		cantidad = 0;
	}
	void setBuscar(function<bool(T, T)>buscar) {
		this->buscar = buscar;
	}
	void insertar(T elemento) {
		if (inicio == nullptr) {
			inicio = new LNodo<T>(elemento);
			fin = inicio;
		}
		else {
			fin->siguiente = new LNodo<T>(elemento);
			fin->siguiente->anterior = fin;
			fin = fin->siguiente;
		}
		++cantidad;
	}
	void mostrarI() {
		LNodo<T>* aux = inicio;
		while (aux != nullptr) {
			mostrar(aux->elemento);
			aux = aux->siguiente;
		}
	}
	void mostrarF() {
		LNodo<T>* aux = fin;
		while (aux != nullptr) {
			mostrar(aux->elemento);
			aux = aux->anterior;
		}
	}
	size_t size() { return cantidad; }
	bool busqueda(T elemento) {
		LNodo<T>* aux = inicio;
		while (aux != nullptr)
		{
			if (buscar(aux->elemento, elemento))
				return true;
			aux = aux->siguiente;
		}
		return false;
	}
	T obtenerP(ull i) {
		if (i == 0)
			return inicio->elemento;
		else if (i == cantidad - 1)
			return fin->elemento;
		else if (i >= 0 && i < cantidad) {
			int n = 0;
			LNodo<T>* aux = inicio;
			while (n < i) {
				aux = aux->siguiente;
				++n;
			}
			return aux->elemento;
		}
		return NULL;
	}
	T obtenerV(T e) {
		if (buscar(inicio->elemento, e))
			return inicio->elemento;
		else if (buscar(fin->elemento, e))
			return fin->elemento;
		else {
			LNodo<T>* aux = inicio;
			while (aux != nullptr) {
				if (buscar(aux->elemento, e))
					return aux->elemento;
				aux = aux->siguiente;
			}
			return NULL;
		}
	}
	void eliminarP(ull i) {
		if (i == 0) {
			LNodo<T>* aux = inicio;
			inicio = inicio->siguiente;
			inicio->anterior = nullptr;
			delete aux;
			--cantidad;
		}
		else if (i == cantidad - 1) {
			LNodo<T>* aux = fin;
			fin = fin->anterior;
			delete aux;
			--cantidad;
		}
		else if (i >= 0 && i < cantidad) {
			ull cant = 0;
			LNodo<T>* aux = inicio;
			while (cant<i){
				aux = aux->siguiente;
				++cant;
			}
			aux->anterior->siguiente = aux->siguiente;
			aux->siguiente->anterior = aux->anterior;
			delete aux;
			--cantidad;
		}
	}
	void eliminarV(T e) {
		if (buscar(inicio->elemento, e)) {
			LNodo<T>* aux = inicio;
			inicio = inicio->siguiente;
			inicio->anterior = nullptr;
			delete aux;
			--cantidad;
		}
		else if (buscar(fin->elemento, e)) {
			LNodo<T>* aux = fin;
			fin = fin->anterior;
			fin->siguiente = nullptr;
			delete aux;
			--cantidad;
		}
		else {
			LNodo<T>* aux = inicio;
			while (aux != nullptr) {
				if (buscar(aux->elemento, e)) {
					aux->anterior->siguiente = aux->siguiente;
					aux->siguiente->anterior = aux->anterior;
					delete aux;
					--cantidad;
					return;
				}
				aux = aux->siguiente;
			}
		}
	}
};