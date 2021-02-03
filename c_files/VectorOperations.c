#include "../headers/VectorOperations.h"

double normL1(double *v, int dim){
	int i;
  	double norm = 0;

 	for(i = 0; i < dim; i++) 
    	norm += fabs(v[i]);

  	return norm;
}

double normL2(double *v, int dim){
	int i;
	double norm = 0.0;
	for(i = 0; i < dim; i++)
		norm += pow(v[i], 2);
	norm = sqrt(norm);
	return norm;
}

double distance(double *v1, double *v2, int dim){
	int i;
	double d = 0.0;
	for(i = 0; i < dim; i++)
		d += pow(v1[i] - v2[i], 2);
	d = sqrt(d);
	return d;
}

double innerproduct(double *v1, double *v2, int dim){
	int i;
	double sum = 0.0;
	for(i = 0; i < dim; i++)
		sum += v1[i]*v2[i];
	return sum;
}


void cpyvector(double *destination, double *source, int dim){
	int i;
	for(i = 0; i < dim; i++)
		destination[i] = source[i];
	return;
}

double maxVector(double *v, int dim){
	int i;
	double max = -INFINITY;
	for(i = 0; i < dim; i++)
		if(v[i] > max)
			max = v[i];
	return max;
}


void getIdealVectorFromPop(double *min, ANT *pop, int size, int nobjs){
	int i, j;

	for(j = 0; j < nobjs; j++)
		min[j] = INFINITY;

	for(i = 0; i < size; i++)
		for(j = 0; j < nobjs; j++)
			if(pop[i].Fx[j] < min[j])
				min[j] = pop[i].Fx[j];	
}

void getNadirVectorFromPop(double *max, ANT *pop, int size, int nobjs){
	int i, j;

	for(j = 0; j < nobjs; j++)
		max[j] = -INFINITY;

	for(i = 0; i < size; i++)
		for(j = 0; j < nobjs; j++)
			if(pop[i].Fx[j] > max[j])
				max[j] = pop[i].Fx[j];	
}

double getMaxValueFromVector(double *v, int nobjs){
	int i;
	double max = -INFINITY;
	for(i = 0; i < nobjs; i++)
		if(v[i] > max)
			max = v[i];

	return max;
}