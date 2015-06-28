/* 4345244 3797928 4577086 */

#include "ABB_T.h"
#include "ColaPrioridad.h"
#include <stdlib.h>
#include <limits.h>

// estructura para la Cola Prioridad
struct AuxColaPrioridad {
    ABB_T* arreglo;     // arreglo de ABB_T
    int* prioridad;     // arreglo de prioridades
    int cantidad;       // cantidad de elementos ingresados en ColaPrioridad
    int tamanio;        // maxima cantidad de elementos permitidos en ColaPrioridad
};
typedef AuxColaPrioridad * ColaPrioridad;

/*	Devuelve en 'cp' una cola de prioridad vacía,
	que podrá contener hasta 'tamanio' elementos.
	Precondición: tamanio > 0. */
void crearColaPrioridad (ColaPrioridad &cp, int tamanio){
   cp= new AuxColaPrioridad;
   cp->prioridad = new int[tamanio+1];
   cp->arreglo = new ABB_T[tamanio+1];
   cp->cantidad = 0;
   cp->tamanio = tamanio;
}

/*auxiliar para encolarColaPrioridad. Filtrado ascendente*/
void agrega(ColaPrioridad &cp, ABB_T abb, int prio){
    cp->cantidad++;
    cp->arreglo[cp->cantidad]=abb;
    cp->prioridad[cp->cantidad]=prio;

	// ordenamos la cola
	int lugar = cp->cantidad;
    while(lugar > 1 && prio>cp->prioridad[lugar/2]){
        ABB_T temp;
        temp = cp->arreglo[lugar];
        cp->arreglo[lugar] = cp->arreglo[lugar/2];
        cp->arreglo[lugar/2] = temp;
        int inttemp;
        inttemp = cp->prioridad[lugar];
        cp->prioridad[lugar] = cp->prioridad[lugar/2];
        cp->prioridad[lugar/2] = inttemp;
        lugar = lugar/2;
    }
}

/*	Agrega a 'cp' el árbol 'abb' con prioridad 'prio' si la prioridad de
	alguno de sus árboles es menor que 'prio' (en cuyo caso, lo agrega luego de
	remover alguno de los árboles con mínima prioridad) o si 'cp' no está llena.
	En otro caso no hace nada.
	En caso de remover un árbol, lo devuelve como resultado de la llamada. En
	caso de no poder insertar el árbol 'abb' por ser peor en prioridad, la función
	retorna 'abb'. En otro caso, se devuelve NULL. */
ABB_T encolarColaPrioridad (ColaPrioridad &cp, ABB_T abb, int prio)
{
    if (cp->tamanio > cp->cantidad){
        agrega(cp,abb,prio);
        return NULL; // otro caso: devuelvo null 
    } else {
        int minprio = cp->prioridad[1];
        int minindice = 1;
        for (int x = 2; x <= cp->cantidad; x++) {
           if (cp->prioridad[x] < minprio) {
            minprio = cp->prioridad[x];
            minindice = x;
           }
        }
        if (prio > minprio) {
            ABB_T aux = cp->arreglo[minindice];
            cp->arreglo[minindice] = abb;
            cp->prioridad[minindice] = prio;
			
			//lo ubico en su lugar
            int lugar = minindice;
            while(lugar>1 && prio>cp->prioridad[lugar/2]) {
                ABB_T temp;
                temp= cp->arreglo[lugar];
                cp->arreglo[lugar] = cp->arreglo[lugar/2];
                cp->arreglo[lugar/2] = temp;
                int inttemp;
                inttemp = cp->prioridad[lugar];
                cp->prioridad[lugar] = cp->prioridad[lugar/2];
                cp->prioridad[lugar/2] = inttemp;
                lugar = lugar/2;
            }
            return aux;
        }
        else
            return abb;
    }
}

/*	Devuelve 'true' si 'cp' es vacía, 'false' en otro caso. */
bool esVaciaColaPrioridad (ColaPrioridad cp){
    return (cp->cantidad == 0);
}

/*	Devuelve 'true' si 'cp' está llena, 'false' en otro caso. */
bool esLlenaColaPrioridad (ColaPrioridad cp){   
   
   if (cp->cantidad == cp->tamanio)
      return true;
	else 
	   return false;
}

/*Devuelve 'true' si 'abb' se encuentra en 'cp', 'false' en otro caso. */
bool perteneceColaPrioridad (ColaPrioridad cp, ABB_T abb){
	int j = 1;
	// buscamos el elemento
    while (cp->arreglo[j]!=abb && j<=cp->tamanio)
	{
        j++;
    }
	if (j <= cp->tamanio)
		return true; // encontrado
	else 
		return false; // no encontrado
}

