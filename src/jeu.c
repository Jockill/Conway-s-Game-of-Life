/**
	\file jeu.c
	\brief Source contenant le corps des fonctions de jeu.h
	\author JOCHYMSKI Hugo, powered by Unistra.
*/

#include "../header/jeu.h"
#include <string.h>
#include <unistd.h>
#include <math.h>



void bellePause(){
	printf("\nAppuyez sur entrée pour continuer...\n");
	getchar();
	getchar();
}

int compte_voisins_vivants (int i, int j, grille g){
	int v = 0, l=g.nbl, c = g.nbc;
	v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
	v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);

	return v;
}

int compte_voisins_vivants_nc (int i, int j, grille g){ //TODO: optimisable ! modulo, if
	int v=0, l=g.nbl, c=g.nbc;
	if(i != 0)
	{
		if (j !=0) 			v+= est_vivante(modulo(i-1,l),modulo(j-1,c),g);
										v+= est_vivante(modulo(i-1,l),modulo(j,c),g);
		if (j+1 != c) 	v+= est_vivante(modulo(i-1,l),modulo(j+1,c),g);
	}
	if (j != 0) 			v+= est_vivante(modulo(i,l),modulo(j-1,c),g);
	if (j+1 != c) 		v+= est_vivante(modulo(i,l),modulo(j+1,c),g);
	if (i+1 != l)
	{
		if (j != 0) 		v+= est_vivante(modulo(i+1,l),modulo(j-1,c),g);
										v+= est_vivante(modulo(i+1,l),modulo(j,c),g);
		if (j+1 != c)		v+= est_vivante(modulo(i+1,l),modulo(j+1,c),g);
	}

	return v;
}

void evolue (grille *g, grille *gc){
	copie_grille (*g,*gc); // copie temporaire de la grille
	int i,j,l=g->nbl, c = g->nbc,v;
	g->generation = g->generation+1;
	for (i=0; i<l; i++)
	{
		for (j=0; j<c; ++j)
		{//Comptage des voisins
			if(g->cyclique == 1)	v = compte_voisins_vivants (i, j, *gc);
			//else v = compte_voisins_vivants_nc(i, j, *gc);
			else {
				int (*compte) (int, int, grille) = &compte_voisins_vivants_nc;
				v = (*compte) (i,j,*gc);
			}

			if(est_vivante(i,j,*g))
			{
					if (v == 2 || v == 3)
					{
						if (g->vieillissement)
						{
							g->cellules[i][j] = g->cellules[i][j]+1;
							if (g->cellules[i][j] == 8) set_morte(i,j,*g);
						}
					}
					else set_morte(i,j,*g);
			}


			else
			{ // evolution d'une cellule morte
				if ( v==3 ) set_vivante(i,j,*g);
			}
		}
	}
	return;
}

void changementGrille(grille *g, grille *gc){
	printf("Entrez le nom de la grille : ");
	char nom[50];
	scanf("%s", nom);

	if(access(nom, F_OK) != -1)
	{ //Check si le nom entré existe
		libere_grille(g);
		libere_grille(gc);
		init_grille_from_file(nom, g);
		alloue_grille(g->nbl, g->nbc, gc);
		printf("La grille a bien été chargée.\n");
	}
	else
	{
		printf("La grille que vous cherchez n'existe pas.\n");
		bellePause();
		printf("\e[1;1H\e[2J"); //Clear
	}
}

int grilleMorte(grille g){
	for(int y=0; y<g.nbc; y++)
	{
		for(int x=0; x<g.nbl; x++)
		{
			if(est_vivante(y, x, g) > 0) return 0; // Elle n'est pas morte
		}
	}
	return 1; //Elle est morte
}

void oscillation(grille g, grille gc){
	printf("Arrivee dans oscillation\n");
	//
	//
	// for(int y=0; y<g.nbl; y++)
	// {
	// 	for(int x=0; x<g.nbc; x++)
	// 	{
	// 		printf("vie : %d\n", est_vivante(y, x, g));
	// 	}
	// }
	//
	//
	//

	// Opti : Check si vieillissement on, demander confirmation

	int nbGenMax = 1000;
	int taille = g.nbc*g.nbl;
	int historique[nbGenMax][taille];
	// long double score; //Long double car permet de stocker le score de 4932 cellules
	// score = 0;
	// printf("score = %ld\n", score);
	int pos;
	int stop = 0;

	grille avance = g;
	grille avanceCp = gc;
	grille *pAvance = &avance;
	grille *pAvanceCp = &avanceCp;

	printf("Debut for\n");
	for(int p=1; p<nbGenMax; p++)
	{
		evolue(pAvance, pAvanceCp);
		printf("p = %d\n", p);
		if(grilleMorte(avance))
		{ // Check si grille morte
			fprintf(stderr, "Cette grille n'oscille pas car morte\n");
			return;
		}
		else
		{ // Remplir le tableau
			pos = 0;
			for(int y=0; y<avance.nbl; y++)
			{
				for(int x=0; x<avance.nbc; x++)
				{
					pos++;
					historique[p][pos] = est_vivante(y, x, avance);
				}
			}
		}

		for(int g=0; g<p-1; g++)
		{
			stop = 0;
			for(int i=0; i<taille; i++)
			{
				if(historique[g][i] == historique[p][i])
				{
					if(i == taille-1)
					{
						printf("Cette grille oscille, avec une période de %d a partir de la generation %d\n", p, g);
						return;
					}
				}
				stop = 1;
				break;
			}
			if(stop) break;
		}




			printf("generation %d\n", p);
		}
	fprintf(stderr, "Cette grille n'oscille pas\n");
	return ;
}


//
// void oscillation(grille g, grille gc){
// 	// Demander si vieillesse == 1
//
// 	grille avance = g;
// 	grille avanceCp = gc;
// 	grille *pAvance = &avance;
// 	grille *pAvanceCp = &avanceCp;
//
// 	int nbGenMax = 1000;
// 	int historique[nbGenMax];
// 	remplirTab(avance, historique);
//
// 	// evolue(pAvance, pAvanceCp);
// 	for(int p=1; p<nbGenMax; p++)
// 	{
// 		if(grilleMorte(avance))
// 		{
// 			fprintf(stderr, "Cette grille n'oscille pas car morte\n");
// 			return ;
// 		}
// 		evolue(pAvance, pAvanceCp);
// 		int *pCells = *avance.cellules;
// 		int cells = *pCells;
// 		historique[p] = cells;
// 		for(int i=0; i<p-1; i++)
// 		{
// 			if(historique[0] == historique[p])
// 			{
// 				fprintf(stderr, "Cette grille a une période de %d, a partir de la %d ieme generation\n", p, i);
// 				return;
// 			}
// 		}
// 		printf("generation %d\n", p);
// 	}
// 	fprintf(stderr, "Cette grille n'oscille pas\n");
// 	return ;
// }
