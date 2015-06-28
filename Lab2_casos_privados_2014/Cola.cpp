/* 4345244 3797928 4577086 */

#include <stdio.h>
#include <stdlib.h>
#include "Cola.h"
#include <string.h>

struct AuxCola
{
    int dato;
    AuxCola* sig;
};
typedef AuxCola* Cola;

/* Devuelve en c la cola vacia.*/
void crearCola (Cola & c)
{
	c = NULL;
}

/* Devuelve 'true' si c es vacia, 'false' en otro caso.*/
bool esVaciaCola (Cola c)
{
	return(c == NULL);
}

/* Agrega el elemento n al final de c.*/
void encolar (int i, Cola &c)
{
    if (!esVaciaCola(c))
        encolar(i, c->sig);
    else
    {
        c = new AuxCola;
        c->dato=i;
        c->sig=NULL;
    }
}

/* Devuelve el primer elemento de c 
   Precondicion: ! esVaciaCola(c).*/
int frente (Cola c)
{
	return(c->dato);
}

/* Remueve el primer elemento de c.
   Precondicion: ! esVaciaCola(c).*/
void desencolar (Cola &c)
{
    AuxCola* aux = c->sig;
    delete c;
    c=aux;
}

/* libera toda la memoria ocupada por c.*/
void destruirCola (Cola &c)
{
    AuxCola* aux;
    while (!esVaciaCola(c))
    {
        aux=c->sig;
        delete c;
        c=aux;
    }
}
