#include "../headers/Outranking.h"

float Epsilon = 0.1;
float Beta = 0.35;
float Lamdba = 0.6;

float valueU = 0.05;
float valueS = 0.1;
float valueV = 0.2;

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

void ORanking(size){
	initValues();
	int i, j;

	float concordanciaArray[T.nap][T.nap];
	float discordanciaArray[T.nap][T.nap];
	float sigmaArray[T.nap][T.nap];
	float preferencesArray[T.nap][T.nap];

	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			if(i != j){
				concordanciaArray[i][j] = concordanse(i, j);
				discordanciaArray[i][j] = discordanse(i, j);
				sigmaArray[i][j] = concordanciaArray[i][j] * discordanciaArray[i][j];
			}else{
				concordanciaArray[i][j] = -1;
				discordanciaArray[i][j] = -1;
				sigmaArray[i][j] = -1;
			}
		}
	}
	
	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			if(i != j){
				preferencesArray[i][j] = preferenceIdentifier(sigmaArray[i][j], sigmaArray[j][i]);
			}else{
				preferencesArray[i][j] = 0;
			}
		}
	}

	for(i = 0; i < T.nap; i++){	
		for(j = 0; j < T.nap; j++){
			if(preferencesArray[i][j] != 0)
				printf("%d\n", (int)preferencesArray[i][j]);
		}
	}
}

void initValues(){
	int i, j;
	float wobjective = 1 / (float)k;
	for(i = 0;i < k; i++){
		vectorW[i] = wobjective;
		vectorU[i] = valueU;
		vectorS[i] = valueS;
		vectorV[i] = valueV;
	}
}

float concordanse(index1, index2){
	// c(x1, x2) = c1(x1, x2) + c2(x1, x2) + c3(x1, x2) + ...

	float total = 0;
	int i;

	for(i = 0; i < k; i++){
		boolean xIky = abs(T.pheromones[i].Fx[index1] - T.pheromones[i].Fx[index2]) <= vectorU[i];

		boolean xPky = T.pheromones[i].Fx[index1] > T.pheromones[i].Fx[index2] && !(xIky);

		if(xPky || xIky){
			total += vectorW[i];
		}
	}

	return total;
}

float discordanse(index1, index2){
	// d(x1, x2) = min{1-d1(x1, x2), 1-d2(x1, x2), 1-d3(x1, x2), ... }

	float min_value = 1;
	int i;

	for(i = 0;i < k;i++){
		float result = 0;
		float dis = T.pheromones[i].Fx[index2] - T.pheromones[i].Fx[index1];

		if(dis < vectorS[i]){
			result = 0;
		}
		if(vectorS[i] < dis < vectorV[i]){
			result = (dis - vectorU[i]) / vectorV[i] - vectorU[i];
		}
		if(dis > vectorV[i]){
			result = 1;
		}

		if((1 - result) < min_value){
			min_value = 1 - result;
		}
	}

	return min_value;
}

float preferenceIdentifier(float sigma_x, float sigma_y){
	float result = 0;

	boolean xPy, xIy;

	if((sigma_x >= Lamdba) && (sigma_y < 0.5) || (sigma_x >= Lamdba) && (0.5 <= sigma_y < Lamdba) && (sigma_x - sigma_y >= Beta)){
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

	if((0.5 <= sigma_x <= Lamdba) && (sigma_y < 0.5) && ((sigma_x - sigma_y) > (Beta / 2))){
		result = 5;
	}

	return result;
}