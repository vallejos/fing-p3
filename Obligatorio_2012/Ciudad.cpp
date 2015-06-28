/* 4580768 3797928 4392392 */

#include "ListaEnteros.h"
#include "Zona.h"
#include <stdlib.h>

//*****Definicion de Tipo*****//
struct NodoCiudad{
	Zona* actual;
	ListaEnteros adyacentes;
	};

struct Ciudad{
    int cant_zonas;
	NodoCiudad* zonas;
	};
//***** Constructores *****//

Ciudad* crearCiudad(int cantZonas){
// Crea una Ciudad con cantZonas Zonas vacias.
// Reserva la memoria para la estructura ciudad y sus zonas.
	Ciudad* c=new Ciudad;
	c->cant_zonas=cantZonas;
	c->zonas= new NodoCiudad[cantZonas];
	for (int i=0; i<cantZonas; i++){
		c->zonas[i].actual=crearZonaVacia();
		c->zonas[i].adyacentes=crearListaEnteros();
	};

	return c;
};
void hacerAdyacentesZonas(Ciudad* c, int idZona1, int idZona2){
// Las zonas idZona1 e idZona2 son adyacentes
// Precondicion: 0 <= idZona1 < cantZonasCiudad(c)
// Precondicion: 0 <= idZona2 < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada
	agregarListaEnteros(c->zonas[idZona1].adyacentes,idZona2);
	agregarListaEnteros(c->zonas[idZona2].adyacentes,idZona1);
};

//***** Selectores *****//

Zona* obtenerZonaCiudad(Ciudad* c, int idZona){
// Devuelve una referencia a la Zona con identificador idZona en la Ciudad c.
// Precondicion: La ciudad c ya fue creada
// Precondicion: 0 <= idZona < cantZonasCiudad(c)
	return c->zonas[idZona].actual;
};

ListaEnteros obtenerAdyacentesZonaCiudad(Ciudad* c, int idZona){
// Devuelve una lista con los identificadores de
// los Zonas adyacentes a la Zona idZona.
// Precondicion: 0 <= idZona < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada
	return c->zonas[idZona].adyacentes;
};

//***** Predicados *****//

bool sonAdyacentesCiudad(Ciudad* c, int idZona1, int idZona2){
// Devuelve true si las zonas idZona1 e idZona2 son adyacentes.
// Precondicion: 0 <= idZona1 < cantZonasCiudad(c)
// Precondicion: 0 <= idZona2 < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada
	ListaEnteros laux=c->zonas[idZona1].adyacentes;
	bool ady=false;
	while ((!esVaciaListaEnteros(laux))&&(ady==false)){
		if (primeroListaEnteros(laux)==idZona2){
			ady=true;
		}
		laux=restoListaEnteros(laux);
	}
	return ady;
};

int cantZonasCiudad(Ciudad* c){
// Devuelve la cantidad de Zonas de la Ciudad c
// Precondicion: La ciudad c ya fue creada
	return c->cant_zonas;
};

int cantAdyacentesZonaCiudad(Ciudad* c, int idZona){
// Devuelve la cantidad de zonas adyacentes a la zona idZona.
// Precondicion: 0 <= idZona < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada
	int cant_ady=0;
	ListaEnteros laux=c->zonas[idZona].adyacentes;
	while (!esVaciaListaEnteros(laux)){
		cant_ady++;
		laux=restoListaEnteros(laux);
	}
	return cant_ady;
};

//***** Destructores *****//

void destruirCiudad(Ciudad* c){
// Libera la memoria de la Ciudad c y la memoria asociada a las Zonas
// Precondicion: La ciudad c ya fue creada
	for(int i=0; i<cantZonasCiudad(c); i++){
	    Zona* z=obtenerZonaCiudad(c,i);
		destruirZona(z);
		ListaEnteros temp=obtenerAdyacentesZonaCiudad(c,i);
		destruirListaEnteros(temp);
	};
	delete c->zonas;
	delete c;
};
