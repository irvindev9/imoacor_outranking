#include "Global.h"
#include "headers/Weights.h"
#include "headers/Miscellaneous.h"
#include "headers/Allocate.h"
#include "headers/Rand.h"
#include "headers/MOMBI.h"
#include "headers/Outranking.h"
#include "headers/WFG.h"
#include "headers/Parameter.h"
#include "headers/AntOperations.h"

void run(int);

int main(int argc, char *argv[]){

	if(argc != 2 && argc != 3) {
		printf("Syntax: ./imoacor parameter_file_name [#runs]\n");
    	exit(1);
  	}

  	if(argc == 3) 
   		executions = atoi(argv[2]);
  	else
    	executions = 1;	
     // Initializes random seed
 	srand(time(0));
	read_param(argv[1]);	

	// MOP espefication
	getInt("n", &n);
	getInt("k", &k);

	getInt("Gmax", &Gmax);
	//getInt("MAX_ARCHIVE_SIZE", &MAX_ARCHIVE_SIZE);
	
	// Parameters for the RECORD data structure.
	getInt("MAX_RECORD_SIZE", &MAX_RECORD_SIZE);
	getDouble("varThreshold", &varThreshold);
	getDouble("tolThreshold", &tolThreshold);

	// Parameters for ACOR.
	//getInt("M", &M);
	getDouble("Xi", &Xi);
	getDouble("q", &q);

	// Parameters for the weight vectors.
	getInt("H", &H);
	N = choose(H + k - 1, k - 1);

	MAX_ARCHIVE_SIZE = M = N;

	// Allocate memory for all the structures
	allocate_Memory();

	// Parameters for MOP
	getString("Function", &Fname);
	getArrayDouble("Rmin", lowerBounds, n);
  	getArrayDouble("Rmax", upperBounds, n);
  	findfunc(Fname, &F);

  	if(strncmp(Fname, "WFG", 3) == 0) {
   		getInt("k_wfg", &k_wfg);
    	init_WFG(Fname[3] - '0', k, n, k_wfg);
  	}

  	// Initialize weight vectors
	init_Weight_Vectors(WV, H, k);

  	int i;
  	// Execution of the algorithm varying the seed of the random number generator.
  	for(i = 1; i <= executions; i++) {
    	Rseed = (double) rand() / RAND_MAX;
    	randomize(Rseed);
    	run(i);
    	printf("Execution %d of %s in %dD is done!\n", i, Fname, k);
 	 }

 	if(strncmp(Fname, "WFG", 3) == 0)
 		free_WFG();
	free_param();
	free_Memory();
	return 1;
}

void run(int exec){;
	genCounter = 0;
	// Generate randomly initial solutions
	initPheromones();
	// Init z_ideal and z_nad from the pheromones
	initRefpoints();
	// Insert z_nad into the first register of RECORD
	initRecord();
	// Normalize objective vectors
	normalizeObjFuncs(MAX_ARCHIVE_SIZE, _PHE_TYPE_);	
	// Apply R2ranking to the pheromones
	// R2rankingPheromones();
	initValues();
	
	int size;	
	while(genCounter < Gmax){
		AntBasedSolutionConstruction();
		updateRefpoints(Ants, M, k, genCounter);
		Union();
		size = M + T.nap;	
		normalizeObjFuncs(size, _ANTS_TYPE_);			
		// R2ranking(size);
		// ORanking(size);
		PheromoneUpdate(size);
		// R2rankingPheromones();
		genCounter++;		
	}
	ORanking(size);
	// readData();
	saveParetoFront(exec, T.pheromones, T.nap);
	saveParetoSet(exec, T.pheromones, T.nap);
}