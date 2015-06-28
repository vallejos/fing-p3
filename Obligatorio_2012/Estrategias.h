#ifndef ESTRATEGIAS_H
#define ESTRATEGIAS_H

#include "Ciudad.h"

//Estructura para almacenar un camino
struct Camino
{
	//indica la cantidad de elementos en la secuencia de zonas del camino
	int cantZonas;
	
	//arreglo que contiene la secuencia de los identificadores 
	//de las zonas por las que pasa el camino
	int* zonas;
	
	//zonas[0] es el origen del camino, zonas[cantZonas-1] es el destino del camino
};

Camino* centroEnvioMasCercano(Ciudad* c, int idZona);
// Devuelve el camino entre idZona y el centro de envio mas cercano. 
// En caso que no exista un camino que cumpla la condicion, retorna cantZonas igual a 0 
// y zonas igual a NULL.
// Precondicion: 0 <= idZona < cantZonasCiudad(c);
// Precondicion: La Ciudad c ya fue creada.

ListaEnteros zonasDeInfluencia(Ciudad* c, int idZona, int n);
// Devuelve las zonas que se encuentran a una distancia menor o igual a n de idZona.
// Precondicion: 0 <= idZona < cantZonasCiudad(c);
// Precondicion: tieneCentroDeEnvio(idZona)
// Precondicion: La Ciudad c ya fue creada.

ListaEnteros  zonasExclusivas(Ciudad* c, int idZona);
// Una zona es exclusiva de un centro de envio cuando no es posible acceder
// a dicha zona desde otro centro de envío sin pasar por el. En este caso
// no importa la distancia de la zona al centro de envío, sino si esta es
// accesible desde el centro.
// Devuelve un listado de las zonas exclusivas de idZona
// Precondicion: 0 <= idZona < cantZonasCiudad(c);
// Precondicion: tieneCentroDeEnvio(idZona)
// Precondicion: La Ciudad c ya fue creada.

#endif /* ESTRATEGIAS_H */


