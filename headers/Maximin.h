#ifndef __MAXIMIN_H__
#define __MAXIMIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../Global.h"

double maximin(double *F1, double *F2, int dim);
void MMFCalculation(PHEROMONE *, int);
void MMFCalculationColony(ANT *, int);

#endif