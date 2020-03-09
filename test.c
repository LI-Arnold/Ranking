#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


typedef struct {
	int i;
	int j;
	double p;
}Element;

typedef struct {
	int m;
	Element *T; //tableau d'elements
	int n; //taille de la matrice carre
	int *debCol;
}Matrice;


void init_element(Element *e, int i, int j, double p) {
	e->i = i;
	e->j = j;
	e->p = p;
}

void init_matrice(Matrice *M, int m, int n) {
	M->m = m;
	M->T = malloc(m * sizeof(Element));
	M->n = n;
	M->debCol = malloc((n + 1) * sizeof(int));
	int i ;
	for(i = 0; i < n + 1; i++) {
		M->debCol[i] = 0;
	}
}

void free_matrice(Matrice *M) {
	free(M->T);
	free(M->debCol);
}

int main(){
	
	
	
	
	
	
	return 0;
}
	
