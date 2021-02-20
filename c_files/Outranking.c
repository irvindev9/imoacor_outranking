#include "../headers/Outranking.h"

float Epsilon = 0.1; // 0.05 a 0.1
float Beta = 0.35; // 0.25 a 0.4
float Lamdba = 0.6; // 0.55 a 0.75
float weights[5];

float valueU = 0.05; // 0.01 a 0.06 > .04 y .01
float valueS = 0.1; // 0.1 a 0.16 > (veto + indiferencia) / 2
float valueV = 0.2; // 0.2 a 0.3 > 0.10 y 0.20

// Restar los valores en ese objetivo y dividirlos sobre el valor de ese parametro en sigma

// Preferences dictionary
// 1 = Strict preference
// 2 = Indifference
// 3 = Weak preference
// 4 = Incomparability
// 5 = k-Preference
// 0 = null

void readData(){
    int i, j;
    for(i = 0; i < T.nap; i++){	
        printf("%d *- ", i);
		for(j = 0; j < k; j++){
			printf("%f", T.pheromones[i].Fx[j]);
			if(j != k - 1){
				printf("\t");
			}
		}
		printf("\n");
	}
}

void ORankingPheromones(int size){
	int i, j;

	float concordanciaArray[T.nap][T.nap];
	float discordanciaArray[T.nap][T.nap];
	float sigmaArray[T.nap][T.nap];
	float preferencesArray[T.nap][T.nap];
	float frontierArray[T.nap][3]; // 0 = strict, 1 = weak - k, 2 = flujo neto

	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			concordanciaArray[i][j] = concordance(i, j);
			discordanciaArray[i][j] = discordance(i, j);

			sigmaArray[i][j] = concordanciaArray[i][j] * discordanciaArray[i][j];
		}
	}

	float netscore[T.nap];

	for(i = 0; i < T.nap; i++){
		netscore[i] = 0;
		for(j = 0; j < T.nap; j++){
			netscore[i] += (sigmaArray[i][j] - sigmaArray[j][i]);
		}
	}
	
	for(i = 0; i < T.nap; i++){	
		frontierArray[i][0] = 0;
		frontierArray[i][1] = 0;
		frontierArray[i][2] = 0;
		for(j = 0; j < T.nap; j++){
			if(i != j){
				preferencesArray[i][j] = preferenceIdentifier(sigmaArray[i][j], sigmaArray[j][i], xdominatey(i, j));

				// Estrictamente dominada
				if(preferencesArray[i][j] == 1){
					frontierArray[i][0] += 1;
				}

				// Debilmente dominadas / k-preferencia
				if(preferencesArray[i][j] == 3 || preferencesArray[i][j] == 5){
					frontierArray[i][1] += 1;
				}

				//Flujo neto
				if(netscore[j] > netscore[i]){
					frontierArray[i][2] += 1;
				}
				
			}else{
				preferencesArray[i][j] = 0;
			}
		}
	}

	FILE *arch;
	char str[100] = "output/test/test.txt";
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}

	for(i = 0; i < T.nap; i++){	
		fprintf(arch, "Index: %d (%d, %d, %d)\n", i, (int)frontierArray[i][0], (int)frontierArray[i][1], (int)frontierArray[i][2]);
		T.pheromones[i].strictOR = (int)frontierArray[i][0];
		T.pheromones[i].weakOR = (int)frontierArray[i][1];
		T.pheromones[i].netscoreOR = (int)frontierArray[i][2];
	}
	
	qsort(T.pheromones, MAX_ARCHIVE_SIZE, sizeof(PHEROMONE), (int (*)(const void *, const void *))&compare_pheromone_alpha_or);

	for(i = 0; i < T.nap; i++){	
		fprintf(arch, "Index: %d (%d, %d, %d)\n", i, T.pheromones[i].strictOR, T.pheromones[i].weakOR, T.pheromones[i].netscoreOR);
	}

	fclose(arch);

}

