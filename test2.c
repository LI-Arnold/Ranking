#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


#define w 0.8

typedef struct {
	int i; //position i de l'élément
	int j; //position j de l'élément
	double p; //valeur élément
}Element;

typedef struct {
	int m;  //nbr d'éléments non nuls de la matrice 
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

void remplir_Matrice(Matrice *M,FILE *f){
	
	int i,j;
	int n,m,d;
	double p;
    
    fscanf (f,"%d %d",&m, &n);
    init_matrice(M,m,n);
    
    for(j=0;j<n;j++){
		fscanf(f,"%d %d",&M->T->i, &d);
		M->T->i -= 1;
		for(i=0;i<d;i++){				
			fscanf(f,"%d %lf",&M->T->i, &p);
			M->T->j -= 1;
					
			M->T->p = p;
		}
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



//combine y et z dans x
void resultat (Matrice M, double *y, double *z, double *x) {
	int i; 
	for (i = 0; i < M.n; i++) {
		x[i] = (w * y[i]) + ((1 - w) * z[i]); 
	}
}


int main(){
	
	
	
	
	
	return 0;
}
	
