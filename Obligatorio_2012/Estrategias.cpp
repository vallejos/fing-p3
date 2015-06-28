/* 4580768 3797928 4392392 */

#include <stdlib.h>
#include "Zona.h"
#include "Ciudad.h"
#include "ListaEnteros.h"
#include "ColaEnteros.h"

//Estructura para almacenar un camino
struct Camino
{
	//indica la cantidad de elementos en la secuencia de zonas del camino
	int cantZonas;

	//arreglo que contiene la secuencia de los identificadores
	//de las zonas por las que pasa el camino
	int* zonas;

	//zonas[0] es el origen del camino, zonas[cantZonas-1] es el destino del camino
};

Camino* centroEnvioMasCercano(Ciudad* c, int idZona){
// Devuelve el camino entre idZona y el centro de envio mas cercano.
// En caso que no exista un camino que cumpla la condicion, retorna cantZonas igual a 0
// y zonas igual a NULL.
// Precondicion: 0 <= idZona < cantZonasCiudad(c);
// Precondicion: La Ciudad c ya fue creada.
	int n=cantZonasCiudad(c);
	int* marcados=new int[n];   // Marcas de zonas visitadas
	int* padres=new int[n];     // Array que relaciona una zona con su padre padres[hijo]
	for (int i=0; i<n; i++){
		marcados[i]=0;
		padres[i]=0;
	}
	Camino* cam = new Camino;
	cam->cantZonas = 0;
	cam->zonas = NULL;
	bool encontrado = false;    //Indica si encontramos un centro de envio
	ColaEnteros Q = crearColaEnteros();
	encolarColaEnteros(Q,idZona);
	marcados[idZona]=1;
	int nivel = 0;              //Cuenta la profundidad del recorrido para conocer la cantidad de zonas del camino
	int nodosTotal = 1;
	int centro;
	while ((!esVaciaColaEnteros(Q))&&(!encontrado)){
		int nodosNivel=0;
		for (int k=1; k<=nodosTotal; k++){
			int u =desencolarColaEnteros(Q);
			Zona* actual = obtenerZonaCiudad(c,u);
			if (tieneCentroDeEnvio(actual)){
				encontrado=true;
				centro=u;
			}
			ListaEnteros lAdy = obtenerAdyacentesZonaCiudad(c,u);
			while ((!esVaciaListaEnteros(lAdy))&&(!encontrado)){
				int w = primeroListaEnteros(lAdy);
				nodosNivel++;
				padres[w]=u;
				marcados[w]=1;
				encolarColaEnteros(Q,w);
				lAdy=restoListaEnteros(lAdy);
			}
		}
		nodosTotal=nodosNivel;
		nivel++;
	}
	if (!esVaciaColaEnteros(Q)){
		destruirColaEnteros(Q);
	}
	if (encontrado){             //Construimos el camino utilizando la estructura auxiliar padres y el nivel de prof del recorrido
		cam->cantZonas=nivel;
		cam->zonas= new int[nivel];
		while (centro!=idZona){
			cam->zonas[nivel-1]=centro;
			nivel--;
			centro=padres[centro];
		}
		cam->zonas[nivel-1]=centro;
	}
	delete []marcados; //Liberamos memoria
	delete []padres;
	return cam;
}

