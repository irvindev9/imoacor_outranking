#include "../headers/Comparisons.h"

int compare_ant_alpha(const void *p1, const void *p2){
	ANT *a, *b;
	double anorm, bnorm;
	a = (ANT *)p1;
	b = (ANT *)p2;

	if(a->alpha < b->alpha)
		return -1;
	else if(a->alpha > b->alpha)
		return 1;

	// Use L1-norm in case a draw.
	anorm = normL2(a->Fx, k);
	bnorm = normL2(b->Fx, k);

	if(anorm < bnorm)
		return -1;
	else if(anorm > bnorm)
		return 1;
	return 0;
}

int compare_ant_alpha_or(const void *p1, const void *p2){
	ANT *a, *b;
	double anorm, bnorm;
	a = (ANT *)p1;
	b = (ANT *)p2;

	if(a->strictOR < b->strictOR){
		return -1;
	}else if(a->strictOR > b->strictOR){
		return 1;
	}

	if(a->weakOR < b->weakOR){
		return -1;
	}else if(a->weakOR > b->weakOR){
		return 1;
	}

	if(a->netscoreOR < b->netscoreOR){
		return -1;
	}else if(a->netscoreOR > b->netscoreOR){
		return 1;
	}

	return 0;
}

int compare_pheromone_alpha_or(const void *p1, const void *p2){
	PHEROMONE *a, *b;
	double anorm, bnorm;
	a = (PHEROMONE *)p1;
	b = (PHEROMONE *)p2;

	if(a->strictOR < b->strictOR){
		return -1;
	}else if(a->strictOR > b->strictOR){
		return 1;
	}

	if(a->weakOR < b->weakOR){
		return -1;
	}else if(a->weakOR > b->weakOR){
		return 1;
	}

	if(a->netscoreOR < b->netscoreOR){
		return -1;
	}else if(a->netscoreOR > b->netscoreOR){
		return 1;
	}

	return 0;
}

int compare_pheromone_alpha(const void *p1, const void *p2){
	PHEROMONE *a, *b;
	double anorm, bnorm;
	a = (PHEROMONE *)p1;
	b = (PHEROMONE *)p2;

	if(a->alpha < b->alpha)
		return -1;
	else if(a->alpha > b->alpha)
		return 1;

	// Use L1-norm in case a draw.
	anorm = normL2(a->Fx, k);
	bnorm = normL2(b->Fx, k);

	if(anorm < bnorm)
		return -1;
	else if(anorm > bnorm)
		return 1;
	return 0;
}

int compare_rank_and_mmf(const void *p1, const void *p2){
	PHEROMONE *a, *b;
	a = (PHEROMONE *)p1;
	b = (PHEROMONE *)p2;


	if(a->rank < b->rank)
		return -1;
	else if(a->rank > b->rank)
		return 1;
	else if(a->rank == b->rank){
		if(a->mmf > b->mmf)
			return -1;
		else if(a->mmf < b->mmf)
			return 1;
	}

	return 0;
}


int compare_Ants_rank_and_mmf(const void *p1, const void *p2){
	ANT *a, *b;
	a = (ANT *)p1;
	b = (ANT *)p2;


	if(a->rank < b->rank)
		return -1;
	else if(a->rank > b->rank)
		return 1;
	else if(a->rank == b->rank){
		if(a->mmf > b->mmf)
			return -1;
		else if(a->mmf < b->mmf)
			return 1;
	}

	return 0;
}


int compare_reduction(const void *p1, const void *p2){
	ANT *a, *b;
	a = (ANT *)p1;
	b = (ANT *)p2;

	double anorm, bnorm;

	if(a->rank < b->rank) return -1;
	else if(a->rank > b->rank) return 1;

	if(a->u < b->u) return -1;
	else if(a->u > b->u) return 1;

	anorm = normL2(a->Fx, k);
	bnorm = normL2(b->Fx, k);

	if(anorm < bnorm) return -1;
	else if(anorm > bnorm) return 1;

	return 0;
}