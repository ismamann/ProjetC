#include "parcours.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "build.h"
#include "supprime.h"
#include "verif.h"

void cd(noeud **n , char *c, bool peutEtreFic) {
    noeud *n1 = *n;
    if(strlen(c) == 0){
        *n = n1 -> racine;
        return;
    }
    if(*c == '/'){
        *n = n1 -> racine;
        n1 = *n;
        if (strlen(c) == 1) return;
    }
    liste_chemin *lc = buildChemin(c);
    liste_chemin *lc1 = lc;
    while(lc1 != NULL){
        if (strcmp(lc1 -> chemin,"..") == 0){
            *n = n1 -> pere;
        } else {
            *n = verifFils(lc1 ->  chemin, n1 -> fils, false);   
        }
        n1 = *n;
       if (!peutEtreFic) assert(n1 -> est_dossier && "Il faut que des dossiers dans le chemin.");
        lc1 = lc1 -> suiv;
    }
    destroyListeChemin(lc);
}


bool chercheNoeudSousArbre(noeud *n, noeud *suivant) {
    if (suivant == suivant -> racine) return false;

    if (n == suivant) {
        printf("%p   %p", n, suivant);
        return true;
    }
    return chercheNoeudSousArbre(n, suivant ->pere);
}


void chercheFils(noeud *n, char *c) {
    liste_noeud *ln = n -> fils;
    while (ln != NULL) {
        assert(strcmp(ln -> no -> nom, c) != 0 && "Ce nom est existe déjà.");
        ln = ln -> succ; 
    }
}