ListaEnteros zonasDeInfluencia(Ciudad* c, int idZona, int n){
// Devuelve las zonas que se encuentran a una distancia menor o igual a n de idZona.
// Precondicion: 0 <= idZona < cantZonasCiudad(c);
// Precondicion: tieneCentroDeEnvio(idZona)
// Precondicion: La Ciudad c ya fue creada.
	ListaEnteros inf = crearListaEnteros();
	int cantZonas=cantZonasCiudad(c);
	int* marcados=new int[cantZonas]; //Marcas de vertices visitados
	for (int i=0; i<cantZonas; i++){
		marcados[i]=0;
	}
	if (n==0) {
		agregarListaEnteros(inf,idZona);
	} else {
		ColaEnteros Q = crearColaEnteros();
		encolarColaEnteros(Q,idZona);
		marcados[idZona]=1;
		int nivel = 0;                    //Contamos la cantidad de nodos por nivel y el nivel de profundidad del recorrido BFS
		int nodosTotal = 1;
		while ((!esVaciaColaEnteros(Q))&&(nivel<=n)) {  //Recorremos en BFS hasta cubrir el grafo o llegar al nivel de profundidad dado
			int nodosNivel = 0;
			for (int k=1; k<=nodosTotal; k++) {
				int u = desencolarColaEnteros(Q);
				agregarListaEnteros(inf,u);
				ListaEnteros lAdy = obtenerAdyacentesZonaCiudad(c, u);
				while (!esVaciaListaEnteros(lAdy)) {
					int w = primeroListaEnteros(lAdy);
					lAdy = restoListaEnteros(lAdy);
					if (marcados[w] != 1) {
						marcados[w] = 1;
						encolarColaEnteros(Q, w);
						nodosNivel++;
					}
				}
			}

			nodosTotal = nodosNivel;
			nivel++;
		}

		if (!esVaciaColaEnteros(Q))
			destruirColaEnteros(Q);
	}
	delete []marcados; //Liberamos memoria
	return inf;
}

//Recorrido DFS para zonas exclusivas, mantiene las marcas del procedimiento principal, modifica la lista aux
void rec_DFS (Ciudad* c, int idZona, ListaEnteros &aux, int* &marcados) {
	marcados[idZona]=1;
	agregarListaEnteros(aux, idZona);

	ListaEnteros lAdy = obtenerAdyacentesZonaCiudad(c, idZona);

	while (!esVaciaListaEnteros(lAdy)) {
		int w = primeroListaEnteros(lAdy);
		lAdy = restoListaEnteros(lAdy);
		if (marcados[w] != 1) {
			rec_DFS(c, w, aux, marcados);
		}
	}
}


ListaEnteros  zonasExclusivas(Ciudad* c, int idZona){
// Una zona es exclusiva de un centro de envio cuando no es posible acceder
// a dicha zona desde otro centro de envío sin pasar por el. En este caso
// no importa la distancia de la zona al centro de envío, sino si esta es
// accesible desde el centro.
// Devuelve un listado de las zonas exclusivas de idZona
// Precondicion: 0 <= idZona < cantZonasCiudad(c);
// Precondicion: tieneCentroDeEnvio(idZona)
// Precondicion: La Ciudad c ya fue creada.
	int cantZonas = cantZonasCiudad(c);
	int* marcados = new int[cantZonas];  //Marcas de zonas visitadas.
	for (int i=0; i<cantZonas; i++){
		marcados[i]=0;
	}
	ListaEnteros pend = crearListaEnteros();  //Lista temporal para verificar la exclusividad
	ListaEnteros exc = crearListaEnteros();   // Lista definitiva de zonas exclusivas
	agregarListaEnteros(exc,idZona);
	marcados[idZona]=1;
	ListaEnteros lAdy = obtenerAdyacentesZonaCiudad(c,idZona);
	while (!esVaciaListaEnteros(lAdy)){
		int w = primeroListaEnteros(lAdy);
		lAdy = restoListaEnteros(lAdy);
		if (marcados[w] != 1) {  //Si no visitados
			rec_DFS(c, w, pend, marcados);
			bool tieneCentro=false;
			ListaEnteros aux = pend;
			while ((!esVaciaListaEnteros(aux)) && (!tieneCentro)) { //Verificamos la existencia de centros en las posibles zonas exclusivas
				int id = primeroListaEnteros(aux);
				aux = restoListaEnteros(aux);
				Zona* u = obtenerZonaCiudad(c,id);
				tieneCentro = tieneCentroDeEnvio(u);
			}
			aux = pend;
			if (!tieneCentro) {  //En caso de no haber centros agregamos cada zona a la lista definitiva
				while (!esVaciaListaEnteros(aux)) {
					int a = primeroListaEnteros(aux);
					agregarListaEnteros(exc,a);
					aux=restoListaEnteros(aux);
				}
			}
			aux = NULL;
			destruirListaEnteros(pend);
		}
	}
	delete []marcados; //Liberamos memoria
	return exc;
}
