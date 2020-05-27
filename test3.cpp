#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define MAX_SIZE 9 // taille de la matrice 
#define bound 50
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
}Matrice;


void init_element(Element *e, int i, int j, double p) {
	e->i = i;
	e->j = j;
	e->p = p;
}

Matrice*  init_matrice( int m, int n) {
	int i = 0;
	Matrice* M = new Matrice;
	M->m = m;
	M->T = (Element*)malloc(m * sizeof(Element));
	for (i = 0; i < m; i++) {
		M->T[i].i = M->T[i].j = M->T[i].p = 0;
	}
	M->n = n;
	return M;
}


Matrice* remplir_Matrice(FILE *f){
	
	int i,j;
	int d; // nbr d'élément s non nul sur la ligne i 
	int m;  //nbr d'éléments non nuls de la matrice 
	int n; //taille de la matrice carre
	double p;
    fscanf (f,"%d %d",&n, &m);
	Matrice* M = init_matrice(m,n);
    
    int k =0;
    for(j=0;j<n;j++){
		int rowNum;
		fscanf(f,"%d %d",&rowNum, &d);
		for(i=0;i<d;i++){	
			M->T[k].i = rowNum - 1;
			fscanf(f,"%d %lf",&M->T[k].j, &p);
			M->T[k].j -= 1;
					
			M->T[k].p = p;
			k++;
		}	
	}
	return M;
}

void affiche_matrice(Matrice *M){
	int i;
	printf("\n J'affiche la matrice : \n");
	for(i = 0; i < M->m ; i++){
		if(i%3 == 0)printf("\n");
		printf("M[%d][%d] = %f \t", M->T[i].i + 1, M->T[i].j + 1, M->T[i].p);
	}
}

void free_matrice(Matrice *M) {
	free(M->T);
	delete M;
}

// Methode des puissances
double * puissance(Matrice* M, double *x,double *y){
	int i;
	for(i=0;i<M->m;i++){
		y[i] = 0;
		y[M->T[i].j] += x[M->T[i].i] * M->T[i].p;
		
	}
	return y;
}

double * multpuissance(Matrice* M,double *x,double *y,int num){
	int i=0;
	double *tmp = x;
	for(i=0;i<num;i++)
	{
		
		tmp=puissance(M,tmp,y);
		
		
	 }
	
	
		
	
	return tmp;
	
	
 }







