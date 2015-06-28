/* 4345244 3797928 4577086 */

#include "ABB_T.h"
#include "ListaOrd.h"
#include "Pila.h"
#include "Deposito.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include "ColaPrioridad.h"

int const tamFrecuente = 10;

// estructura para Deposito
struct AuxDeposito{
	int cantArt;
	ABB_T palabrasClave;
	ListaOrd * referencias;
	ColaPrioridad * palabrasFrecuentes; 		// la prioridad es la frecuencia de esa palabra
};
typedef AuxDeposito * Deposito;

/*	Devuelve un deposito con 'cantidad_articulos' articulos, sin referencias. */
Deposito crearDeposito (int cantidad_articulos) {
    Deposito dep = new AuxDeposito;
    dep->cantArt = cantidad_articulos;
    crearABB(dep->palabrasClave);
	
	// inicializamos memoria para las aristas
    dep->referencias = new ListaOrd[cantidad_articulos];
    for (int i = 0; i<cantidad_articulos; i++) {
        crearLista(dep->referencias[i]);
    }
	
	// inicializamos memoria para las palabras mas frecuentes
    dep->palabrasFrecuentes = new ColaPrioridad[cantidad_articulos];
    for (int i = 0; i<cantidad_articulos; i++) {
        crearColaPrioridad(dep->palabrasFrecuentes[i], tamFrecuente);
    }
    return dep;
}

/*	Establece en 'd' una referencia desde 'a1' hacia 'a2'. 
	La operación se debe realizar en promedio en O(r),
	siendo r la cantidad de referencias del artículo 'a1'.
	Precondición: 0 <= a1,a2 < cantidad de artículos de 'd'. */
void agregarReferencia (Deposito &d, int a1, int a2){
    insLista(a2,d->referencias[a1]);
}

/*	Inserta la palabra clave 'p' en 'd' si 'p' no existe en 'd'.
	En otro caso no hace nada.
	La operaci�n se debe realizar en promedio en O(log C),
	siendo C la cantidad total de palabras clave. */
void insertarPalabraClave (Deposito &d, char * p){
    agregarABB(d->palabrasClave,p);
}

//FUNCION AUXILIAR
bool estarecur(ABB_T abb, char * p){
    if (esVacioABB(abb))
        return false;
	else if (strcmp(palabraClaveABB(abb),p) <0) {
        abb = arbolDerecho(abb);
        return estarecur(abb,p);
  } else if (strcmp(palabraClaveABB(abb),p)>0) {
        abb = arbolIzquierdo(abb);
        return estarecur(abb,p);
  } else
     return true;
}

/*	Devuelve 'true' si la palabra clave 'p' existe en 'd',
	'false' en otro caso.
	La operación se debe realizar en promedio en O(log C),
	siendo C la cantidad total de palabras clave. */
bool estaPalabraClave (Deposito d, char * p){
    return estarecur(d->palabrasClave,p);
}

//FUNCION AUXILIAR
ABB_T buscoPalabraClave(ABB_T palabrasClave, char * p)
{
	if (strcmp(p,palabraClaveABB(palabrasClave))<0){
		palabrasClave = arbolIzquierdo(palabrasClave);
		return buscoPalabraClave(palabrasClave,p);}
	else if (strcmp(p,palabraClaveABB(palabrasClave))>0){
		palabrasClave = arbolDerecho(palabrasClave);
		return buscoPalabraClave(palabrasClave,p);}
	else
		return palabrasClave;
}

/*	Incluye a 'p' en las palabras claves del art�culo 'a' y a 'a' entre los
	art�culos de 'p'. El par�metro 'c' corresponde a la cantidad de veces
	que aparece 'p' en 'a'. Si ya hay 10 palabras clave asociadas a 'a' y
	alguna de las palabras asociadas a 'a' ocurre menos de 'c' veces,
	entonces 'p' sustituye a la que tiene menos en la asociaci�n con 'a'
	(si m�s de una cumple esa condici�n sustituye a cualquiera de ellas).
	La operaci�n se debe realizar en promedio en O(log C + art_prom),
	siendo C la cantidad total de palabras clave y art_prom la cantidad
	promedio de art�culos de las palabras clave.
    Precondici�n: c > 0.
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'.
    Precondici�n: existe la palabra clave 'p' en 'd'.
    Precondici�n: no hay asociaci�n entre el art�culo 'a' y la palabra
    clave 'p'. */
