/**
	\file grille.c
	\brief Source contenant le corps des fonctions de grille.h
	\author JOCHYMSKI Hugo, powered by Unistra.
*/

#include "../header/grille.h"

void alloue_grille(int l, int c, grille* g){
	g->nbl = l;
	g->nbc = c;
	g->generation = 0;

	g->cellules = malloc(sizeof(int*)*l);
	for(int i=0; i<l; i++) g->cellules[i] = calloc(c+1, sizeof(int)*c);
}

void libere_grille(grille* g){
	for(int x=0; x<g->nbl; x++){
		free(g->cellules[x]);
	}
	free(g->cellules);
}

void init_grille_from_file (char * filename, grille* g){
	FILE * pfile = NULL;
	pfile = fopen(filename, "r");
	assert (pfile != NULL); //Stop le programme si pfile == NULL

	int i,j,n,l,c,vivantes,nonViable=0;

	fscanf(pfile, "%d", & l);
	fscanf(pfile, "%d", & c);

	alloue_grille(l,c,g);

	fscanf(pfile, "%d", & vivantes);
	for (n=0; n< vivantes; ++n){
		fscanf(pfile, "%d", & i);
		fscanf(pfile, "%d", & j);
		set_vivante(i,j,*g);
	}

	fscanf(pfile, "%d", &nonViable);
	for(n=0; n<nonViable; n++){
		fscanf(pfile, "%d", &i);
		fscanf(pfile, "%d", &j);
		set_non_viable(i,j,*g);
	}

	fclose (pfile);
	return;
}


void copie_grille (grille gs, grille gd){
	int i, j;
	for (i=0; i<gs.nbl; ++i) for (j=0; j<gs.nbc; ++j) gd.cellules[i][j] = gs.cellules[i][j];
	return;
}
