/* 4345244 3797928 4577086 */

#include "Pila.h"
#include <stdlib.h>
#include <stdio.h>

struct AuxPila {
    int cota;       // cantidad maxima de elementos en la pila (tope o cota)
    int cima;       // cantidad de elementos en la pila (para no tener que contar cada vez)
    int* datos;     // los elementos en si
};

typedef AuxPila* Pila;

/* Devuelve en p la pila vacia, que podra contener hasta cota elementos. */
void crearPila (int cota, Pila &p) {
    p = new AuxPila;
    p->cota = cota;
    p->cima = 0;
    p->datos = new int[cota];
}

/* Devuelve 'true' si p es vacia, 'false' en otro caso.*/
bool esVaciaPila (Pila p) {
    if ((p->cima == 0) || (p == NULL)) {
        // la pila esta vacia
        // si esta creada pero no tiene elementos
        // o si no esta creada
        return true;
    }
    return false;
}

/* Devuelve 'true' si p tiene cota elementos, donde cota es el valor del
   parametro pasado en crearPila, 'false' en otro caso.*/
bool esLlenaPila (Pila p) {
    if (p->cima == p->cota) {
        return true;
    }
    return false;
}

/* Si !esLlenaPila (p) inserta n en la cima de p,
   en otro caso no hace nada.*/
void apilar (int i, Pila &p) {
    if (!esLlenaPila(p)) {
        p->datos[p->cima] = i;
        p->cima++;
    }
}

/* Devuelve la cima de p.
   Precondicion: ! esVaciaPila(p).*/
int cima (Pila p) {
    return p->datos[p->cima -1];
}

/* Remueve la cima de p.
   Precondicion: ! esVaciaPila(p).*/
void desapilar (Pila &p) {
    if (!esVaciaPila(p)) {
        p->cima--;
    }
}

/* libera toda la memoria ocupada por p.*/
void destruirPila (Pila &p) {
    delete [] p->datos;
    p->cota = 0;
    p->cima = 0;
    delete p;
    p = NULL;
}
