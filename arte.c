#include "arte.h"

typedef char string_t[50];

void mostrar_medalla(char* ruta){
	FILE* archivo = fopen(ruta, "r");
	string_t texto;
	fgets(texto, 50, archivo);

	while(!feof(archivo)){
		printf("%s",texto);
		fgets(texto, 50, archivo);
	}
	printf("%s\n",texto);
	fclose(archivo);
}

void arte_medallas(gimnasio_t* gimnasio){
	
	if(strcmp(gimnasio->tipo , "Roca") == 0)
		mostrar_medalla("arte/medalla_roca.txt");
	if(strcmp(gimnasio->tipo , "Agua") == 0)
		mostrar_medalla("arte/medalla_cascada.txt");
	if(strcmp(gimnasio->tipo , "Electrico") == 0)
		mostrar_medalla("arte/medalla_trueno.txt");
	if(strcmp(gimnasio->tipo , "Planta") == 0)
		mostrar_medalla("arte/medalla_arcoiris.txt");
	if(strcmp(gimnasio->tipo , "Veneno") == 0)
		mostrar_medalla("arte/medalla_alma.txt");
	if(strcmp(gimnasio->tipo , "Psiquico") == 0)
		mostrar_medalla("arte/medalla_pantano.txt");
	if(strcmp(gimnasio->tipo , "Fuego") == 0)
		mostrar_medalla("arte/medalla_volcan.txt");
	if(strcmp(gimnasio->tipo , "Tierra") == 0)
		mostrar_medalla("arte/medalla_hoja.txt");
}