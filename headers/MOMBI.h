#ifndef __MOMBI_H__
#define __MOMBI_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "VectorOperations.h"
#include "ScalarizingFunctions.h"
#include "Comparisons.h"
#include "../Global.h"

#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

void R2ranking(int);
void R2rankingPheromones();
void initRefpoints();
void saveRegisterInRecord(double *, double *, int, int);
double getMeanRecord(double *, int, int, int);
double getVarRecord(double *, double, int, int, int);
void updateRefpoints(ANT *, int, int, int);
void initRecord();
void updateVectors();
double R2();
double varianceR2record(); // MODIFICACION !!!!!!!!!!



#endif