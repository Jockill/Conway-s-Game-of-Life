/**
  \file io.h
  \brief Header contenant les fonctions relatives aux input/output du programme.
  \author JOCHYMSKI Hugo, powered by Unistra.
*/

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include "grille.h"
#include "jeu.h"

/**
  \fn bellePause
  \brief Permet de forcer une pause au programme, attendant un input utilisateur pour continuer.
*/
void bellePause();

// affichage d'un trait horizontal
/**
  \fn affiche_trait
  \brief Affichage d'un trait horizontal.
  \param int c : Nombre de traits à afficher.
*/
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
  \fn affiche_ligne
  \brief Affichage d'une ligne de la grille.
  \param int c : Nombre de cases à afficher. N.B: L'affichage commence à la première case.
  \param int* ligne : Pointeur vers la ligne à afficher.
*/
void affiche_ligne (int c, int* ligne);

// affichage d'une grille
/**
  \fn affiche_grille
  \brief Affichage d'une grille.
  \param grille g : Grille à afficher.
*/
void affiche_grille (grille g);

// effacement d'une grille
/**
  \fn efface_grille
  \brief Efface une grille affichée à l'écran.
  \param grille g : Grille affichée à l'écran avant l'appel.
*/
void efface_grille (grille g);

// debute le jeu
/**
  \fn debut_jeu
  \brief Débute le jeu.
  \param grille* g : Pointeur vers la grille permettant de débuter le jeu.
  \param grille* gc : Pointeur vers la grille qui sera utilisée pour copier la grille de jeu.
*/
void debut_jeu(grille *g, grille *gc);

#endif
