#ifndef LISTAENTEROS_H
#define LISTAENTEROS_H

struct auxLista;
typedef auxLista* ListaEnteros;

ListaEnteros crearListaEnteros();
// Crea una lista de nodos vacia. 

bool esVaciaListaEnteros(ListaEnteros l);
// Devuelve true si la lista es vacia y false en caso contrario. 
// Precondici�n: l fue previamente creada.

void agregarListaEnteros(ListaEnteros &l, int n);
// Agrega el elemento n al principio de la lista  l.
// Precondici�n: l fue previamente creada.

int primeroListaEnteros(ListaEnteros l);
// Devuelve el primer elemento de la lista. 
// Precondicion: !esVaciaListaEnteros(l).
// Precondici�n: l fue previamente creada.

ListaEnteros restoListaEnteros(ListaEnteros l);
// Devuelve el resto de la lista l.
// Precondicion: !esVaciaListaEnteros(l).
// Precondici�n: l fue previamente creada.

void destruirListaEnteros(ListaEnteros &l);
// libera la memoria asociada a la lista.
// Precondici�n: l fue previamente creada. 

#endif /* LISTAENTEROS_H */
