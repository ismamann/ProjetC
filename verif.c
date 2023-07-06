#include "verif.h"
#include "structure.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "build.h"
#include "supprime.h"
#include "parcours.h"

void verifNom(noeud *n, char* c) {
    assert(strlen(c)!=100 && "Nom dépassant les 100 caractères");
    assert(strlen(c)>0 && "Il faut entrer un nom");
    for(size_t i = 0; i < strlen(c); i++){
        assert(((*(c+i)>='0' && *(c+i)<='9') || 
        (*(c+i)>='a' && *(c+i)<='z')||
        (*(c+i)>='A' && *(c+i)<='Z')  )&& ("Seulement des caractères alphanumériques"));

    }
    if(n != NULL){
        liste_noeud *n1 = n -> fils;
        while(n1 != NULL) {
            assert(strcmp(n1 -> no -> nom, c) != 0 && "Nom déjà existant");
            n1 = n1 -> succ;
        }
   }
}

noeud *verifFils(char *c, liste_noeud *l, bool peutEtreFichier) { // cherche dans les fils le noeud avec comme nom c.
    noeud *n2 = NULL;
    while(l != NULL) {
        if (strcmp(l -> no -> nom, c) == 0) {
            n2 = l -> no;
            break;
        } else {
            l = l -> succ;

        }
    }
    assert(n2 != NULL && "Le chemin n'existe pas.");
   if (peutEtreFichier) assert(n2 -> est_dossier && "Le chemin doit être formé qu'avec des dossiers.");
    return n2;
}

bool verifCheminActuel(noeud *n, char *chem1) {
    noeud *n1 = n;
    cd(&n1,chem1,true);
    return chercheNoeudSousArbre(n1, n);
}

noeud *verifChem2(noeud *n, noeud *depart, char *chem, char **dernierNomChem2) {
    liste_chemin *lc = buildChemin(chem);
    liste_chemin *lc1 = lc;
    if(*chem == '/'){
        n = n -> racine;
    }
    while(lc1 -> suiv != NULL){
        if (strcmp(lc1 -> chemin,"..") == 0) {
            n = n -> pere;   
        } else {
            n = verifFils(lc1 ->  chemin, n -> fils, false); 
        }
        assert(n -> est_dossier && "Il faut que des dossiers dans le chemin.");
        lc1 = lc1 -> suiv;
    }
    *dernierNomChem2 = malloc((strlen(lc1 -> chemin)+1) * sizeof(char));
    assert(*dernierNomChem2 != NULL);
    memmove(*dernierNomChem2, lc1 -> chemin, strlen(lc1 -> chemin)+1);
    chercheFils(n, lc1 -> chemin);
    destroyListeChemin(lc); 
    assert(chercheNoeudSousArbre(depart, n) == false && "Il n'est pas possible de déplacer un dossier dans ses fils.");
    return n;
}