#include <stdio.h>
#include <stdlib.h>

/*************************************************/
/*                                               */
/*                sucre syntaxique               */
/*                                               */
/*************************************************/

#define AND &&
#define OR ||
#define ISNOT !=
#define NOT !
#define then 

typedef enum { false, true} bool;

/*************************************************/
/*                                               */
/*            factorielle                        */
/*                                               */
/*************************************************/

long fact (int n) 
{ if (n==0) return 1 ;
  else return n * fact(n-1) ; 
}

// itou avec un arg out => passage par adresse

void bisfact(int n, long * r) 
{ if (n==0) 
         *r=1.0 ;
  else { bisfact(n-1,r) ;
         *r = *r *n ;
       }
}

long fact2 (int n)
{ long r ;
  bisfact(n,&r) ;
  return r ;
}

/*************************************************/
/*                                               */
/*            Calcul de e                        */
/*                                               */
/*************************************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

     // Il est proposé de faire 3 versions pour observer des phénomènes de précision.
     // C'est le même code, seul le type change.

/*************************************************/

float Efloat () {
    float acc = 0.0;
    float den = 1.0;
    float terme;
    int i = 1;
    do {
        terme = 1 / den;
        acc += terme;
        den *= i;
        i++;
    } while (terme > 1e-7); // On choisit la valeur 1e-7, puisqu'on utilise des floats.
    return acc;
 }

/*************************************************/

double Edouble () { 
    double acc = 0.0;
    double den = 1.0;
    double terme;
    int i = 1;
    do {
        terme = 1 / den;
        acc += terme;
        den *= i;
        i++;
    } while (terme > 1e-14);
    return acc; 
}
  
/*************************************************/

long double Elongdouble () { 
    long double acc = 0.0;
    long double den = 1.0;
    long double terme;
    int i = 1;
    do {
        terme = 1 / den;
        acc += terme;
        den *= i;
        i++;
    } while (terme > 1e-18);
    return acc; 
}





/*************************************************/
/*                                               */
/*            Suite Y                            */
/*                                               */
/*************************************************/



void afficheYfloat (int n) {
    float y = Efloat() - 1;
    for (int i = 1; i <= n + 1; i++) {
        printf("y(%d): %f \n", i - 1, y);
        y = (i * y) - 1;
    }
}

/*************************************************/

void afficheYdouble (int n) {
    double y = Edouble() - 1;
    for (int i = 1; i <= n + 1; i++) {
        printf("y(%d): %lf \n", i - 1, y);
        y = (i * y) - 1;
    }
}

/*************************************************/

void afficheYlongdouble (int n) {
    long double y = Elongdouble() - 1;
    for (int i = 1; i <= n + 1; i++) {
        printf("y(%d): %Lf \n", i - 1, y);
        y = (i * y) - 1;
    }
}





/*************************************************/
/*                                               */
/*            Puissance                          */
/*                                               */
/*************************************************/



double power1 (double x, long n) { 
  if(n == 0) { 
    return 1; // Cette ligne a comme conséquence que 0^0=1
  }

  if(n > 0) {
    return x * power1(x, n - 1);
  }

  if(n < 0) {
    return (1 / x) * power1(x, n + 1); // On ne gère pas le cas x = 0, puisque celui-ci va planter.
  }

}

/*************************************************/

double power2a (double x, long n) { 
  double r = 1; // Cela implique que 0^0 renvoie 1
  for(int i = 0; i < n; i++) {
    if(n < 0) {
      r = (1 / x) * r; // Cela plante si x = 0
    }
    else {
       r = x * r;
    }
  }
  return r;
}

/*************************************************/

double power2b (double x, long n) { 
  double r = 1;
  while(n != 0) {
    r = x * r;
    n--;
  }
  return r;
 }

/*************************************************/

