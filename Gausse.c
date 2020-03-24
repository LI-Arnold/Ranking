int Gauss_Seidel ( int n, double a[][MAX_SIZE], double b[], double x[], double TOL, int MAXN )
{
    //Turning "ax=b" into "x=Bx+f"
    double B[n][n]; 
    int i,j;
    int count[n]; //Comptez le nombre d'éléments dans une colonne spécifiée de la matrice B comme 0
    for(i=0;i<n;i++)
    {
        B[i][i] = 0;
        for(j=0;j<n;j++)
        {
            if(j!=i)
                B[i][j] = -a[i][j]/a[i][i];
        }
    }
    // Si les valeurs des éléments d'une colonne de la matrice B sont toutes 0
     // La fonction Gauss_Seidel renvoie -1
    for(i=0;i<n;i++)
    {
        count[i] = 0;
        for(j=0;j<n;j++)
        {
            if(B[i][j] == 0)
                count[i]++;
        }
    }
    if(count[i]==n)
        return -1;
    //Iteration
    int k = 0; //nombre d'itération k=0
    double x_kp1[n]; //Créez un nouveau tableau pour stocker la valeur d'itération de x après la k + 1ème fois
    double sum;
    double max = 0; //Utilisé pour calculer la différence
    while(k<MAXN)
    {
        k++;
        for(i=0;i<n;i++)
        {
            sum = 0;
            for(j=0;j<n;j++)
            {
                if(j<i)
                    sum += a[i][j]*x_kp1[j];
                if(j>i)
                    sum += a[i][j]*x[j];
            }
            x_kp1[i] = sum/(1-a[i][i]);
        }
        //Trouver la norme infinie de la différence entre x à la k + 1ème itération et x à la kème itération
        max = fabs(x_kp1[0]-x[0]);
        for(i=1;i<n;i++)
        {
            if(max<fabs(x_kp1[i]-x[i]))
                max = fabs(x_kp1[i]-x[i]);
        }
        // Si une valeur de composant de x dans la kème itération dépasse l'intervalle maximum [-bound, bound] limite
        // La fonction Gauss_Seidel renvoie -2
        for(i=0;i<n;i++)
        {
            if(fabs(x_kp1[i])>bound)
               return -2;
            x[i] = x_kp1[i]; 
        }

        for(i=0;i<n;i++)
            x[i] = x_kp1[i]; //Réutiliser le vecteur x pour stocker la valeur x de la k-ième itération
        // Si l'exigence de précision TOL est atteinte après k itérations
         // La fonction Gauss_Seidel retourne la valeur de k (la solution obtenue est stockée dans x)
        if(max<TOL)
            return k;
    }
   // Si l'algorithme n'a pas atteint l'exigence de précision TOL après les itérations MAXN
     // La fonction Gauss_Seidel retourne 0
    return 0;
}


int main()
{
  int n, MAXN, i, j, k;
  double a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE], x[MAX_SIZE];
  double TOL;
    printf("Result of Gauss-Seidel method:\n");
    for ( i=0; i<n; i++ )
      x[i] = 0.0;
    k = Gauss_Seidel( n, a, b, x, TOL, MAXN );
    switch ( k ) {
      case -2:
        printf("No convergence.\n");
        break;
      case -1:
        printf("Matrix has a zero column. No unique solution exists.\n");
        break;
      case 0:
        printf("Maximum number of iterations exceeded.\n");
        break;
      default:
        printf("no_iteration = %d\n", k);
        for ( j=0; j<n; j++ )
          printf("%.8lf\n", x[j]);
        break;
    }
    printf("\n");
  }
  return 0;
}
