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
  \brief Affiche "oui" ou "non" en fonction d'un booléen passé en parametre sur stderr. Respectivement si il vaut 1 ou 0.
  \param int b ; int agissant comme un booléen. (valeurs possible : 0/1).
*/
void afficheBool(int b);

/**
  \brief Affiche graphiquement la grille en cours de jeu en utilisant la bibliotheque cairo.
  \param cairo_surface_t *surface : surface de travail pour cairo.
  \param grille *g : grille à afficher.
  \param int sizeX : longueur de la fenetre en pixels.
  \param int sizeY : hauteur de la fenetre en pixels.
  \param int cellSize : taille du coté du carré d'une cellule
  \param int lineWidth : épaisseur de la ligne séparant les cellules.
*/
void cairoAfficheGrille(cairo_surface_t *surface, grille *g, int sizeX, int sizeY, int cellSize, int lineWidth);

// debute le jeu
/**
  \brief Débute le jeu.
  \param grille* g : Pointeur vers la grille permettant de débuter le jeu.
  \param grille* gc : Pointeur vers la grille qui sera utilisée pour copier la grille de jeu.
*/
void debut_jeu(grille *g, grille *gc);

#endif
