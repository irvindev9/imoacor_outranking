/*
*	CINVESTAV
*	Maestría en Ciencias en Computación
* 	Tesis
*	A new Ant-Colony Multiobjective Optimization algorithm for Continuos Spaces
*
*	Descripción: Implementación de las funciones
* 	para generar números aleatorios. Estas funciones
*	pertenecen al Simple Genetic Algorithm de
* 	David Goldberg.
*	
*	rand.c
*/

#include "../headers/Rand.h"

/*
	Función: rndreal
	Params:
		lo : float -> límite inferior.
		hi : float -> límite superior.
	Return 
		float -> número aletorio escogido.
	Descricpión: Elije un número aleatorio 
	p tal que lo <= p <= hi.
*/
float rndreal(float lo ,float hi){
    return((randomperc() * (hi - lo)) + lo);
}

/*
	Función: rnd
	Params:
		low : int -> límite inferior.
		high : int -> límite superior.
	Return 
		int -> número entero aletorio escogido.
	Descricpión: Elije un número entero aleatorio 
	p tal que low <= p <= high.
*/
int rnd(int low, int high){
    int i;
    if(low >= high)
		i = low;
    else{
		i = (randomperc() * (high - low + 1)) + low;
		if(i > high) 
			i = high;
    }
    return i;
}

/*
	Función: randomize
	Params: void
	Return: void
	Descripción: Inicializa el lote de números aleatorios.
	Esta función fue tomada del código aportado por el
	Dr. Coello.
*/
void randomize(){
    int j;
    for(j = 0; j < 55; j++)
      oldrand[j] = 0.0;
    jrand=0;
    warmup_random(Rseed);
}

/*
	Función: warmup_random
	Params:
		random_seed : float -> semilla para números aleatorios.
	Return: void
	Descripción: Remueve un aleatorio y continúa. Esta función 
	fue tomada del código aportado por el Dr. Coello. 
*/
void warmup_random(float random_seed){
    int j, i;
    double new_random, prev_random;
    oldrand[54] = random_seed;
    new_random = 0.000000001;
    prev_random = random_seed;
    for(j = 1 ; j < 55; j++){
		i = (21*j)%54;
		oldrand[i] = new_random;
		new_random = prev_random - new_random;
		if(new_random < 0.0) 
			new_random = new_random + 1.0;
		prev_random = oldrand[i];
    }
    advance_random();
    advance_random();
    advance_random();
    jrand = 0;
}

/* 
	Función: flip
	Params: 
		prob : float -> probabilidad del flip.
	Return:
		int -> Valor 0 ó 1 dependiendo del flip.
	Descripción: Simulación del lanzamiento de una 
	moneda con probabilidad prob.
*/
int flip(float prob){
    if(randomperc() <= prob)
		return 1;
    else
		return 0;
}

/* 	
	Fetch a single random number between 0.0 and 1.0 - Subtractive Method
	See Knuth, D. (1969), v. 2 for details 
	name changed from random() to avoid library conflicts on some machines
*/

/*
	Función: randomperc
	Params: void
	Return 
		float -> número aleatorio en el intervalo [0, 1].
	Descripción: Toma un número aleatorio entre 0 y 1. Método 
	subtractivo. Ver Knuth, D. (1969), v. 2 para más detalles.
*/
float randomperc(){
    jrand++;
    if(jrand >= 55){
		jrand = 1;
		advance_random();
    }
    return (float)oldrand[jrand];
}

/*
	Función: advance_random
	Params: void
	Return: void
	Descripción: Genera el siguiente lote de 55
	números aleatorios. Función tomada del código
	aportado por el Dr. Coello.
*/
void advance_random(){
    int j;
    double new_random;
    for(j = 0; j < 24; j++){
		new_random = oldrand[j] - oldrand[j + 31];
		if(new_random < 0.0) 
			new_random = new_random + 1.0;
		oldrand[j] = new_random;
    }
    for(j = 24; j < 55; j++){
		new_random = oldrand [j] - oldrand [j - 24];
		if(new_random < 0.0) 
			new_random = new_random + 1.0;
		oldrand[j] = new_random;
    }
}