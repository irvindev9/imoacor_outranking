#include "../headers/Allocate.h"

void allocate_Memory(){
	int i;
	
	Ants = (ANT *)malloc((M + MAX_ARCHIVE_SIZE)*sizeof(ANT));
	WV = (WEIGHT *)malloc(N*sizeof(WEIGHT));
	T.pheromones = (PHEROMONE *)malloc(DATA_Size*sizeof(PHEROMONE));
	T.w = (double *)calloc(MAX_ARCHIVE_SIZE, sizeof(double));
	T.p = (double *)calloc(MAX_ARCHIVE_SIZE, sizeof(double));
	T.stdDev = (double *)calloc(MAX_ARCHIVE_SIZE, sizeof(double));
	

	mark = (int *)calloc(k, sizeof(int));
	z_ideal = (double *)malloc(k*sizeof(double));
	z_nad = (double *)malloc(k*sizeof(double));
	z_min = (double *)malloc(k*sizeof(double));
	z_max = (double *)malloc(k*sizeof(double));
	lowerBounds = (double *)calloc(n, sizeof(double));
	upperBounds = (double *)calloc(n, sizeof(double));
	Fname =  (char *) malloc(sizeof(char) * MAX_CHAR);
	//R2record = (double *)calloc(MAX_R2_RECORD, sizeof(double));
	RECORD = (double *)calloc(MAX_RECORD_SIZE*k, sizeof(double));

	for(i = 0; i < M + MAX_ARCHIVE_SIZE; i++){
		Ants[i].x = (double *)calloc(n, sizeof(double));
		Ants[i].Fx = (double *)calloc(k, sizeof(double));	
		Ants[i].nFx = (double *)calloc(k, sizeof(double));	
	}

	for(i = 0; i < N; i++){
		WV[i].w = (double *)calloc(k, sizeof(double));
		WV[i].Elements = (lista *)malloc(sizeof(lista));
		Initialize(WV[i].Elements);
	}

	for(i = 0; i < DATA_Size; i++){
		// T.pheromones[i].x = (double *)calloc(n, sizeof(double));
		// T.pheromones[i].Fx = (double *)calloc(k, sizeof(double));
		T.pheromones[i].nFx = (double *)calloc(k, sizeof(double));
		T.pheromones[i].sigma = (double *)calloc(DATA_Size, sizeof(double));
		T.pheromones[i].frontier = (double *)calloc(3, sizeof(double));
	}
}

void free_Memory(){
	int i;

	for(i = 0; i < M + MAX_ARCHIVE_SIZE; i++){
		free(Ants[i].x);
		free(Ants[i].Fx);	
		free(Ants[i].nFx);	
	}

	for(i = 0; i < N; i++){
		free(WV[i].w);
		Destroy(WV[i].Elements);
		free(WV[i].Elements);
	}

	
	for(i = 0; i < MAX_ARCHIVE_SIZE; i++){
		free(T.pheromones[i].x);
		free(T.pheromones[i].Fx);
		free(T.pheromones[i].nFx);
	}


	free(Ants);
	free(WV);
	free(T.pheromones);
	free(T.w);
	free(T.p);
	free(T.stdDev);


	free(mark);
	free(z_ideal);
	free(z_nad);
	free(z_min);
	free(z_max);
	free(lowerBounds);
	free(upperBounds);
	free(Fname);
	//free(R2record);// MODIFICACION !!!!!!!!!!
	free(RECORD);
}