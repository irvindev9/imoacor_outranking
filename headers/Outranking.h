#ifndef __OUTRANKING_H__
#define __OUTRANKING_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../Global.h"
#include "ScalarizingFunctions.h"
#include "Comparisons.h"

void readData();
void readVars();
void ORankingPheromones(int);
void initValues(int);
float concordance(int, int);
float discordance(int, int);
float preferenceIdentifier(float, float, boolean);
float generateRandomValue(float, float);
boolean xdominatey(int, int);
void ORankingAnts(int);
float concordanceAnts(int, int);
float discordanceAnts(int, int);
boolean xdominateyAnts(int, int);
void outrankingFromFile();

#endif