/**
  \file jeu.h
  \brief Header contenant les fonctions relatives au déroulement du jeu.
  \author JOCHYMSKI Hugo, powered by Unistra.
*/

#ifndef __JEU_H
#define __JEU_H

#include "grille.h"

/**
  \brief Permet de forcer une pause au programme, attendant un input utilisateur pour continuer.
*/
void bellePause();

/**
  \brief Fonction appelée lors d'un changement de grille
  \param grille* g : Grille en jeu avant l'appel
  \param grille* gc : Copie de la grille en jeu avant l'appel
*/
void changementGrille(grille *g, grille *gc);

/**
  \brief Inverse la valeur d'un booléen passé en parametre
  \pre b doit valoir 1 ou 0.
  \param int b : Booléen à inverser.
*/
int boolSwitch(int b);

// modulo modifié pour traiter correctement les bords i=0 et j=0
// dans le calcul des voisins avec bords cycliques
/**
  \brief Modulo modifié pour traiter correctement les bords i=0 et j=0 dans le calcul des voisins avec bords cycliques.
  \param int i : Membre de gauche de l'opération.
  \param int m : Membre de droite de l'opération.
*/
static inline int modulo(int i, int m) {return (i+m)%m;}

// compte le nombre de voisins vivants de la cellule (i,j)
// les bords sont cycliques.
/**
  \brief Compte le nombre de voisins vivants de la cellule (i,j).
  \param int i : Index de la colonne sur laquelle se trouve la cellule.
  \param int j : Index de la ligne sur laquelle se trouve la cellule.
  \param grille g : Grille dans laquelle se trouve la cellule.
*/
int compte_voisins_vivants (int i, int j, grille g);

// fait évoluer la grille g d'un pas de temps
/**
  \brief Fait évoluer la grille g d'une génération.
  \param grille* g : Grille à faire évoluer.
  \param grille* gc: Grille servant de copie a 'g'.
*/
void evolue (grille *g, grille *gc);

void oscillation(grille g, grille gc);

#endif
