#ifndef TEST_HELPER_H
#define TEST_HELPER_H

#include "Zona.h"
#include "Ciudad.h"
#include "Estrategias.h"

extern char STR_ERRORS[7][1024];

#define CHECK_OK 0
/* Camino mas corto */
#define CHECK_CAMINO_LARGO 1
#define CHECK_CAMINO_ID1 2
#define CHECK_CAMINO_ID2 3
#define CHECK_CAMINO_NOTNULL 4
#define CHECK_CAMINO_NOVECINOS 5

/* Listas */
#define CHECK_CONJUNTOS_DISTINTOS 6

/* Retorna CHECK_OK si `sol' es un camino válido de largo `cantZonas'
   desde `id1' a `id2'.
   Retorna un valor de error adecuado en otro caso. */
int check_camino (Ciudad *c, int id1, int id2, int largo, Camino *sol);

int check_lista (ListaEnteros sol, ListaEnteros posibleSol);

Ciudad* crear_ciudad1 ();


#endif /* TEST_HELPER_H */
