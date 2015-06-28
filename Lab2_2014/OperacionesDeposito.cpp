/* 4345244 3797928 4577086 */

#include "Deposito.h"
#include "ListaOrd.h"
#include "Cola.h"
#include "ABB_T.h"
#include "Pila.h"
#include <stdio.h>
#include <string.h>
#include <limits.h>


//FUNCI�N AUXILIAR
int SeparacionArticulosBFS(Deposito d, int articulo, bool* articulos_considerados) {
//inicializamos variables a utilizar
    Cola Q;
    int u,w;
    int separacion[cantidadArticulos(d)];
    int maximo = 0;
    int* visitados;
    int consideradosVisitados = 0;
    int cantidadConsiderados = 0;
//contamos la cantidad de articulos considerados
    for (int x=0; x<cantidadArticulos(d); x++) {
        if (articulos_considerados[x]) {
            cantidadConsiderados++;
        }
    }
//inicializamos el vector de visitados en 0
    visitados = new int[cantidadArticulos(d)];
    for (int j=0; j<cantidadArticulos(d); j++) {
        visitados[j] = 0;
    }
    crearCola(Q);
    visitados[articulo] = 1;
    encolar(articulo, Q);
//inicializamos el vector separacion en 0 en el articulo dado,
//y en INT_MAX si es un articulo considerado diferente del dado 
    for (int j=0; j<cantidadArticulos(d); j++) {
        if (articulos_considerados[j]) {
            if (j != articulo) {
                separacion[j] = INT_MAX;
            } else {
                separacion[j] = 0;
            }
        }
    }
//hacemos recorrida BFS para encontrar las separaciones entre
//cada articulo considerado y el dado
    while (!esVaciaCola(Q)) {
        w = frente(Q);
        desencolar(Q);
        ListaOrd adyacentes = referencias(d, w);
        while (!esVaciaLista(adyacentes) && (consideradosVisitados<cantidadConsiderados)) {
            u = primeroLista(adyacentes);
            restoLista(adyacentes);
            if (!visitados[u]) {
                visitados[u] = true;
                separacion[u] = separacion[w]+1;
                if (articulos_considerados[u]) {
                    consideradosVisitados++;
 
                    if (separacion[u]>maximo) {
                        maximo = separacion[u];
                    }

                }
                encolar(u, Q);
            }
        }
    }
// elijo el mayor de las separaciones y lo retorno en maximo
    int maxTemp=0;
    for (int x=0; x<cantidadArticulos(d); x++) {
        if (articulos_considerados[x]) {
            if (separacion[x]>maxTemp) {
                maxTemp = separacion[x];
            }
        }
    }
    if (maximo < maxTemp) {
        maximo = maxTemp;
    }
    return maximo;
}

/*	Devuelve los grados de separaci�n entre un conjunto de art�culos
    considerados. El art�culo n�mero i es considerado si y s�lo si
    articulos_considerados[i] == true.
    De no poder llegar mediante referencias desde un art�culo a otro,
    transitando solo por art�culos considerados,
    se debe retornar INT_MAX, incluido de limits.h
    De haber uno o menos art�culos considerados retornar 0.
	La operaci�n se debe realizar en peor caso en O(n . m ), sinedo 'm' la
	cantidad de referencias entre los art�culos de 'd' y 'n' la cantidad de
	art�culos de 'd'.	Precondici�n: el tama�o de 'articulos_considerados' es igual a
	la cantidad de art�culos de 'd'. */
int gradosDeSeparacion (Deposito d, bool * articulos_considerados)
{
    int maxTotal = 0;
    int maxSep = 0;
//para cada articulo busco su maxima separacion con la funcion auxiliar
//retorno el maximo de �stos
    for (int i=0; i<cantidadArticulos(d); i++) {
        if (articulos_considerados[i] == true) {
            maxSep = SeparacionArticulosBFS(d, i, articulos_considerados);
            if (maxSep > maxTotal) {
                maxTotal = maxSep;
            }
            maxSep = 0;
        }
    }
    return maxTotal;
}

