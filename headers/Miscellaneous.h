#ifndef __MISCELLANEOUS_H__
#define __MISCELLANEOUS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ObjectiveFunctions.h"
#include "WFG.h"
#include "../Global.h"


void saveParetoFront(int, PHEROMONE *, int);
void saveParetoSet(int, PHEROMONE *, int);
void saveParetoFrontNewFormat(int, PHEROMONE *, int);


void savePartialFront(int exec);
#endif