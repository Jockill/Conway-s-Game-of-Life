The AMC: Game of Life
====
- - -
=MANUEL D'UTILISATION=
---
###Liste des commandes en jeu
 * _Entrée_ : Permet d'avancer d'une génération.
 * _n_ : Permet de charger une nouvelle grille.
 * _v_ : Permet d'activer/désactiver le vieillissement des cellules.  _Quand ce mode est activé, les cellules mourront une fois la 8e génération passée._
 * _c_ : Permet d'activer/désactiver le comportement cyclique de la grille. _La grille se comportera alors comme une sphère. La cellule d'ordonnée maximum sera considérée comme voisine avec celle d'ordonnée minimum. De même pour l'axe des abscisses._
 * _q_ : Quitte le jeu.


###Ajout de grilles personalisées
Voici un exemple de grille :
```
1.  4 6
2.
3.  3
4.  1 2
5.  1 3
6.  1 4
7.  
8.  0
```
_Ligne 1_ : Indiquez le nombre de lignes et de colonnes souhaitées.(ici 4 lignes et 6 colonnes)

_Ligne 2_ : Suivez d'un saut de ligne.

_Ligne 3_ : Indiquez le nombre total de cellules en vie au début du jeu.

_Lignes 4 à 6_ : Indiquez l'index de la cellule que vous souhaitez rendre vivante. __ATTENTION :__ _Le compte commence à 0 !_

_Ligne 7_ : Laissez une ligne vide.

_Ligne 8_ : Terminez le document par une ligne contenant uniquement un 0.


Enregistrez le document en __*.txt__, dans le dossier __grilles__.
Le nom doit être formaté comme suit :
~~~
grille_<nom>.txt
~~~

Où <nom> peut être n'importe quelle chaine de caractère que vous souhaitez
- - -


=UTILISATION DU MAKEFILE=
---
### Création de l'éxécutable

~~~{.sh}
make
~~~

### Création de la documentation

~~~{.sh}
make doc
~~~

### Création de l'archive

~~~{.sh}
make dist
~~~
> Crée le fichier zegameoflife.tar.xz dans le dossier où se trouve le makefile.

### Nettoyage du dossier.

~~~{.sh}
make clean
~~~
> Supprime le dossier obj, l'éxécutable ainsi que la documentation


- - -


=TODO=
---
 * Makefile: utiliser vpath a la place des user var.
      - ```
      vpath %.c ../src
      grille.o: grille.c
        gcc $<
      ```
 * Enlever l'amélioration de l'user expérience sur le nom de grilles.
 * Ajouter un test apres malloc/calloc (vérifier si la mémoire a bien été allouée)
 * Ajouter un auto-play.
 * Faire un menu principal.


NOTES
---
 * Le fait que l'age des cellules ne soit pas remis a 0 lors de l'activation/désactivation de la vieilliesse est volontaire.

SYSTEME DE VERSIONNEMENT
---
Les tags de versions se présentent de cette manière :
```
X.Y[.NDY]
```


X   : Correspond au niveau le plus haut accompli grâce à ce code.

Y   : Correspond au numéro de l'update .

NDY : Facultatif, est utilisé si la version en cours ne possède pas de documentation complète.