void asociarArticuloPalabraClave (Deposito &d, int a, char * p, int c){
	ABB_T pc, aux;
	pc = buscoPalabraClave(d->palabrasClave,p);
	asociarArticuloABB(pc,p,a);
	aux = encolarColaPrioridad(d->palabrasFrecuentes[a],pc,c);
	if (aux != NULL) {
		desasociarArticuloABB(aux,palabraClaveABB(aux),a);
    }
}

/*	Devuelve 'true' si hay asociaci�n entre el art�culo 'a' y la palabra
	clave 'p', 'false' en otro caso.
	La operaci�n se debe realizar en promedio en O(1).
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'.
    Precondici�n: existe la palabra clave 'p' en 'd'. */
bool estaAsociadoArticuloPalabraClave (Deposito d, int a, char * p){
    if (esVaciaColaPrioridad(d->palabrasFrecuentes[a]))
        return false;
    else if (strcmp(p, (palabraClaveABB(maximoColaPrioridad(d->palabrasFrecuentes[a]))))==0)
        return true;
    else {
        ColaPrioridad aux = copiarColaPrioridad(d->palabrasFrecuentes[a]);
        while (!esVaciaColaPrioridad(aux)) {
            if (strcmp(p , (palabraClaveABB(maximoColaPrioridad(aux))))==0)
                return true;
        removerMaximoColaPrioridad(aux);
        }
        return false;
    }
}

/*	Devuelve el �rbol cuya ra�z es la palabra clave que aparece
    m�s veces en 'a'.
	La operaci�n se debe realizar en promedio en O(1).
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'.
    Precondici�n: el art�culo 'a' tiene palabras clave asociadas. */
ABB_T claveMasFrecuente (Deposito d, int a){
   return maximoColaPrioridad(d->palabrasFrecuentes[a]);
}

/*  Devuelve una lista con los art�culos que tienen a 'p' como palabra clave.
	La operaci�n se debe realizar en promedio en O(log C), siendo C la
	cantidad total de palabras clave.
    Precondici�n: existe la palabra clave 'p'. */
ListaOrd articulosConPalabraClave (Deposito d, char * p){
    return listaArticulosABB(buscoPalabraClave(d->palabrasClave,p));
}

/*  Imprime las palabras clave de 'a' y su cantidad de ocurrencias
    (separados por un espacio) en orden descendente seg�n su frecuencia,
    una por l�nea (entre las que tengan igual frecuencia se imprimen en
    cualquier orden).
    Por ejemplo, si se tiene la	palabra clave "hola" con cantidad 3 y la
    palabra clave "chau" con cantidad 5, se debe imprimir:
	chau 5
	hola 3
	La operaci�n se debe realizar en promedio en O(1).
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'. */
void imprimirPalabrasClaveEnArticulo (Deposito d, int a){
    ColaPrioridad copia;
	copia= copiarColaPrioridad(d->palabrasFrecuentes[a]);
    while (!esVaciaColaPrioridad(copia))
	{
        printf("%s %i\n",palabraClaveABB(maximoColaPrioridad(copia)),prioridadMaximoColaPrioridad(copia));
        removerMaximoColaPrioridad(copia);
    }
    destruirColaPrioridad(copia);
}

/*	Devuelve la lista ordenada de las referencias de 'a'.
	La operaci�n se debe realizar en promedio en O(1).
	Precondici�n: 0 <= a < cantidad de art�culos de 'd'. */
ListaOrd referencias (Deposito d, int a){
  return (d->referencias[a]);
}

