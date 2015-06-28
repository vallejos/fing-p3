/* 4580768 3797928 4392392 */

#include <string.h>
#include <stdio.h>

//*****Definicion de Tipo*****//

struct Zona{
		char* nom;
		bool centro;
		};

//***** Constructores *****//

Zona* crearZonaVacia(){
// Crea una nueva zona con nombre "" y sin centro_de_envio
	Zona* z=new Zona;
	z->nom=NULL;
	z->centro=false;
	return z;
	};

void asignarNombreZona(Zona* z, const char* nombre){
// Precondicion: La zona z ya fue creada
// Precondicion: nombre != NULL
// Precondicion: nombre no contiene espacios
// Precondicion: La zona z no tiene nombre asignado
    int largo=strlen(nombre);
    z->nom = new char[largo];
	strcpy(z->nom,nombre);
	};

void asignarCentroDeEnvioZona(Zona* z){
// Precondicion: La zona z ya fue creada
// Precondicion: La zona z no tiene centro_de_envio asignado
	z->centro=true;
	};

Zona* copiarZona(Zona* z){
// Devuelve una copia limpia de la zona z. (no comparte memoria)
// Precondicion: La zona z ya fue creada
	Zona* copia_z=new Zona;
	int largo=strlen(z->nom);
	copia_z->nom=new char[largo];
	strcpy(copia_z->nom,z->nom);
	copia_z->centro=z->centro;
	return copia_z;
	};

//***** Selectores *****//

char* obtenerNombreZona(Zona* z){
// Devuelve una copia del nombre de la zona z
// Precondicion: La zona z ya fue creada
	char* nombre= new char;
	return strcpy(nombre,z->nom);
	};

//***** Predicados *****//

bool tieneCentroDeEnvio(Zona* z){
// Devuelve true si la zona tiene centro_de_envio.
// Precondicion: La zona z ya fue creada
	return z->centro;
	};

//***** Destructores *****//

void destruirZona(Zona* z){
// Libera la memoria asociada a la zona z
// Precondicion: La zona z ya fue creada
    delete[] z->nom;
    delete z->nom;
z->nom = NULL;
//    printf("%s\n", z->nom);
	delete z;
	z = NULL;
	};
