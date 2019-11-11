/**
	\file main.c
	\brief Source contenant le main.
	\author JOCHYMSKI Hugo, powered by Unistra.
*/

#include <stdio.h>

#include "../header/grille.h"
#include "../header/io.h"
#include "../header/jeu.h"

int main (int argc, char ** argv) {

	if (argc != 2 )
	{
		printf("usage : main <fichier grille>\n");
		return 1;
	}

	grille g, gc;
	init_grille_from_file(argv[1],&g);
	alloue_grille (g.nbl, g.nbc, &gc);

	debut_jeu(&g, &gc);

	libere_grille(&g);
	libere_grille(&gc);
	return 0;
}
