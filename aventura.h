#ifndef __AVENTURA_POKEMON__
#define __AVENTURA_POKEMON__

#include "lista.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_EQUIPO 6
#define MAX_ATRIBUTO 63
#define MAX_MEDALLAS 8

typedef int (*funcion_batalla)(void*, void*);

typedef char string_t[MAX_NOMBRE];

typedef struct pokemon{
	string_t nombre;
	int velocidad;
	int defensa;
	int ataque;
}pokemon_t;

typedef struct entrenador{
	string_t nombre;
	pokemon_t* pokemones;
	int cantidad_pokemones;
	int medallas;
}entrenador_t;

typedef struct gimnasio{
	string_t nombre;
	int dificultad;
	int id;
	string_t tipo;
	int cantidad_entrenadores;
	entrenador_t* entrenadores;
	lista_t* pila_entrenadores;
}gimnasio_t;


entrenador_t* ingresar_entrenador_principal(char*);

void mostrar_entrenador(entrenador_t* entrenador);

void datos_gimnasio_actual(void*);

char* nombre_lider(gimnasio_t* gimnasio);

void* ingresar_gimnasio(char**, int);

bool gimnasio_vacio(gimnasio_t* gimnasio);

int simular_partida();

int iniciar_batalla(entrenador_t*, void*);

entrenador_t* modificar_pokemones(entrenador_t* entrenador);

int menu_derrota(entrenador_t*);

entrenador_t* menu_victoria(entrenador_t*, void*);

bool gimnasios_derrotados(void*);

#endif /* __AVENTURA_POKEMON__ */