void initValues(int dm){
	int i, j;

	FILE *archivo;
	char str[100];
	sprintf(str, "output/DM%d_config.txt", dm);
	archivo = fopen(str, "r");
	if(archivo == NULL){
		printf("The file %s couldn't be found... creating..\n", str);
		// exit(-1);
		archivo = fopen(str, "w");
		// Weights
		fprintf(archivo, "%f ", 0.05);
		fprintf(archivo, "%f ", 0.04);
		fprintf(archivo, "%f ", 0.01);
		fprintf(archivo, "%f ", 0.2);
		fprintf(archivo, "%f ", 0.05);
		fprintf(archivo, "%f ", 0.05);
		fprintf(archivo, "%f ", 0.01);
		fprintf(archivo, "%f ", 0.09);
		fprintf(archivo, "%f ", 0.35);
		fprintf(archivo, "%f\n", 0.15);

		float vetoArray[k];
		float indiferenciaArray[k];
		// veto
		for(i = 0;i < k; i++){
			vetoArray[i] = generateRandomValue(0.10, 0.20);
			fprintf(archivo, "%f", vetoArray[i]);
			if(i == (k-1)){
				fprintf(archivo, "\n");
			}else{
				fprintf(archivo, " ");
			}
		}

		// indiferencia
		for(i = 0;i < k; i++){
			indiferenciaArray[i] = generateRandomValue(0.01, 0.04);
			fprintf(archivo, "%f", indiferenciaArray[i]);
			if(i == (k-1)){
				fprintf(archivo, "\n");
			}else{
				fprintf(archivo, " ");
			}
		}

		// Preveto
		for(i = 0;i < k; i++){
			fprintf(archivo, "%f", (vetoArray[i] + indiferenciaArray[i]) / 2);
			if(i == (k-1)){
				fprintf(archivo, "\n");
			}else{
				fprintf(archivo, " ");
			}
		}

		fclose(archivo);
		archivo = fopen(str, "r");
	}

	char line[5000];
	int contlimiter = 0;
	while( fgets(line,2000,archivo) ) {
		// char strtext[] = line;
		int init_size = strlen(line);
		char delim[] = " ";
		char *ptr = strtok(line, delim);
		int cont_in = 0;
		while(ptr != NULL)
		{
			// printf("'%s'\n", ptr);
			if(contlimiter == 0){
				vectorW[cont_in] = atof(ptr);
			}
			if(contlimiter == 1){
				vectorV[cont_in] = atof(ptr);
			}
			if(contlimiter == 2){
				vectorU[cont_in] = atof(ptr);
			}
			if(contlimiter == 3){
				vectorS[cont_in] = atof(ptr);
			}
			ptr = strtok(NULL, delim);
			cont_in++;
		}
		contlimiter++;
	}

	for(i = 0; i < k; i++){
		printf("%f ", vectorW[i]);
	}
}

