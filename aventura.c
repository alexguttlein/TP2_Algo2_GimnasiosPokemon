#include "aventura.h"
#include "lista.h"
#include "heap.h"
#include "batallas.h"
#include "arte.h"

#define ERROR -1
#define OK 0


void leer_archivo(FILE* archivo, entrenador_t* entrenador, gimnasio_t* gimnasio){
	char caracter_inicial = 'a'; //se lee el primer caracter para determinar el tipo elemento
	caracter_inicial = fgetc(archivo);
	fgetc(archivo);

	switch(caracter_inicial){
		case 'E':{
			if(!gimnasio){ //si no es un entrenador de ginmasio
				string_t texto;
				fscanf(archivo, "%s", texto);
				strcpy(entrenador->nombre , texto);
			}else{  //si es un entrenador de gimnasio
				gimnasio->cantidad_entrenadores++;
				entrenador_t* entrenadores = realloc(gimnasio->entrenadores, sizeof(entrenador_t) * gimnasio->cantidad_entrenadores);
				if(entrenadores){  //se aumenta el tamaño del vector de entrenadores
					gimnasio->entrenadores = entrenadores;
				}
				entrenador = gimnasio->entrenadores+(gimnasio->cantidad_entrenadores-1);
				string_t texto;
				fscanf(archivo, "%s", texto);
				strcpy(entrenador->nombre , texto);

			}
			break;
		}
		case 'P':{
			entrenador->cantidad_pokemones++;
			int pos = entrenador->cantidad_pokemones-1;
			entrenador->pokemones = realloc(entrenador->pokemones, sizeof(pokemon_t) * entrenador->cantidad_pokemones);
			fscanf(archivo, "%[^;];%i;%i;%i", entrenador->pokemones[pos].nombre, &(entrenador->pokemones[pos].velocidad),&(entrenador->pokemones[pos].defensa), &(entrenador->pokemones[pos].ataque));
			break;
		}
		case 'L':{
			string_t texto;
			fscanf(archivo, "%s", texto);
			strcpy(entrenador->nombre , texto);
			break;
		}
		case 'G':{
			fscanf(archivo, "%[^;];%i;%i;%s", gimnasio->nombre, &(gimnasio->dificultad), &(gimnasio->id), gimnasio->tipo);
			break;
		}
	}
}


void mostrar_entrenador(entrenador_t* entrenador){
	printf("NOMBRE\t %s\n",entrenador->nombre);
	printf("POKEMONES\n");
	for(int i=0; i<entrenador->cantidad_pokemones; i++){
		printf("%i - %s %i %i %i\n", i+1, entrenador->pokemones[i].nombre, entrenador->pokemones[i].velocidad, entrenador->pokemones[i].defensa, entrenador->pokemones[i].ataque);
	}
}


char* nombre_lider(gimnasio_t* gimnasio){
	char* lider = ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->nombre;
	return lider;
}


void datos_lider(gimnasio_t* gimnasio){
	printf("LIDER: %s\n", ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->nombre);
	printf("POKEMONES:\n");
	printf("NOMBRE\tVELOC.\tDEFENSA\tATAQUE\n");
	int cantidad = ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->cantidad_pokemones;
	for(int i=0; i<cantidad; i++){
		printf("%s\t", ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->pokemones[i].nombre );
		printf("%i\t", ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->pokemones[i].velocidad );
		printf("%i\t", ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->pokemones[i].defensa );
		printf("%i\n", ((entrenador_t*)(gimnasio->pila_entrenadores->nodo_inicio->elemento))->pokemones[i].ataque );
	}
}


void mostrar_gimnasio(gimnasio_t* gimnasio){
	printf("%s | dificultad: %i | id: %i | tipo: %s\nLider: %s\n",gimnasio->nombre, gimnasio->dificultad, gimnasio->id, gimnasio->tipo, nombre_lider(gimnasio));
}


bool gimnasio_vacio(gimnasio_t* gimnasio){
	return gimnasio->cantidad_entrenadores == 0;
}


void datos_gimnasio_actual(void* heap){
	heap_t* heap_gimnasios = (heap_t*)heap;
	gimnasio_t* gym = heap_raiz(heap_gimnasios);
	mostrar_gimnasio(gym);
}


void mostrar_pokemon(pokemon_t* pokemon){
	printf("         -------------\n");
	printf("           %s\n",pokemon->nombre);
	printf("           ----------\n");
	printf("           | VELOC. | %i\n",pokemon->velocidad);
	printf("           | DEFENSA| %i\n",pokemon->defensa);
	printf("           | ATAQUE | %i\n",pokemon->ataque);
	printf("           ----------\n\n");
}


