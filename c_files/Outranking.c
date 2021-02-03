#include "../headers/Outranking.h"

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
			printf("%.6e", T.pheromones[i].Fx[j]);
			if(j != k - 1)
				printf("\t");
		}
		printf("\n");
	}
}