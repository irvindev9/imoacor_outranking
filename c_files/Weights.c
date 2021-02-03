#include "../headers/Weights.h"

void init_Weight_Vectors(WEIGHT *WV, const int H, const int k) {
  int i, j;
  int c = 0;
  int num, sum;
  int *count;

  count = (int *)malloc(k*sizeof(int));
  num = choose(H + k - 1, k - 1);

  i = 0;
  while(i < mypow(H + 1, k)){
    sum = 0;
    int2kary(i, H + 1, k, count);
    for(j = 0; j < k; j++)
      sum += count[j];
    if(sum == H){
      for(j = 0; j < k; j++){
        WV[c].w[j] = (double)count[j]/(double)H;
        if(WV[c].w[j] == 0.0)
          WV[c].w[j] = EPSILON;
      }
      c++;
    }      
    i++;
  }
  free(count);
}

// Calculates nCr.
int choose(const int n, const int r) {
  return(factorialdiff(n, r)/factorial(r));
}

/*Own pow function which is easily call by other functions. This is
due to the inline keyword*/
inline int mypow(int x, int exp){
  int i;
  int var = 1;

  for(i = 0; i < exp; i++)
    var *= x;
  return var;
}

int factorialdiff(const int n, const int r) {
  //this function calculates n!/(n-r)!
  int i;
  int result=1;

  for(i = n ; i > (n-r); i--)
    result *= i;
  return(result);
}


int factorial(const int n) {
  if(n > 11) {
    printf("too big number to factorial!\n");
    exit(1);
  }

  int i;
  int result=1;

  for(i = n; i > 1; i--)
    result *= i;
  return(result);
}

void int2kary(int x, const int basek, const int digits, int *kary) {
  int i;
  int val;

  if (x >= mypow(basek,digits)) {
    printf("Number in int2kary() too large. Exiting.\n");
    exit(-1);
  }

  val = digits - 1;

  for(i = 0; i < digits; i++)
    kary[i]=0;

  i=0;

  while(x){
    if(x >= mypow(basek, val)){
      kary[i] += 1;
      x -= mypow(basek, val);
    }else{
      val -= 1;
      i++;
    }
  }
}