// Sous-procédure pour la fonction power3
double spow3 (double x, long n, double *r){
  if(n > 0) { // Si n <= 0 on ne fait rien. Le cas n = 1 sera, alors le dernier qui lance un appel récursif.
    *r = *r * x;
    spow3(x, n - 1, r);
  }
}

double power3 (double x, long n) { 
  double r = 1;
  spow3(x, n, &r);
  return r;
}

/*************************************************/

// Sous-fonction pour power4
double spow4 (double x, long n, double r) {
  if(n==0) { return r; } // On ne gère pas le cas n < 0. Ceci causera un SegFault.
  return spow4(x, n - 1, x * r);
}

double power4 (double x, long n) {
  return spow4(x, n, 1);
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : rame : 8 en 1/2s, 9 en qqs s, 10 en 1m

double power5 (double x, long n)
{
    if (n == 0)
         return 1 ;
    else if (n % 2 == 0)
              return (power5(x,n/2)*power5(x,n/2)   ) ;
         else return (power5(x,n/2)*power5(x,n/2) *x) ;   
}

/*************************************************/

double power6 (double x, long n) {
  if (n == 0) { return 1; }
  double y = power6(x, n / 2);
  if (n % 2 == 0) {
    return y * y;
  }
  // Si n impair
  return y * y * x;
}

/*************************************************/

double power7 (double x, long n) { 
  if (n == 0) { return 1; }
  if (n % 2 == 0) {
    return power7(x * x, n / 2);
  }
  // Si n impair
  return power7(x * x, n / 2) * x;
}

/*************************************************/
// Sous-fonction pour power8
double spow8(double x, long n, double r) {
  if(n == 0) { return r; }
  if (n % 2 == 0) {
    return spow8(x * x, n / 2, r);
  }
  // Si n impair
  return spow8(x * x, n / 2, r * x);
}

double power8 (double x, long n) { 
  return spow8(x, n, 1);
}

/*************************************************/
// Sous-procédure pour power9
void spow9(double x, long n, double *r) {
  if(n == 0) { return; }
  if(n % 2 == 1) {
    *r = *r * x;
  }
  spow9(x * x, n / 2, r);
}

double power9 (double x, long n) { 
  double r = 1;
  spow9(x, n, &r);
  return r;
}

/*************************************************/

     //   Observation (1+1/10^k)^(10^k) : calcul immédiat

double power10 (double x, long n)
{
    double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

double power (double x, long n, int i)
{ switch (i)  
   {
   case 1 : return power1(x,n) ; break ;
   case 2 : return power2a(x,n) ; break ;  // 2 pour 2a
   case 0 : return power2b(x,n) ; break ; // 0 pour 2b
   case 3 : return power3(x,n) ; break ;
   case 4 : return power4(x,n) ; break ;
   case 5 : return power5(x,n) ; break ;
   case 6 : return power6(x,n) ; break ;
   case 7 : return power7(x,n) ; break ;
   case 8 : return power8(x,n) ; break ;
   case 9 : return power9(x,n) ; break ;
  case 10 : return power10(x,n) ; break ;
     default : return 0 ; 
   }
}

   // remarque : les break sont ici inutiles car les returns font déjà des break

/*************************************************/

    // memes versions que la 10 mais avec des long double, puis des floats
    // but du jeu : observer des variations de precision

   // observation :
   //   imprécision à partir de k~5 (float), k~12 (double), k~14 (long double)
   //   rend 1 à partir de k=8 (float), k=16 (double)
   //   rend 1 non observé sur les long double, maxint atteint avant

long double power11 (long double x, long n)
{
    long double r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}

/*************************************************/

float power12 (float x, long n)
{
    float r = 1.0 ;
    while (n ISNOT 0) 
      { if (n % 2 == 1) then r = r*x ; // no else
        n = n / 2 ; 
        x = x * x ;
       }
    return r ;
}





/*************************************************/
/*                                               */
/*             Ackermann                         */
/*                                               */
/*************************************************/



/*********************/
/* Version récursive */
/*********************/


int A1(int m, int n) { 
  if(m == 0){ return n + 1; }
  if(n == 0){ return A1(m - 1, 1); }

  return A1(m-1, A1(m,n-1));
 }

int Ackermann1 (int m) { return A1(m, 0); }



/******************************************/
/* Version récursive en m, itérative en n */
/******************************************/


int A2(int m, int n) { 
  if (m == 0) return  n + 1;

  int resultat = 1;
  for(int i = 1; i <= n + 1; i++) {
    resultat = A2(m - 1, resultat);
  }

  return resultat;
}

int Ackermann2 (int m) { return A2(m, 0); }



/******************************************/
/* Version itértative en m, récursive en n */
/******************************************/


int A3(int m, int n){
    if(n == 0) {
        if(m == 0) return 1;
        else return A3(m - 1, 1);
    }
    else{
        int acc = n;
        for(int i = 0; i < m; i++){
            acc = A3(m - i, acc - 1);
        }
        return acc + 1;
    }
}

int Ackermann3 (int m) { return A3(m, 0); }



/*********************/
/* Version itérative */
/*********************/


int A4(int m, int n) {
    int *dyarray = NULL;  // Pointeur vers un tas (tableau dynamic array)
    int taille = 0;
    while(1) {
        if (m == 0) {
            n++;
            if (taille == 0) {
                break;
            }
            taille--;
            m = dyarray[taille];
            dyarray = realloc(dyarray, taille * sizeof (int));  // Ajuste la taille du tas
            continue;
        }

        if (n == 0) {
            m--;
            n = 1;
            continue;
        }

        dyarray = realloc(dyarray, (taille + 1) * sizeof (int));
        dyarray[taille] = m - 1;
        taille++;
        n--;
    }
    free(dyarray);
    return n;
}

int Ackermann4 (int m) { return A4(m, 0); }



/*******************************/
/* Version itérative optimisée */
/*******************************/


/* Implementation pile */
typedef struct Bloc {
    int m;
    int occurence;
    struct Bloc *next;
    } Bloc;

typedef Bloc *Pile;

Pile ajoute(int m,Pile L){
    Pile tmp = (Pile) malloc(sizeof (Bloc));
    tmp -> m = m;
    tmp -> occurence = 1;
    tmp -> next = L;
    return tmp;
}

void empile(int m, Pile *L){
    *L = ajoute(m, *L);
}

void depile(Pile *L)
{
    Pile tmp = *L;
    *L = tmp -> next;
    free(tmp);
}

bool estVide(Pile L)
{
    return L == NULL;
}

void PrintPile(Pile L){
    while(!estVide(L)) {
        printf("[occ:%d,val:%d]\n", L->occurence, L->m);
        L = L -> next;
    }
}


/* Implementation Ackermann */
int Hackermann(int m, int n) {
  Pile pIle = (Pile) malloc(sizeof (Bloc));
  pIle -> m = m;
  pIle -> occurence = 1;
  pIle -> next = NULL;
  while(pIle != NULL) {
    if(pIle -> occurence <= 0||pIle->m<0){
      depile(&pIle);
    }
    else if(n == 0){
      n++;
      if(pIle -> occurence == 1) {
        pIle -> m --;
        m = pIle -> m;
      }
      else {
        pIle -> occurence --;
        if(pIle -> occurence <= 0) {
          depile(&pIle);
        }
        empile((pIle -> m) - 1, &pIle);          
      }
    }
    else if (pIle -> m == 0) {
      n++;
      pIle -> occurence --;
      if(pIle -> occurence <= 0){
        depile(&pIle);
      }
    }
    else {
      int k = pIle -> m;
      pIle -> occurence --;
      if(pIle -> occurence <= 0){
        depile(&pIle);
      }

      empile(k - 1, &pIle);
      pIle -> occurence = pIle -> occurence + n;
      n = 1;
    }
  }

  return n;
}

int Ackermann5 (int m) { return Hackermann(m,0); }



/************************************************/
/* Gestion des différentes versions d'Ackermann */
/************************************************/

  
int Ackermann (int m, int i)
{ switch (i)  
   {
   case 1 : return Ackermann1 (m) ; // break ;
   case 2 : return Ackermann2 (m) ; // break ;
   case 3 : return Ackermann3 (m) ; // break ;
   case 4 : return Ackermann4 (m) ; // break ;
   case 5 : return Ackermann5 (m) ; // break ;
   default : return 0 ; 
   }
}





/*************************************************/
/*                                               */
/*               Suites x                        */
/*                                               */
/*************************************************/



int ln2(int n) {
  int acc = 0;
  while(n > 1) {
    n = n / 2;
    acc ++;
  }
  return acc;
}


int X_iter(int n) {
  int x = 2;
  for(int i = 0; i < n; i++) {
    x = x + ln2(x);
  }
  return x;
}


int X_rec(int n) {
  if( n == 0) return 2;
  else {
    int res = X_rec(n - 1);
    return res + ln2(res);
  }
}


int X_sous_fonction_aux(int n, int acc) {
  if (n == 0) return acc;
  else {
    acc = acc + ln2(acc);
    return X_sous_fonction_aux(n - 1, acc);
  }
}


int X_rec_sous_fonction(int n) {
  return X_sous_fonction_aux(n, 2);
}


void X_sous_procedure_aux(int n, int *acc) {
  if (n == 0);
  else {
    *acc = *acc + ln2(*acc);
    X_sous_procedure_aux(n - 1, acc);
  }
}


int X_rec_sous_procedure(int n) {
  int r = 2;
  X_sous_procedure_aux(n, &r);
  return r;
}



/*************************************************/
/*                                               */
/*               main                            */
/*                                               */
/*************************************************/


int main(int argc, char** argv)
{

       double x ;
       long double y ;
       float z ;
       
       int cptx ;
  
       long nx ;
       
       int i,j ; 
       
/******************************************************************************/
 
    // mettre "if true" vs "if false" selon que vous voulez les tests ou non
  
/****************  petit test sur le fonctionnement du switch  ************/

if (false) {

 switch (2)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }


 switch (4)  
   {
   case 1 : printf("toc\n") ;  break ;
   case 2 : printf("pata") ; 
   case 3 : printf("pouf\n") ;  break ;
   case 4 : printf("youpla") ; 
   default : printf("boum\n") ; 
   }

   printf("\n") ; 

}
      
      
/************************  taille des nombres  *************************/
      
if (true) {     
       
       printf("ce programme suppose que les long font 8 octets\n") ;
       printf("S'ils n'en font que 4, il faudra utiliser long long\n") ;

       printf("short : %d octets\n", (int) sizeof(short));
       printf("int : %d octets\n", (int) sizeof(int));
       printf("long : %d octets\n", (int) sizeof(long));
       printf("long long : %d octets\n", (int) sizeof(long long));
       printf("float : %d octets\n", (int) sizeof(float));
       printf("double : %d octets\n", (int) sizeof(double));
       printf("long double : %d octets\n", (int) sizeof(long double));
       printf("\n") ;
 
       x = 1.0 ;
       cptx = 0 ;
       while ( (1.0 + x) - 1.0 != 0 )
          { x = x/10 ; cptx ++ ; }
       printf("1+1/10^c devient 1 a partir de c=%d pour les double\n", cptx) ; 
       printf("et 1+1/10^%d vaut en fait 1+%lf\n", cptx-1, (1.0 + 10*x) - 1.0) ;
        
       printf("ce programme suppose que les doubles font au moins 8 octets\n") ;
       printf("et que ((double) 1+1/10^-15) n'est pas 1 \n") ;       
       printf("Si ce n'est pas le cas, utiliser des long double \n") ;
       
       printf("\n") ;      
}

/************************  factorielle  *************************/

if (true) {

     printf("%ld \n",fact(5)) ;
     printf("%ld \n",fact2(5)) ;
     printf("\n") ;
}


/******************    Autour de e      *******************************/

  // d'après google,
  // e = 2,7182818284 5904523536 0287471352 6624977572 4709369995 
  //       9574966967 6277240766 3035354759 4571382178 5251664274

if (true) {  
       

        printf(" e1 = %.20f \n", Efloat()) ;
        printf(" e3 = %.30lf \n", Edouble()) ; 
        printf(" e3 = %.40Lf \n", Elongdouble()) ; 
        
}

if (true) {  
            printf("Suite Y\n");
            afficheYfloat(30) ;
            afficheYdouble(30) ;
            afficheYlongdouble(30) ;
}
        
/******************    power     *******************************/

if (true) {  

        //   test simplet, vérifie le B.A. BA, test de 2^10 pour toutes les versions
        
        for(i=0 ; i<=10 ; i++)
        printf("Power %d dit que power(2,10) vaut %.0lf \n", i, power(2,10,i) ) ;
        
        printf("\n") ;
      
}

        
if (true) {  

        i=8 ;  // numéro de la version que l'on teste

        // test de la résistance de power version i, calcul de (1+1/N)^N
        // pour des N puissances de 10 de plus en plus grosses
     
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=15 ; j++)
        {
        printf("power %d ((1+10^-%2d)^(10^%2d)) rend %.12lf\n", i, j, j, power(1+x,nx,i)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;
       
} // REMARQUE: POUR LES VERSIONS RÉCURSIVES TERMINALES, LE PROGRAMME NE CAUSE PAS DE SEG-FAULT, ALORS LE COMPILATEUR OPTIMISE LE CODE.

// Teste toutes les versions pour calculer e (Cause un seg-fault pour les versions récursives)
if (false) {
        z = 1.0 ;
        nx = 1 ;
        for(int i = 0; i <= 10; i++) {
          for(int j = 0 ; j <= 15 ; j++) {
            printf("power %d dit que ((1+ 10^-%2d)^(10^%2d)) = %.12f\n", i, j, j, power(1+z, nx, i)) ;
            z = z/10 ;
            nx = nx * 10 ;
          }
        }
}
     
if (false) {

        // tests sur la précision que l'on obtient suivant que
        // l'on utilise float, double, long double

        printf("VERSION 12 avec float \n") ;
        z = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12f\n", j, j, power12(1+z,nx)) ;
        z = z/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 10 avec double \n") ;
        x = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12lf\n", j, j, power10(1+x,nx)) ;
        x = x/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;


        printf("VERSION 11 avec long double \n") ;
        y = 1.0 ;
        nx = 1 ;
        for(j=0 ; j<=18 ; j++)
        {
        printf("power((1+10^-%2d)^(10^%2d)) rend %.12LF\n", j, j, power11(1+y,nx)) ;
        y = y/10 ;
        nx = nx * 10 ;
        }
        printf("\n") ;



}

/******************    Ackermann    *******************************/
                
if (true) { 
 
        for(i=0 ; i<=5 ; i++)  // numéro de version
        
        for(j=0 ; j<=5 ; j++)  // test de A(j,0) pour j de 0 à 5
        
        printf("Ack%d(%d) = %d \n", i, j, Ackermann(j,i)) ;
}

/***********************************************************************/

/******************       Suite x_n      *******************************/
                
if (true) { 
  printf("SUITE X_n\n");
  printf("Calcul de X_100:\n");
  printf("Itérative: %d\n", X_iter(100));
  printf("Récursive: %d\n", X_rec(100));
  printf("Récursive avec sous fonction: %d\n", X_rec_sous_fonction(100));
  printf("Récursive avec sous procédure: %d\n", X_rec_sous_procedure(100));
}

/***********************************************************************/

    return 0;
}
