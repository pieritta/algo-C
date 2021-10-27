#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

void initTableau(int *tab, int taille){
	int i;
	for(i = 0; i < taille; i++)
		tab[i]=random();
}

void swap(int *a, int *b){
	int x = *a;
	*a = *b;
	*b = x;
}

char domine( int *tab, int taille, int j ){

	if( 2*(j+1)-1 >= taille) /* tab[j] est seul */
		return TRUE;

	else if(2*(j+1)-1 == taille-1 && tab[j] >= tab[2*(j+1)-1]) /* tab[j] a 1 descendant et domine */
			return TRUE;

	else if(tab[j] >= tab[2*(j+1)-1] && tab[j] >= tab[2*(j+1)]) /* tab[j] a 2 descendants et domine */
			return TRUE;

	return FALSE; /* Dans le cas ou tab[j] n'est pas seul et ne domine pas */
}

void retablirTas( int *tab, int j, int taille ){

	while(!domine(tab, taille, j)){/* I(j) et j domine => tab[0...taille-1] est un tas.*/

		if( 2*(j+1) == taille){ /* degre 1 && I(2(j+1)-1) */
			swap(&tab[j], &tab[ 2*(j+1)-1 ]);
			j = 2*(j+1)-1;
		}

		else{ /* degre 2 */
			if( tab[ 2*(j+1)-1 ] >= tab[ 2*(j+1) ] ){ /* I(2(j+1)-1) */
				swap( &tab[ 2*(j+1)-1 ], &tab[j] );
				j = 2*(j+1)-1; /* I(j) */
			}

			else{ /*I(2*(j+1)) */
				swap(&tab[ 2*(j+1) ], &tab[j]);
				j = 2*(j+1); /* I(j) */
			}
		}
	}
}

void faireTas(int *tab, int taille){
	int k;
	for(k = taille-1; k >= 0; k--)
		retablirTas(tab, k, taille);
}

int main(){
	int *tab;
	int taille;
	int f;

	/* Mesure du temps d'execution*/
	clock_t start, end;
	double elapsed;

	printf("Entrer la taille du tableau :\t");
	scanf("%d", &taille);
	f = taille;

	if ( ( tab = (int *)malloc( (sizeof(int)*taille)) ) == NULL)
		exit(EXIT_FAILURE);

	initTableau(tab,taille);

	start = clock(); /* lancement de la mesure */

	faireTas(tab, taille);

	/* I(f) = tab[0 ... f-1] est un tas
	&& ensemble des elements de tab[0 ... f-1] inferieur ou egal
	a ensemble des elements tab[f ... taille-1]
	&& tab[f ... taille-1] est trie croissant
	*/

	while ( f > 1){ /* I(k) && (k>1)*/
                swap(&tab[0], &tab[f-1]);
                retablirTas(tab, 0, f-1); /* I(k-1) */
                f--;
        }

	end = clock(); /* arret de la mesure */
	elapsed =(double)(end-start)/CLOCKS_PER_SEC;
	printf("Temps de calcul : %lf\n",elapsed);

	exit(EXIT_SUCCESS);
}
