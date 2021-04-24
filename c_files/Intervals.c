#include "../headers/Intervals.h"

float arrayTest[5][2];
float arrayResults[4][2];
float W_vector[4][2];
float Sigma_Array[4][4];

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
      // printf("%f ", val);
    }
    // printf("\n");
  }

  // printf("-------------------\n");

  // addInterval(0, 0, 1);
  // addInterval(1, 0, 2);
  // addInterval(2, 0, 3);
  // addInterval(3, 0, 4);

  // for(i = 0; i < 4; i++){
  //   printf("%f ", arrayResults[i][0]);
  //   printf("%f ", arrayResults[i][1]);
  //   printf("\n");
  // }

  // printf("-------------------\n");

  // subInterval(0, 0, 1);
  // subInterval(1, 0, 2);
  // subInterval(2, 0, 3);
  // subInterval(3, 0, 4);

  // for(i = 0; i < 4; i++){
  //   printf("%f ", arrayResults[i][0]);
  //   printf("%f ", arrayResults[i][1]);
  //   printf("\n");
  // }

  // printf("-------------------\n");

  // multInterval(0, 0, 1);
  // multInterval(1, 0, 2);
  // multInterval(2, 0, 3);
  // multInterval(3, 0, 4);

  // for(i = 0; i < 4; i++){
  //   printf("%f ", arrayResults[i][0]);
  //   printf("%f ", arrayResults[i][1]);
  //   printf("\n");
  // }
  
  // printf("%f\n", PInterval(0, (arrayTest[1][1] - arrayTest[2][1])));
  // printf("%f\n", PInterval(0, (arrayTest[1][1] - arrayTest[3][1])));
  // printf("%f\n", PInterval(0, (arrayTest[1][1] - arrayTest[4][1])));

  
  printf("k %f k ", vectorW[1][0]);
  printf("k %f k \n", vectorW[1][1]);

  // exit(1);

  

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

float pedValue(int i, int j){ return (W_vector[i][1] - Lamdba[0]) / ((W_vector[i][1] - W_vector[i][0]) + (Lamdba[1] - Lamdba[0])); } 

float PInterval(float val1, float val2, float subtotal){
  float ped = pedValueInterval(subtotal, val1, val2);
  // printf("vals : %f %d\n", subtotal, index);
  // printf("ped : %f\n", ped);
  if (ped > 1) {
    // printf("1\n");
    return 1;
  }
  if ((0 <= ped) && (ped <= 1)) {
    // printf("%f\n", ped);
    return ped;
  }
  if (ped <= 0) {
    // printf("0\n");
    return 0;
  }
}

float pedValueInterval(float i, float j1, float j2){ 
  // printf("(%f - (-%f)) / ((-%f) - (-%f))\n",i,vectorU[j][0], vectorU[j][1], vectorU[j][0]);
  return (i - (-j1)) / ((-j2) - (-j1));
} 

boolean xSy(int i, int j){
  return Sigma_Array[i][j] >= Beta[1];
}

boolean xPy(int i, int j){
  return (xSy(i, j) && !xSy(j, i));
}
