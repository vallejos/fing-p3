/* 4580768 3797928 4392392 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Estructura.h"

//Estructuras

// Cola IP

struct nodoIP {
	IP* ip;
	nodoIP* sig;
	};

typedef nodoIP* lstIP;

struct nodocolaIP{
	lstIP primero;
	lstIP ultimo;
	lstIP pos;
	};

typedef nodocolaIP* colaIP;

// AVL IP
struct nodoAVL {
	IP* nodo;
	nodoAVL* der;
	nodoAVL* izq;
	int FB;
};

typedef nodoAVL* AVL;

//Hash de Dominios
struct nodoDom {
	char* nombre;
	char* comprador;
	char* email;
	nodoDom* sig;
};

typedef nodoDom* lstDom;

struct tablaHashDom{
	lstDom Tabla[cantDominios];
};

typedef tablaHashDom* HashDominios;

//Hash de Dominios Autoritativos

struct nodoDomAut{
	nodoDom* InfoDom;
	AVL IPs;
	colaIP colaIPs;
	nodoDomAut* sig;
};

typedef nodoDomAut* lstDomAut;

struct tablaHashDomAut
{
	lstDomAut Tabla[cantDominiosAutoritativos];
};

typedef tablaHashDomAut* HashDominiosAut;

//Hash de Servidores

struct nodoServ {
	int codSN;
	HashDominiosAut DominiosAutoritativos;
	nodoServ* sig;
};
typedef nodoServ* lstServ;

struct tablaHashServ{
	lstServ Tabla[cantServidores];
};

typedef tablaHashServ* HashServidores;

// Estructura
struct Estructura {
	HashDominios Dominios;
	HashServidores Servidores;
};

//Funciones Auxiliares
//AVL

//Crea el AVL vacio
AVL CrearAVL(){
	return NULL;
	}

//Retorna true si y solo si el AVL a es vacio
bool EsVacioAVL(AVL a){
	return (a==NULL);
	}

//Realiza una rotacion LL en el arbol a
void Rot_LL(nodoAVL* &a){
    nodoAVL* aux= a->izq->der;
	a->izq->der=a;
	nodoAVL* aux2= a->izq;
	a->izq=aux;
	a=aux2;
}

//Realiza una rotacion LL en el arbol a y actualiza los factores de balanceo
void Reb_LL (nodoAVL* &a){
	Rot_LL(a);
	a->FB=0;
	a->der->FB=0;
}

//Realiza una rotacion RR en el arbol a
void Rot_RR(nodoAVL* &a){
	nodoAVL* aux= a->der->izq;
	a->der->izq=a;
	nodoAVL* aux2= a->der;
	a->der=aux;
	a=aux2;
}

//Realiza una rotacion RR en el arbol a y actualiza los factores de balanceo
void Reb_RR(nodoAVL* &a){
	Rot_RR(a);
	a->FB=0;
	a->izq->FB=0;
}

//Realiza un rebalanceo LR en el arbol a, actualizando los factores de balanceo
void Reb_LR (nodoAVL* &K) {
	nodoAVL* ptrC = K->izq->der;

	int FBC = K->izq->der->FB;

	Rot_RR(K->izq);
	Rot_LL(K);

	switch (FBC) {
		case 0:
			ptrC->FB = 0;
			ptrC->izq->FB = 0;
			ptrC->der->FB = 0;
		break;
		case 1:
			ptrC->FB = 0;
			ptrC->izq->FB = 0;
			ptrC->der->FB = -1;
		break;
		case -1:
			ptrC->FB = 0;
			ptrC->izq->FB = 0;
			ptrC->der->FB = 1;
		break;
	}
}

//Realiza un rebalanceo RL en el arbol a actualizando los factores de balanceo
void Reb_RL (nodoAVL* &K) {
	nodoAVL* ptrC = K->der->izq;
	int FBC = K->der->izq->FB;
	Rot_LL(K->der);
	Rot_RR(K);
	switch (FBC) {
		case 0:
			ptrC->FB = 0;
			ptrC->der->FB = 0;
			ptrC->izq->FB = 0;
		break;
		case 1:
			ptrC->FB = 0;
			ptrC->der->FB = 0;
			ptrC->izq->FB = 1;
		break;
		case -1:
			ptrC->FB = 0;
			ptrC->der->FB = 0;
			ptrC->izq->FB = -1;
		break;
	}
}

//Inserta el puntero a IP X en el arbol a
void InsertarAVL(IP* X, bool &aumento, AVL &a)
{
    if (EsVacioAVL(a))
    {
		AVL b= new nodoAVL;
		b->nodo=X;
		b->der=NULL;
		b->izq=NULL;
		b->FB=0;
		a=b;
		aumento = true;
    }
    else
        if (X->ip < a->nodo->ip)
        {
            InsertarAVL(X, aumento, a->izq);
            if (aumento)
            {
                switch(a->FB)
                {
                    case -1: //antes de la ins. ALT(TL) < ALT(TR)
                            a->FB = 0;//No se produce desbalanceo
                            aumento = false;
                            break;
                    case 0: //antes de la ins. ALT(TL) = ALT(TR)
                            a->FB=1;//mirar los ancestros
                            break;
                    case 1: //antes de la ins. ALT(TL) > ALT(TR)
                              //rebalanceo, el tipo es LL o LR
                            if (a->izq->FB == 1) // es LL
                                Reb_LL(a);
                            else //es LR
                                Reb_LR(a);
                            aumento = false;
							break;
                }
            }
        }
	 else
        {
            InsertarAVL(X, aumento, a->der);
            if(aumento)
            {
                switch(a->FB)
                {
                    case 1: //antes de la ins. ALT(TR) < ALT(TL)
                            a->FB = 0;//No se produce desbalanceo
                            aumento = false;
                            break;
                    case 0: //antes de la ins. ALT(TR) = ALT(TL)
                            a->FB = -1; // mirar los ancestros
                            break;
                    case -1: //antes de la ins. ALT(TR) > ALT(TL)
                            //rebalanceo, el tipo es RR o RL
							if (a->der->FB == -1) // es RR
                                Reb_RR(a);
                            else //es RL
                                Reb_RL(a);
                            aumento = false;
                            break;
                }
            }
        }
}

//Imprime la informacion del arbol a en preorden en la salida estándar
void ImprimirAVL(AVL a){
	if (!EsVacioAVL(a))
	{
		ImprimirAVL(a->izq);
		printf("%d\n",a->nodo->ip);
		ImprimirAVL(a->der);
	}
}

//Libera la memoria reservada del AVL a sin destruir los punteros a las IP de cada nodo
void DestruirAVL(AVL &a){
	if (!EsVacioAVL(a))
	{
		DestruirAVL(a->izq);
		DestruirAVL(a->der);
		delete a;
	}
}

//Cola IP

//Crea la cola vacia
colaIP CrearCola(){
	return NULL;
}

//Inserta un puntero a IP al final de la cola c
void InsertarCola(IP* ip, colaIP &c){
	lstIP insert= new nodoIP;
	IP* ipinsert= new IP;
	ipinsert->ip=ip->ip;
	insert->ip=ipinsert;
	insert->sig=NULL;
	if (c==NULL)
	{
		colaIP d = new nodocolaIP;
		d->primero=insert;
		d->ultimo=insert;
		d->pos=insert;
		c=d;
	}
	else
	{
		c->ultimo->sig=insert;
		c->ultimo=c->ultimo->sig;
		if (c->pos==NULL)
            c->pos=c->ultimo;
	}
}

//Retorna la IP de la cola c indicada por pos. Si pos es nulo se retorna el primer elemento
IP* MostrarIP(colaIP &c){
	IP* prim;
	if (c->pos==NULL)
    {
        prim=c->primero->ip;
        c->pos=c->primero->sig;
    }
    else
    {
        prim=c->pos->ip;
        c->pos=c->pos->sig;
    }
    return prim;
}

//Libera la memoria reservada por la cola y sus elementos
void DestruirCola(colaIP &c){
	c->ultimo=NULL;
	c->pos=NULL;
	lstIP borrar=c->primero;
	while (c->primero!=NULL)
	{
		c->primero=c->primero->sig;
		delete borrar->ip;
		delete borrar;
		borrar=c->primero;
	}
	delete c;
	c=NULL;
}

//Fin de funciones auxiliares

//Funciones de Hash

// funcion hash servidores
int fHashServ(int codSN) {
	int pos = codSN % cantServidores;
	return pos;
}


// funcion hash dominios
int fHashDom(char* nombre_dominio){
	int pos=(atoi(nombre_dominio))%cantDominios;
	return pos;
}
//Fin funciones de Hash

//Crea la estructura de datos vacia.
Estructura* crearDNS() {
	Estructura* E=new Estructura;
	HashServidores hashServ = new tablaHashServ;    //Inicializa Hash de Servidores
	for (int i=0; i<cantServidores; i++) {
		hashServ->Tabla[i] = NULL;
	}
	E->Servidores=hashServ;
	HashDominios hashDom = new tablaHashDom;    //Inicializa Hash de Dominios
	for (int i=0; i<cantDominios; i++) {
		hashDom->Tabla[i] = NULL;
	}
	E->Dominios=hashDom;
	return E;
}

//Ingresa un Servidor de nombres con codigo codSN a la estructura E
// Esta operacion debe realizarse en O(1) promedio.
// Pre: la estructura fue creada previamente.
// Pre: no existe un servidor de codigo codNS en la estructura E
void altaServidorNombres(int codSN, Estructura* E) {
	int pos = fHashServ(codSN);
	lstServ insert = new nodoServ;
	insert->codSN=codSN;
    insert->DominiosAutoritativos=NULL;
	insert->sig=E->Servidores->Tabla[pos];
	E->Servidores->Tabla[pos]=insert;
}

//Ingresa un dominio de nombre nombreDominio, comprador nombreComprador e email emailContacto a la estructura E
// Esta operacion debe realizarse en O(1) promedio.
// Pre: nombreDominio != NULL, nombreComprador != NULL, emailContacto != NULL
// Pre: la estructura fue creada previamente.
// Pre: no existe un dominio de nombre nombreDominio en la estructura
void altaDominio(const char* nombreDominio, const char* nombreComprador, const char* emailContacto, Estructura* E) {
	lstDom insert = new nodoDom;
	char* nombre= new char[strlen(nombreDominio)+1];
	char* comprador = new char[strlen(nombreComprador)+1];
	char* email= new char[strlen(emailContacto)+1];
	strcpy(nombre,nombreDominio);
	strcpy(comprador,nombreComprador);
	strcpy(email,emailContacto);
	insert->nombre=nombre;
	insert->comprador=comprador;
	insert->email=email;
	int pos = fHashDom(insert->nombre);
	insert->sig = E->Dominios->Tabla[pos];
	E->Dominios->Tabla[pos] = insert;
}

//Agrega una ip autoritativa al dominio de nombre nombreDominio en el servidor de codigo codSN
// Esta operacion debe realizarse en O(cantServidores + cantDominios + cantDominiosAutoritativos + log (cantIP))  peor caso
// Pre: nombreDominio != NULL
// Pre: la estructura fue creada previamente.
// Pre: existe un servidor de codigo codSN en la estructura
// Pre: existe un dominio de nombre nombreDominio en la estructura
// Pre: existen menos de cantIP traducciones para el dominio de nombre nombreDominio en el servidor de codigo codSN
void agregarIPAutoritativa(int codSN, const char* nombreDominio, IP* ip, Estructura* E) {
	char* nombre= new char[strlen(nombreDominio)+1];
	strcpy(nombre,nombreDominio);
	int posServ = fHashServ(codSN);
	int posDom = fHashDom(nombre);
	delete [] nombre;
	lstServ auxServ = E->Servidores->Tabla[posServ];
	while ((auxServ!=NULL)&&(auxServ->codSN!=codSN))    //Busco el Servidor de codigo codSN
	{
		auxServ=auxServ->sig;
	}
	if (auxServ->DominiosAutoritativos==NULL)       //Si el hash de Dominios Autoritavos del servidor codSN es nulo, lo inicializo
    {
        HashDominiosAut hashDomAut= new tablaHashDomAut;
        for (int i=0; i<cantDominiosAutoritativos; i++)
		{
			hashDomAut->Tabla[i]=NULL;
        }
        auxServ->DominiosAutoritativos=hashDomAut;
    }
	lstDomAut auxDomAut=auxServ->DominiosAutoritativos->Tabla[posDom];              //Buscamos el dominio de nombre nombreDominio en el hash de Dominios autoritativos
	while ((auxDomAut!=NULL)&&(strcmp(auxDomAut->InfoDom->nombre,nombreDominio)!=0))
	{
		auxDomAut=auxDomAut->sig;
	}
	bool aumento=false;
	if (auxDomAut==NULL)    //En caso de que no este, se agrega el dominio al hash de Dominios Autoritativos
	{
		lstDom auxDom=E->Dominios->Tabla[posDom];   //Se busca su informacion en el hash de Dominios
		while ((auxDom!=NULL)&&(strcmp(auxDom->nombre,nombreDominio)!=0))
		{
			auxDom=auxDom->sig;
		}
		lstDomAut insert = new nodoDomAut;
		insert->InfoDom=auxDom;
		AVL avlinsert =CrearAVL();          //Se crea el AVL y la cola y se inserta la IP
		colaIP colainsert=CrearCola();
		InsertarCola(ip,colainsert);
		insert->colaIPs=colainsert;
		InsertarAVL(colainsert->ultimo->ip, aumento, avlinsert);
		insert->IPs=avlinsert;
		insert->sig=auxServ->DominiosAutoritativos->Tabla[posDom];
		auxServ->DominiosAutoritativos->Tabla[posDom]=insert;
	}
	else
	{
		InsertarCola(ip,auxDomAut->colaIPs);    //Se inserta la ip al AVL y la cola
		InsertarAVL(auxDomAut->colaIPs->ultimo->ip,aumento,auxDomAut->IPs);

	}
}

//Retorna, en caso de existir, una ip autoritativa correspondiente al dominio de nombre nombreDominio del servidor de codigo codSN
//Esta operacion respeta el balance de carga de todas las ip distintas correspondientes a ese dominio en ese servidor
// Esta operacion debe realizarse en O(1) promedio.
// Pre: nombreDominio != NULL
// Pre: la estructura fue creada previamente.
// Pre: existe un servidor de codigo codSN en la estructura
// Pre: existe un dominio de nombre nombreDominio en la estructura
IP* consultaNoJerarquica(int codSN, const char* nombreDominio, bool& hayTraduccion, Estructura* E) {
	int posServ = fHashServ(codSN);
	char* nombre= new char[strlen(nombreDominio)+1];
	strcpy(nombre,nombreDominio);
	int posDom = fHashDom(nombre);
	delete[] nombre;
	IP* IPresult= NULL;
	lstServ auxServ = E->Servidores->Tabla[posServ];        //Se busca el servidor en el Hash de Servidores
	while ((auxServ!=NULL)&&(auxServ->codSN!=codSN))
	{
		auxServ=auxServ->sig;
	}
	lstDomAut auxDomAut=auxServ->DominiosAutoritativos->Tabla[posDom];      //Se busca el dominio en el Hash de Dominios Autoritativos
	while ((auxDomAut!=NULL)&&(strcmp(auxDomAut->InfoDom->nombre,nombreDominio)!=0))
	{
		auxDomAut=auxDomAut->sig;
	}
	if (auxDomAut==NULL)       //En caso de no encontrarse el dominio, se devuelve un puntero nulo y hayTraduccion es falso
	{
		hayTraduccion=false;
	}
	else                       //En caso de existir el dominio en el hash, se devuelve una IP con el procedimiento MostrarIP e hayTraduccion en true
	{
		hayTraduccion=true;
		IPresult=MostrarIP(auxDomAut->colaIPs);
	}
	return IPresult;
}

//Imprime todas las ip correspondientes al dominio de nombre nombreDominio que se encuentren en el servidor de codigo codSN
//En caso de no haber traducciones se imprime el mensaje: "El servidor no es autoritativo para el dominio especificado"
// Esta operacion debe realizarse en O(cantIP) promedio
// El orden de impresión será ascendente segun el valor de las direcciones ip
// Pre: nombreDominio != NULL
// Pre: la estructura fue creada previamente.
// Pre: existe un dominio de nombre nombreDominio en la estructura
// Pre: existe un servidor de nombres de codigo codSN en la estructura
void dig(int codSN, const char* nombreDominio, Estructura* E){
	int posServ = fHashServ(codSN);
	char* nombre = new char[strlen(nombreDominio)+1];
	int posDom = fHashDom(nombre);
	delete [] nombre;
	lstServ auxServ = E->Servidores->Tabla[posServ];    //Busco el servidor en el hash de Servidores
	while ((auxServ!=NULL)&&(auxServ->codSN!=codSN))
	{
		auxServ=auxServ->sig;
	}
	if (auxServ->DominiosAutoritativos==NULL)           //Si el hash de Dominios Autoritativos es nulo, se imprime el mensaje
	{
	    printf("El servidor no es autoritativo para el dominio especificado\n");
	}
	else
	{
        lstDomAut auxDomAut=auxServ->DominiosAutoritativos->Tabla[posDom];  //Busco el dominio en el hash de Dominios Autoritativos
        while ((auxDomAut!=NULL)&&(strcmp(auxDomAut->InfoDom->nombre,nombreDominio)!=0))
        {
            auxDomAut=auxDomAut->sig;
        }
        if (auxDomAut==NULL)   //Si el dominio no esta en el hash imprimo el mensaje
        {
            printf("El servidor no es autoritativo para el dominio especificado\n");
        }
        else    //Si el dominio esta en el hash, se imprime el AVL con sus IPs
        {
            ImprimirAVL(auxDomAut->IPs);
        }
	}
}

//Libera la memoria reservada por la estructura E
//Pre: La estructura E fue previamente creada.
//Destruye la estructura, liberando por completo la memoria asignada.
void destruirDNS(Estructura* E){
	for (int i=0; i<cantServidores; i++)    //Destruyo el hash de servidores
	{
		lstServ auxServ=E->Servidores->Tabla[i];
		while (auxServ!=NULL)
		{
			if (auxServ->DominiosAutoritativos!=NULL)
			{
				for (int k=0; k<cantDominiosAutoritativos; k++) //Para cada servidor destruyo su hash de Dominios Autoritativos
				{
					lstDomAut auxDomAut=auxServ->DominiosAutoritativos->Tabla[k];
					lstDomAut borrarDomAut=auxDomAut;
					while (auxDomAut!=NULL)
					{
						auxDomAut=auxDomAut->sig;
						DestruirAVL(borrarDomAut->IPs);
						DestruirCola(borrarDomAut->colaIPs);
						borrarDomAut->InfoDom=NULL;
						delete borrarDomAut;
						borrarDomAut=auxDomAut;
					}
				}
				delete auxServ->DominiosAutoritativos;
			}
			lstServ borrarServ=auxServ;
			auxServ=auxServ->sig;
			delete borrarServ;
		}
	}
	delete E->Servidores;
	for(int j=0; j<cantDominios; j++) //Destruyo el hash de Dominios
	{
		lstDom auxDom=E->Dominios->Tabla[j];
		while (auxDom!=NULL)
		{
			lstDom borrarDom=auxDom;
			auxDom=auxDom->sig;
			delete[] borrarDom->nombre;
			delete[] borrarDom->comprador;
			delete[] borrarDom->email;
			delete borrarDom;
		}
	}
	delete E->Dominios;
	delete E;
}

