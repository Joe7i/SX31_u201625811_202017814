#pragma once
#include "User.h"
#include "ClassUsers.h"
class CPublicacion {
	string titulo;
	string descripcion;
	CFecha* pubDate;
	CUsuario* usuario;
	ull id;
	ull likes;
public:
	CPublicacion(ull id, string t = "-", string d="-", CFecha* f=nullptr, CUsuario* u=nullptr, ull l = 0) :id(id),titulo(t), descripcion(d), pubDate(f), usuario(u), likes(l) {}
	string getTitulo() { return titulo; }
	string getDescripcion() { return descripcion; }
	CFecha* getPubDate() { return pubDate; }
	ull getLikes() { return likes; }
	CUsuario* getUsuario() { return usuario; }
	/*void asignarUsuario(ull id, DBUsuarios* db) {
		this->usuario = db->buscarPorID(id);
	}*/
	ull getId() { return id; }
	void toString() {
		cout << "LIST OF PUBLICATIONS : " << id << endl;
		cout << "Title : " << titulo << endl;
		cout << "Description : " << endl;
		cout << descripcion << endl;
		cout << "Likes : " << likes << endl;
		cout << "User : "; usuario->toString();
		cout << "DATE: " << pubDate->getString() << endl;
	}
};