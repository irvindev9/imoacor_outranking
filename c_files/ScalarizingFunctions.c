#include "../headers/ScalarizingFunctions.h"

//#define WT
//#define PBI
#define ASF


#ifdef WT
double u(double *Fx, WEIGHT *wv){
	return 0.0;
}
#endif

#ifdef PBI
double u(double *Fx, WEIGHT *wv){
	int i;
	double d1, d2, g, w_norm, *diff;

	diff = (double *)calloc(k, sizeof(double));

	// Calculating d1
	w_norm = normL2(wv->w, k);
	for(i = 0; i < k; i++)
		diff[i] = Fx[i] - z_min[i];
	d1 = fabs(innerproduct(diff, wv->w, k))/w_norm;
	// Calculating d2
	for(i = 0; i < k; i++)
		diff[i] = Fx[i] - (z_min[i] + d1*wv->w[i]/w_norm);
	d2 = normL2(diff, k);
	g = d1 + theta*d2;
	free(diff);
	return g;
}
#endif

#ifdef ASF
double u(double *Fx, WEIGHT *wv){
	int i;
	double  asf = -INFINITY, aux, fprime;
	for(i = 0; i < k; i++){
		aux = fabs(Fx[i])/wv->w[i]; // Se emplea el vector 0 como referencia. 
		if(aux > asf)
			asf = aux;
	}
	return asf;
}
#endif
