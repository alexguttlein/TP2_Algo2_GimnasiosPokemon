#include "aventura.h"
#define MAX_GIMNASIOS 8

int menu_batalla(entrenador_t* entrenador, void* carga_gimnasios){
	bool gimnasio_terminado = false;
	int derrota = 0;
	do{
		int batalla = -1;
		batalla = iniciar_batalla(entrenador, carga_gimnasios);
		if(batalla == 0){
			menu_victoria(entrenador, carga_gimnasios);
			gimnasio_terminado = true;
		}
		else if(batalla == 1)
			derrota = menu_derrota(entrenador);
	}while(!gimnasio_terminado && derrota != -1);
	
	if(derrota == -1){
		printf("TE RENDISTE!! NO TIENES LO NECESARIO PARA SER UN MAESTRO POKEMON\n");
		return -1;
	}
	return 0;
}

int menu_gimnasio(entrenador_t* entrenador, void* carga_gimnasios){
	int op;
	int batalla = -1;
	bool fin_juego = false;
	while(!fin_juego){
		do{
				printf("\n\t\tMENU DE GIMNASIO\n");
				printf("\tSelecciona opcion:\n");
				printf("\t<E> Ver entrenador principal con sus Pokemones");
				printf("\n\t<G> Ver informacion del Gimnasio actual");
				printf("\n\t<C> Modificar los Pokemones de Batalla");
				printf("\n\t<B> Realizar Siguiente Batalla\n");
				scanf("%i",&op);
				fflush(stdin);
			}while(op > 4);
	
		switch(op){
			case 1:{
				printf("DATOS ENTRENADOR\n");
				mostrar_entrenador(entrenador);
				break;
			}
			case 2:{
				printf("GIMNASIO ACTUAL\n");
				datos_gimnasio_actual(carga_gimnasios);
				break;
			}
			case 3:{
				entrenador = modificar_pokemones(entrenador);
				break;
			}
			case 4:{
				batalla = menu_batalla(entrenador, carga_gimnasios);
				if (batalla == -1) return -1;
				if(entrenador->medallas == 8) fin_juego = true;
				break;
			}
		}
	}
	//FIN DEL JUEGO
	return 0;
}


void menu_inicio(entrenador_t* entrenador, void* carga_gimnasios){

	//char opciones[] = {"EAIS"};
	int op;
	bool juego_iniciado = false;
	int info_cargada[] = {-1,-1};

	while(!juego_iniciado){
		do{
			printf("\n\t\tMENU INICIAL\n");
			printf("\tSelecciona opcion:\n");
			printf("\t<E> Cargar entrenador principal");
			printf("\n\t<A> Cargar gimnasios");
			printf("\n\t<I> Comenzar partida");
			printf("\n\t<S> Simular partida\n");
			scanf("%i",&op);
			fflush(stdin);
		}while(op <= 1 && op >= 2);

		switch(op){
			case 1:{
				entrenador = ingresar_entrenador_principal("entrenador/lista_pkmn.txt");
				info_cargada[0] = 0;
				break;
			}
			case 2:{
				char gimnasio1[] = {"gimnasios/01_plateada.txt"};
				char gimnasio2[] = {"gimnasios/02_celeste.txt"};
				char gimnasio3[] = {"gimnasios/03_carmin.txt"};
				char gimnasio4[] = {"gimnasios/04_azulona.txt"};
				char gimnasio5[] = {"gimnasios/05_fuscia.txt"};
				char gimnasio6[] = {"gimnasios/06_azafran.txt"};
				char gimnasio7[] = {"gimnasios/07_canela.txt"};
				char gimnasio8[] = {"gimnasios/08_verde.txt"};
				
				char* gimnasios[] = {gimnasio1, gimnasio2, gimnasio3, gimnasio4, gimnasio5, gimnasio6, gimnasio7, gimnasio8};
				carga_gimnasios = ingresar_gimnasio(gimnasios, MAX_GIMNASIOS);
				info_cargada[1] = 0;
				break;	
			}
			case 3:{
				if(info_cargada[0] == 0 && info_cargada[1] == 0){
					menu_gimnasio(entrenador, carga_gimnasios);
				}
			}
		}
	}
}

int main(){
	entrenador_t* entrenador_principal = NULL;
	void* gimnasios;
	menu_inicio(entrenador_principal, gimnasios);
	return 0;
}