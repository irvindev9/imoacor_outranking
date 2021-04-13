#include "../headers/Intervals.h"

float arrayTest[5][2];
float arrayResults[4][2];

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
      printf("%f ", val);
    }
    printf("\n");
  }

  printf("-------------------\n");

  addInterval(0, 0, 1);
  addInterval(1, 0, 2);
  addInterval(2, 0, 3);
  addInterval(3, 0, 4);

  for(i = 0; i < 4; i++){
    printf("%f ", arrayResults[i][0]);
    printf("%f ", arrayResults[i][1]);
    printf("\n");
  }

  printf("-------------------\n");

  subInterval(0, 0, 1);
  subInterval(1, 0, 2);
  subInterval(2, 0, 3);
  subInterval(3, 0, 4);

  for(i = 0; i < 4; i++){
    printf("%f ", arrayResults[i][0]);
    printf("%f ", arrayResults[i][1]);
    printf("\n");
  }

  printf("-------------------\n");

  multInterval(0, 0, 1);
  multInterval(1, 0, 2);
  multInterval(2, 0, 3);
  multInterval(3, 0, 4);

  for(i = 0; i < 4; i++){
    printf("%f ", arrayResults[i][0]);
    printf("%f ", arrayResults[i][1]);
    printf("\n");
  }

}

float generateRandomValueINT(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

void addInterval(int index, int i, int j){
  arrayResults[index][0] = arrayTest[i][0] + arrayTest[j][0];
  arrayResults[index][1] = arrayTest[i][1] + arrayTest[j][1];
}

void subInterval(int index, int i, int j){
  arrayResults[index][0] = arrayTest[i][0] - arrayTest[j][0];
  arrayResults[index][1] = arrayTest[i][1] - arrayTest[j][1];
}

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