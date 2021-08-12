# TP2_Algo2_GimnasiosPokemon
TP2 Algoritmos y Programación II - Batallas de Gimnasios Pokemon

INTRODUCCIÓN
Este proyecto busca emular las batallas de los Gimnasios de Pokemon. El objetivo es enfrentar a los diferentes entrenadores y líderes para
poder obtener las diferentes medallas que permiten acceder a la Liga Pokemon.

ARCHIVOS
El trabajo consta de los siguientes archivos:
- batallas.h: contiene los prototipos de las funciones de batalla.
- batallas.c: contiene las funciones con la lógica que determina al ganador de cada combate entre Pokemones. Cada Gimnasio seguirá las reglas
de una de estas funciones, esta elección se basará en el "id" que posea cada uno de ellos.
- aventura.h: biblioteca principal del juego. Contiene los prototipos de las funciones que determinan el desarollo del juego además de las 
estructuras utilizadas por el mismo.
- aventura.c: en este archivo estan implementadas las funciones de la biblioteca "aventura.h". Las formas en que están implementadas las funciones
no son conocidas por el usuario, sino que éste sólo puede acceder a los encabezados y sus explicaciones mediante el "aventura.h".
- heap.h: biblioteca que contiene los prototipos de un heap, el cual será utilizado para almacenar los gimnasios del juego.
- heap.c: implementación de las funciones del heap. En este caso el heap implementado es para elementos genéricos que serán ordenados de menor
a mayor (heap minimal). Para poder realizar sus funciones es necesario que el usuario brinde una funcion comparadora (en el juego se comparan 
los niveles de dificultad de cada Gimnasio)
- lista.h: Biblioteca que contiene los prototipos de las funciones de listas enlazadas, pilas y colas, con sus explicaciones correspondientes, 
a las que se podrá llamar para realizar las diferentes acciones que el programa requiere. En éste estan además las estructuras principales de la 
biblioteca. El usuario puede tener acceso a este archivo para conocer la forma de utilizar esta biblioteca, pero no puede realizarle modificaciones.
- lista.c: en este archivo están implementadas las funciones de la biblioteca "lista.h". La forma de implementar estas funciones no son conocidas 
por el usuario, sino que éste solo deberá tener acceso a los encabezados de las mismas (del archivo lista.h). En el juego se utilizan diferentes 
tipos de listas para ordenar a los Pokemones y a los entrenadores.
- menus.h: biblioteca creada para mantener mayor orden en el código. Contiene los prototipos de las funciones en donde el usuario debe interactuar 
con el juego y decidir que acciones realizar en cada momento.
- menus.c: contiene la implementación de las funciones de "menus.h"
- game.c: en este archivo se encuentra el main del juego, se definen las variables principales como el entrenador y el heap y se llama a las diferentes
funciones de "aventura.h" a medida que avanza la partida.
- arte.h: biblioteca que contiene los prototipos de las funciones de "arte.c".
- arte.c: se implementan las funciones de "arte.h". Creado sólo para añadir ilustraciones como las medallas que ganará el entrenador en el transcurso
del juego. Se utilizan "ASCII Arts" creados por el programador. No son esenciales para el desarrollo del juego pero proveen algunos dibujos al mismo.
Además se cuenta con tres carpetas adicionales:
- arte: contiene los archivos de los "ASCII Arts" descriptos anteriormente.
- entrenador: contiene el archivo del entrenador que utilizará el usuario. En el mismo se encuentra el nombre del personaje junto con todos sus pokemones
iniciales y sus características (tipo, velocidad, defensa, ataque).
- gimnasios: contiene el archivo con el detalle de cada Gimnasio junto con su líder y el resto de los entrenadores a los cuales se deberá combatir. Además 
contiene un par de archivos de prueba que demuestran que el programa acepta que se ingresen más de un Gimnasio (o todos) desde un mismo archivo.

ESTRUCTURAS
Para el juego se utilizaron tres estructuras principales:
- pokemon_t: es la estructura donde se definen las características de cada Pokemon que tendrán relevancia en el juego y sobre todo en las batallas.
- entrenador_t: en esta estructura se encuentran los datos que van a definir a cada entrenador, ya sea el personaje principal del juego como los rivales 
a los cual se deberá enfrentar (entrenadores y líderes de Gimnaiso). El detalle a tomar en cuenta es la manera en que se decidió almacenar a los Pokemones 
de cada uno mediante la creación de una lista enlazada para cada entrenador. Esta es una de las razones por la que se utilizó la biblioteca "lista.h". Los 
mismos podrían haberse almacenado en otras estructuras como por ejemplo un vector dinámico o un árbol, pero el programador decidió que su elección era la
más conveniente.
- gimnasio_t: ésta, como su nombre lo indica, es la estructura que posee cada Gimnasio. Debido a que los archivos de cada Gimnasio tenían ordenados a los 
entrenadores en el orden inverso a cómo debían ser enfrentados, se determinó que la manera más eficiente de almacenarlos sería mediante una pila.
Además, siempre que se necesite mostrar todos los Pokemones de un enternador, se utiliza un iterador externo (función de lista.h) para recorrerlo.

La lógica del juego dicta que, como se explicó anteriormente, los Pokemones se almacenan en listas enlazadas dentro de la estructura de cada entrenador; 
los entrenadores se apilan al iniciar la partida y se desapilan a medida que el personaje principal los vaya derrotando; y por último los Gimnasios se 
insertan en un heap minimal ordenado según la dificultad de cada uno. De esta manera, el Gimnasio a enfrentar siempre se encontrará en la raíz y, cuando 
sea derrotado (y el personaje gane la medalla del mismo), se eliminará facilmente extrayendo la raíz.

El juego cuenta además con una opción de simulación, en donde el usuario no interactúa con el programa sino que sólo se le informa al mismo si obtuvo la 
victoria o si fue derrotado.
