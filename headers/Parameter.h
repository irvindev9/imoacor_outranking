/* parametros.h: Prototipos de funcion para el procesamiento de archivos
 *               de configuracion.
 *
 * Seccion de Computacion - CINVESTAV
 *
 * Introduccion a la Computacion Evolutiva
 * Profesor: Carlos Coello Coello
 * Autor:    Raquel Hernandez Gomez
 * Junio 2012
 */

 #ifndef __PARAMETER_H__
 #define __PARAMETER_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
 
void init_param();
void free_param(); 
int count_param(FILE *fp); 
void read_param(char *arch); 
int find_param(char *s); 
void getInt(char *s, int *v); 
void getDouble(char *s, double *v); 
void getString(char *s, char **v); 
char *getToken(char *str, char *token); 
void getArrayDouble(char *s, double *v, int n); 
void getArrayInt(char *s, int *v, int n); 

#endif