/*	Devuelve las colecciones de 'd', cada una en una lista diferente.
	La salida de esta operaci�n debe ser un array en donde
	para la posici�n i se encuentra el n�mero de colecci�n a la que
	pertenece el art�culo i.

# Formato de la salida

	Las colecciones se identifican con enteros de 0 a (k-1),
	siendo k la cantidad de colecciones. Una colecci�n A tiene
	un identificador menor que otra colecci�n B si y s�lo si
	hay un art�culo de A cuyo n�mero es menor que todos los
	n�meros de los art�culos de B.

	Por ejemplo, dado el dep�sito que tiene los
	art�culos 0, 1, 2 y 3, cuyas colecciones son:

	A = {1}
	B = {0, 2}
	C = {3}

	La salida debe ser: 0 1 0 2

	Observar que 0 2 0 1, 1 0 1 2, 1 2 1 0, 2 0 2 1, 2 1 2 0
	tambi�n agrupan correctamente las colecciones,
	pero no cumplen la forma de orden solicitada.

	La operaci�n se debe realizar en peor caso en O(m + n), sinedo 'm' la
	cantidad de referencias entre los art�culos de 'd' y 'n' la cantidad de
	art�culos de 'd'. */
int * colecciones (Deposito d)
{
// realizamos las colecciones:
	int * colecciones_dep = new int[cantidadArticulos(d)];
	for (int i=0; i<cantidadArticulos(d); i++) {
            colecciones_dep[i] = -1;
	}
	Deposito d_transpuesto = transpuesto(d);
	Pila pilaDFS = dfsPostOrden(d);
	int coleccion_num = 0;
    while (!esVaciaPila(pilaDFS)){
	    int primero = cima(pilaDFS);
		if (colecciones_dep[primero]==-1){
			colecciones_dep[primero] = coleccion_num;
			nuevosAccesibles(d_transpuesto, primero, coleccion_num, colecciones_dep);
			coleccion_num ++;
		}
		desapilar(pilaDFS);
    }
// acomodamos salida
	int * colecciones_dep_return = new int[cantidadArticulos(d)];
	for (int i=0; i<cantidadArticulos(d); i++) {
            colecciones_dep_return[i] = -1;
	}
	coleccion_num = 0;
	for (int i=0; i<cantidadArticulos(d); i++) {
		if (colecciones_dep_return[i]==-1){
			colecciones_dep_return[i]= coleccion_num;
			for (int j=0; j<cantidadArticulos(d); j++) {
				if (colecciones_dep[i]==colecciones_dep[j])
					colecciones_dep_return[j]= coleccion_num;
			}
			coleccion_num++;
		}
	}
	return (colecciones_dep_return);
}

/*	Devuelve la cantidad de art�culos de 'd' cuya palabra clave m�s
	frecuente es 'key', siendo 'key' la palabra clave m�s frecuente del
	art�culo 'a' (si m�s de una cumple esa condici�n se elije cualquiera de
	ellas).
	La operaci�n se debe realizar, en promedio, en O(c1), siendo 'c1' la
	cantidad de art�culos asociados a 'key'.
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'.
    Precondici�n: el art�culo 'a' tiene al menos una palabra clave. */
int cantidadArticulosConMismaPalabraClaveMasFrecuente (Deposito d, int a)
{
	ABB_T arbol_palabras, arbol_aux;
	int cantidad, articulo_aux;
	ListaOrd lista_articulos;
	arbol_palabras = claveMasFrecuente(d, a); // busco el arbol
	lista_articulos = listaArticulosABB(arbol_palabras); // busco la lista de articulos
	cantidad = 0;
	while (!esVaciaLista(lista_articulos))
		{
		articulo_aux = primeroLista(lista_articulos); // saco el primero de la lista
		arbol_aux = claveMasFrecuente(d, articulo_aux); // busco el arbol
		if (strcmp(palabraClaveABB(arbol_aux), palabraClaveABB(arbol_palabras))==0)
			cantidad++;
		restoLista(lista_articulos);
		}
	return cantidad;
}

/*	Devuelve la cantidad de art�culos de 'd' hacia los que tiene referencia
	directa el art�culo 'a', y est�n asociados a la palabra clave m�s
	frecuente de 'a' (si m�s de una cumple esa condici�n se elije cualquiera de
	ellas).
	La operaci�n se debe realizar, en promedio, en O(r) siendo r la cantidad de
	referencias que hay en 'a'.
    Precondici�n: 0 <= a < cantidad de art�culos de 'd'.
    Precondici�n: el art�culo 'a' tiene al menos una palabra clave. */