void datos_batalla(entrenador_t* entrenador1, entrenador_t* entrenador2, pokemon_t* pokemon1, pokemon_t* pokemon2){
	printf("         %s\t\t %s\n", entrenador1->nombre, entrenador2->nombre);
	printf("POKEMON| %s\t\t|%s\n", pokemon1->nombre, pokemon2->nombre );
	printf("VELOC. | %i\t\t\t|%i\n", pokemon1->velocidad, pokemon2->velocidad );
	printf("DEFENSA| %i\t\t\t|%i\n", pokemon1->defensa, pokemon2->defensa );
	printf("ATAQUE | %i\t\t\t|%i\n", pokemon1->ataque, pokemon2->ataque );
}


entrenador_t* ingresar_entrenador_principal(char* ruta){
	FILE* archivo;
	archivo = fopen(ruta, "r");

	entrenador_t* entrenador = calloc(1, sizeof(entrenador_t));
	if(!entrenador) return NULL;
	
	//se crea el vector de pokemones
	entrenador->pokemones = calloc(1, sizeof(pokemon_t));
	if(!entrenador->pokemones) return NULL;

	//se lee una linea del archivo
	leer_archivo(archivo, entrenador, NULL);
	while(!feof(archivo)){ //se continua leyendo hasta que se llegue al final del archivo
		leer_archivo(archivo, entrenador, NULL);
	}
	fclose(archivo);
	return entrenador;
}


void convertir_a_pila(gimnasio_t* gym){
	lista_t* lista = lista_crear();
	for(int i=0; i<gym->cantidad_entrenadores; i++){
		lista_apilar(lista, gym->entrenadores+i);
	}
	gym->pila_entrenadores = lista;
}


//se carga el archivo de un gimnasio reservando memoria para el mismo.
//si funciona devuelve el gimnasio, sino devuelve error.
gimnasio_t* cargar_gimnasio(string_t ruta){
	FILE* archivo = fopen(ruta,"r");
	if (!archivo) return NULL;
	
	gimnasio_t* gym = calloc(1, sizeof(gimnasio_t));
	if(!gym) return NULL;

	leer_archivo(archivo, NULL, gym);

	gym->cantidad_entrenadores++;
	//se crea un vector de enternadores
	entrenador_t* entrenadores = calloc(1, sizeof(entrenador_t) * gym->cantidad_entrenadores);
	if(!entrenadores) return NULL;

	gym->entrenadores = entrenadores;

	while(!feof(archivo)){ //se continua leyendo hasta que se llegue al final del archivo
		leer_archivo(archivo, gym->entrenadores+(gym->cantidad_entrenadores-1), gym);
	}

	fclose(archivo);

	convertir_a_pila(gym);
	return gym;
}


int comparar_gimnasios(void* gimnasio1, void* gimnasio2){
    if(!gimnasio1 || !gimnasio2)
        return 0;
    if(((gimnasio_t*)gimnasio1)->dificultad > ((gimnasio_t*)gimnasio2)->dificultad)
        return 1;
    if(((gimnasio_t*)gimnasio1)->dificultad < ((gimnasio_t*)gimnasio2)->dificultad)
        return -1;
    return 0;
}


//se ingresan los archivos de gimnasios
//si funciona devuelve un heap con los gimnasios, de lo contrario devuelve error.
void* ingresar_gimnasio(char** gimnasios, int tamanio){
	
	heap_t* heap_gimnasios = heap_crear(comparar_gimnasios);

	for(int i=0; i<tamanio; i++){
		gimnasio_t* gym = cargar_gimnasio(gimnasios[i]);
		mostrar_gimnasio(gym);
		heap_insertar(heap_gimnasios, gym);
	}

	return (void*)(heap_gimnasios);
}


entrenador_t* swap_pokemones(entrenador_t* entrenador, int op1, int op2){
	
	pokemon_t aux = entrenador->pokemones[op1-1];
	entrenador->pokemones[op1-1] = entrenador->pokemones[op2-1];
	entrenador->pokemones[op2-1] = aux;
	return entrenador;
}


entrenador_t* modificar_pokemones(entrenador_t* entrenador){
	int op1 = -1;
	int op2 = -1;
	
	do{
		printf("MODIFICA TUS POKEMONES\n");
		mostrar_entrenador(entrenador);
		printf("\n¿Que Pokemon quieres mover? (selecciona su numero): ");
		scanf("%i",&op1);
		fflush(stdin);
		printf("¿Por que Pokemon quieres reemplazar a %s? (selecciona su numero): ",entrenador->pokemones[op1-1].nombre);
		scanf("%i",&op2);
		fflush(stdin);
		entrenador = swap_pokemones(entrenador, op1 , op2);
		mostrar_entrenador(entrenador);
		printf("¿Quieres modificar otro Pokemon? \n(1) SI\t(2) NO\n");
		fflush(stdin);
		scanf("%i",&op1);
		printf("\n");
		fflush(stdin);
	}while(op1 != 2);

	return entrenador;
}


