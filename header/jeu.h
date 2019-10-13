/**
  \file jeu.h
  \brief Header contenant les fonctions relatives au déroulement du jeu.
  \author JOCHYMSKI Hugo, powered by Unistra.
*/

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
  \fn modulo
  \brief Modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques.
  \param int i : Membre de gauche de l'opération.
  \param int m : Membre de droite de l'opération.
*/
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
  \fn compte_voisins_vivants
  \brief Compte le nombre de voisins vivants de la cellule (i,j).
  \param int i : Index de la colonne sur laquelle se trouve la cellule.
  \param int j : Index de la ligne sur laquelle se trouve la cellule.
  \param grille g : Grille dans laquelle se trouve la cellule.
*/
int compte_voisins_vivants (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
/**
  \fn evolue
  \brief Fait évoluer la grille g d'une génération.
  \param grille* g : Grille à faire évoluer.
  \param grille* gc: Grille servant de copie a 'g'.
*/
void evolue (grille *g, grille *gc);

#endif
