#ifndef __COMPARISONS_H__
#define __COMPARISONS_H__

#include <stdio.h>
#include "../headers/VectorOperations.h"
#include "../Global.h"


int compare_ant_alpha(const void *, const void *);
int compare_ant_alpha_or(const void *, const void *);
int compare_pheromone_alpha(const void *, const void *);
int compare_pheromone_alpha_or(const void *, const void *);
int compare_rank_and_mmf(const void *, const void *);
int compare_Ants_rank_and_mmf(const void *, const void *);
int compare_reduction(const void *, const void *);

#endif
