#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "headers/TADListaDoblementeLigadaInt.h"

#define MAX_CHAR 50
#define EPSILON 1e-4
#define NONDOMINATED 1
#define DOMINATED 0

typedef struct AUX{
	double v;					/* Value to be used by the sorting. */
	int index;					/* Index of the object to which the value belongs. */
}AUX;

typedef struct WEIGHT{
	double *w;					/* Weight vector. */
	lista *Elements;
	int nicheCount;
}WEIGHT;

typedef struct ANT{
	double *x;					/* Vector of decision variables. */
	double *Fx;					/* Vector of evaluated objective functions. */	
	double *nFx;				/* Normalized objective vector */
	double u;					/* Scalarizing value corresponding to the weight pointed out by the weight index. */
	double alpha;				/* Current utility value. */
	int strictOR;			/* OutRanking Strict value. */
	int weakOR;				/* OutRanking weak or k-preference value. */
	int netscoreOR;			/* OutRanking netscore value. */
	int rank;					/* Rank assigned by the R2 ranking. */
	int weight_index;			/* index of the weight corresponding to the best utility value. */
	int kernelIndex;			/* Index of selected the Gaussian kernel */
	double mmf;
	//int USED;
}ANT;

typedef struct PHEROMONE{
	double *x;					/* Vector of decision variables */
	double *Fx;					/* Evaluated objective vector */
	double *nFx; 				/* Normalized objective vector */
	double u;					/* Scalarizing value */
	double alpha;
	int strictOR;			/* OutRanking Strict value. */
	int weakOR;				/* OutRanking weak or k-preference value. */
	int netscoreOR;			/* OutRanking netscore value. */
	float netscore;			/* OutRanking netscore value. */
	// float *sigma;			/* OutRanking sigma value. */
	float *preference;			/* OutRanking preference value. */
	float *frontier;			/* OutRanking frontier value. */
	double mmf;					/* Maximin fitness value */
	int rank;					/* Rank associated by the R2 ranking algorithm */
	int rankOR;					/* Rank associated by the Outranking algorithm */
	int weight_index;
}PHEROMONE;

typedef struct DATA{
	double *nFx; 				/* Normalized objective vector */
	float netscore;			/* OutRanking netscore value. */
	float *sigma;			/* OutRanking sigma value. */
	float *frontier;			/* OutRanking frontier value. */
}DATA;

typedef struct ARCHIVE{
	PHEROMONE *pheromones;		/* Pheromones */
	double *w;					/* Vector of weights. Each one is linked to a pheromone */
	double *p;					/* Probabilities for each pheromone */
	double *stdDev;				/* Vector of Standard deviations */ 
	int nap; 					/* Number of active pheromones */ // k
}ARCHIVE;




WEIGHT *WV;						/* Set of weight vectors. */
ANT *Ants;						/* Set of ants. */
ARCHIVE T;



int n;							/* Dimension of the decision space - USER PARAMETER */	
int k;							/* Dimension of the objective space - USER PARAMETER */
int k_wfg;						/* Variable used by WFG functions - USER PARAMETER*/
int MAX_ARCHIVE_SIZE;	 		/* Maximum size of the archive of solutions - USER PARAMETER */
int N; 							/* Number of weight vectors */
int M;							/* Number of ants - USER PARAMETER*/
int H;							/* Parameter used to calculte the number of weight vectors - USER PARAMETER */		
int Gmax;						/* Maximum number of iterations - USER PARAMETER*/
int genCounter;					/* Current iteration counter */
int executions;					/* Indicates how many executions will be performed - USER PARAMETER LINE COMMAND */
int MAX_RECORD_SIZE;			/* Maximum size of the record - USER PARAMETER */
int *mark;						/* Used in Record */

int MAX_R2_RECORD; 
double R2variance; 
double R2threshold;	
double R2value;

double varThreshold;			/* Variance threshold used by the reference point update function - USER PARAMETER */
double tolThreshold;			/* Tolerance threshold used by the reference point update function - USER PARAMETER */
double Xi;						/* Convergence speed (~Evaporation rate) - USER PARAMETER */
double q;						/* Control de diversificación - USER PARAMETER */

float Rseed;					/* Random seed for number generator - USER PARAMETER*/

double *lowerBounds;			/* Lower bounds per variable */
double *upperBounds;			/* Upper bounds per variable */
double *z_ideal;				/* Vector which acts as the ideal vector */
double *z_nad;					/* Vector which acts as the nadir vector */
double *z_min;					/* Ideal vector for the reference-point update function */
double *z_max;					/* Nadir vector for the reference-point update function */
double *R2record;				/* Circular array for R2 record */

double *RECORD;					/* RECORD for the nadir vectors obtained at each generation */
				

char *Fname;					/* Name of the file containing variable's bounds - USER PARAMETER*/

void (*F)(double *, double *);	/* Pointer to objective function */


int cont;						
int numIt;

float vectorW[100];
float vectorU[100];
float vectorS[100];
float vectorV[100];

float Epsilon; // = 0.1; // 0.05 a 0.1
float Beta; // = 0.35; // 0.25 a 0.4
float Lamdba; // = 0.6; // 0.55 a 0.75


#endif