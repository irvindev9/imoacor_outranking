#include "../headers/Outranking.h"

float Epsilon = 0.1; // 0.05 a 0.1
float Beta = 0.35; // 0.25 a 0.4
float Lamdba = 0.6; // 0.55 a 0.75
float weights[3];

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

void ORanking(size){
	// initValues();
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
				if(concordanciaArray[i][j] == -1 || discordanciaArray[i][j] == -1){
					sigmaArray[i][j] = -1.1;
				}else{
					sigmaArray[i][j] = concordanciaArray[i][j] * discordanciaArray[i][j];
				}
				
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
				if(sigmaArray[i][j] == -1.1){
					preferencesArray[i][j] = 2;
				}else{
					preferencesArray[i][j] = preferenceIdentifier(sigmaArray[i][j], sigmaArray[j][i], xdominatey(i, j));
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
		for(j = 0; j < T.nap; j++){
			// if(preferencesArray[i][j] != 0)
			fprintf(arch, "Sigma(%d, %d) = %f; Sigma(%d, %d) = %f; Relation: %d \n", i, j, sigmaArray[i][j], j, i, sigmaArray[j][i], (int)preferencesArray[i][j]);
			// printf("Sigma(%d, %d) = %f; Sigma(%d, %d) = %f; Relation: %d \n", i, j, sigmaArray[i][j], j, i, sigmaArray[j][i], (int)preferencesArray[i][j]);
		}
	}
	fclose(arch);
	
}

void initValues(){
	int i, j;
	weights[0] = 0.2;
	weights[1] = 0.3;
	weights[2] = 0.1;
	weights[3] = 0.2;
	weights[4] = 0.1;
	float wobjective = 1 / (float)k;
	for(i = 0;i < k; i++){
		float veto = generateRandomValue(0.01, 0.04);
		float indiferencia = generateRandomValue(0.10, 0.20);
		vectorW[i] = weights[i];
		vectorU[i] = generateRandomValue(0.01, 0.04);
		vectorS[i] = (veto + indiferencia) / 2;
		vectorV[i] = generateRandomValue(0.10, 0.20);
		printf("W: %f\n", vectorW[i]);
		printf("U: %f\n", vectorU[i]);
		printf("S: %f\n", vectorS[i]);
		printf("V: %f\n", vectorV[i]);
	}
}

float generateRandomValue(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float concordanse(index1, index2){
	// c(x1, x2) = c1(x1, x2) + c2(x1, x2) + c3(x1, x2) + ...
	// printf("%d %d\n", index1, index2);
	float total = 0;
	int i;

	for(i = 0; i < k; i++){
		float maxvalue = 0;

		if(T.pheromones[index1].Fx[i] < T.pheromones[index2].Fx[i]){
			maxvalue = T.pheromones[index2].Fx[i];
		}else{
			maxvalue = T.pheromones[index1].Fx[i];
		}



		if(maxvalue == 0){
			// printf("0 %f,%f\n", maxvalue, T.pheromones[index2].Fx[i]);
			return -1; // 2 = Indifference
		}else{
			// printf("!0 %f,%f\n", maxvalue, T.pheromones[index2].Fx[i]);
		}

		boolean xIky = (abs(T.pheromones[index1].Fx[i] - T.pheromones[index2].Fx[i]) / maxvalue) <= vectorU[i];

		boolean xPky =T.pheromones[index1].Fx[i] > T.pheromones[index2].Fx[i] && !(xIky);

		if(xPky || xIky){
			total += vectorW[i];
		}
	}
	if(total == 0){
		// printf("c 0\n");
	}

	return total;
}

float discordanse(index1, index2){
	// d(x1, x2) = min{1-d1(x1, x2), 1-d2(x1, x2), 1-d3(x1, x2), ... }

	float min_value = 1;
	int i;

	for(i = 0;i < k;i++){
		float result = 0;
		float maxvalue = 0;

		if(T.pheromones[index1].Fx[i] < T.pheromones[index2].Fx[i]){
			maxvalue = T.pheromones[index2].Fx[i];
		}else{
			maxvalue = T.pheromones[index1].Fx[i];
		}
		if(maxvalue == 0){
			// printf("0 %f,%f\n", maxvalue, T.pheromones[index2].Fx[i]);
			return -1; // 2 = Indifference
		}else{
			// printf("!0 %f,%f\n", maxvalue, T.pheromones[index2].Fx[i]);
		}
		float dis = (T.pheromones[index2].Fx[i] - T.pheromones[index1].Fx[i])/maxvalue;

		if(dis < vectorS[i]){
			result = 0;
		}
		if(vectorS[i] < dis < vectorV[i]){
			result = (dis - vectorU[i]) / (vectorV[i] - vectorU[i]);
		}
		if(dis > vectorV[i]){
			result = 1;
		}

		if((1 - result) < min_value){
			min_value = 1 - result;
		}
	}
	if(min_value == 0){
		// printf("d 0");
	}
	return min_value;
}

float preferenceIdentifier(float sigma_x, float sigma_y, boolean xdominatey){
	float result = 0;

	boolean xPy, xIy;

	// Agregar dominancia * !
	// Encontrar por que no entra a 3 y 5 * !
	// Calcular no dominada, debilmente, flujo neto

	if(xdominatey || ((sigma_x >= Lamdba) && (sigma_y < 0.5)) || ((sigma_x >= Lamdba) && (0.5 <= sigma_y < Lamdba) && (sigma_x - sigma_y >= Beta))){
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

boolean xdominatey(index1, index2){
	int max = 0;
	int min = 0;
	int i;

	for(i = 0; i < k; i++){
		if(T.pheromones[index1].Fx[i] < T.pheromones[index2].Fx[i]){
			min++;
		}
		if(T.pheromones[index1].Fx[i] > T.pheromones[index2].Fx[i]){
			max++;
		}
	}

	if(min == 0 && max > 0){
		return TRUE;
	}else{
		return FALSE;
	}
}