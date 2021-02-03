#include "../headers/Maximin.h"


double maximin(double *F1, double *F2, int dim){
	double min = INFINITY, diff;
	int i;
	for(i = 0; i < dim; i++){
		diff = F1[i] - F2[i];
		if(diff < min)
			min = diff;
	}
	return min;
}


void MMFCalculation(PHEROMONE *pheromones, int size){
	int i, j;
	double max, aux_maximin;
	for(i = 0; i < size; i++){
		max = -INFINITY;
		for(j = 0; j < size; j++){
			if(j != i){
				aux_maximin = maximin(pheromones[i].Fx, pheromones[j].Fx, k);
				if(aux_maximin > max)
					max = aux_maximin;
			}
		}
		pheromones[i].mmf = -1.0*max; // In this way, nondominanted individuals will have a positive mmf.
	}
}

void MMFCalculationColony(ANT *ants, int size){
	int i, j;
	double max, aux_maximin;
	for(i = 0; i < size; i++){
		max = -INFINITY;
		for(j = 0; j < size; j++){
			if(j != i){
				aux_maximin = maximin(ants[i].Fx, ants[j].Fx, k);
				if(aux_maximin > max)
					max = aux_maximin;
			}
		}
		ants[i].mmf = -1.0*max; // In this way, nondominanted individuals will have a positive mmf.
	}
}

