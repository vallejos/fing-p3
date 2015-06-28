/* 4345244 3797928 4577086 */

#include "ListaOrd.h"
#include <stdlib.h>
#include <stdio.h>

struct AuxListaOrd {
    int valor;
    ListaOrd sig;
};
typedef AuxListaOrd* ListaOrd;


/*	Devuelve en l la lista vacia. */
void crearLista (ListaOrd &l) {
    l = NULL;
}

/*	Inserta i, manteniendo el orden, en la lista l, si i no esta en l.
	En otro caso no hace nada. */
void insLista (int i, ListaOrd &l) {
    if (esVaciaLista(l)) {
        l = new AuxListaOrd;
        l->valor = i;
        l->sig = NULL;
    } else if (i < primeroLista(l)) {
        ListaOrd aux = new AuxListaOrd;
        aux->valor = i;
        aux->sig = l;
        l = aux;
    } else {
        insLista(i, l->sig);
    }
}

/*	Devuelve 'true' si l es vacia, 'false' en otro caso. */
bool esVaciaLista (ListaOrd l) {
    return (l == NULL);
}

/*	Devuelve el valor del primer elemento de l.
	Precondicion: !esVaciaLista (l). */
int primeroLista (ListaOrd l) {
    return l->valor;
}

/*	Cambia l a su resto.
	Precondicion: !esVaciaLista (l). */
void restoLista (ListaOrd & l) {
    l = l->sig;
}

/*	Remueve el elemento 'i' de la lista 'l'.
	Si no estaba, no hace nada. */
void removerLista (int i, ListaOrd &l) {
    ListaOrd temp;
    if (!esVaciaLista(l)) {
        if (i == primeroLista(l)) {
            temp = l;
            restoLista(l);
            delete temp;
        } else {
            removerLista(i, l->sig);
        }
    }
}

/*	Libera toda la memoria ocupada por l. */
void destruirLista (ListaOrd &l) {
    ListaOrd aux;
    while (!esVaciaLista(l)) {
        aux = l;
        restoLista(l);
        delete aux;
    }
}
