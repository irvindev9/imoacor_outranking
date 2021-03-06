#include "../headers/Miscellaneous.h"

void saveHistogram(int exec, int gen){
	FILE *arch;
	char str[100];
	sprintf(str, "output/histograms/iMOACOR_%s_%dD_R%d_G%d.hist", Fname, k, exec, gen);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int i;
	for(i = 0; i < N; i++)
		fprintf(arch, "%d\n", WV[i].nicheCount);
	fclose(arch);
}

void saveDistroWeightsAnts(int *niche, int gen, int exec){
	FILE *arch;
	char str[100];
	sprintf(str, "output/histograms/iMOACOR_%s_%dD_R%d_G%d_ants.hist", Fname, k, exec, gen);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int i;
	for(i = 0; i < N; i++)
		fprintf(arch, "%d\n", niche[i]);
	fclose(arch);
}

void saveDistroWeightsPheromones(int *niche, int gen, int exec){
	FILE *arch;
	char str[100];
	sprintf(str, "output/histograms/iMOACOR_%s_%dD_R%d_G%d_pheromones.hist", Fname, k, exec, gen);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int i;
	for(i = 0; i < N; i++)
		fprintf(arch, "%d\n", niche[i]);
	fclose(arch);
}


void saveParetoFront(int exec, PHEROMONE *pheromones, int size, int dm){
	FILE *arch;
	char str[100];
	sprintf(str, "output/original_DM%d_%s_%dD_R%d.pof", dm, Fname, k, exec);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int  i, j;
	boolean original = TRUE; //Original IMOACOr?
	int strictOR = pheromones[0].strictOR;
	int weakOR = pheromones[0].weakOR;
	int netscoreOR = pheromones[0].netscoreOR;

	// printf("%d <- \n", pheromones[0].netscoreOR);

	// fprintf(arch, "# %d %d\n", k, size);	
	for(i = 0; i < 1; i++){	
		int breakline = 0;
		for(j = 0; j < k; j++){
			if(pheromones[i].strictOR <= strictOR || original){
				strictOR = pheromones[i].strictOR;
				if(pheromones[i].weakOR <= weakOR || original){
					weakOR = pheromones[i].weakOR;
					if(pheromones[i].netscoreOR <= netscoreOR || original){
						netscoreOR = pheromones[i].netscoreOR;
						fprintf(arch, "%f", pheromones[i].nFx[j]);
						breakline = 1;
					}
				}
			}

			if(j != k - 1 && breakline)
				fprintf(arch, " ");
		}
		if(breakline)
			fprintf(arch, "\n");
	}
	fclose(arch);
}

void saveParetoFrontNewFormat(int exec, PHEROMONE *pheromones, int size){
	int dm_num = 1;
	int run_exec = 1;

	FILE *archivo;
	char str[100];
	sprintf(str, "output/global%s.txt", Fname);
	archivo = fopen(str, "a");
	if(archivo == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}

	int  i, j;
	boolean original = TRUE; //Original IMOACOr?
	int strictOR = pheromones[0].strictOR;
	int weakOR = pheromones[0].weakOR;
	int netscoreOR = pheromones[0].netscoreOR;

	for(i = 0; i < 1; i++){	
		int breakline = 0;
		for(j = 0; j < k; j++){
			// fprintf(archivo, "%.6e", pheromones[i].Fx[j]);
			if(pheromones[i].strictOR <= strictOR || original){
				strictOR = pheromones[i].strictOR;
				if(pheromones[i].weakOR <= weakOR || original){
					weakOR = pheromones[i].weakOR;
					if(pheromones[i].netscoreOR <= netscoreOR || original){
						netscoreOR = pheromones[i].netscoreOR;
						fprintf(archivo, "%f", pheromones[i].nFx[j]);
						breakline = 1;
					}
				}
			}

			if(j != k - 1 && breakline)
				fprintf(archivo, " ");
		}
		if(breakline)
			fprintf(archivo, "\n");
	}
	fclose(archivo);
}

void saveParetoSet(int exec, PHEROMONE *pheromones, int size){
	FILE *arch;
	char str[100];
	sprintf(str, "output/iMOACOR_%s_%dD_R%d.pos", Fname, k, exec);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int  i, j;	
	for(i = 0; i < size; i++){	
		for(j = 0; j < n; j++){
			// fprintf(arch, "%.6e", pheromones[i].x[j]);
			fprintf(arch, "%f", pheromones[i].x[j]);
			if(j != n - 1)
				fprintf(arch, "\t");
		}
		fprintf(arch, "\n");
	}
	fclose(arch);
}

void saveR2values(double *r2, int size, int exec){
	FILE *arch;
	char str[100];
	sprintf(str, "output/iMOACOR_R2_%s_%dD_R%d.dat", Fname, k, exec);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int i;
	for(i = 0; i < size; i++)
		fprintf(arch, "%.6e\n", r2[i]);
	fclose(arch);
}


void savePartialSet(int exec){
	FILE *arch;
	char str[100];

	sprintf(str, "output/progress/iMOACOR_%s_%dD_R%d_PS_part_%d.dat", Fname, k, exec, cont);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int  i, j;
	
	for(i = 0; i < T.nap; i++){
		for(j = 0; j < n; j++){
			fprintf(arch, "%.6e", T.pheromones[i].x[j]);
			if(j != n - 1)
				fprintf(arch, "\t");
		}
		fprintf(arch, "\n");
	}
	fclose(arch);
}


void savePartialFront(int exec){
	FILE *arch;
	char str[100];

	sprintf(str, "output/progress/iMOACOR_%s_%dD_R%d_PF_part_%d.dat", Fname, k, exec, cont);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int  i, j;
	
	for(i = 0; i < 2*N; i++){
		for(j = 0; j < k; j++){
			fprintf(arch, "%.6e", Ants[i].Fx[j]);
			if(j != k - 1)
				fprintf(arch, "\t");
		}
		fprintf(arch, "\n");
	}
	fclose(arch);
}


void plotVectors(){
		FILE *arch;
	char str[100];

	sprintf(str, "output/iMOACOR_%d_weightvectors.dat", N);
	arch = fopen(str, "w");
	if(arch == NULL){
		printf("Error! The file %s couldn't be created\n", str);
		exit(-1);
	}
	int  i, j;
	
	for(i = 0; i < N; i++){

		for(j = 0; j < k; j++)
			fprintf(arch, "0\t");

		for(j = 0; j < k; j++){
			fprintf(arch, "%.6e", WV[i].w[j]);
			if(j != k - 1)
				fprintf(arch, "\t");
		}
		fprintf(arch, "\n");
	}
	fclose(arch);
}