double * Gauss_Seidel ( Matrice* a, double x[], double TOL, int MAXN,double y[],double *z )
{
    //Turning "ax=b" into "x=Bx+f"
    //double B[MAX_SIZE][MAX_SIZE]; 
    Matrice* B = init_matrice(a->m, a->n);
    
    
    int i,j, k, l, tmp1, tmp2;
    l = 0;
    for(i=0;i<MAX_SIZE;i++)
    {
        for(j=0;j<MAX_SIZE;j++)
        {
			tmp1 = tmp2 = 0;
            if(j!=i)
            {
				//B[i][j] = -a[i][j]/a[i][i];
				for(k = 0 ; k < a->m ; k++)
				{
					if((a->T[k].i == i) && (a->T[k].j == j))
						tmp1 = -a->T[k].p;
						
					if((a->T[k].i == i) && (a->T[k].j == i))
						tmp2 = a->T[k].p;
						
					if((tmp1 != 0) && (tmp2 != 0)){
						B->T[l].i = i;
						B->T[l].j = j;
						B->T[l].p = tmp1/tmp2;
						l++;
					}
				}
			}
			/*else{
				B.T[l].i = i;
				B.T[l].j = j;
				B.T[l].p = 0;
				l++;
			}
			* En enlèvant ça, il n'y aura jamais d'éléments nuls dans la matrice  B
			*/
			
        }
    }
    
	//Si les valeurs des éléments d'une colonne de la matrice B sont toutes 0
	//La fonction Gauss_Seidel renvoie -1
	
	int count[MAX_SIZE]; //Comptez le nombre d'éléments dans une colonne spécifiée de la matrice B comme 0
	for(i=0;i<MAX_SIZE;i++)
	{
		count[i] = 0;
	}
    for(i = 0; i < B->m; i++)
    {
		if(B->T[i].p != 0)  //Attention voir ligne 100 
			count[B->T[i].i]++;
    }
    
    //if(count[i]==n) return -1;
     
    for(i = 0; i<MAX_SIZE ; i++)
		if(count[i]== 0) ;//return -1;
	
	
	

	
    
  	//Iteration
    l = 0; //nombre d'itération k=0
    double *x_kp1 = y; //Créez un nouveau tableau pour stocker la valeur d'itération de x après la k + 1ème fois
    
    double sum;
    double max = 0; //Utilisé pour calculer la différence
    
    
    for(i=0;i<a->m;i++){
		z[i] = 0;
        
        
            sum = 0;
            for(j=0;j<MAX_SIZE;j++)
            {
				
                if(j<i)
                {
					 // sum += a[i][j]*x_kp1[j];
					for(k = 0 ; k < a->n ; k++)
					{
						if((a->T[k].i == i) && (a->T[k].j == j))
							z[i] += a->T[k].p * x_kp1[j];
					}
				}
                 
                else if(j>i){
					//  sum += a[i][j]*x[j];
					for(k = 0 ; k < a->n ; k++)
					{
						if((a->T[k].i == i) && (a->T[k].j == j))
							z[i] += a->T[k].p * x[j];
					}
				}
            }
            //x_kp1[i] = sum/(1-a[i][i]);
            for(k = 0 ; k < a->n ; k++)
			{
				if((a->T[k].i == i) && (a->T[k].j == i))
					z[i] = z[i]/(1 - a->T[k].p );
					
			}
        
        
        
        
        
	free_matrice(B);
    return z;
   
}
}








//combine y et z dans x
void resultat (Matrice* M, double *y, double *z, double *x) {
	int i; 
	for (i = 0; i < M->n; i++) {
		x[i] = (w * y[i]) + ((1 - w) * z[i]); 
	}
}


void init_vecteur(double * V, int taille){
	int i; 
	
	for(i = 0; i<taille ; i++){
		V[i] = (1.0 / taille * 1.0);
	}
	printf("\n");
}

void affiche_vecteur(double * V, int taille){
	int i; 
	
	printf("\nVecteur : \n");
	for(i = 0; i<taille ; i++)
		printf("%f \t",V[i]);
	printf("\n");
}
int main(){
	FILE *f1 = fopen("web2.txt","r");
	Matrice* M = remplir_Matrice(f1);
	affiche_matrice(M);
	int maxN = (M->n > M->m ? M->n : M->m);
	double* x = (double*)malloc(maxN * sizeof(double));
	
	init_vecteur(x, M->n);
	affiche_vecteur(x, M->n);
	
	double* Y = (double*)malloc(maxN * sizeof(double));
	double* yk = (double*)malloc(maxN * sizeof(double));
	Y=puissance(M,x,Y);
	yk=multpuissance(M,x,Y,10);
	affiche_vecteur(yk, M->n);
	
	
	int MAXN = 100; //Nbre d'itération max
	double TOL = 10.0;
	int i;
	
	
    printf("Result of Gauss-Seidel method:\n");
    
    double *z = (double*)malloc((MAX_SIZE) * sizeof(double));
    z = Gauss_Seidel(M, x, TOL, MAXN ,Y,z);
    for(i = 0; i < MAX_SIZE; i++){
		printf("[%.8lf]\t", z[i]);		
	}
    
   
	
	double* res = (double*)malloc(maxN * sizeof(double));
	
	resultat(M,Y,z,res);
	affiche_vecteur(res, M->n);
	
	free_matrice(M);
	
	
	
	
	free(x);
	free(Y);
	free(res);
	return 0;
}
	
