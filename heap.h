#ifndef __ARBOL_BINARIO_DE_BUSQUEDA_H__
#define __ARBOL_BINARIO_DE_BUSQUEDA_H__

#include <stdbool.h>

typedef int (*heap_comparador)(void*, void*);

typedef struct{
	void** vector;
	int tope;
	heap_comparador comparador;
}heap_t;

heap_t* heap_crear(heap_comparador comparador);

int posicion_padre(int n);

int posicion_hijo_derecho(int n);

int posicion_hijo_izquierdo(int n);

void swap(void** vector, int i, int j);

void sift_up(heap_t* heap, int n);

int heap_insertar(heap_t* heap, void* elemento);

void sift_down(heap_t* heap, int n);

void heap_destruir(heap_t* heap);

void* heap_raiz(heap_t* heap);

void* heap_extraer_raiz(heap_t* heap);

bool heap_vacio(heap_t* heap);

#endif /* __ARBOL_BINARIO_DE_BUSQUEDA_H__ */