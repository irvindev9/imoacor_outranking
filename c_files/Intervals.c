#include "../headers/Intervals.h"
#include "../headers/Outranking.h"

float arrayTest[5][2];
float arrayResults[4][2];
float W_vector[4][2];
float returnValue1;
float returnValue2;
float W_concordance[440][440][2];
float Sigma_Array[440][440];

void initializeIntervals(){
  srand (time(NULL));
  int i, j;

  for(i = 0; i < 5; i++){
    for(j = 0; j < 2; j++){
      float val;
      if(j == 0){
        val = generateRandomValueINT(0,5);
        arrayTest[i][j] = val;
      }else{
        val = generateRandomValueINT(5,10);
        arrayTest[i][j] = val;
      }
    }
  }

  for(i = 0; i < 4; i++){
    float c_up = 0;
    float c_down = 0;
    float d_up = 0;
    float d_down = 0;
    for(j = 0;j < 4; j++){
      if(i != j){
        // Revisar logica cuando este aplicado (por cuestiones de indices)
        if(PInterval(vectorU[i][0], vectorU[i][1], (arrayTest[j][1] - arrayTest[i][1])) >= 0.5){
          c_up += vectorW[i][1];
          c_down += vectorW[i][0];
        }else{
          d_up += vectorW[i][1];
          d_down += vectorW[i][0];
        }
      }
    }

    if((c_up + d_down) <= 1){
      W_vector[i][1] = c_up;
    }else{
      W_vector[i][1] = 1 - d_down;
    }

    if((c_down + d_up) >= 1){
      W_vector[i][0] = c_down;
    }else{
      W_vector[i][0] = 1 - d_up;
    }
  }

  for(i = 0; i < 4; i++){
    printf("%f ", W_vector[i][0]);
    printf("%f ", W_vector[i][1]);
    printf("\n");
  }

  float D_vector[4][2];
  float max_value = -9999999;
  
  for(i = 0; i < 4; i++){
    
    for(j = 0;j < 4; j++){
      if(i != j){
        // Revisar logica cuando este aplicado (por cuestiones de indices)
        if(PInterval(vectorV[i][0], vectorV[i][1], (arrayTest[j][1] - arrayTest[i][1])) > max_value){
          max_value = PInterval(vectorV[i][0], vectorV[i][1], (arrayTest[j][1] - arrayTest[i][1]));
        }
      }
    }
  }

  float discordanse = 1 - max_value;

  printf("%f ", discordanse);

  // Sigma 

  for(i = 0;i < 4;i++){
    for(j = 0; j < 4; j++){
      if(i != j){
        if(possInterval(i, j) < discordanse){
          Sigma_Array[i][j] = possInterval(i, j);
        }else{
          Sigma_Array[i][j] = discordanse;
        }
      }else{
        Sigma_Array[i][j] = 0;
      }
    }
  }

  for(i = 0;i < 4;i++){
    for(j = 0; j < 4; j++){
      if(i != j){
        printf("%f \n",  Sigma_Array[i][j]);
      }
    }
  }

}

