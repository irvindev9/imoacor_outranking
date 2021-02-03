#ifndef __WEIGHTS_H__
#define __WEIGHTS_H__

#include <stdio.h>
#include <stdlib.h>

#include "../Global.h"


void init_Weight_Vectors(WEIGHT *WV, const int H, const int k); 
int choose(const int n, const int r); 
inline int mypow(int x, int exp); 
int factorialdiff(const int n, const int r); 
int factorial(const int n); 
inline void int2kary(int x, const int basek, const int digits, int *kary);

#endif