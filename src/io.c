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

void affiche_ligne (int c, int* ligne, int vieillissement){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   ");
		else
		{
			if (vieillissement==1) printf ("| %d ", ligne[i]);
			else printf ("| x ");
		}
	printf("|\n");
	return;
}

void affiche_grille (grille g, int vieillissement){
	int i, l=g.nbl, c=g.nbc;
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i], vieillissement);
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

void affiche_header(grille g, int cyclique, int vieillissement){
	printf("Generation : %d\nCalcul cyclique : ", g.generation);
	afficheBool(cyclique);
	printf("\nPrise en compte du vieillissement : ");
	afficheBool(vieillissement);
	printf("\n");
}

void clear(){
	printf("\e[1;1H\e[2J");
}
/*
void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*3 + 5);
}
*/
void debut_jeu(grille *g, grille *gc){
	clear();
	int cyclique = 0;
	int vieillissement = 0;
	affiche_header(*g, cyclique, vieillissement);
	affiche_grille(*g, vieillissement);

	char c = getchar();

	do
	{
		switch (c) {
			case 'v' :
			{ //Touche v pour activer/désactiver l'affichage du vieillissement.
				vieillissement = boolSwitch(vieillissement);
				break;
			}
			case 'c' :
			{//Active/Désactive le calcul cyclique des voisins.
				cyclique = boolSwitch(cyclique);
				break;
			}
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc,cyclique,vieillissement);
				clear();
				affiche_header(*g, cyclique, vieillissement);
				affiche_grille(*g, vieillissement);
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