/*	Devuelve la cantidad de art�culos de 'd'.
	La operaci�n se debe realizar en promedio en O(1). */
int cantidadArticulos (Deposito d){
  return (d->cantArt);
}


// FUNCION AUXILIAR
void dfsrecur(Deposito d,int i,int * visitados,Pila & p){
  ListaOrd laux = d->referencias[i];
  visitados[i]=1;
  while (!esVaciaLista(laux)) {
    int j = primeroLista(laux);
    if (!visitados[j])
      dfsrecur(d,j,visitados,p);
    restoLista(laux);
  }
  apilar(i,p);
}

/*	Devuelve una pila con todos los art�culos de 'd' tras una recorrida dfs.
	Los apila en postorden. Cuando haya que decidir entre m�s de un art�culo
	a visitar, se debe elegir el de menor n�mero.
	La operaci�n se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los art�culos de 'd' y 'n' la cantidad de
	art�culos de 'd'. */
Pila dfsPostOrden (Deposito d){
  Pila p;
  crearPila(d->cantArt,p);
  int * visitados = new int[d->cantArt];
  for (int i=0; i<d->cantArt; i++){
     visitados[i]=0;
  } 
  for (int i = 0;i<(d->cantArt);i++){
     if (!visitados[i])
       dfsrecur(d,i,visitados,p);
  }
  return p;
}

/*	Devuelve un dep�sito igual a 'd' pero con las referencias en sentido inverso.
	La operaci�n se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los art�culos de 'd' y 'n' la cantidad de
	art�culos de 'd'. */
Deposito transpuesto (Deposito d){
	Deposito trans = crearDeposito(d->cantArt);
	for (int i=0; i<d->cantArt; i++)  {
		ListaOrd ltrans;
		ltrans= d->referencias[i];
		while (!esVaciaLista(ltrans))
		{
			int x =primeroLista(ltrans);
			agregarReferencia(trans,x,i);
			restoLista(ltrans);
		}
	}
	return trans;
}

/*	Modifica 'colecciones' asignando 'id' a los art�culos cuyo actual valor es
	-1 y son accesibles desde 'a' siguiendo referencias por art�culos cuyo
	actual valor tambi�n es -1.
	La operaci�n se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los art�culos de 'd' y 'n' la cantidad de
	art�culos de 'd'.
	Precondici�n: el tama�o de colecciones es igual a la cantidad de art�culos
	de 'd'.
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'.
	Precondici�n: colecciones[a] == id. */
void nuevosAccesibles (Deposito d, int a, int id, int * &colecciones){
	ListaOrd laux = d->referencias[a];
	while (!esVaciaLista(laux)){
		int x = primeroLista(laux);
		if (colecciones[x]==-1)
		{
			colecciones[x]=id;
			nuevosAccesibles(d,x,id,colecciones);
		}
		restoLista(laux);
	}
}

/*  NUEVO  */
/*	Devuelve la cantidad asociada a la palabra clave 'p' en el artículo 'a'.
    Precondición: estaAsociadoArticuloPalabraClave (d, a, p). */
int cantidadPalabraClaveEnArticulo (Deposito d, int a, char * p){
	int cantidad;
	ABB_T pc;
	//funcion auxiliar implementada en lineas 82 a 92
	pc = buscoPalabraClave(d->palabrasClave, p); 
	//busco la prioridad de esa palabra clave en la cola de prioridad del articulo a
	cantidad = prioridadColaPrioridad(d->palabrasFrecuentes[a], pc); 
	//retorno la cantidad asociada a 'p' en 'a'
	return cantidad;
}

/*	Libera la memoria asignada a 'd'. */
void destruirDeposito (Deposito &d){
    for (int i=0; i<(d->cantArt); i++)
    {
       destruirLista(d->referencias[i]);
       destruirColaPrioridad(d->palabrasFrecuentes[i]);
    }
    delete [] d->referencias;
    delete [] d->palabrasFrecuentes;
    destruirABB(d->palabrasClave);
    delete d;
	d = NULL;
}
