/*
*	CINVESTAV
*	Maestría en Ciencias en Computación
* 	Tesis
*	A new Multi-Objective Ant-Colony Optimization Algorithm for Continuos Spaces
*	
*	Versión 1.0 MOACO_R
*	30/Septiembre/2015
*
*	Autor: Ing. Jesús Guillermo Falcón Cardona
*	Asesor: Dr. Carlos A. Coello Coello
*	Descripción: Archivo de cabecera para el conjunto de funciones objetivo
*	de prueba  (ZDT y DTLZ).
*	
*	ObjectiveFunctions.h
*/
#ifndef __OBJECTIVE_FUNCTIONS_H__
#define __OBJECTIVE_FUNCTIONS_H__

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "WFG.h"
#include "../Global.h"

void findfunc(char *nom, void (**apf)(double *, double *));

void ZDT1(double *x, double *F);
void ZDT2(double *x, double *F);
void ZDT3(double *x, double *F);
void ZDT4(double *x, double *F);
void ZDT6(double *x, double *F);
void DTLZ1(double *x, double *F);
void DTLZ2(double *x, double *F);
void DTLZ3(double *x, double *F);
void DTLZ4(double *x, double *F);
void DTLZ5(double *x, double *F);
void DTLZ6(double *x, double *F);
void DTLZ7(double *x, double *F);

#endif