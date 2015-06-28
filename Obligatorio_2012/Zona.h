#ifndef ZONA_H
#define ZONA_H

struct Zona;

//***** Constructores *****//

Zona* crearZonaVacia();
// Crea una nueva zona con nombre "" y sin centro_de_envio


void asignarNombreZona(Zona* z, const char* nombre);
// Precondicion: La zona z ya fue creada
// Precondicion: nombre != NULL
// Precondicion: nombre no contiene espacios
// Precondicion: La zona z no tiene nombre asignado

void asignarCentroDeEnvioZona(Zona* z);
// Precondicion: La zona z ya fue creada
// Precondicion: La zona z no tiene centro_de_envio asignado

Zona* copiarZona(Zona* z);
// Devuelve una copia limpia de la zona z. (no comparte memoria)
// Precondicion: La zona z ya fue creada


//***** Selectores *****//

char* obtenerNombreZona(Zona* z);
// Devuelve una copia del nombre de la zona z
// Precondicion: La zona z ya fue creada

//***** Predicados *****//

bool tieneCentroDeEnvio(Zona* z);
// Devuelve true si la zona tiene centro_de_envio.
// Precondicion: La zona z ya fue creada


//***** Destructores *****//

void destruirZona(Zona* z);
// Libera la memoria asociada a la zona z
// Precondicion: La zona z ya fue creada

#endif /* ZONA_H */