entrenador_t* tomar_pokemon_de_lider(entrenador_t* entrenador, entrenador_t* lider){
	int op = -1;
	printf("Selecciona el pokemon que quieres agregar a tu grupo\n");
	mostrar_entrenador(lider);
	scanf("%i",&op);

	entrenador->cantidad_pokemones++;
	entrenador->pokemones = realloc(entrenador->pokemones, sizeof(pokemon_t) * entrenador->cantidad_pokemones);
	if(!entrenador->pokemones) return NULL;

	entrenador->pokemones[entrenador->cantidad_pokemones-1] = lider->pokemones[op-1];
	
	return entrenador;
}


int menu_derrota(entrenador_t* entrenador){
	int op = 1;
	
	do{
		printf("HAS SIDO DERROTADO\n¿Que deseas hacer?\n");
		printf(" <C> Modificar Pokemones de Batalla\n <R> Reintentar Gimnasio\n <F> Finalizar Partida\n");
		scanf("%i",&op);
	
		switch(op){
			case 1:{
				modificar_pokemones(entrenador);
				break;
			}
			case 2:{
				op = 0;
				break;
			}
			case 3:{
				op = -1;
				break;
			}
		}
	}while (op == 1);
	return op;
}


entrenador_t* menu_victoria(entrenador_t* entrenador, void* heap_gimnasios){
	heap_t* heap = ((heap_t*)heap_gimnasios);
	gimnasio_t* gym_actual = (gimnasio_t*)(heap_raiz((heap_t*)heap_gimnasios));
	
	printf("DERROTASTE A %s\n", nombre_lider(gym_actual));
	entrenador->medallas++;
	
	arte_medallas(gym_actual);

	int op = 0;
	bool pokemon_tomado = false;
	do{
		printf("SELECCIONA LA OPCION DESEADA\n");
		if(!pokemon_tomado)
			printf(" <T> Tomar un Pokemon del Lider\n <C> Cambiar Orden Pokemones\n <N> Pasar al Proximo Gimnasio\n");
		else printf(" <C> Cambiar Orden Pokemones\n <N> Pasar al Proximo Gimnasio\n");
		scanf("%i",&op);

		switch(op){
			case 1:{
				if(!pokemon_tomado)
					entrenador = tomar_pokemon_de_lider(entrenador, lista_tope(gym_actual->pila_entrenadores));
					pokemon_tomado = true;
				break;
			}
			case 2:{
				modificar_pokemones(entrenador);
				break;
			}
		}
	}while(op>0 && op<3);
	heap_extraer_raiz(heap);
	return entrenador;
}


void mejorar_habilidades_pokemon(pokemon_t* pokemon){
	printf("\n   %s aumento sus habilidades\n",pokemon->nombre);
	if(pokemon->velocidad < 63) pokemon->velocidad++;
	if(pokemon->defensa < 63) pokemon->defensa++;
	if(pokemon->ataque < 63) pokemon->ataque++;
	mostrar_pokemon(pokemon);
}


int iniciar_batalla(entrenador_t* entrenador, void* heap_gimnasios){
	heap_t* heap = ((heap_t*)heap_gimnasios);
	
	gimnasio_t* gym_actual = (gimnasio_t*)(heap_raiz((heap_t*)heap_gimnasios));	
	entrenador_t* rival = (entrenador_t*)lista_tope(gym_actual->pila_entrenadores);
	
	bool rival_derrotado = false;

	int i=0;
	int j=0;
	while(j < rival->cantidad_pokemones && i<6){
			printf("\t\tPROXIMA PELEA\n");
			datos_batalla(rival, entrenador, rival->pokemones+j, entrenador->pokemones+i);
			if(reglas_batallas(rival->pokemones+j,entrenador->pokemones+i, gym_actual->id) == GANO_PRIMERO){
				i++;
			}
			else{
				j++;
				mejorar_habilidades_pokemon(entrenador->pokemones+i);
			}
		}
	
	if(j == rival->cantidad_pokemones){
		gym_actual->cantidad_entrenadores--;
		if(gym_actual->cantidad_entrenadores == 0)
			return 0;	//se derroto al lider
		else{
			printf("\nDERROTASTE A %s\n", rival->nombre);
			lista_desapilar(gym_actual->pila_entrenadores);
			return -1;	//se derroto al entrenador pero aun no al lider
		} 
	}
	return 1; //se perdio la batalla
}


bool gimnasios_derrotados(void* heap_gimnasios){
	heap_t* heap = ((heap_t*)heap_gimnasios);
	return heap_vacio(heap);
}