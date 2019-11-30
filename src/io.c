/**
	\file io.c
	\brief Source contenant le corps des fonctions de io.h
	\author JOCHYMSKI Hugo, powered by Unistra.
*/

#include "../header/io.h"
#include "../header/jeu.h"
#include <string.h>
#include <unistd.h>



void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne, grille g){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   ");
		else
		{
			if (ligne[i] == -1) printf("| X ");
			else if (g.vieillissement==1) printf ("| %d ", ligne[i]);
			else printf ("| ¤ ");
		}
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], g);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void afficheBool(int b){
	if (b == 1) printf("Oui");
	else if (b == 0) printf("Non");
	else printf("afficheBool : ERREUR");
}

void affiche_header(grille g){
	printf("Generation : %d\nCalcul cyclique : ", g.generation);
	afficheBool(g.cyclique);
	printf("\nPrise en compte du vieillissement : ");
	afficheBool(g.vieillissement);
	printf("\n");
}

void clear(){
	printf("\e[1;1H\e[2J");
}

void debut_jeu(grille *g, grille *gc){
	clear();
	g->cyclique = 0;
	g->vieillissement = 0;
	affiche_header(*g);
	affiche_grille(*g);

	char c = getchar();

	do
	{
		switch (c) {
			case 'v' :
			{ //Touche v pour activer/désactiver l'affichage du vieillissement.
				g->vieillissement = !g->vieillissement;
				break;
			}
			case 'c' :
			{//Active/Désactive le calcul cyclique des voisins.
				g->cyclique = !g->cyclique;
				break;
			}
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				clear();
				affiche_header(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			{ //Touche n pour changer de grille.
				changementGrille(g, gc);
				break;
			}
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	} while (c != 'q'); // touche 'q' pour quitter
	return;
}
