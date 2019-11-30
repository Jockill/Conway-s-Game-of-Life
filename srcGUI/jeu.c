/**
	\file jeu.c
	\brief Source contenant le corps des fonctions de jeu.h
	\author JOCHYMSKI Hugo, powered by Unistra.
*/

#include "../header/jeu.h"
#include <string.h>
#include <unistd.h>



void bellePause(){
	printf("\nAppuyez sur entrée pour continuer...\n");
	getchar();
	getchar();
}

int boolSwitch(int b){
	if(b == 1) return 0;
	else if (b == 0) return 1;
	else{
		printf("boolSwitch : ERREUR\n");
		return -1;
	}
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
			if(g.cellules[y][x] > 0) return 0; // Elle n'est pas morte
		}
	}
	return 1; //Elle est morte
}
//
// int celluleVivante(grille *g, int x, int y){
// 	if(g->cellules[y][x] > 0) return 1;
// 	else return 0;
// }

// int oscillation(grille *g, grille *gc)
// {
// 	// Opti : Check si vieillissement on, demander confirmation
//
// 	int nbGenMax = 100;
// 	int taille = g->nbc*g->nbl;
// 	int historique[nbGenMax][taille];
// 	grille avance = *g;
//
// 	// check si avance est morte
// 	if(grilleMorte(&avance))
// 	{
// 		// Lancer le test avec les generations d'apres
// 	}
// 	else
// 	{
// 		unsigned long double score = 0; //Long double car permet de stocker le score de 4932 cellules
// 		int pos = 1;
// 		int vie = 0;
// 		for(int y=0; y<avance.nbc; y++)
// 		{
// 			for(int x=0; x<avance.nbl; x++)
// 			{
// 				vie = celluleVivante(&avance, x, y);
// 				score += vie*pos;
// 				pos*=10;
// 			}
// 		}
//
// 	}
// }

void oscillation(grille g, grille gc){
	// Demander si vieillesse == 1

	// grille gSave = *g;
	// grille gcSave = *gc;
	grille avance = g;
	grille avanceCp = gc;
	grille *pAvance = &avance;
	grille *pAvanceCp = &avanceCp;

	int nbGenMax = 1000;
	grille historique[nbGenMax];
	historique[0] = avance;

	// evolue(pAvance, pAvanceCp);
	for(int p=1; p<nbGenMax; p++)
	{
		if(grilleMorte(avance))
		{
			fprintf(stderr, "Cette grille n'oscille pas\n");
			return ;
		}
		evolue(pAvance, pAvanceCp);
		historique[p] = avance;
		for(int i=0; i<p-1; i++)
		{
			if(historique[i].cellules == historique[p].cellules)
			{
				fprintf(stderr, "Cette grille a une période de %d, a partir de la %d ieme generation\n", p, i);
				return;
			}
		}
	fprintf(stderr, "Cette grille n'oscille pas\n");
	return ;
	}
}
