#ifndef __OUTRANKING_H__
#define __OUTRANKING_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../Global.h"

void readData();
void ORanking(int);
void initValues();
float concordanse(int, int);
float discordanse(int, int);
float preferenceIdentifier(float, float, boolean);
float generateRandomValue(float, float);
boolean xdominatey(int, int);

#endif