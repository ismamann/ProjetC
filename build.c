#include "verif.h"
#include "structure.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>



liste_chemin *buildChemin(char *c) {
    if (strlen(c) != 0 ) {
        assert(*(c+strlen(c)-1) != '/' && "Le chemin ne doit pas se terminer par '/' ");
    }
    size_t i = 0;
    liste_chemin *debut = malloc(sizeof(liste_chemin));
    assert(debut != NULL);
    debut -> suiv = NULL;
    liste_chemin *lc = debut;
    if (strlen(c) != 0 && *c == '/') i = 1;
    while(true) {
        size_t l = 0;
        for (size_t k = i; k < strlen(c); ++k, ++l) {
            if (*(c+k) == '/') break;
        }
        lc -> chemin = malloc((l+1) * sizeof(char));
        assert(lc -> chemin != NULL);
        l = 0;
        for (size_t k = i; k < strlen(c); ++k, ++l) {
            if (*(c+k) == '/') {
                i = k+1;
                *(lc -> chemin+l) = '\0';
                break;
            }
            *(lc -> chemin+l) = *(c+k);
            if (k == strlen(c)-1) {
                 *(lc -> chemin+l+1) = '\0';
                return debut;
            }
        }
        lc -> suiv = calloc(1, sizeof(liste_chemin));
        assert(lc -> suiv != NULL);
        lc = lc ->suiv;
        lc -> suiv = NULL;
    }
}

noeud *buildRacine(){
    noeud *n = malloc(sizeof(noeud));
    n -> est_dossier = true;
    *(n -> nom) = '\0';
    n -> pere = n;
    n -> racine = n;
    n -> fils = NULL;
    return n;
}

noeud *build(bool estDossier, char* nom , noeud *p, noeud*r) {
    verifNom(NULL, nom);
    noeud *n = malloc(sizeof(noeud));
    assert(n != NULL);
    if(n != NULL){
        n -> est_dossier = estDossier;
        strncpy(n -> nom, nom, strlen(nom));
        *(n -> nom+strlen(nom)) = '\0';
        n -> pere = p;
        n -> racine = r;
        n -> fils = NULL;
        return n;
    }
    return NULL;
}


void mkdir(noeud *n, char *nom) {
    verifNom(n,nom);
    liste_noeud *n2 = malloc(sizeof(liste_noeud));
    assert(n2 != NULL); 
    n2 -> no = build(true, nom, n, n -> racine);
    n2 -> succ = n -> fils;
    n -> fils = n2;
}



void touch(noeud *n, char *nom){
    verifNom(n,nom);
    liste_noeud *n1 = malloc(sizeof(liste_noeud));
    assert(n1 != NULL);
    n1 -> no = build(false,nom , n , n -> racine);
    n1 -> succ = n -> fils;
    n -> fils = n1;
}

