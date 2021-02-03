/*
* CINVESTAV
* Maestría en Ciencias en Computación
*   Tesis
* A new Multi-Objective Ant-Colony Optimization Algorithm for Continuos Spaces
* 
* Versión 1.0 MOACO_R
* 30/Septiembre/2015
*
* Autor: Ing. Jesús Guillermo Falcón Cardona
* Asesor: Dr. Carlos A. Coello Coello
* Descripción: Implementación del conjunto de funciones de prueba (ZDT y DTLZ)
* 
* ObjectiveFunctions.c
*/


#include "../headers/ObjectiveFunctions.h"


void findfunc(char *nom, void (**apf)(double *, double *)) {

  char *name[] = { "ZDT1", "ZDT2", "ZDT3", "ZDT4", "ZDT6",
                  "DTLZ1", "DTLZ2", "DTLZ3","DTLZ4", 
                  "DTLZ5", "DTLZ6", "DTLZ7",
                  "WFG1", "WFG2", "WFG3", "WFG4", "WFG5", "WFG6",
                  "WFG7", "WFG8", "WFG9"
                };

  void (*fdic[])(double *, double *) = {
                   ZDT1, ZDT2, ZDT3, ZDT4, ZDT6,
                   DTLZ1, DTLZ2, DTLZ3, DTLZ4, DTLZ5,
                   DTLZ6, DTLZ7,
                   wfg1, wfg2, wfg3, wfg4, wfg5, wfg6, 
                   wfg7, wfg8, wfg9
                };

  int i = 0;

  while(name[i] != NULL) {

    if(strcmp(nom, name[i]) == 0) {
      *apf = fdic[i];
      return;
    }
    i++;
  }
  *apf = fdic[0];
}



void ZDT1(double *x, double *F){
  double f1, f2, g, h;
  int i;
  f1 = x[0];
  g = 0.0;
  for (i = 1; i < n; i++) {
    g += x[i];
  }
  g = 9.0 * g / (n - 1);
  g += 1.0;
  h = 1.0 - sqrt(f1 / g);
  f2 = g * h;
  F[0] = f1;
  F[1] = f2;
  return;
}


void ZDT2(double *x, double *F) {
    double f1, f2, g, h;
    int i;
    f1 = x[0];
    g = 0;
    for(i = 1; i < n; i++)
      g += x[i];

    g = 9.0 * g / (n - 1.0);
    g += 1;
    h = 1 - pow((f1/g), 2);
    f2 = g * h;
    F[0] = f1;
    F[1] = f2;
    return;
}


void ZDT3(double *x, double *F){
  double f1, f2, g, h;
  int i;
  f1 = x[0];
  g = 0.0;
  for (i = 1; i < n; i++) {
    g += x[i];
  }
  g = 9.0 * g / (n - 1.0);
  g += 1.0;
  h = 1.0 - sqrt(f1 / g) - (f1 / g) * sin(10.0 * M_PI * f1);
  f2 = g * h;
  F[0] = f1;
  F[1] = f2;
  return;
}

void ZDT4(double *x, double *F){
  double f1, f2, g, h, sum;
  int j;

  f1 = x[0];
  sum = 0.0;
  for (j = 1; j < n; j++) {
    sum += (pow(x[j], 2.0) - 10.0 * cos(4.0 * M_PI * x[j]));
  }
  g = 1.0 + 10.0 * (n - 1.0) + sum;
  h = 1.0 - sqrt(f1 / g);
  f2 = g * h;
  F[0] = f1;
  F[1] = f2;
  return;
}

void ZDT6(double *x, double *F) {
    double f1, f2, g, h;
    int i;

    f1 = 1 - (exp(-4.0 * x[0])) * pow((sin(6.0 * M_PI * x[0])), 6);
    g = 0;

    for(i = 1; i < n; i++)
      g += x[i];

    g = g/9;
    g = pow(g, 0.25);
    g = 1 + 9*g;
    h = 1 - pow((f1/g),2);
    f2 = g * h;
    F[0] = f1;
    F[1] = f2;
  return;
}


