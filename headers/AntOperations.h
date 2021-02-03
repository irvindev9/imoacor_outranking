#ifndef __ANTOPERATIONS_H__
#define __ANTOPERATIONS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define POLAR
#define _ANTS_TYPE_ 0
#define _PHE_TYPE_ 1
//#define BOX_MULLER


#include "Rand.h"
#include "VectorOperations.h"
#include "Comparisons.h"
#include "ScalarizingFunctions.h"
#include "Maximin.h"
#include "../Global.h"

void dividePheromones(PHEROMONE *, int);
void normalizeObjFuncs(int, int);
void initPheromones();
void sortPheromones();
void AntBasedSolutionConstruction();
double calculateWeights();
void calculateProbabilities(double);
void chooseGaussianKernels();
void calculateStdDev(int);
void sampling(int);
double Normal(double, double, int);
void evaluatePheromones();
void PheromoneUpdate();
int rouletteWheelSelection();

void Union();
void shuffling(int *, int);

void real_mutate(double *, double, double);


#endif