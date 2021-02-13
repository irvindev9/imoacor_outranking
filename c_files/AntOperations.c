#include "../headers/AntOperations.h"

void cleanSubregions(){
	int i;
	for(i = 0; i < N; i++){
		Destroy(WV[i].Elements);
		WV[i].nicheCount = 0;
	}
}

void dividePheromones(PHEROMONE *pheromones, int size){
	int i, j,subregIndex;
	double cosValue = -INFINITY, aux;

	for(i = 0; i < size; i++){
		for(j = 0; j < N; j++){
			aux = innerproduct(pheromones[i].Fx, WV[j].w, k) / (normL2(pheromones[i].Fx, k)*normL2(WV[j].w, k));
			if(aux > cosValue){
				cosValue = aux;
				subregIndex = j;
			}
		}
		elemento e;
		e.value = subregIndex;

		Add(WV[subregIndex].Elements, e);
		WV[subregIndex].nicheCount++;

		cosValue = -INFINITY;
	}
}


void normalizeObjFuncs(int size, int type){
	int i, j;
	double v;	
	for(i = 0; i < size; i++){
		for(j = 0; j < k; j++){
			v = z_nad[j] - z_ideal[j];
			if(type == _ANTS_TYPE_)
				Ants[i].nFx[j] = (v == 0.0)? Ants[i].Fx[j] : (Ants[i].Fx[j] - z_ideal[j])/v;
			else if(type == _PHE_TYPE_)
				T.pheromones[i].nFx[j] = (v == 0.0)? T.pheromones[i].Fx[j] : (T.pheromones[i].Fx[j] - z_ideal[j])/v;
		}
	}
}

void initPheromones(){
	int i, j;
	for(i = 0; i < MAX_ARCHIVE_SIZE; i++){
		for(j = 0; j < n; j++)
			T.pheromones[i].x[j] = rndreal(lowerBounds[j], upperBounds[j]);
		(*F)(T.pheromones[i].x, T.pheromones[i].Fx);
	}
	// Initialize Number of Active Pheromones (nap) as the MAXIMUM_ARCHIVE_SIZE.
	T.nap = MAX_ARCHIVE_SIZE;
}


void sortPheromones(){
	qsort(T.pheromones, T.nap, sizeof(PHEROMONE), (int (*)(const void *, const void *))&compare_rank_and_mmf);
}

void AntBasedSolutionConstruction(){
	int index; 
	double S;
	S = calculateWeights();
	calculateProbabilities(S);
	chooseGaussianKernels(S);
	for(index = 0; index < n; index++){
		calculateStdDev(index);
		sampling(index);
	}
	evaluatePheromones();
}

double calculateWeights(){
	int i, size = T.nap;
	double S = 0.0;
	for (i = 0; i < size; i++){
        T.w[i] = exp (-1.0*pow(T.pheromones[i].rank - 1.0, 2)/(2.0*pow(q, 2)*pow(size, 2)))/(q*size*sqrt(2.0*M_PI));  // $%$ rank hay que cambiar
        S += T.w[i];
    }
    return S;
}

void calculateProbabilities(double S){
	int i, size = T.nap;
	for(i = 0; i < size; i++)
		T.p[i] = T.w[i]/S;
}

void chooseGaussianKernels(){
	int i;
	for(i = 0; i < M; i++)
		Ants[i].kernelIndex = rouletteWheelSelection();	
}

int rouletteWheelSelection(){
	int *players, i, size = T.nap, result;
	//printf("t.nap = %d\n", size);
	double r, sum = 0.0;
	players = (int *)malloc(size*sizeof(int));

	for(i = 0; i < size; i++)
		players[i] = i;

	shuffling(players, size);

	r = rndreal(0.0, 1.0);	
	for(i = 0; i < size; i++){
		sum += T.p[players[i]];
		if(sum >= r){
			result = players[i];
			free(players);
			return result;
		}
	}
	free(players);
	return 0;
}

void calculateStdDev(int index){
	int i, j, size = T.nap;
	for (i = 0; i < size; i++) {
      	T.stdDev[i] = 0.0;
      	for (j = 0; j < size; j++)
         	T.stdDev[i] += fabs (T.pheromones[j].x[index] - T.pheromones[i].x[index]);
      	T.stdDev[i] *= Xi/((double)size - 1.0);
   	}
}

void sampling(int index){
	int i, selectedKernel;
	for (i = 0; i < M; i++) {
    	selectedKernel = Ants[i].kernelIndex;
    	Ants[i].x[index] = Normal(T.pheromones[selectedKernel].x[index], T.stdDev[selectedKernel], index);
   	}
}

#ifdef POLAR
double Normal(double mean, double stdDev, int index){
	double U1, U2, V1, V2, Z, X, R;
	
	do{
		do{
			U1 = rndreal(0, 1);
		}while(U1 == 0.0 || U1 == 1.0);

		do{
			U2 = rndreal(0, 1);
		}while(U2 == 0.0 || U1 == 1.0);

		V1 = 2*U1 - 1;
		V2 = 2*U2 - 1;

		R = pow(V1, 2) + pow(V2, 2);

	}while(R > 1);

	if(flip(0.5))
		Z = V1*sqrt(-2.0*log(R)/R);
	else
		Z = V2*sqrt(-2.0*log(R)/R);
	X = stdDev*Z + mean;
	
	if(X < lowerBounds[index])
		X = lowerBounds[index];
	else if(X > upperBounds[index])
		X = upperBounds[index];

	return X;
}
#endif


