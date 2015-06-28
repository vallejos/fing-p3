#ifndef ESTRUCTURA_H
#define ESTRUCTURA_H

#define cantServidores 53 /* cantidad de servidores */
#define cantDominios 101 /* cantidad de dominios */
#define cantIP 5 /* cantidad de ips por dominio */
#define cantDominiosAutoritativos 101 /* cantidad de dominios autoritativos de un servidor */

struct Estructura;

struct IP
{
	int ip;

};


Estructura* crearDNS();
//Crea la estructura de datos vacia.

void altaServidorNombres(int codSN, Estructura* E);
// Esta operacion debe realizarse en O(1) promedio.
// Pre: la estructura fue creada previamente.
// Pre: no existe un servidor de codigo codNS en la estructura E

void altaDominio(const char* nombreDominio, const char* nombreComprador, const char* emailContacto, Estructura* E);
// Esta operacion debe realizarse en O(1) promedio.
// Pre: nombreDominio != NULL, nombreComprador != NULL, emailContacto != NULL
// Pre: la estructura fue creada previamente.
// Pre: no existe un dominio de nombre nombreDominio en la estructura

void agregarIPAutoritativa(int codSN, const char* nombreDominio, IP *ip, Estructura* E);
// Esta operacion debe realizarse en O(cantServidores + cantDominios + cantDominiosAutoritativos + log (cantIP))  peor caso
// Pre: nombreDominio != NULL
// Pre: la estructura fue creada previamente.
// Pre: existe un servidor de codigo codSN en la estructura
// Pre: existe un dominio de nombre nombreDominio en la estructura
// Pre: existen menos de cantIP traducciones para el dominio de nombre nombreDominio en el servidor de codigo codSN

IP* consultaNoJerarquica(int codSN, const char* nombreDominio, bool& hayTraduccion, Estructura* E);
// Esta operacion debe realizarse en O(1) promedio.
// Pre: nombreDominio != NULL
// Pre: la estructura fue creada previamente.
// Pre: existe un servidor de codigo codSN en la estructura
// Pre: existe un dominio de nombre nombreDominio en la estructura

void dig(int codSN, const char* nombreDominio, Estructura* E);
// Esta operacion debe realizarse en O(cantIP) promedio
// El orden de impresión será ascendente segun el valor de las direcciones ip
// Pre: nombreDominio != NULL
// Pre: la estructura fue creada previamente.
// Pre: existe un dominio de nombre nombreDominio en la estructura
// Pre: existe un servidor de nombres de codigo codSN en la estructura

void destruirDNS(Estructura* E);
//Pre: La estructura E fue previamente creada.
//Destruye la estructura, liberando por completo la memoria asignada.

#endif /* ESTRUCTURA_H */
