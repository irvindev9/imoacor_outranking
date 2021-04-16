#ifndef __OUTRANKING_H__
#define __OUTRANKING_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h> 

#include "../Global.h"

void initializeIntervals();
float generateRandomValueINT(float, float);
void addInterval(int, int, int);
void subInterval(int, int, int);
void multInterval(int, int, int);
float possInterval(int, int, int);
float pedValue(int, int);
float PInterval(int, float);
float pedValueInterval(float, int);

#endif