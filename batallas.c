#include "batallas.h"
#include "aventura.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int funcion_batalla_1(void* pkm_1, void* pkm_2){
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(pokemon_1->velocidad < pokemon_2->velocidad)
		return GANO_SEGUNDO;
	return GANO_PRIMERO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;
	if(pokemon_1->velocidad < pokemon_2->velocidad && pokemon_1->ataque < pokemon_2->ataque)
		return GANO_SEGUNDO;
	return GANO_PRIMERO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(pokemon_1->defensa < pokemon_2->ataque)
		return GANO_SEGUNDO;
	return GANO_PRIMERO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;

	if(pokemon_1->ataque < pokemon_2->velocidad)
		return GANO_SEGUNDO;
	return GANO_PRIMERO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
	pokemon_t* pokemon_1 = (pokemon_t*)pkm_1;
	pokemon_t* pokemon_2 = (pokemon_t*)pkm_2;
	//MODIFICAR
	if(pokemon_1->ataque < pokemon_2->velocidad)
		return GANO_SEGUNDO;
	return GANO_PRIMERO;
}

int reglas_batallas(void* pkm_1, void* pkm_2, int funcion){
	int resultado = 0;
	switch(funcion){
		case 1:{
			resultado = funcion_batalla_1(pkm_1, pkm_2);
			break;
		}
		case 2:{
			resultado = funcion_batalla_2(pkm_1, pkm_2);
			break;
		}
		case 3:{
			resultado = funcion_batalla_3(pkm_1, pkm_2);
			break;
		}
		case 4:{
			resultado = funcion_batalla_4(pkm_1, pkm_2);
			break;
		}
		case 5:{
			resultado = funcion_batalla_5(pkm_1, pkm_2);
			break;
		}
	}
	return resultado;
}