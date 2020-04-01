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
	int *debCol;
}Matrice;


void init_element(Element *e, int i, int j, double p) {
	e->i = i;
	e->j = j;
	e->p = p;
}

Matrice  init_matrice( int m, int n) {
	Matrice M;
	M.m = m;
	M.T = malloc(m * sizeof(Element));
	M.n = n;
	M.debCol = malloc((n + 1) * sizeof(int));
	int i ;
	for(i = 0; i < n + 1; i++) {
		M.debCol[i] = 0;
	}
	return M;
}


Matrice remplir_Matrice(Matrice M,FILE *f){
	
	int i,j;
	int d; // nbr d'élément s non nul sur la ligne i 
	int m;  //nbr d'éléments non nuls de la matrice 
	int n; //taille de la matrice carre
	double p;
    fscanf (f,"%d %d",&n, &m);
    M = init_matrice(m,n);
    
    int k =0;
    for(j=0;j<m;j++){
		fscanf(f,"%d %d",&M.T[k].i, &d);	
		M.T[k].i-= 1; 
		
		for(i=0;i<d;i++){				
			fscanf(f,"%d %lf",&M.T[k].j, &p);
			M.T[k].j -= 1;
					
			M.T[k].p = p;
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
		printf("M[%d][%d] = %f \t", M->T[i].i, M->T[i].j, M->T[i].p);
	}
}

void free_matrice(Matrice *M) {
	free(M->T);
	free(M->debCol);
}

// Methode des puissances
void puissance(Matrice M, double *x, int k, double *y){
	int i;
	for(i=0;i<M.m;i++){
		y[i] = 0;
		y[M.T[i].j] += x[M.T[i].i] * M.T[i].p;
		
	}
	
	
	/*
	 int i,j;
	for(i=0;i<M.n;i++){
		for (j = M.debCol[i]; j < M.debCol[i + 1]; j++) {
				y[i] += x[M.T[j].i] * M.T[j].p;
			}
			
	}
	*/
	
}



double * Gauss_Seidel ( Matrice a, double x[], double TOL, int MAXN )
{
    //Turning "ax=b" into "x=Bx+f"
    //double B[MAX_SIZE][MAX_SIZE]; 
    Matrice B = init_matrice(a.m, a.n);
    
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
				for(k = 0 ; k < a.m ; k++)
				{
					if((a.T[k].i == i) && (a.T[k].j == j))
						tmp1 = -a.T[k].p;
						
					if((a.T[k].i == i) && (a.T[k].j == i))
						tmp2 = a.T[k].p;
						
					if((tmp1 != 0) && (tmp2 != 0)){
						B.T[l].i = i;
						B.T[l].j = j;
						B.T[l].p = tmp1/tmp2;
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
    for(i = 0; i < B.m; i++)
    {
		if(B.T[i].p != 0)  //Attention voir ligne 100 
			count[B.T[i].i]++;
    }
    
    //if(count[i]==n) return -1;
     
    for(i = 0; i<MAX_SIZE ; i++)
		if(count[i]== 0) ;//return -1;
	
	
	

	
    
  	//Iteration
    l = 0; //nombre d'itération k=0
    double *x_kp1 = malloc((MAX_SIZE) * sizeof(double)); //Créez un nouveau tableau pour stocker la valeur d'itération de x après la k + 1ème fois
    
    double sum;
    double max = 0; //Utilisé pour calculer la différence
    
    
    while(k<MAXN)
    {
        l++;
        for(i=0;i<MAX_SIZE;i++)
        {
            sum = 0;
            for(j=0;j<MAX_SIZE;j++)
            {
                if(j<i)
                {
					 // sum += a[i][j]*x_kp1[j];
					for(k = 0 ; k < a.n ; k++)
					{
						if((a.T[k].i == i) && (a.T[k].j == j))
							sum += a.T[k].p * x_kp1[j];
					}
				}
                 
                else if(j>i){
					//  sum += a[i][j]*x[j];
					for(k = 0 ; k < a.n ; k++)
					{
						if((a.T[k].i == i) && (a.T[k].j == j))
							sum += a.T[k].p * x[j];
					}
				}
            }
            //x_kp1[i] = sum/(1-a[i][i]);
            for(k = 0 ; k < a.n ; k++)
			{
				if((a.T[k].i == i) && (a.T[k].j == i))
					x_kp1[i] = sum/(1 - a.T[k].p );
					
			}
        }
        
        
        
        //Trouver la norme infinie de la différence entre x à la k + 1ème itération et x à la kème itération
        max = fabs(x_kp1[0]-x[0]);
        for(i=1;i<MAX_SIZE;i++)
        {
            if(max<fabs(x_kp1[i]-x[i]))
                max = fabs(x_kp1[i]-x[i]);
        }
        //Si une valeur de composant de x dans la kème itération dépasse l'intervalle maximum [-bound, bound] limite
        //La fonction Gauss_Seidel renvoie -2 
		
        for(i=0;i<MAX_SIZE;i++)
        {
            //if(fabs(x_kp1[i])>bound)
               //return 2;
               
            x[i] = x_kp1[i]; 
        }

        for(i=0;i<MAX_SIZE;i++)
            x[i] = x_kp1[i]; 	//Réutiliser le vecteur x pour stocker la valeur x de la k-ième itération
        //Si l'exigence de précision TOL est atteinte après k itérations
         //La fonction Gauss_Seidel retourne la valeur de k (la solution obtenue est stockée dans x)
        
        //if(max<TOL)
         //  return k;
        
        
         
    }
    
   // Si l'algorithme n'a pas atteint l'exigence de précision TOL après les itérations MAXN
    // La fonction Gauss_Seidel retourne 0
	
    return x_kp1;
   
}








//combine y et z dans x
void resultat (Matrice M, double *y, double *z, double *x) {
	int i; 
	for (i = 0; i < M.n; i++) {
		x[i] = (w * y[i]) + ((1 - w) * z[i]); 
	}
}


void init_vecteur(double * V, int taille){
	int i; 
	
	for(i = 0; i<taille ; i++){
		V[i] = 1;
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
	
	
	Matrice M = init_matrice(5,5);
	FILE *f1 = fopen("web2.txt","r");
	M = remplir_Matrice(M, f1);
	affiche_matrice(&M);
	double x[M.n];
	
	init_vecteur(x, M.n);
	affiche_vecteur(x, M.n);
	double y[M.n];
	
	puissance(M,x,2,y);
	affiche_vecteur(y, M.n);
	
	
	int MAXN = 10; //Nbre d'itération max
	double TOL = 10.0;
	int i;
	
    printf("Result of Gauss-Seidel method:\n");
    double *z = malloc((MAX_SIZE) * sizeof(double));
    z = Gauss_Seidel( M, x, TOL, MAXN );
    for(i = 0; i < MAX_SIZE; i++){
		printf("[%.8lf]\t", z[i]);		
	}
    
   
	
	double res[M.n];
	
	resultat(M,y,z,res);
	affiche_vecteur(res, M.n);
	
	//free_matrice(&M);
	
	
	
	
	
	return 0;
}
	