float generateRandomValue(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float concordance(int index1, int index2){
	// c(x1, x2) = c1(x1, x2) + c2(x1, x2) + c3(x1, x2) + ...
	float total = 0;
	int i;

	for(i = 0; i < k; i++){
		boolean xIky;
		boolean xPky;

		xIky = abs(T.pheromones[index1].nFx[i] - T.pheromones[index2].nFx[i]) <= vectorU[i];

		xPky = T.pheromones[index1].nFx[i] < T.pheromones[index2].nFx[i] && !(xIky);

		if(xPky || xIky){
			total += vectorW[i];
		}
	}

	return total;
}

float discordance(int index1, int index2){
	// d(x1, x2) = min{1-d1(x1, x2), 1-d2(x1, x2), 1-d3(x1, x2), ... }

	float min_value = 1;
	int i;

	for(i = 0;i < k;i++){
		float result = 0;

		float dis = T.pheromones[index1].nFx[i] - T.pheromones[index2].nFx[i];

		if(dis < vectorS[i]){
			result = 0;
		}
		if((vectorS[i] <= dis) && (dis < vectorV[i])){
			result = (dis - vectorU[i]) / (vectorV[i] - vectorU[i]);
		}
		if(dis >= vectorV[i]){
			result = 1;
		}

		if((1 - result) < min_value){
			min_value = 1 - result;
		}
	}

	return min_value;
}

float preferenceIdentifier(float sigma_x, float sigma_y, boolean xdominatey){
	float result = 0;

	boolean xPy, xIy;

	// Agregar dominancia * !
	// Encontrar por que no entra a 3 y 5 * !
	// Calcular no dominada, debilmente, flujo neto (3, 4, 7)

	if(xdominatey || ((sigma_x >= Lamdba) && (sigma_y < 0.5)) || ((sigma_x >= Lamdba) && ((0.5 <= sigma_y) && (sigma_y < Lamdba)) && (sigma_x - sigma_y >= Beta))){
		result = 1;
		xPy = TRUE;
	}else{
		xPy = FALSE;
	}

	if((sigma_x >= Lamdba) && (sigma_y >= Lamdba) && (abs(sigma_x - sigma_y) <= Epsilon)){
		result = 2;
		xIy = TRUE;
	}else{
		xIy = FALSE;
	}

	if((sigma_x >= Lamdba) && (sigma_x >= sigma_y) && !(xPy) && !(xIy)){
		result = 3;
	}

	if((sigma_x < 0.5) && (sigma_y < 0.5)){
		result = 4;
	}

	if(((0.5 <= sigma_x) && (sigma_x <= Lamdba)) && (sigma_y < 0.5) && ((sigma_x - sigma_y) > (Beta / 2))){
		result = 5;
	}

	return result;
}

boolean xdominatey(int index1, int index2){
	int atleastone = 0;
	int minlimit = 0;
	int i;

	for(i = 0; i < k; i++){
		if(T.pheromones[index1].Fx[i] > T.pheromones[index2].Fx[i]){
			minlimit++; 
		}
		if(T.pheromones[index1].Fx[i] < T.pheromones[index2].Fx[i]){
			atleastone++;
		}
	}

	if(minlimit == 0 && atleastone > 0){
		return TRUE;
	}else{
		return FALSE;
	}
}

void ORankingAnts(int size){
	int i, j;

	float concordanciaArray[size][size];
	float discordanciaArray[size][size];
	float sigmaArray[size][size];
	float preferencesArray[size][size];
	float frontierArray[size][3];

	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			concordanciaArray[i][j] = concordanceAnts(i, j);
			discordanciaArray[i][j] = discordanceAnts(i, j);

			sigmaArray[i][j] = concordanciaArray[i][j] * discordanciaArray[i][j];
		}
	}

	float netscore[size];

	for(i = 0; i < size; i++){
		netscore[i] = 0;
		for(j = 0; j < size; j++){
			netscore[i] += (sigmaArray[i][j] - sigmaArray[j][i]);
		}
	}

	for(i = 0; i < size; i++){	
		frontierArray[i][0] = 0;
		frontierArray[i][1] = 0;
		frontierArray[i][2] = 0;
		for(j = 0; j < size; j++){
			if(i != j){
				preferencesArray[i][j] = preferenceIdentifier(sigmaArray[i][j], sigmaArray[j][i], xdominateyAnts(i, j));

				// Estrictamente dominada
				if(preferencesArray[i][j] == 1){
					frontierArray[i][0] += 1;
				}

				// Debilmente dominadas / k-preferencia
				if(preferencesArray[i][j] == 3 || preferencesArray[i][j] == 5){
					frontierArray[i][1] += 1;
				}

				//Flujo neto
				if(netscore[j] > netscore[i]){
					frontierArray[i][2] += 1;
				}
				
			}else{
				preferencesArray[i][j] = 0;
			}
		}
	}

	FILE *arch;
	char str[100] = "output/test/testants.txt";
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}

	for(i = 0; i < size; i++){	
		fprintf(arch, "Index: %d (%d, %d, %d)\n", i, (int)frontierArray[i][0], (int)frontierArray[i][1], (int)frontierArray[i][2]);
		Ants[i].strictOR = (int)frontierArray[i][0];
		Ants[i].weakOR = (int)frontierArray[i][1];
		Ants[i].netscoreOR = (int)frontierArray[i][2];
	}
	
	qsort(Ants, size, sizeof(ANT), (int (*)(const void *, const void *))&compare_ant_alpha_or);

	for(i = 0; i < size; i++){	
		fprintf(arch, "Index: %d (%d, %d, %d)\n", i, Ants[i].strictOR, Ants[i].weakOR, Ants[i].netscoreOR);
	}

	fclose(arch);
}

float concordanceAnts(int index1, int index2){
	float total = 0;
	int i;

	for(i = 0; i < k; i++){
		boolean xIky;
		boolean xPky;

		xIky = abs(Ants[index1].nFx[i] - Ants[index2].nFx[i]) <= vectorU[i];

		xPky = Ants[index1].nFx[i] < Ants[index2].nFx[i] && !(xIky);

		if(xPky || xIky){
			total += vectorW[i];
		}
	}

	return total;
}

float discordanceAnts(int index1, int index2){
	float min_value = 1;
	int i;

	for(i = 0;i < k;i++){
		float result = 0;

		float dis = Ants[index1].nFx[i] - Ants[index2].nFx[i];

		if(dis < vectorS[i]){
			result = 0;
		}
		if((vectorS[i] <= dis) && (dis < vectorV[i])){
			result = (dis - vectorU[i]) / (vectorV[i] - vectorU[i]);
		}
		if(dis >= vectorV[i]){
			result = 1;
		}

		if((1 - result) < min_value){
			min_value = 1 - result;
		}
	}

	return min_value;
}

boolean xdominateyAnts(int index1, int index2){
	int atleastone = 0;
	int minlimit = 0;
	int i;

	for(i = 0; i < k; i++){
		if(Ants[index1].Fx[i] > Ants[index2].Fx[i]){
			minlimit++; 
		}
		if(Ants[index1].Fx[i] < Ants[index2].Fx[i]){
			atleastone++;
		}
	}

	if(minlimit == 0 && atleastone > 0){
		return TRUE;
	}else{
		return FALSE;
	}
}
