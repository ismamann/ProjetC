#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "stdbool.h"

struct noeud;
struct liste_noeud;
struct liste_chemin;

struct noeud {
    bool est_dossier ;
    char nom [100];
    struct noeud * pere ;
    struct noeud * racine ;
    struct liste_noeud * fils ;
};

struct liste_noeud {
    struct noeud * no ;
    struct liste_noeud * succ ;
};

struct liste_chemin {
    char *chemin;
    struct liste_chemin *suiv;
};

typedef struct noeud noeud ;
typedef struct liste_noeud liste_noeud ;
typedef struct liste_chemin liste_chemin;


#endif