#ifdef BOX_MULLER
double Normal(double mean, double stdDev, int index){
	double U1, U2, Z, X;
	do{				
		do{
			U1 = rndreal(0, 1);
		}while(U1 == 0.0 || U1 == 1.0);

		do{
			U2 = rndreal(0, 1);
		}while(U2 == 0.0 || U1 == 1.0);

		if(flip(0.5))
			// Standard random variable (media = 0, desvStd = 1)
			Z = sqrt(-2.0*log(U1))*cos(2.0*M_PI*U2);
		else
			// Standard random variable (media = 0, desvStd = 1)
			Z = sqrt(-2.0*log(U1))*sin(2.0*M_PI*U2);
		/* Transformando la variable aleatoria normal estándar Z, a una variable 
		aleatoria normal con media y desviación tomadas del archivo de soluciones
		previamente.
		*/
		X = Z*stdDev + mean;
	}while(X < lowerBounds[index] || X > upperBounds[index]);
	return X;
}
#endif

void evaluatePheromones(){
	int i;
	for(i = 0; i < M; i++)
		(*F)(Ants[i].x, Ants[i].Fx);	
}

void PheromoneUpdate(int size){
	int i, aux_index;		
	// Updating the archive
	qsort(Ants, size, sizeof(ANT), (int (*)(const void *, const void *))&compare_ant_alpha_or);
	for(i = 0; i < MAX_ARCHIVE_SIZE; i++){
		cpyvector(T.pheromones[i].x, Ants[i].x, n);
		cpyvector(T.pheromones[i].Fx, Ants[i].Fx, k);
		cpyvector(T.pheromones[i].nFx, Ants[i].nFx, k);
	}
	/*int *used, cont = 0, j;
	used = (int *)calloc(N, sizeof(int));
	// Copiar las soluciones con rank = 1 (primer frente)
	for(i = 0; i < size; i++){
		if(Ants[i].rank == 1 && cont < N){
			used[Ants[i].weight_index] = 1;
			cpyvector(T.pheromones[cont].x, Ants[i].x, n);
			cpyvector(T.pheromones[cont].Fx, Ants[i].Fx, k);
			cpyvector(T.pheromones[cont].nFx, Ants[i].nFx, k);
			Ants[i].USED = 1;
			cont++;
		}
	}

	printf("He encontrado %d sol. con rank = 1\n", cont);
	// Si aún quedan lugares que llenar
	if(cont < N){
		for(i = 0; i < N; i++){
			if(used[i] == 0){
				for(j = 0; j < size; j++){
					if(Ants[j].USED == 0 && Ants[j].weight_index == i){
						used[i] = 1;
						cpyvector(T.pheromones[cont].x, Ants[j].x, n);
						cpyvector(T.pheromones[cont].Fx, Ants[j].Fx, k);
						cpyvector(T.pheromones[cont].nFx, Ants[j].nFx, k);
						Ants[j].USED = 1;
						cont++;
						break;
					}
				}
			}
		}
	}
	if(cont < N){
		for(i = 0; i < size; i++){
			if(Ants[i].USED == 0){
				cpyvector(T.pheromones[cont].x, Ants[i].x, n);
				cpyvector(T.pheromones[cont].Fx, Ants[i].Fx, k);
				cpyvector(T.pheromones[cont].nFx, Ants[i].nFx, k);
				Ants[i].USED = 1;
				cont++;
			}
			if(cont >= N) break;
		}
	}
	for(i = 0; i < size; i++)
		Ants[i].USED = 0;
	free(used);*/
	T.nap = MAX_ARCHIVE_SIZE;	
}

void Union(){
	int i;
	for(i = M; i < M + T.nap; i++){
		cpyvector(Ants[i].x, T.pheromones[i - M].x, n);
		cpyvector(Ants[i].Fx, T.pheromones[i - M].Fx, k);
		cpyvector(Ants[i].nFx, T.pheromones[i - M].nFx, k);
	}
}

void shuffling(int *indexes, int size){
	int i, rand1, rand2, temp;
	for (i = 0; i < size; i++){
		rand1 = rnd(i, size - 1);
		rand2 = rnd(i, size - 1);
		temp = indexes[rand1];
		indexes[rand1] = indexes[rand2];
		indexes[rand2] = temp;
	}
}

void sortAnts(int size){
	qsort(Ants, size, sizeof(ANT), (int (*)(const void *, const void *))&compare_Ants_rank_and_mmf);
}

void real_mutate (double *x, double pm, double eta_m) {
	int i, j, flag = 0;
  	double rnd, delta1, delta2, mut_pow, deltaq;
  	double y, yl, yu, val, xy;

  	
	for (j = 0; j < n; j++) {
		if (flip(pm)) {
			y = x[j];
			yl = lowerBounds[j];
			yu = upperBounds[j];
			delta1 = (y - yl)/(yu - yl);
			delta2 = (yu - y)/(yu - yl);
			rnd = rndreal(0, 1);
			mut_pow = 1.0/(eta_m + 1.0);

			if (rnd <= 0.5) {
			xy = 1.0 - delta1;
			val = 2.0*rnd + (1.0 - 2.0*rnd)*(pow(xy,(eta_m + 1.0)));
				deltaq =  pow(val,mut_pow) - 1.0;
			}else {
			xy = 1.0-delta2;
				val = 2.0*(1.0-rnd)+2.0*(rnd-0.5)*(pow(xy,(eta_m+1.0)));
			deltaq = 1.0 - (pow(val,mut_pow));
			}

			y = y + deltaq*(yu-yl);

			if (y<yl) y = yl;
			if (y>yu) y = yu;

			x[j] = y;
			
		}
	}
	
}