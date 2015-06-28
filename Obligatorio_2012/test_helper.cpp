
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "test_helper.h"
#include "ListaEnteros.h"
#include "ColaEnteros.h"

char STR_ERRORS[7][1024] =
  {"OK",

   /* Camino mas corto */
   "cantZonas del camino es incorrecto",
   "El camino no comienza en idZona1",
   "El camino no termina en idZona2",
   "cantZonas es cero, pero zonas no es NULL",
   "El camino conecta territorios que no son vecinos",
   /* Listas */
   "Los conjuntos son distintos"
  };

#define CANT_ZONAS_CIUDAD1 7
char nombres_ciudad1[CANT_ZONAS_CIUDAD1][3]     = {"z0", "z1", "z2", "z3", "z4", "z5", "z6"};
bool centros_envio_ciudad1[CANT_ZONAS_CIUDAD1] = { false, false, false, true, false, true, false};
/* CADA ARISTA DEBE ESTAR UNA VEZ SOLA. */
int adyacentes_ciudad1[CANT_ZONAS_CIUDAD1][CANT_ZONAS_CIUDAD1] =
//  0  1  2  3  4  5  6
  {{0, 1, 1, 1, 1, 1, 1},  // 0
   {0, 0, 1, 1, 1, 1, 1},  // 1
   {0, 0, 0, 1, 1, 1, 1},  // 2
   {0, 0, 0, 0, 1, 1, 1},  // 3
   {0, 0, 0, 0, 0, 1, 1},  // 4
   {0, 0, 0, 0, 0, 0, 1},  // 5
   {0, 0, 0, 0, 0, 0, 0}}; // 6



Ciudad* crear_ciudad1(){
  int i, j;
  Ciudad* c = crearCiudad (CANT_ZONAS_CIUDAD1);

  for (i = 0; i < CANT_ZONAS_CIUDAD1; i++){
      Zona* z = obtenerZonaCiudad (c, i);
      asignarNombreZona (z, nombres_ciudad1[i]);
      if (centros_envio_ciudad1[i])
        asignarCentroDeEnvioZona (z);

      for (j = 0; j < CANT_ZONAS_CIUDAD1; j++)
      	if (adyacentes_ciudad1[i][j])
	        hacerAdyacentesZonas (c, i, j);
  }

  return c;
}

int adyacentes(Ciudad* c, int z1, int z2){
  return sonAdyacentesCiudad(c,z1,z2) ? 1 : 0;
}

int check_camino (Ciudad *c, int z1, int z2,int largo, Camino *sol){
  int i;

  if (sol->cantZonas != largo)
    return CHECK_CAMINO_LARGO;

  if (largo > 0){
    if (sol->zonas[0] != z1)
	    return CHECK_CAMINO_ID1;
    else if (sol->zonas[largo-1] != z2)
	    return CHECK_CAMINO_ID2;
  }
  else if (largo == 0 && sol->zonas != NULL)
    return CHECK_CAMINO_NOTNULL;

  for (i = 1; i < sol->cantZonas; i++){
    if (! adyacentes (c, sol->zonas[i-1], sol->zonas[i]))
      return CHECK_CAMINO_NOVECINOS;
  }

  return CHECK_OK;
}

ListaEnteros insertar_ordenado (ListaEnteros lista, int elem) {
	if (esVaciaListaEnteros(lista)) {
		agregarListaEnteros(lista, elem);
		return lista;
	} else if (elem <= primeroListaEnteros(lista)) {
		agregarListaEnteros(lista, elem);
		return lista;
	} else {
		ListaEnteros aux = insertar_ordenado(restoListaEnteros(lista), elem);
		agregarListaEnteros(aux, primeroListaEnteros(lista));
		return aux;
	}
}

ListaEnteros ordenar_lista (ListaEnteros lista) {
	if (esVaciaListaEnteros(lista))
		return lista;
	else
		return insertar_ordenado(ordenar_lista(restoListaEnteros(lista)), primeroListaEnteros(lista));
}

/* compara si l1 = l2 */
int comparar_listas(ListaEnteros l1, ListaEnteros l2) {
	if (esVaciaListaEnteros(l1) && esVaciaListaEnteros(l2))
		return CHECK_OK;
	else if (esVaciaListaEnteros(l1) || esVaciaListaEnteros(l2))
		return CHECK_CONJUNTOS_DISTINTOS;
//	else if (a != b)
	else if (primeroListaEnteros(l1) != primeroListaEnteros(l2))
		return CHECK_CONJUNTOS_DISTINTOS;
	else
		return comparar_listas(restoListaEnteros(l1), restoListaEnteros(l2));
}


int check_lista (ListaEnteros sol, ListaEnteros posibleSol) {
	ListaEnteros solOrdenada = ordenar_lista(sol);
	ListaEnteros posibleSolOrdenada = ordenar_lista(posibleSol);
	return comparar_listas(solOrdenada, posibleSolOrdenada);
}
