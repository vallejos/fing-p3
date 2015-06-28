#ifndef CIUDAD_H
#define CIUDAD_H

#include "Zona.h"
#include "ListaEnteros.h"

struct Ciudad;

//***** Constructores *****//

Ciudad* crearCiudad(int cantZonas);
// Crea una Ciudad con cantZonas Zonas vacias.
// Reserva la memoria para la estructura ciudad y sus zonas.

void hacerAdyacentesZonas(Ciudad* c, int idZona1, int idZona2);
// Las zonas idZona1 e idZona2 son adyacentes
// Precondicion: 0 <= idZona1 < cantZonasCiudad(c)
// Precondicion: 0 <= idZona2 < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada


//***** Selectores *****//

Zona* obtenerZonaCiudad(Ciudad* c, int idZona);
// Devuelve una referencia a la Zona con identificador idZona en la Ciudad c.
// Precondicion: La ciudad c ya fue creada
// Precondicion: 0 <= idZona < cantZonasCiudad(c)

ListaEnteros obtenerAdyacentesZonaCiudad(Ciudad* c, int idZona);
// Devuelve una lista con los identificadores de 
// los Zonas adyacentes a la Zona idZona.
// Precondicion: 0 <= idZona < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada

//***** Predicados *****//

bool sonAdyacentesCiudad(Ciudad* c, int idZona1, int idZona2);
// Devuelve true si las zonas idZona1 e idZona2 son adyacentes.
// Precondicion: 0 <= idZona1 < cantZonasCiudad(c)
// Precondicion: 0 <= idZona2 < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada

int cantZonasCiudad(Ciudad* c);
// Devuelve la cantidad de Zonas de la Ciudad c
// Precondicion: La ciudad c ya fue creada

int cantAdyacentesZonaCiudad(Ciudad* c, int idZona);
// Devuelve la cantidad de zonas adyacentes a la zona idZona.
// Precondicion: 0 <= idZona < cantZonasCiudad(c)
// Precondicion: La ciudad c ya fue creada

//***** Destructores *****//

void destruirCiudad(Ciudad* c);
// Libera la memoria de la Ciudad c y la memoria asociada a las Zonas
// Precondicion: La ciudad c ya fue creada

#endif /* CIUDAD_H */
