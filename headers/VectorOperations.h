#ifndef __VECTOR_OPERATIONS_H__
#define __VECTOR_OPERATIONS_H__

#include "../Global.h"
#include <math.h>

double normL1(double *v, int dim);
double normL2(double *v, int dim);
double distance(double *v1, double *v2, int dim);
double innerproduct(double *v1, double *v2, int dim);
void cpyvector(double *destination, double *source, int dim);
double maxVector(double *v, int dim);

void getIdealVectorFromPop(double *, ANT *, int, int);
void getNadirVectorFromPop(double *, ANT *, int, int);
double getMaxValueFromVector(double *, int);

#endif