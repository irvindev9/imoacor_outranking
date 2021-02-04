#include "../headers/Outranking.h"

float Epsilon = 0.1;
float Beta = 0.35;
float Lamdba = 0.6;

float valueU = 0.05;
float valueS = 0.1;
float valueV = 0.2;

void readData(){
    int i, j;
	// for(i = 0; i < MAX_ARCHIVE_SIZE; i++){
	// 	for(j = 0; j < n; j++)
    //         printf("%.6e \n", T.pheromones[i].Fx[j]);
	// 		// T.pheromones[i].x[j] = rndreal(lowerBounds[j], upperBounds[j]);
	// 	// (*F)(T.pheromones[i].x, T.pheromones[i].Fx);
	// }
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

void ORanking(size){
	// printf("%d\n", size);
	int i, j;
	float concordanciaArray[T.nap];

	for(i = 0; i < T.nap; i++){	
        // printf("%d *- ", i);
		float result = 0;
		for(j = 0; j < k; j++){
			result += T.pheromones[i].Fx[j];
		}
		concordanciaArray[i] = result;
	}

	for(i = 0; i < T.nap; i++){
		printf("%f\n",concordanciaArray[i]);
	}
}

void initValues(){

}