#include "../headers/MOMBI.h"

void R2ranking(int size){
	int i, j, rank;
	for(i = 0; i < size; i++){
		Ants[i].rank = INT_MAX;
		Ants[i].alpha = INFINITY;
	}
	for(i = 0; i < N; i++){
		for(j = 0; j < size; j++)
			Ants[j].alpha = u(Ants[j].nFx, &WV[i]);
		
		// Sort the pheromones with respect to the field alpha in increasing order.
		qsort(Ants, size, sizeof(ANT), (int (*)(const void *, const void *))&compare_ant_alpha);
		rank = 1;
		for(j = 0; j < size; j++){
			if(rank < Ants[j].rank){
				Ants[j].rank = rank;
				Ants[j].weight_index = i;
				Ants[j].u = Ants[j].alpha;
			}
			rank++;
		}
	}
}

void R2rankingPheromones(){
	int i, j, rank;
	for(i = 0; i < MAX_ARCHIVE_SIZE; i++){
		T.pheromones[i].rank = INT_MAX;
		T.pheromones[i].alpha = INFINITY;
	}
	for(i = 0; i < N; i++){
		for(j = 0; j < MAX_ARCHIVE_SIZE; j++)
			T.pheromones[j].alpha = u(T.pheromones[j].nFx, &WV[i]);
		
		// Sort the pheromones with respect to the field alpha in increasing order.
		qsort(T.pheromones, MAX_ARCHIVE_SIZE, sizeof(PHEROMONE), (int (*)(const void *, const void *))&compare_pheromone_alpha);
		rank = 1;
		for(j = 0; j < MAX_ARCHIVE_SIZE; j++){
			if(rank < T.pheromones[j].rank){
				T.pheromones[j].rank = rank;
				T.pheromones[j].weight_index = i;
				T.pheromones[j].u = T.pheromones[j].alpha;
			}
			rank++;
		}
	}
}


void initRefpoints(){
	int i, j, numSolutionsPM;
	for(i = 0; i < k; i++){
		z_ideal[i] = INFINITY;
		z_nad[i] = -INFINITY;
	}
	
	for(i = 0; i < MAX_ARCHIVE_SIZE; i++){
		for(j = 0; j < k; j++){
			if(T.pheromones[i].Fx[j] < z_ideal[j])
				z_ideal[j] = T.pheromones[i].Fx[j];
			if(T.pheromones[i].Fx[j] > z_nad[j])
				z_nad[j] = T.pheromones[i].Fx[j];	
		}
	}
}

void initRecord(){
	int i;
	for(i = 0; i < k; i++)
		RECORD[i] = z_nad[i];
}

void saveRegisterInRecord(double *RECORD, double *reg, int nobjs, int gen){
	int i, j;
	i = gen % MAX_RECORD_SIZE;
	for(j = 0; j < nobjs; j++)
		RECORD[i*nobjs + j] = reg[j];
}

double getMeanRecord(double *RECORD, int max_size, int nobjs, int component){
	int i;
	double mean = 0.0;
	for(i = 0; i < max_size; i++){
		mean += RECORD[component];
		component += nobjs; 
	}
	mean /= (double)max_size;
	return mean;
}

double getVarRecord(double *RECORD, double mean, int max_size, int nobjs, int component){
	int i = 0;
	double var = 0.0;
	for(i = 0; i < max_size; i++){
		var += pow(RECORD[component] - mean, 2.0);
		component += nobjs;
	}
	var /= (double)max_size;
	return var;
}

double getMaxValueFromRecord(double *RECORD, int max_size, int nobjs, int component){
	int i;
	double max = -INFINITY;
	for(i = 0; i < max_size; i++){
		if(RECORD[component] > max)
			max = RECORD[component];
		component += nobjs;
	}
	return max;
}

void updateRefpoints(ANT *pop, int size, int nobjs, int gen){
	double mu, v;
	int i, j;
	// Get the current ideal vector from the population
	getIdealVectorFromPop(z_min, pop, size, nobjs);
	// Update the ideal vector z_ideal
	for(i = 0; i < nobjs; i++)
		if(z_min[i] < z_ideal[i])
			z_ideal[i] = z_min[i];
	// Get the current nadir vector from the population
	getNadirVectorFromPop(z_max, pop, size, nobjs);
	// Save z_max in RECORD
	saveRegisterInRecord(RECORD, z_max, nobjs, gen);
	if(gen >= MAX_RECORD_SIZE - 1){
		for(i = 0; i < nobjs; i++){
			mu = getMeanRecord(RECORD, MAX_RECORD_SIZE, nobjs, i);
			v = getVarRecord(RECORD, mu, MAX_RECORD_SIZE, nobjs, i);
			if(v > varThreshold){
				v = getMaxValueFromVector(z_max, nobjs);
				for(j = 0; j < nobjs; j++)
					z_nad[j] = v;
				break;
			}else{
				if(fabs(z_nad[i] - z_ideal[i]) < tolThreshold){
					v = getMaxValueFromVector(z_nad, nobjs);
					z_nad[i] = v;
					mark[i] = MAX_RECORD_SIZE;
				}else if(z_max[i] > z_nad[i]){
					z_nad[i] = z_max[i] + fabs(z_max[i] - z_nad[i]);
					mark[i] = MAX_RECORD_SIZE;
				}else if(v == 0 && (z_max[i] <= mu || (z_max[i] - mu) > tolThreshold) && mark[i] == 0){
					v = getMaxValueFromRecord(RECORD, MAX_RECORD_SIZE, nobjs, i);
					z_nad[i] = (z_nad[i] + v) / 2.0;
					mark[i] = MAX_RECORD_SIZE;
				}
			}
			if(mark[i] > 0)
				mark[i]--;
		}
	}
	
}


void updateVectors(){
	int i, j;
	for(i = 0; i < M; i++){
		for(j = 0; j < k; j++){
			if(Ants[i].Fx[j] < z_ideal[j])
				z_ideal[j] = Ants[i].Fx[j];

			if(Ants[i].Fx[j] > z_nad[j])
				z_nad[j] = Ants[i].Fx[j];
		}
	}
}