/*	Devuelve el árbol de 'cp' que tiene asignada mayor prioridad
	(si más de uno cumple esa condición devuelve cualquiera de ellos).
	Precondición: 'cp' no es vacía. */
ABB_T maximoColaPrioridad (ColaPrioridad cp){
	// al estar ordenada, el de mayor prioridad esta en la posicion 1
    return cp->arreglo[1];
}

/*	Devuelve la mayor prioridad de los árboles de 'cp'.
	Precondición: 'cp' no es vacía. */
int prioridadMaximoColaPrioridad (ColaPrioridad cp){
	// al estar ordenada, el de mayor prioridad esta en la posicion 1
    return cp->prioridad[1];
}

/*	Remueve de 'cp' el árbol de mayor prioridad
	(si más de uno cumple esa condición remueve cualquiera de ellos).
	Precondición: 'cp' no es vacía. */
void removerMaximoColaPrioridad (ColaPrioridad &cp){
    cp->arreglo[1] = cp->arreglo[cp->cantidad];
    cp->prioridad[1] = cp->prioridad[cp->cantidad];
    cp->cantidad--;
    bool terminar;
	int prioaux; ABB_T abbaux;
    terminar= false;
	int lugar = 1;
    while(terminar==false && 2*lugar <= cp->cantidad){
		// reordenamos los elementos
	    if (2*lugar+1 > cp->cantidad){
            if (cp->prioridad[2*lugar] > cp->prioridad[lugar]){
              abbaux=cp->arreglo[lugar];
              cp->arreglo[lugar] = cp->arreglo[2*lugar];
              cp->arreglo[2*lugar] = abbaux;
              prioaux=cp->prioridad[lugar];
              cp->prioridad[lugar] = cp->prioridad[2*lugar];
              cp->prioridad[2*lugar] = prioaux;
              lugar = 2*lugar;
            }
            else terminar=true;
        }
        else{
            if (cp->prioridad[2*lugar] > cp->prioridad[2*lugar+1]){
                if (cp->prioridad[2*lugar] > cp->prioridad[lugar]){
                    abbaux = cp->arreglo[lugar];
                    cp->arreglo[lugar] = cp->arreglo[2*lugar];
                    cp->arreglo[2*lugar] = abbaux;
                    prioaux = cp->prioridad[lugar];
                    cp->prioridad[lugar] = cp->prioridad[2*lugar];
                    cp->prioridad[2*lugar] = prioaux;
                    lugar = 2*lugar;
                }
                else terminar = true;
            }
            else
            {   if (cp->prioridad[2*lugar+1] > cp->prioridad[lugar]){
                    abbaux = cp->arreglo[lugar];
                    cp->arreglo[lugar] = cp->arreglo[2*lugar+1];
                    cp->arreglo[2*lugar+1] = abbaux;
                    prioaux = cp->prioridad[lugar];
                    cp->prioridad[lugar] = cp->prioridad[2*lugar+1];
                    cp->prioridad[2*lugar+1] = prioaux;
                    lugar = 2*lugar+1;
                }
                else terminar = true;
            }
        }
    }
}

/*	Devuelve una cola de prioridad con los mismos elementos de 'cp'	(comparte
	memoria). */
ColaPrioridad copiarColaPrioridad (ColaPrioridad cp){
    ColaPrioridad copiacola;
    crearColaPrioridad(copiacola,cp->tamanio);
    copiacola->cantidad = cp->cantidad;
	//agrego las prioridades y sus arboles
    for (int x = 1; x <= cp->cantidad; x++){
	    copiacola->prioridad[x] = cp->prioridad[x];
        copiacola->arreglo[x] = cp->arreglo[x];
    }
    return copiacola;
}

/*  NUEVO  */
/*	Devuelve la prioridad asociada a 'abb' en 'cp'.
	Precondición: perteneceColaPrioridad (cp, abb) */
int prioridadColaPrioridad(ColaPrioridad cp,ABB_T abb){
    int x=1;
	//busco abb en el arreglo
    while(abb != (cp->arreglo[x]))
        x++;
    //devuelvo su prioridad
    return (cp->prioridad[x]);
}

/*	Libera toda la memoria ocupada por 'cp'. */
void destruirColaPrioridad (ColaPrioridad &cp){
    delete [] cp->arreglo;
    delete [] cp->prioridad;
    delete cp;
}
