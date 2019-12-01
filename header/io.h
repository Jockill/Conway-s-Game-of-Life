/**
  \file io.h
  \brief Header contenant les fonctions relatives aux input/output du programme.
  \author JOCHYMSKI Hugo, powered by Unistra.
*/

#ifndef __IO_H
#define __IO_H

#include <stdio.h>
#include <cairo.h>
#include <cairo-xlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "jeu.h"
#include "grille.h"


/**
  \brief Affiche "oui" ou "non" en fonction d'un booléen passé en parametre. Respectivement si il vaut 1 ou 0.
  \param int b ; int agissant comme un booléen. (valeurs possible : 0/1).
*/
void afficheBool(int b);

// affichage d'un trait horizontal
/**
  \brief Affichage d'un trait horizontal.
  \param int c : Nombre de traits à afficher.
*/
void affiche_trait (int c);

// affichage d'une ligne de la grille
/**
  \brief Affichage d'une ligne de la grille.
  \param int c : Nombre de cases à afficher. N.B: L'affichage commence à la première case.
  \param int* ligne : Pointeur vers la ligne à afficher.
*/
void affiche_ligne (int c, int* ligne, grille g);

// affichage d'une grille
/**
  \brief Affichage d'une grille.
  \param grille g : Grille à afficher.
*/
void affiche_grille (grille g);

/**
  \brief Affiche le panneau d'informations : generation, cyclique, vieillissement
  \param grille g : grille en jeu
*/
void affiche_header(grille g);

// effacement d'une grille
/**
  \brief Efface une grille affichée à l'écran.
  \param grille g : Grille affichée à l'écran avant l'appel.
  \deprecated Dépendant de la taille du terminal pour fonctionner correctement.
  \sa clear
*/
void efface_grille (grille g);

/**
  \brief Nouvelle forme de efface_grille réglant les soucis d'affichage causés par celle-ci.
  \sa efface_grille
*/
void clear();

// debute le jeu
/**
  \brief Débute le jeu.
  \param grille* g : Pointeur vers la grille permettant de débuter le jeu.
  \param grille* gc : Pointeur vers la grille qui sera utilisée pour copier la grille de jeu.
*/
void debut_jeu(grille *g, grille *gc);

#endif
