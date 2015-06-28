#include <stdlib.h>
#include <stdio.h>

#include "test_helper.h"

/* Verifica que el centro de envio mas cercano y el camino son correctos */
/* Recibe como parametros la ciudad, el origen, el destino y el largo */
void test_camino_mas_cercano(Ciudad* c, int origen, int destino, int largo){
  int res;

  printf ("Calculando centro de envio mas cercano. Pedido en zona: %i. \n", origen);
  printf ("Resultado esperado. Largo: %i, Destino: %i \n", largo, destino);

  Camino* camino = centroEnvioMasCercano (c, origen);

  res = check_camino (c, origen, destino, largo, camino);
  if (res == CHECK_OK)
    printf ("OK\n");
  else
    printf ("ERROR\n(%s)\n", STR_ERRORS[res]);

  delete [] camino->zonas;
  delete camino;

}

/* Verifica que las zonas de influencia son las correctas */
void test_zonas_de_influencia(Ciudad *c){
  int res;
  printf ("Calculando zonas de influencia del centro de envio %i a distancia %i\n", 5, 2);
  ListaEnteros zdi = zonasDeInfluencia(c, 5, 2);
  for (ListaEnteros iter = zdi; !esVaciaListaEnteros(iter); iter = restoListaEnteros(iter))
	printf("-%i-", primeroListaEnteros(iter));
  
  ListaEnteros sol = crearListaEnteros();
  agregarListaEnteros(sol, 1);
  agregarListaEnteros(sol, 2);
  agregarListaEnteros(sol, 4);
  agregarListaEnteros(sol, 5);
  
  res = check_lista (sol, zdi);
  if (res == CHECK_OK)
    printf ("OK\n");
  else
    printf ("ERROR\n(%s)\n", STR_ERRORS[res]);

  destruirListaEnteros(zdi);
  destruirListaEnteros(sol);
}

/* Verifica que las zonas exclusivas son las correctas */
void test_zonas_exclusivas(Ciudad *c){
  int res;
  printf ("Calculando zonas exclusivas del centro de envio %i\n", 3);
  
  ListaEnteros ze = zonasExclusivas(c, 3);
  
  ListaEnteros sol = crearListaEnteros();
  agregarListaEnteros(sol, 0);
  agregarListaEnteros(sol, 3);
  
  res = check_lista (sol, ze);
  if (res == CHECK_OK)
    printf ("OK\n");
  else
    printf ("ERROR\n(%s)\n", STR_ERRORS[res]);

  destruirListaEnteros(ze);
  destruirListaEnteros(sol);
}

int main (int argc, char *argv[]){

  Ciudad *c = crear_ciudad1();

  test_camino_mas_cercano(c, 4, 5, 3);

  test_zonas_de_influencia(c);
  
  test_zonas_exclusivas(c);

  destruirCiudad (c);

  return 0;
}