int referenciasConMismaPalabraMasFrecuente (Deposito d, int a)
{
	ABB_T arbol_palabras;
	int cantidad, articulo_aux;
	char* palabra_mas_frecuente;
	ListaOrd lista_articulos;
	arbol_palabras = claveMasFrecuente(d, a);
	palabra_mas_frecuente = palabraClaveABB(arbol_palabras);
	lista_articulos = referencias(d, a);
	cantidad = 0;
	while (!esVaciaLista(lista_articulos))
		{
		articulo_aux = primeroLista(lista_articulos);
		if (estaAsociadoArticuloPalabraClave(d, articulo_aux, palabra_mas_frecuente))
			cantidad++;
		restoLista(lista_articulos);
		}
	return cantidad;
}

/**
 * FUNCIONES AUXILIARES PARA LAB.2
 */

/* Retorna la suma de apariciones de la 'palabra' en todos los articulos de la 'coleccion' 
Pre-Condicion: perteneceTodos(d, arregloColecciones, coleccion, palabra) */
int sumaApariciones(Deposito d, int coleccion, int * arregloColecciones, char * palabra) {
    int sumaTotal = 0;
	int cantidad = cantidadArticulos(d);
    for (int i = 0; i < cantidad; i++) {
        if (arregloColecciones[i] == coleccion) {
            sumaTotal = sumaTotal + cantidadPalabraClaveEnArticulo(d, i, palabra);
        }
    }
    return sumaTotal;
}

/* Retorna true si la 'palabra' pertenece a todos los articulos de la 'coleccion' en el deposito 'd'
y false en caso contrario */
bool perteneceTodos(int coleccion, int * arregloColecciones, char * palabra, Deposito d) {
    bool pertenece = true;
    int i = 0;
	int cant = cantidadArticulos(d);
    while (pertenece && i < cant) {
		if ((arregloColecciones[i] == coleccion) && (!estaAsociadoArticuloPalabraClave(d, i, palabra))) {
			pertenece = false;
		}
		i++;
    }
    return pertenece;
}

/* buscamos la coleccion teniendo en cuenta la condicion para podar */
void identificarColeccionesConPoda (int paso, int * & tuplaBT, int suma, int & sumaOptima, bool * marcados,int * arregloColecciones, 
	int * arregloValores, int valorRestante, Deposito d, char ** palabras_identificadoras, int cantidad_palabras_identificadoras, 
	char ** &identificaciones, int tamanio_arreglo) {

	int proxPaso, valorProxPaso, i;
	int sumaPosible = suma + valorRestante;

	// si la suma no va a ser >= que la optima, podamos
	if  (sumaPosible >= sumaOptima) {
		if (paso == cantidad_palabras_identificadoras) {
			for (i = 0; i < tamanio_arreglo; i++) {
				identificaciones[i] = NULL;
			}

			for (i = 0; i< cantidad_palabras_identificadoras; i++) {
				if (tuplaBT[i] != -1) {
					identificaciones[tuplaBT[i]] = palabras_identificadoras[i];
				}
			}

			sumaOptima = suma;
		} else {
			for (i = 0; i < tamanio_arreglo; i++) {
				if (!marcados[i] && perteneceTodos(i, arregloColecciones, palabras_identificadoras[paso], d)) {
					tuplaBT[paso] = i;
					marcados[i] = true;
					proxPaso = paso + 1;
					sumaPosible = suma + sumaApariciones(d, i, arregloColecciones, palabras_identificadoras[paso]);
					valorProxPaso = valorRestante - arregloValores[paso];
					identificarColeccionesConPoda(proxPaso, tuplaBT, sumaPosible, sumaOptima, marcados, arregloColecciones, arregloValores, valorProxPaso, d, palabras_identificadoras, cantidad_palabras_identificadoras, identificaciones, tamanio_arreglo);
					marcados[i] = false;
				}
			}

			tuplaBT[paso] = -1;
			proxPaso = paso + 1;
			valorProxPaso = valorRestante - arregloValores[paso];
			identificarColeccionesConPoda(proxPaso, tuplaBT, suma, sumaOptima, marcados, arregloColecciones, arregloValores, valorProxPaso, d, palabras_identificadoras, cantidad_palabras_identificadoras, identificaciones, tamanio_arreglo);
		}
	}
}

