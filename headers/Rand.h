/*
*	CINVESTAV
*	Maestría en Ciencias en Computación
* 	Tesis
*	A new Ant-Colony Multiobjective Optimization algorithm for Continuos Spaces
*	
*	Descripción: Declaración de funciones y variables
*	para el generador de números aleatorios. Éstas han sido 
* 	tomadas del Simple Genetic Algorithm de David Goldberg.
*	
*	rand.h
*/
#ifndef __RAND_H__
#define __RAND_H__

#include "../Global.h"

double oldrand[55];              	/* Arreglo para lote de 55 números aleatorios */
int jrand;							/* Índice del actual número aleatorio */

/* RANDOM FUNCTIONS */
float rndreal(float lo, float hi);
int rnd(int low, int high);
void randomize();
void warmup_random(float random_seed);
int flip(float prob);
float randomperc();
void advance_random();

#endif