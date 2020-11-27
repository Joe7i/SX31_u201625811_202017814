#pragma once
#include <iomanip>
#include "ClassUsers.h"
class CRedSocial {
	CArchivos* datos;
	DBUsuarios* dbUsuarios;
	CUsuario* activo;
	CPublicaciones* datPublicaciones;
	void ingresar() {
		int opcion;
		while (true)
		{
			cout << "\n		W E L C O M E  \n  " << endl;
			cout << "[1]. See my profile" << endl;
			cout << "[2]. View Followers " << endl;
			cout << "[3]. Follow" << endl;
			cout << "[4]. View publications " << endl;
			cout << "[5]. Post status " << endl;
			cout << "[6]. Sign off " << endl;
			cout << " Enter - return" << endl;
			cin >> opcion;
			switch (opcion)
			{
			case 1:
				activo->toString();
				break;
			case 2:
				SeguidoresNew();
				break;
			case 3:
				buscarPersonas();
				break;
			case 4:
				
				break;
			case 5:
				break;
			case 6: return; break;
			default:
				cout << " Check the options " << endl;
				break;
			}
			system("pause");
			system("cls");
		}
	}
	void buscarPersonas() {
		string nombre;
		cout << " Enter the name of the person you want to follow:  ", cin >> nombre;
		if (dbUsuarios->buscarNombre(nombre)) {
			dbUsuarios->buscarPorNombre(nombre)->agregarSeguidor(dbUsuarios->buscarPorID(activo->getId()));
			cout << activo->getNombre() << " tarted to follow :  " << dbUsuarios->buscarPorNombre(nombre)->getNombre();
		}
		else cout << " The person is not in the database " << endl;
	}
	void SeguidoresNew() {
		dbUsuarios->buscarPorID(activo->getId())->SeguidoresNew();
	}

	//void Publicaciones() {
		//dbUsuarios->buscarPorID(activo->getId())->Publicaciones();
	//}


public:
	CRedSocial() {
		datos = new CArchivos();
		dbUsuarios = new DBUsuarios();
		datPublicaciones = new CPublicaciones();
		datos->leerUsuarios(dbUsuarios->getArbolId(), dbUsuarios->getArbolNombre(), dbUsuarios->getArbolMail());
		datos->cargarSolicitudes(dbUsuarios->getArbolId());
	//	datos->cargarPublicaciones(datPublicaciones, dbUsuarios->getArbolId());
	}
	void pantallaInicio() {
		string name, mail;
		int año;
		short dia, mes;
		CUsuario* nuevo;
		
		int opcion;
		do
		{
			cout << "		RED SOCIAL		-  Algoritmos y Estructuras de datos 	" << endl;
			cout << "[1]. Log in " << endl;
			cout << "[2]. Create New Account " << endl;
			cout << "[3]. View users in ascending order : " << endl;
			cout << "[4]. View users in descending order : " << endl;
			cout << "[5]. Exit" << endl;
			cout << "\n\n\n\n\n\n\n\n							 2020-2 " << endl;
			cin >> opcion;
			switch (opcion)
			{
			case 1:
				cout << "User name : ", cin >> name;
				cout << "E-mail : ", cin >> mail;
				if (iniciarSesion(name, mail)) {
					activo = dbUsuarios->buscarPorMail(mail);
					activo->setEstado(true);
					cout << " ....... Done ...... " << endl;
					system("cls");
					ingresar();
				}
				else cout << "	Check your details	 " << endl;
			break;
			case 2:
				cout << " Enter your name : ", cin >> name;
				cout << " Enter your E-mail : ", cin >> mail;
				cout << " Enter the day : ", cin >> dia;
				cout << " Enter the month : ", cin >> mes;
				cout << " Enter the year : ", cin >> año;
				 nuevo = new CUsuario(mail, name, new CFecha(dia, mes, año), dbUsuarios->size() + 1);
				dbUsuarios->registrar(nuevo); 
				break;
			case 3:
				dbUsuarios->mostrarUsuariosAscendente();
				break;
			case 4:
				dbUsuarios->mostrarUsuariosDescendente();
			case 5:
				guardarDatos();
				return; break;
			default:
				cout << "....... Incorrect Option......." << endl;
				break;
			}
			_sleep(10000);
			system("cls");
		} while (true);
	}
	bool iniciarSesion(string nombre, string mail) {
		if (dbUsuarios->buscarNombre(nombre) && dbUsuarios->buscarPorMail(mail))
			return true;
		else return false;
	}
	void guardarDatos() {
		datos->guardarUsuarios(dbUsuarios->getArbolId());
	}
	DBUsuarios* getDBUsuarios() { return dbUsuarios; }
	~CRedSocial() { 
		delete dbUsuarios; 
	}
	
};