void DTLZ1(double *x, double *F) {
  double g;
  int i, j, t, c;

  g = 0;
  c = n - k + 1;

  for(i = n - c; i < n; i++)
    g += pow(x[i] - 0.5, 2) - cos(20*M_PI*(x[i] - 0.5));

  g = 100*(c + g);

  for(i = 0; i < k; i++) {
    F[i] = 0.5*(1 + g);

    t = k - i - 1; 

    for(j = 0; j < t; j++) {
      F[i] *= x[j];
    }

    if(t < k - 1) {
      F[i] *= (1 - x[t]);
    }
  }
}


void DTLZ2(double *x, double *F) {
  double g;
  int i, j, t, c;

  g = 0;
  c = n - k + 1;

  for(i = n - c; i < n; i++)
    g += pow(x[i] - 0.5, 2);


  for(i = 0; i < k; i++) {
    F[i] = (1 + g);

    t = k - i - 1; 

    for(j = 0; j < t; j++) {
      F[i] *= cos(x[j]*M_PI*0.5);
    }

    if(t < k - 1) {
      F[i] *= sin(x[t]*M_PI*0.5);
    }
  }
}


void DTLZ3(double *x, double *F) {
  double g;
  int i, j, t, c;

  g = 0;
  c = n - k + 1;

  for(i = n - c; i < n; i++)
    g += pow(x[i] - 0.5, 2) - cos(20*M_PI*(x[i] - 0.5));

  g = 100*(c + g);

  for(i = 0; i < k; i++) {
    F[i] = (1 + g);

    t = k - i - 1; 

    for(j = 0; j < t; j++) {
      F[i] *= cos(x[j]*M_PI*0.5);
    }

    if(t < k - 1) {
      F[i] *= sin(x[t]*M_PI*0.5);
    }
  }
}


void DTLZ4(double *x, double *F) {
  double g, alpha = 100;
  int i, j, t, c;

  g = 0;
  c = n - k + 1;

  for(i = n - c; i < n; i++)
    g += pow(x[i] - 0.5, 2);


  for(i = 0; i < k; i++) {
    F[i] = (1 + g);

    t = k - i - 1; 

    for(j = 0; j < t; j++) {
      F[i] *= cos(pow(x[j], alpha)*M_PI*0.5);
    }

    if(t < k - 1) {
      F[i] *= sin(pow(x[t], alpha)*M_PI*0.5);
    }
  }
}


void DTLZ5(double *x, double *F) {
  double g, *theta, p;
  int i, j, t, c;

  theta = (double *) malloc(sizeof(double) * (k - 1));
  g = 0;
  c = n - k + 1;

  for(i = n - c; i < n; i++)
    g += pow(x[i] - 0.5, 2);

  theta[0] = x[0] * M_PI * 0.5;
  p = M_PI / (4 * (1 + g));

  for(i = 1; i < k - 1; i++)
    theta[i] = p * (1 + 2 * g * x[i]);

  for(i = 0; i < k; i++) {
    F[i] = (1 + g);

    t = k - i - 1; 

    for(j = 0; j < t; j++) {
      F[i] *= cos(theta[j]);
    }

    if(t < k - 1) {
      F[i] *= sin(theta[t]);
    }
  }

  free(theta);
}

void DTLZ6(double *x, double *F){
  
  double g, *theta, p;
    int i, j, t, c;

    theta = (double *) malloc(sizeof(double) * (k-1));
    g = 0;
    c = n - k + 1;

    for(i = n - c; i < n; i++)
      g += pow(x[i], 0.1);

    theta[0] = x[0] * M_PI * 0.5;
    p = M_PI / (4 * (1 + g));

    for(i = 1; i < k-1; i++)
      theta[i] = p * (1 + 2 * g * x[i]);

    for(i = 0; i < k; i++) {
      F[i] = (1 + g);

      t = k - i - 1; 

      for(j = 0; j < t; j++) {
          F[i] *= cos(theta[j]);
      }

      if(t < k - 1) {
          F[i] *= sin(theta[t]);
      }
    } 

    free(theta);

  return; 
}


void DTLZ7(double *x, double *F) {
  double g, h;
  int i, c;

  g = h = 0;
  c = n - k + 1;

  for(i = 0; i < k - 1; i++) 
    F[i] = x[i];

  for(i = n - c; i < n; i++)
    g += x[i];

  g = 1 + 9 * g / c;

  for(i = 0; i < k - 1; i++)
    h += x[i] / (1 + g) * (1 + sin(3*M_PI*x[i]));

  h = k - h;

  F[k-1] = (1 + g) * h;
}