float generateRandomValueINT(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void addInterval(int index, int i, int j){ arrayResults[index][0] = arrayTest[i][0] + arrayTest[j][0]; arrayResults[index][1] = arrayTest[i][1] + arrayTest[j][1]; }

void subInterval(int index, int i, int j){ arrayResults[index][0] = arrayTest[i][0] - arrayTest[j][0]; arrayResults[index][1] = arrayTest[i][1] - arrayTest[j][1]; }

void multInterval(int index, int i, int j){
  float min = 9999999999;
  float max = -9999999999;

  if((arrayTest[i][0] * arrayTest[j][0]) < min){
    min = arrayTest[i][0] * arrayTest[j][0];
  }

  if((arrayTest[i][0] * arrayTest[j][1]) < min){
    min = arrayTest[i][0] * arrayTest[j][1];
  }

  if((arrayTest[i][1] * arrayTest[j][0]) < min){
    min = arrayTest[i][1] * arrayTest[j][0];
  }

  if((arrayTest[i][1] * arrayTest[j][1]) < min){
    min = arrayTest[i][1] * arrayTest[j][1];
  }
  // Max
  if((arrayTest[i][0] * arrayTest[j][0]) > max){
    max = arrayTest[i][0] * arrayTest[j][0];
  }

  if((arrayTest[i][0] * arrayTest[j][1]) > max){
    max = arrayTest[i][0] * arrayTest[j][1];
  }

  if((arrayTest[i][1] * arrayTest[j][0]) > max){
    max = arrayTest[i][1] * arrayTest[j][0];
  }

  if((arrayTest[i][1] * arrayTest[j][1]) > max){
    max = arrayTest[i][1] * arrayTest[j][1];
  }

  arrayResults[index][0] = min;
  arrayResults[index][1] = max;
}

float possInterval(int i, int j){ float ped = pedValue(i, j); if(ped > 1){ return 1; } if((0 <= ped) && (ped <= 1)){ return ped; } if(ped <= 0){ return 0; } }

float pedValue(int i, int j){ return (W_concordance[i][j][1] - Lamdba[0]) / ((W_concordance[i][j][1] - W_concordance[i][j][0]) + (Lamdba[1] - Lamdba[0])); } 

float PInterval(float val1, float val2, float subtotal){
  float ped = pedValueInterval(subtotal, val1, val2);
  if (ped > 1) {
    return 1;
  }
  if ((0 <= ped) && (ped <= 1)) {
    return ped;
  }
  if (ped <= 0) {
    return 0;
  }
}

float pedValueInterval(float i, float j1, float j2){ 
  return (i - (j1)) / ((j2) - (j1));
} 

boolean xSy(int i, int j){
  return Sigma_Array[i][j] >= Beta[1];
}

boolean xPy(int i, int j){
  return xdominateyInterval(i, j) || (xSy(i, j) && !xSy(j, i));
}

boolean xPyAnts(int i, int j){
  return xdominateyAntsInterval(i, j) || (xSy(i, j) && !xSy(j, i));
}


void intervalsAnts(int size){
  
  int i, j, y, z;

  // printf("* %d * ", size);

  for(i = 0; i < size; i++){
    float c_up = 0;
    float c_down = 0;
    float d_up = 0;
    float d_down = 0;
    for(j = 0;j < size; j++){
      if(i != j){
        // Revisar logica cuando este aplicado (por cuestiones de indices)
        for(y = 0; y < k; y++){
          if(PInterval(-vectorU[y][0], -vectorU[y][1], (Ants[j].nFx[y] - Ants[i].nFx[y])) >= 0.5){
            c_up += vectorW[y][1];
            c_down += vectorW[y][0];
          }else{
            d_up += vectorW[y][1];
            d_down += vectorW[y][0];
          }
        }

        if((c_up + d_down) <= 1){
          W_concordance[i][j][1] = c_up;
        }else{
          W_concordance[i][j][1] = 1 - d_down;
        }

        if((c_down + d_up) >= 1){
          W_concordance[i][j][0] = c_down;
        }else{
          W_concordance[i][j][0] = 1 - d_up;
        }
      }
    }
  }

  // printf("* %d * ", size);


  float D_vector[size][size];
  
  for(i = 0; i < size; i++){
    float max_value = -9999999;

    for(j = 0;j < size; j++){
      if(i != j){
        if(PInterval(vectorV[y][0], vectorV[y][1], (Ants[i].nFx[y] - Ants[j].nFx[y])) > max_value){
          max_value = PInterval(vectorV[y][0], vectorV[y][1], (Ants[i].nFx[y] - Ants[j].nFx[y]));
        }
      }
    }
    D_vector[i][j] = max_value;
  }


  for(i = 0;i < size;i++){
    for(j = 0; j < size; j++){
      if(i != j){
        if(possInterval(i, j) < D_vector[i][j]){
          Sigma_Array[i][j] = possInterval(i, j);
        }else{
          Sigma_Array[i][j] = D_vector[i][j];
        }
      }else{
        Sigma_Array[i][j] = 0;
      }
    }
  }


  for(i = 0; i < size; i++){
    Ants[i].strictOR = 0;
    Ants[i].weakOR = 0;
    Ants[i].netscoreOR = 0;
    for(j = 0; j < size; j++){
      if(i != j){
        Ants[i].weakOR += xSy(i, j); //Fortaleza en el modelo de Outranking
        Ants[i].strictOR += xPyAnts(j, i); //Debilidad en el modelo de Outranking
      }
    }
  }

  // for(i = 0; i < size; i++){	
	// 	printf("Index: %d (%d, %d)\n", i, Ants[i].strictOR, Ants[i].weakOR, Ants[i].netscoreOR);
	// }

  qsort(Ants, size, sizeof(ANT), (int (*)(const void *, const void *))&compare_ant_alpha_or);

  // for(i = 0; i < size; i++){	
	// 	printf("Index: %d (%d, %d)\n", i, Ants[i].strictOR, Ants[i].weakOR, Ants[i].netscoreOR);
	// }
}

void intervalsPheromones(){
  
  int i, j, y, z;

  for(i = 0; i < T.nap; i++){
    float c_up = 0;
    float c_down = 0;
    float d_up = 0;
    float d_down = 0;
    for(j = 0;j < T.nap; j++){
      if(i != j){
        // Revisar logica cuando este aplicado (por cuestiones de indices)
        for(y = 0; y < k; y++){
          if(PInterval(-vectorU[y][0], -vectorU[y][1], (T.pheromones[j].nFx[y] - T.pheromones[i].nFx[y])) >= 0.5){
            c_up += vectorW[y][1];
            c_down += vectorW[y][0];
          }else{
            d_up += vectorW[y][1];
            d_down += vectorW[y][0];
          }
        }

        if((c_up + d_down) <= 1){
          W_concordance[i][j][1] = c_up;
        }else{
          W_concordance[i][j][1] = 1 - d_down;
        }

        if((c_down + d_up) >= 1){
          W_concordance[i][j][0] = c_down;
        }else{
          W_concordance[i][j][0] = 1 - d_up;
        }
      }
    }
  }

  float D_vector[T.nap][T.nap];
  
  for(i = 0; i < T.nap; i++){
    float max_value = -9999999;

    for(j = 0;j < T.nap; j++){
      if(i != j){
        if(PInterval(vectorV[y][0], vectorV[y][1], (T.pheromones[i].nFx[y] - T.pheromones[j].nFx[y])) > max_value){
          max_value = PInterval(vectorV[y][0], vectorV[y][1], (T.pheromones[i].nFx[y] - T.pheromones[j].nFx[y]));
        }
      }
    }
    D_vector[i][j] = max_value;
  }
  for(i = 0;i < T.nap;i++){
    for(j = 0; j < T.nap; j++){
      if(i != j){
        if(possInterval(i, j) < D_vector[i][j]){
          Sigma_Array[i][j] = possInterval(i, j);
        }else{
          Sigma_Array[i][j] = D_vector[i][j];
        }
      }else{
        Sigma_Array[i][j] = 0;
      }
    }
  }

  for(i = 0; i < T.nap; i++){
    T.pheromones[i].strictOR = 0;
    T.pheromones[i].weakOR = 0;
    T.pheromones[i].netscoreOR = 0;
    for(j = 0; j < T.nap; j++){
      if(i != j){
        T.pheromones[i].weakOR += xSy(i, j);//Fortaleza en el modelo de Outranking
        T.pheromones[i].strictOR += xPy(j, i); //Debilidad en el modelo de Outranking
      }
    }
  }
  qsort(T.pheromones, MAX_ARCHIVE_SIZE, sizeof(PHEROMONE), (int (*)(const void *, const void *))&compare_pheromone_alpha_or);
}

boolean xdominateyInterval(int index1, int index2){
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

boolean xdominateyAntsInterval(int index1, int index2){
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