int obtenerTamanioArreglo(Deposito d, int * arregloColecciones) {
	int tamanio = 0;
	for (int i = 0; i < cantidadArticulos(d); i++) {
		if (arregloColecciones[i] > tamanio) {
			tamanio = arregloColecciones[i];
		}
	}
	tamanio ++;
	return tamanio;
}
 
/**
 * LAB.2
 */

/*	Asocia palabras identificadoras a las colecciones, buscando maximizar
	las suma de las apariciones de esas palabras en los art�culos de las
	colecciones.
	Cada colecci�n tiene hasta una palabra identificadora asignada y
	una palabra identificadora tiene hasta una colecci�n asignada. Para que
	haya asignaci�n entre una palabra identificadora 'p' y una colecci�n 'c',
	'p' debe ser palabra identificadora de cada uno de los art�culos de 'c'.
	La operaci�n devuelve un array de palabras identificadoras, en donde en la
	posici�n 'i' se tiene la palabra identificadora asociada a la colecci�n
	'i', seg�n la numeraci�n que se usa en la operaci�n colecciones. Si una
	colecci�n no tiene palabra identificadora, se le asocia NULL.
	La salida de esta funci�n debe estar en el arreglo 'identificaciones', y
	en 'tamanio_arreglo' debe estar su tama�o.
	De haber m�s de una soluci�n �ptima, devolver cualquiera de ellas.
	Precondici�n: en 'palabras_identificadoras' hay
	'cantidad_palabras_identificadoras' elementos.
	Precondici�n: para todo 0 <= i < cantidad_palabras_identificadoras se
	cumple estaPalabraClave (d, palabras_clave [i]) */
void identificarColecciones (Deposito d, char* * palabras_identificadoras, int cantidad_palabras_identificadoras, char ** &identificaciones, 
	int &tamanio_arreglo) {

	int sumaOptima = 0;
	int i, j, cant;

	// obtenemos las colecciones del deposito
	int * arregloColecciones = colecciones(d);

	tamanio_arreglo = obtenerTamanioArreglo(d, arregloColecciones);
	
	identificaciones = new char * [tamanio_arreglo];

	//A cada palabra se le asigna el maximo valor posible
	int * arregloValoresPalabras = new int[cantidad_palabras_identificadoras];
	
	for (i = 0; i < cantidad_palabras_identificadoras; i++) {
		arregloValoresPalabras[i] = 0;
		for (j = 0; j < tamanio_arreglo; j++) {
			if (perteneceTodos(j, arregloColecciones, palabras_identificadoras[i], d)) {
				cant = sumaApariciones(d, j, arregloColecciones, palabras_identificadoras[i]);
				if (cant > arregloValoresPalabras[i]) {
					arregloValoresPalabras[i] = cant;
				}
			}
		}
	}

	// inicializamos marcados en falso
	bool * marcados = new bool[tamanio_arreglo];
	for (i = 0; i < tamanio_arreglo; i++) {
		marcados[i] = false;
	}

	// creamos la tupla
	int * tuplaBT = new int [cantidad_palabras_identificadoras];

	int valorRestantePalabras = 0;
	for (i = 0; i < cantidad_palabras_identificadoras; i++) {
		valorRestantePalabras += arregloValoresPalabras[i];
	}

	identificarColeccionesConPoda(0, tuplaBT, 0, sumaOptima, marcados, arregloColecciones, arregloValoresPalabras, valorRestantePalabras, d, palabras_identificadoras, cantidad_palabras_identificadoras, identificaciones, tamanio_arreglo);

	delete tuplaBT;
	delete [] marcados;
	delete [] arregloValoresPalabras;
    delete [] arregloColecciones;

	tuplaBT = NULL;
	marcados = NULL;
	arregloValoresPalabras = NULL;
	arregloColecciones = NULL;
}
