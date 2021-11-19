#include "../headers/Outranking.h"

/**
 * @brief Used as utility to read the preferences
 * @return (void)
 * */
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

/**
 * @brief Read the configuration file
 * @return (void)
 * */
void readVars(){
	int i;

	printf("%f ", Epsilon);
	printf("\n");
	printf("%f ", Beta);
	printf("\n");
	printf("%f ", Lamdba);
	printf("\n");
	for(i = 0; i < k; i++){
		printf("%f ", vectorW[i]);
	}
	printf("\n");
	for(i = 0; i < k; i++){
		printf("%f ", vectorV[i]);
	}
	printf("\n");
	for(i = 0; i < k; i++){
		printf("%f ", vectorU[i]);
	}
	printf("\n");
	for(i = 0; i < k; i++){
		printf("%f ", vectorS[i]);
	}
	printf("\n");
	
}

/**
 * @brief Main function of outranking for pheromones
 * @param size of the solutions / size = M + T.nap
 * @return (void)
 * */
void ORankingPheromones(int size){
	int i, j;

	float sigmaArray[T.nap][T.nap];
	float preferencesArray[T.nap][T.nap];
	float frontierArray[T.nap][3]; // 0 = strict, 1 = weak - k, 2 = flujo neto

	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			sigmaArray[i][j] = concordance(i, j) * discordance(i, j);
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

/**
 * @brief Initialize the outranking configuration, readed from output/DM%d_%s_config.txt
 * @param dm number of the DM file
 * @return (void)
 * */
void initValues(int dm){
	int i, j;

	FILE *archivo;
	char str[100];
	sprintf(str, "output/DM%d_%s_config.txt", dm, Fname);
	archivo = fopen(str, "r");
	float tempweight = 0;
	if(archivo == NULL){
		printf("The file %s couldn't be found... creating..\n", str);
		archivo = fopen(str, "w");
		Epsilon = generateRandomValue(0.05, 0.1);
		Beta = generateRandomValue(0.25, 0.4);
		Lamdba = generateRandomValue(0.55, 0.75);
		fprintf(archivo, "%f\n", Epsilon);
		fprintf(archivo, "%f\n", Beta);
		fprintf(archivo, "%f\n", Lamdba);

		for(i = 0;i < k; i++){
			if(tempweight == 0){
				float value = generateRandomValue(0.0, 0.20);
				tempweight = 0.2 - value;
				fprintf(archivo, "%f", value);
			}else{
				fprintf(archivo, "%f", tempweight);
				tempweight = 0;
			}
			
			if(i == (k-1)){
				fprintf(archivo, "\n");
			}else{
				fprintf(archivo, " ");
			}
		}

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
		int init_size = strlen(line);
		char delim[] = " ";
		char *ptr = strtok(line, delim);
		int cont_in = 0;
		while(ptr != NULL)
		{
			if(contlimiter == 0){
				Epsilon = atof(ptr);
			}
			if(contlimiter == 1){
				Beta = atof(ptr);
			}
			if(contlimiter == 2){
				Lamdba = atof(ptr);
			}
			if(contlimiter == 3){
				vectorW[cont_in] = atof(ptr);
			}
			if(contlimiter == 4){
				vectorV[cont_in] = atof(ptr);
			}
			if(contlimiter == 5){
				vectorU[cont_in] = atof(ptr);
			}
			if(contlimiter == 6){
				vectorS[cont_in] = atof(ptr);
			}
			ptr = strtok(NULL, delim);
			cont_in++;
		}
		contlimiter++;
	}
}

/**
 * @brief Generate random values between a range
 * @param a minimum value
 * @param b maximum value
 * @return random value
 * */
float generateRandomValue(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

/**
 * @brief Calculate concordance of two vectors
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @return concordance
 * */
float concordance(int index1, int index2){
	// c(x1, x2) = c1(x1, x2) + c2(x1, x2) + c3(x1, x2) + ...
	float total = 0;
	int i;

	for(i = 0; i < k; i++){
		boolean xIky;
		boolean xPky;

		xIky = abs(T.pheromones[index2].nFx[i] - T.pheromones[index1].nFx[i]) <= vectorU[i];

		xPky = T.pheromones[index1].nFx[i] < T.pheromones[index2].nFx[i] && !(xIky);

		if(xPky || xIky){
			total += vectorW[i];
		}
	}

	return total;
}

/**
 * @brief Calculate discordance of two vectors
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @return discordance
 * */
float discordance(int index1, int index2){
	// d(x1, x2) = min{1-d1(x1, x2), 1-d2(x1, x2), 1-d3(x1, x2), ... }

	float min_value = 1;
	int i;

	for(i = 0;i < k;i++){
		float result = 0;

		float dis = T.pheromones[index2].nFx[i] - T.pheromones[index1].nFx[i];

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

/**
 * @brief Select preference of two vectors (by sigma)
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @return preference
 * 
 * Preferences dictionary
 * 1 = Strict preference
 * 2 = Indifference
 * 3 = Weak preference
 * 4 = Incomparability
 * 5 = k-Preference
 * 0 = null
 * */
float preferenceIdentifier(float sigma_x, float sigma_y, boolean xdominatey){
	float result = 0;

	boolean xPy, xIy;

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

/**
 * @brief Say if x dominate y (two vectors)
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @return TRUE if x dominate y, FALSE otherwise
 * */
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

/**
 * @brief Calculate Outranking (Ants)
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @return (void)
 * */
void ORankingAnts(int size){
	int i, j;

	float sigmaArray[size][size];
	float preferencesArray[size][size];
	float frontierArray[size][3];

	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			sigmaArray[i][j] = concordanceAnts(i, j) * discordanceAnts(i, j);
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

				// Strictly dominated
				if(preferencesArray[i][j] == 1){
					frontierArray[i][0] += 1;
				}

				// Weak dominated / k-preference
				if(preferencesArray[i][j] == 3 || preferencesArray[i][j] == 5){
					frontierArray[i][1] += 1;
				}

				// Net score
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

/**
 * @brief Calculate concordance (two vectors)
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @exception if index1 or index2 are out of range (0 to T.nap-1)
 * @return concordance value
 * */
float concordanceAnts(int index1, int index2){
	float total = 0;
	int i;

	for(i = 0; i < k; i++){
		boolean xIky;
		boolean xPky;

		xIky = abs(Ants[index2].nFx[i] - Ants[index1].nFx[i]) <= vectorU[i];

		xPky = Ants[index1].nFx[i] < Ants[index2].nFx[i] && !(xIky);

		if(xPky || xIky){
			total += vectorW[i];
		}
	}

	return total;
}

/**
 * @brief Calculate discordance (two vectors)
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @exception if index1 or index2 are out of range (0 to T.nap-1)
 * @return discordance value
 * */
float discordanceAnts(int index1, int index2){
	float min_value = 1;
	int i;

	for(i = 0;i < k;i++){
		float result = 0;

		float dis = Ants[index2].nFx[i] - Ants[index1].nFx[i];

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

/**
 * @brief Say if x dominate y (two vectors)
 * @param index1 index of the first vector
 * @param index2 index of the second vector
 * @return TRUE if x dominate y, FALSE otherwise
 * */
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

/**
 * @brief Outranking from file (global file that contains all the results)
 * @return best solution
 * */
void outrankingFromFile(){

	int dmfile = 1;

	for(dmfile = 1; dmfile <= 10; dmfile++){
		initValues(dmfile);

		FILE *arch;
		arch = fopen("output/Globalwithoutduplicates6.txt", "r"); // Global without duplicates file
		if(arch == NULL){
			printf("Error! The file couldn't be created\n");
			exit(-1);
		}
		char line[5000];
		int contlimiter = 0;

		int i, j;
		int size_of_file = 0;

		while( fgets(line,5000,arch) ) {
			int init_size = strlen(line);
			char delim[] = " ";
			char *ptr = strtok(line, delim);
			int cont_in = 0;
			while(ptr != NULL)
			{
				float val = atof(ptr);
				T.pheromones[size_of_file].nFx[cont_in] = val;

				ptr = strtok(NULL, delim);
				cont_in++;
			}
			size_of_file++;
		}

		printf("Size: %d...\n", size_of_file);

		fclose(arch);

		printf("Saved finished!!! \nContinue with outranking...\n");

		// for(i = 0; i < size_of_file; i++){	
		// 	for(j = 0; j < size_of_file; j++){
		// 		T.pheromones[i].sigma[j] = concordance(i, j) * discordance(i, j);
		// 	}
		// }

		// printf("Sigma finished!!! \nContinue with outranking...\n");

		for(i = 0; i < size_of_file; i++){
			T.pheromones[i].netscore = 0;
			for(j = 0; j < size_of_file; j++){
				T.pheromones[i].netscore += ((concordance(i, j) * discordance(i, j)) - (concordance(j, i) * discordance(j, i)));
			}
		}

		// for(i = 0; i < size_of_file; i++){
		// 	free(T.pheromones[i].nFx);
		// }

		printf("Netscore finished!!! \nContinue with outranking...\n");

		float preference;

		for(i = 0; i < size_of_file; i++){	
			T.pheromones[i].frontier[0] = 0;
			T.pheromones[i].frontier[1] = 0;
			T.pheromones[i].frontier[2] = 0;
			for(j = 0; j < size_of_file; j++){
				if(i != j){
					preference = preferenceIdentifier((concordance(i, j) * discordance(i, j)), (concordance(j, i) * discordance(j, i)), xdominatey(i, j));

					// Estrictamente dominada
					if(preference == 1){
						T.pheromones[i].frontier[0] += 1;
					}

					// Debilmente dominadas / k-preferencia
					if(preference == 3 || preference == 5){
						T.pheromones[i].frontier[1] += 1;
					}

					//Flujo neto
					if(T.pheromones[j].netscore > T.pheromones[i].netscore){
						T.pheromones[i].frontier[2] += 1;
					}
					
				}else{
					preference = 0;
				}
			}

		}

		printf("Preference finished!!! \nContinue with printing results...\n");

		FILE *outresults;
		char str[100];
		sprintf(str, "output/GlobalResults_%s_%dD_DM%d.txt", Fname, k, dmfile);
		outresults = fopen(str, "w");
		if(outresults == NULL){
			printf("Error! The file %s couldn't be created\n", str);
			exit(-1);
		}

		for(i = 0; i < size_of_file; i++){
			fprintf(outresults, "(%d, %d, %d) \n", (int)T.pheromones[i].frontier[0], (int)T.pheromones[i].frontier[1], (int)T.pheromones[i].frontier[2]);
		}

		fclose(outresults);
	}
}

void manhattanChebyshev(){

	FILE *arch2;
	// arch = fopen("output/globaldeprueba.txt", "r");
	char str[100];
	sprintf(str, "output/resultsDManAvg.csv");
	arch2 = fopen(str, "w");
	if(arch2 == NULL){
		printf("Errorm12! The file couldn't be created\n");
		exit(-1);
	}

	fprintf(arch2, "IO-ACO, iMOACOR\n");	

	fclose(arch2);

	sprintf(str, "output/resultsDManMin.csv");
	arch2 = fopen(str, "w");
	if(arch2 == NULL){
		printf("Errorm2! The file couldn't be created\n");
		exit(-1);
	}

	fprintf(arch2, "IO-ACO, iMOACOR\n");	

	fclose(arch2);

	sprintf(str, "output/resultsDChebAvg.csv");
	arch2 = fopen(str, "w");
	if(arch2 == NULL){
		printf("Errorm3! The file couldn't be created\n");
		exit(-1);
	}

	fprintf(arch2, "IO-ACO, iMOACOR\n");	

	fclose(arch2);

	sprintf(str, "output/resultsDChebMin.csv");
	arch2 = fopen(str, "w");
	if(arch2 == NULL){
		printf("Errorm4! The file couldn't be created\n");
		exit(-1);
	}

	fprintf(arch2, "IO-ACO, iMOACOR\n");	

	fclose(arch2);

	int dmfile = 1;

	for(dmfile = 1; dmfile <= 10; dmfile++){
		// initValues(dmfile);

		FILE *arch;
		// arch = fopen("output/globaldeprueba.txt", "r");
		char str[100];
		sprintf(str, "output/DM%d.txt", dmfile);
		arch = fopen(str, "r");
		if(arch == NULL){
			printf("Error! The file %s couldn't be created\n", str);
			exit(-1);
		}
		char line[5000];
		int contlimiter = 0;

		int i, j;
		int size_of_file_best = 0;
		float best_solution[10];

		while( fgets(line,5000,arch) ) {
			int init_size = strlen(line);
			char delim[] = " ";
			char *ptr = strtok(line, delim);
			int cont_in = 0;
			while(ptr != NULL)
			{
				if(size_of_file_best == 0){
					float val = atof(ptr);
					best_solution[cont_in] = val;
				}
				

				ptr = strtok(NULL, delim);
				cont_in++;
			}
			size_of_file_best++;
		}

		printf("File: %s ...\n", str);
		printf("Size: %f ...\n", best_solution[9]);

		fclose(arch);

		int run = 1;

		for(run = 1; run <= 30; run++){

			sprintf(str, "output/ioaco_DM%d_%s_%dD_R%d.pof", dmfile, Fname, k, run);
			arch = fopen(str, "r");
			if(arch == NULL){
				printf("Error! The file %s couldn't be created\n", str);
				exit(-1);
			}
			
			int size_of_file_ioaco = 0;

			while( fgets(line,5000,arch) ) {
				int init_size = strlen(line);
				char delim[] = " ";
				char *ptr = strtok(line, delim);
				int cont_in = 0;
				while(ptr != NULL)
				{
					float val = atof(ptr);
					Ants[size_of_file_ioaco].nFx[cont_in] = val;

					ptr = strtok(NULL, delim);
					cont_in++;
				}
				size_of_file_ioaco++;
			}

			// printf("File: %s ...\n", str);
			// printf("Size: %f ...\n", Ants[0].nFx[9]);

			fclose(arch);

			sprintf(str, "output/original_DM1_%s_%dD_R%d.pof", Fname, k, run);
			arch = fopen(str, "r");
			if(arch == NULL){
				printf("Error! The file %s couldn't be created\n", str);
				exit(-1);
			}
			
			int size_of_file_original = 0;

			while( fgets(line,5000,arch) ) {
				int init_size = strlen(line);
				char delim[] = " ";
				char *ptr = strtok(line, delim);
				int cont_in = 0;
				while(ptr != NULL)
				{
					float val = atof(ptr);
					T.pheromones[size_of_file_original].nFx[cont_in] = val;

					ptr = strtok(NULL, delim);
					cont_in++;
				}
				size_of_file_original++;
			}

			// printf("File: %s ...\n", str);
			// printf("Size: %f ...\n", T.pheromones[0].nFx[9]);

			fclose(arch);

			printf("Saved finished!!! \nContinue with metrics...\n");

			//IOACO

			float min_man = 9999999;
			float avg_man = 0;
			

			for(i = 0; i < size_of_file_ioaco; i++){
				float total = 0;
				for(j = 0; j < k; j++){
					printf("min_man: %f ...\n", (Ants[i].nFx[j] - best_solution[j]));
					total += (Ants[i].nFx[j] > best_solution[j]) ? (Ants[i].nFx[j] - best_solution[j]) : 0;
				}

				// total = sqrt(total);

				min_man = (min_man > total) ? total : min_man;

				avg_man += total;
			}

			avg_man = avg_man / size_of_file_ioaco;

			// IMOACOR

			float min_man_original = 9999999;
			float avg_man_original = 0;
			

			for(i = 0; i < size_of_file_original; i++){
				float total = 0;
				for(j = 0; j < k; j++){
					// printf("min_man_original: %f ...\n", (T.pheromones[i].nFx[j] - best_solution[j]));
					total += (T.pheromones[i].nFx[j] > best_solution[j]) ? (T.pheromones[i].nFx[j] - best_solution[j]) : 0;
				}

				// total = sqrt(total);

				min_man_original = (min_man_original > total) ? total : min_man_original;

				avg_man_original += total;
			}

			avg_man_original = avg_man_original / size_of_file_original;

			// printf("min_man_original: %f ...\n", min_man_original);
			// printf("avg_man_original: %f ...\n", avg_man_original);

			sprintf(str, "output/resultsDManAvg.csv");
			arch2 = fopen(str, "a");
			if(arch2 == NULL){
				printf("Errorm5! The file couldn't be created\n");
				exit(-1);
			}

			fprintf(arch2, "%f, %f\n", avg_man, avg_man_original);	

			fclose(arch2);

			sprintf(str, "output/resultsDManMin.csv");
			arch2 = fopen(str, "a");
			if(arch2 == NULL){
				printf("Errorm6! The file couldn't be created\n");
				exit(-1);
			}

			fprintf(arch2, "%f, %f\n", min_man, min_man_original);	

			fclose(arch2);

			//IOACO

			float min_cheb = 9999999;
			float avg_cheb = 0;
			

			for(i = 0; i < size_of_file_ioaco; i++){
				float total = 0;
				for(j = 0; j < k; j++){
					if((Ants[i].nFx[j] > best_solution[j]) && (Ants[i].nFx[j] - best_solution[j]) > total){
						total = Ants[i].nFx[j] - best_solution[j];
					}
				}

				min_cheb = (min_cheb > total) ? total : min_cheb;

				avg_cheb += total;
			}

			avg_cheb = avg_cheb / size_of_file_ioaco;

			//IMOACOR

			float min_cheb_original = 9999999;
			float avg_cheb_original = 0;
			

			for(i = 0; i < size_of_file_original; i++){
				float total = 0;
				// total = T.pheromones[i].nFx[0] - best_solution[0];
				for(j = 0; j < k; j++){
					if((T.pheromones[i].nFx[j] > best_solution[j]) && (T.pheromones[i].nFx[j] - best_solution[j]) > total){
						total = T.pheromones[i].nFx[j] - best_solution[j];
					}
				}

				min_cheb_original = (min_cheb_original > total) ? total : min_cheb_original;

				avg_cheb_original += total;
			}

			avg_cheb_original = avg_cheb_original / size_of_file_original;

			sprintf(str, "output/resultsDChebAvg.csv");
			arch2 = fopen(str, "a");
			if(arch2 == NULL){
				printf("Errorm7! The file couldn't be created\n");
				exit(-1);
			}

			fprintf(arch2, "%f, %f\n", avg_cheb, avg_cheb_original);	

			fclose(arch2);

			sprintf(str, "output/resultsDChebMin.csv");
			arch2 = fopen(str, "a");
			if(arch2 == NULL){
				printf("Errorm8! The file couldn't be created\n");
				exit(-1);
			}

			fprintf(arch2, "%f, %f\n", min_cheb, min_cheb_original);	

			fclose(arch2);

			printf("RUN#: %d\n", run);
		}

	}
}