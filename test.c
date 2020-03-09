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

// Methode des puissances
void puissance(Matrice M, double *x, int k, double *y){
	int i,j;
	for(i=0;i<M.n;i++){
		for (j = M.debCol[i]; j < M.debCol[i + 1]; j++) {
				y[i] += x[M.T[j].i] * M.T[j].p;
			}
	}
}



int main(){
	
	
	
	
	
	return 0;
}
	
