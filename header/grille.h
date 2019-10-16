/**
  \file grille.h
  \brief Header contenant les fonctions relatives à la modification des grilles.
  \author JOCHYMSKI Hugo, powered by Unistra.
*/

#ifndef __GRILLE_H
#define __GRILLE_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/**
  \struct Grille
  \brief Structure permettant de créer et d'utiliser des grilles.
*/

// structure grille : nombre de lignes, nombre de colonnes, tableau de tableau de cellules
typedef struct {
  int nbl; /**< Nombre de lignes. */
  int nbc; /**< Nombre de colonnes. */
  int** cellules; /**< Tableau a 2 dimensions représentant la grille. */
  int generation; /**< Numero de la génération de la grille. */
} grille;

// alloue une grille de taille l*c, et initialise toutes les cellules à mortes
/**
  \fn alloue_grille
  \brief Alloue une grille de taille l*c, et initialise toutes les cellules à mortes.
  \param int l : Nombre de lignes de la grille.
  \param int c : Nombre de colonnes de la grille.
  \param grille* g : Pointeur vers la grille à allouer.
*/
void alloue_grille (int l, int c, grille* g);

// libère une grille
/**
  \fn librer_grille
  \brief Libère une grille.
  \param grille* g : Pointeur vers la grille à libérer.
*/
void libere_grille (grille* g);

// alloue et initalise la grille g à partir d'un fichier
/**
  \fn init_grille_from_file
  \brief Alloue et initalise une grille à partir d'un fichier.
  \param char* filename : Fichier à utiliser pour l'initalisation.
  \param grille* g : Pointeur vers la grille à initialiser.
*/
void init_grille_from_file (char * filename, grille* g);

// rend vivante la cellule (i,j) de la grille g
/**
  \fn set_vivante
  \brief Rend vivante la cellule (i,j) de la grille g.
  \param int i : Index de la colonne sur laquelle se trouve la cellule.
  \param int j : Index de la ligne sur laquelle se trouve la cellule.
  \param grille g : Grille sur laquelle agit la fonction.
*/
static inline void set_vivante(int i, int j, grille g){g.cellules[i][j] = 1;}
// rend morte la cellule (i,j) de la grille g
/**
  \fn set_morte
  \brief Rend morte la cellule (i,j) de la grille g.
  \param int i : Index de la colonne sur laquelle se trouve la cellule.
  \param int j : Index de la ligne sur laquelle se trouve la cellule.
  \param grille g : Grille sur laquelle agit la fonction.
*/
static inline void set_morte(int i, int j, grille g){g.cellules[i][j] = 0;}
// teste si la cellule (i,j) de la grille g est vivante
/**
  \fn est_vivante
  \brief Teste si la cellule (i,j) de la grille g est vivante. Renvoie 1 si c'est le cas, 0 sinon.
  \brief modifie en 2.x pour permettre l'implementation du vieillissement
  \param int i : Index de la colonne sur laquelle se trouve la cellule.
  \param int j : Index de la ligne sur laquelle se trouve la cellule.
  \param grille g : Grille sur laquelle agit la fonction.
*/
static inline int est_vivante(int i, int j, grille g){
  if (g.cellules[i][j] > 0) return 1;
  else return 0;
}

// recopie gs dans gd (sans allocation)
/**
  \fn copie_grille
  \brief Recopie gs dans gd sans allocation.
  \param grille gs : Grille source.
  \param grille gd : Grille destination.
*/
void copie_grille (grille gs, grille gd);

#endif
