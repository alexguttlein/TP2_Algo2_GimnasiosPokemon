#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

#define ERROR -1
#define OK 0

heap_t* heap_crear(heap_comparador comparador){
	heap_t* heap = calloc(1, sizeof(heap_t));
	heap->comparador = comparador;
	return heap;
}


int posicion_padre(int n){
	return (n-1)/2;
}


int posicion_hijo_derecho(int n){
	return 2*n+2;
}


int posicion_hijo_izquierdo(int n){
	return 2*n+1;	
}


void swap(void** vector, int i, int j){
	void* aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

// HEAP MINIMAL
void sift_up(heap_t* heap, int n){
	if (n==0)
		return;
	
	int padre = posicion_padre(n);

	if(heap->comparador(heap->vector[n], heap->vector[padre]) == -1){
		swap(heap->vector, n, padre);
		sift_up(heap, padre);
	}
}


int heap_insertar(heap_t* heap, void* elemento){
	
	void* aux = realloc(heap->vector, sizeof(elemento) * (heap->tope+1));
	if (!aux) return ERROR;

	heap->tope ++;
	heap->vector = aux;
	heap->vector[heap->tope-1] = elemento;

	sift_up(heap, heap->tope-1);

	return OK;
}


void* heap_raiz(heap_t* heap){
	return heap->vector[0];
}


void sift_down(heap_t* heap, int n){
	int pos_der = posicion_hijo_derecho(n); 
	int pos_izq = posicion_hijo_izquierdo(n);
	int pos_menor = pos_izq;

	if(pos_izq >= heap->tope)
		return;

	if(pos_der < heap->tope){
		if(heap->comparador(heap->vector[pos_der] , heap->vector[pos_izq]) == -1)
			pos_menor = pos_der;
	}

	if(heap->comparador(heap->vector[n] , heap->vector[pos_menor]) == 1){
		swap(heap->vector, n, pos_menor);
		sift_down(heap, pos_menor);
	}

}


void* heap_extraer_raiz(heap_t* heap){

	if(heap->tope == 0)
		return NULL;

	void* valor = heap->vector[0];

	heap->vector[0] = heap->vector[heap->tope-1];
	heap->tope--;

	void* aux = realloc(heap->vector, sizeof(heap) * (heap->tope));
	if (!aux) return NULL;

	if(heap->tope != 0)
		sift_down(heap, 0);

	return valor;
}


bool heap_vacio(heap_t* heap){
	if(!heap->vector) return true;
	return false;
}


void heap_destruir(heap_t* heap){
	if(heap)
		free(heap->vector);
	free(heap);
}



/*
int main(){
	heap_t* heap = heap_crear();

	heap_insertar(heap,1);
	heap_insertar(heap,2);
	heap_insertar(heap,3);
	heap_insertar(heap,4);
	heap_insertar(heap,5);
	heap_insertar(heap,6);
	heap_insertar(heap,7);
/*
	heap_insertar(heap,1);
	heap_insertar(heap,10);
	heap_insertar(heap,25);
	heap_insertar(heap,40);
	heap_insertar(heap,23);
	heap_insertar(heap,5);
	heap_insertar(heap,7);
	heap_insertar(heap,12);
	heap_insertar(heap,17);
	heap_insertar(heap,21);
*/
//	mostrar_arbol(heap->vector, heap->tope);
	
/*	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));

	mostrar_arbol(heap->vector, heap->tope);

	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
	mostrar_arbol(heap->vector, heap->tope);

	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
	mostrar_arbol(heap->vector, heap->tope);

	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
	mostrar_arbol(heap->vector, heap->tope);

	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
	mostrar_arbol(heap->vector, heap->tope);

	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
	mostrar_arbol(heap->vector, heap->tope);

	printf("Extraigo raiz (valor %i)\n", heap_extraer_raiz(heap));
	mostrar_arbol(heap->vector, heap->tope);

	if(heap->tope == 0) printf("GANASTE!!\n");

	heap_destruir(heap);

	return 0;
}*/