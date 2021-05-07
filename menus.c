#include "menus.h"
#include "aventura.h"

char menu_inicial(){
	char opcion;
	printf("\n\t\tMENU INICIAL\n");
	printf("\tSelecciona opcion:\n");
	printf("\t<A> Cargar entrenador principal");
	printf("\n\t<B> Cargar gimnasios");
	printf("\n\t<C> Comenzar partida");
	printf("\n\t<D> Simular partida\n");
	scanf("%c", &opcion);
	return opcion;
}