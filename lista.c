#include "lista.h"
#include <stdio.h>
#include <string.h>	
#include <stdlib.h>

lista_t* lista_crear(){
	lista_t* lista = calloc(1,sizeof(lista_t));
	if(!lista) return NULL;
	return lista;
}


int lista_insertar(lista_t* lista, void* elemento){
	if(!lista) return -1;

	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo) return -1;
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;

	if(!lista->nodo_inicio){
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
		lista->cantidad += 1;
		return 0;
	}

	lista->nodo_fin->siguiente = nuevo_nodo;
	lista->cantidad += 1;
	lista->nodo_fin = nuevo_nodo;
	return 0;
}


int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista) return -1;

	if(posicion >= lista->cantidad){
		return lista_insertar(lista, elemento);
	}

	nodo_t* nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo) return -1;
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;

	if(lista->cantidad == 0){
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_fin = nuevo_nodo;
		lista->cantidad += 1;
		return 0;
	}

	if(posicion == 0){
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		lista->cantidad += 1;
		return 0;
	}

	nodo_t* nodo_aux = lista->nodo_inicio;
	for(size_t i=0; i<posicion-1; i++){
		nodo_aux = nodo_aux->siguiente;
	}
	nuevo_nodo->siguiente = nodo_aux->siguiente;
	nodo_aux->siguiente = nuevo_nodo;
	lista->cantidad += 1;
	return 0;
}


int lista_borrar(lista_t* lista){
	if(!lista) return -1;
	if(lista_vacia(lista)) return -1;

	if(lista->cantidad == 1){
		free(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		lista->cantidad -= 1;
		return 0;
	}
	
	nodo_t* nodo_aux = lista->nodo_inicio;
	while(nodo_aux->siguiente->siguiente != NULL){
		nodo_aux = nodo_aux->siguiente;
	}
	
	free(nodo_aux->siguiente);
	nodo_aux->siguiente = NULL;

	lista->nodo_fin = nodo_aux;
	lista->cantidad -= 1;

	return 0;
}


int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(!lista) return -1;
	if(lista_vacia(lista)) return -1;
	
	if(posicion > lista->cantidad){
		return lista_borrar(lista);
	}	
	
	nodo_t* nodo_aux = lista->nodo_inicio;
	if(posicion == 0){
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		lista->cantidad -=1;
		free(nodo_aux);
		return 0;
	}

	for(size_t i=0; i<posicion-1; i++){
		nodo_aux = nodo_aux->siguiente;
	}
	nodo_t* nodo_aux_2 = nodo_aux->siguiente;
	nodo_aux->siguiente = nodo_aux->siguiente->siguiente;
	lista->cantidad -=1;
	free(nodo_aux_2);
	return 0;
}


void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(!lista || lista->cantidad == 0) return NULL;
	if(posicion >= lista->cantidad) return NULL;

	if(posicion == 0){
		return lista->nodo_inicio->elemento;
	}

	nodo_t* nodo_aux = lista->nodo_inicio;
	for(size_t i=0; i<posicion; i++){
		nodo_aux = nodo_aux->siguiente;
	}
	return nodo_aux->elemento;
}


void* lista_ultimo(lista_t* lista){
	if(!lista) return NULL;
	if(!lista->nodo_fin) return NULL;
	return lista->nodo_fin->elemento;
}


bool lista_vacia(lista_t* lista){
	if(!lista) return true;
	if(lista->nodo_inicio == NULL) return true;
	return false;
}


size_t lista_elementos(lista_t* lista){
	if(!lista) return 0;
	return lista->cantidad;
}


int lista_apilar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}
	

int lista_desapilar(lista_t* lista){
	return lista_borrar(lista);
}


void* lista_tope(lista_t* lista){
	if(!lista) return NULL;
	if(lista_vacia(lista)) return NULL;
	return lista->nodo_fin->elemento;
}


int lista_encolar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}


int lista_desencolar(lista_t* lista){
	return(lista_borrar_de_posicion(lista,0));
}


void* lista_primero(lista_t* lista){
	if(!lista) return NULL;
	if(lista_vacia(lista)) return NULL;
	return lista->nodo_inicio->elemento;
}


void lista_destruir(lista_t* lista){
	while(lista && lista->nodo_inicio != NULL){
		nodo_t* nodo_aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		lista->cantidad -= 1;
		free(nodo_aux);
	}
	
	if(lista)
		free(lista);
}


lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(!lista){
		lista_iterador_t* iterador = NULL;
		return iterador;
	}
	
	lista_iterador_t* iterador = malloc(sizeof(lista_iterador_t));
	if(!iterador) return NULL;
	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;
	
	return iterador;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador) return false;
	if(!iterador->corriente) return false;
	return true;
}


bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente) return false;
	if(iterador->corriente){
		iterador->corriente = iterador->corriente->siguiente;
	}
	return (lista_iterador_tiene_siguiente(iterador));
}


void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador) return NULL;
	if(iterador->corriente)
		return iterador->corriente->elemento;
	return NULL;
}


void lista_iterador_destruir(lista_iterador_t* iterador){
	if(iterador)
		free(iterador);
}


size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	if (!lista) return 0;
	if (!funcion) return 0;
	if (!contexto) return 0;

	if(!lista->nodo_inicio) return *(size_t*)(contexto);

	size_t elementos_recorridos = 0;

	nodo_t* nodo_aux = lista->nodo_inicio;
	for(size_t i=0; i<lista->cantidad; i++){
		void* elemento = nodo_aux->elemento;
		if(funcion(elemento, contexto)){
			nodo_aux = nodo_aux->siguiente;
			elementos_recorridos++;
		}
	}
	return elementos_recorridos;
}