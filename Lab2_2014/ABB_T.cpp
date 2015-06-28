/* 4345244 3797928 4577086 */

#include "ListaOrd.h"
#include "ABB_T.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct AuxABB_T {
    char* clave;
    ListaOrd lista;
    ABB_T izq;
    ABB_T der;
};
typedef AuxABB_T* ABB_T;


/*	Devuelve en 'abb' el arbol vac�o. */
void crearABB (ABB_T & abb) {
    abb = NULL;
}

/*	Agrega la palabra clave 'p' en 'abb'.
	En otro caso no hace nada. */
void agregarABB (ABB_T &abb, char* p) {
    if (esVacioABB(abb)) {
        ABB_T t = new AuxABB_T;
        t->clave = new char[MAX_STR];
        strcpy(t->clave, p);
        t->izq = NULL;
        t->der = NULL;
        crearLista(t->lista);
        abb = t;
    } else {
        if (strcmp(palabraClaveABB(abb), p) > 0) {
            agregarABB(abb->izq, p);
        } else if (strcmp(palabraClaveABB(abb), p) < 0) {
            agregarABB(abb->der, p);
        }
    }
}

/*	Devuelve 'true' si 'abb' es vac�o, 'false' en otro caso. */
bool esVacioABB (ABB_T abb) {
    return (abb == NULL);
}

/*	Devuelve la palabra clave de la ra�z de 'abb'.
	Precondici�n: ! esVacioABB(abb). */
char * palabraClaveABB (ABB_T abb) {
    return abb->clave;
}

/*  Devuelve la lista de art�culos asociada a la palabra clave
	de la ra�z de 'abb'.
	Precondici�n: ! esVacioABB(abb) */
ListaOrd listaArticulosABB (ABB_T abb) {
	return abb->lista;
}

/*  Asocia en 'abb' el art�culo 'a' con la palabra clave 'p',
	si �sta es una palabra del �rbol. En otro caso no hace nada. */
void asociarArticuloABB (ABB_T abb, char* p, int a) {
    bool encontrado = false;

    while (!encontrado && !esVacioABB(abb)) {
        if (strcmp(palabraClaveABB(abb), p) > 0) {
            abb = arbolDerecho(abb);
            asociarArticuloABB(abb, p, a);
        } else if (strcmp(palabraClaveABB(abb), p) < 0) {
            abb = arbolIzquierdo(abb);
            asociarArticuloABB(abb, p, a);
        } else {
            encontrado = true;
        }
    }
    if (encontrado) {
        insLista(a, abb->lista);
    }
}

/*  Desasocia en 'abb' el art�culo 'a' de la palabra clave 'p',
	si �sta es una palabra del �rbol y si contiene al art�culo.
	En otro caso no hace nada. */
void desasociarArticuloABB(ABB_T abb, char* p, int a) {
    removerLista(a, abb->lista);
}

/*	Devuelve el sub�rbol izquierdo de 'abb'.
	Precondicion: ! esVacioABB(abb). */
ABB_T arbolIzquierdo (ABB_T abb) {
    return abb->izq;
}

/*	Devuelve el sub�rbol derecho de 'abb'.
	Precondicion: ! esVacioABB(abb).*/
ABB_T arbolDerecho (ABB_T abb) {
    return abb->der;
}

/*	Libera toda la memoria ocupada por 'abb'. */
void destruirABB (ABB_T &abb) {
    if (!esVacioABB(abb)) {
        destruirABB(abb->izq);
        destruirABB(abb->der);
        delete [] abb->clave;
        delete abb;
        abb = NULL;
    }
}
