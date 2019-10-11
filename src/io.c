#include "../header/io.h"
#include <string.h>
#include <unistd.h>

void bellePause(){
	printf("\nAppuyez sur entrée pour continuer...\n");
	getchar();
	getchar();
}

void affiche_trait (int c){
	int i;
	for (i=0; i<c; ++i) printf ("|---");
	printf("|\n");
	return;
}

void affiche_ligne (int c, int* ligne){
	int i;
	for (i=0; i<c; ++i)
		if (ligne[i] == 0 ) printf ("|   "); else printf ("| O ");
	printf("|\n");
	return;
}

void affiche_grille (grille g){
	int i, l=g.nbl, c=g.nbc;
	printf("\n");
	affiche_trait(c);
	for (i=0; i<l; ++i) {
		affiche_ligne(c, g.cellules[i]);
		affiche_trait(c);
	}
	printf("\n");
	return;
}

void efface_grille (grille g){
	printf("\n\e[%dA",g.nbl*2 + 5);
}

void debut_jeu(grille *g, grille *gc){
	char c = getchar();
	int pass = 0;
	char nom[25] = "grilles/grille";
	char num[3] = "";

	while (c != 'q') // touche 'q' pour quitter
	{
		switch (c) {
			case '\n' :
			{ // touche "entree" pour évoluer
				evolue(g,gc);
				efface_grille(*g);
				affiche_grille(*g);
				break;
			}
			case 'n' :
			pass = 0;
				do{
					printf("\e[1;1H\e[2J"); //Clear
					printf("Veuillez entrer le numero de la grille a charger, ou q pour quitter : ");
					scanf("%s", num);

					if(num[0] == 'q') return;

					strcat(nom, num);
					strcat(nom, ".txt");

					if(access(nom, F_OK) != -1){ //Check si le nom entré existe
						libere_grille(g);
						libere_grille(gc);
						init_grille_from_file(nom, g);
						alloue_grille(g->nbl, g->nbc, gc);
						pass = 1;
					}
					else{
						strcpy(nom, "grilles/grille");
						strcpy(num, "");
						printf("La grille que vous cherchez n'existe pas.\nVeuillez vous assurer : \n1. Que vous l'avez bien enregistrée dans le format 'grille<numero>.txt'\n2. Que vous l'avez enregistrée dans <dossier_racine_du_jeu>/grilles\n");
						bellePause();
						printf("\e[1;1H\e[2J"); //Clear
					}
				}while(pass == 0);
			break;
			default :
			{ // touche non traitée
				printf("\n\e[1A");
				break;
			}
		}
		c = getchar();
	}
	return;
}
