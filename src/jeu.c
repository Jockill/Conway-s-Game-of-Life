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
	int pass = 0;
	char nom[30] = "grilles/grille_";
	char num[3] = "";

	do
	{
		printf("\e[1;1H\e[2J"); //Clear
		printf("Veuillez entrer le numero de la grille a charger, ou q pour quitter : ");
		scanf("%s", num);

		if(num[0] == 'q') return;

		strcat(nom, num);
		strcat(nom, ".txt");

		if(access(nom, F_OK) != -1)
		{ //Check si le nom entré existe
			libere_grille(g);
			libere_grille(gc);
			init_grille_from_file(nom, g);
			alloue_grille(g->nbl, g->nbc, gc);
			pass = 1;
			strcpy(nom, "grilles/grille");
			strcpy(num, "");
		}
		else
		{
			strcpy(nom, "grilles/grille");
			strcpy(num, "");
			printf("La grille que vous cherchez n'existe pas.\nVeuillez vous assurer : \n1. Que vous l'avez bien enregistrée dans le format 'grille<numero>.txt'\n2. Que vous l'avez enregistrée dans <dossier_racine_du_jeu>/grilles\n");
			bellePause();
			printf("\e[1;1H\e[2J"); //Clear
		}
	}while(pass == 0);
}
