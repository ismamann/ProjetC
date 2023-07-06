#include "copie.h"
#include "supprime.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "parcours.h"
#include "verif.h"
#include "build.h"

noeud *copyNoeud(noeud *n) {
    liste_noeud *ln = n -> fils;
    liste_noeud *cpln = malloc(sizeof(liste_noeud));
    assert(cpln != NULL);
    cpln -> no = NULL;
    cpln -> succ = NULL;
    noeud *cpn = malloc(sizeof(noeud));
    assert(cpn != NULL);
    memmove(cpn, n, sizeof(noeud));
    if (ln != NULL) {
        cpn -> fils = cpln;
    } else {
        free(cpln);
    }
    while(ln != NULL) {
        cpln -> no = copyNoeud(ln -> no);
        cpln -> no -> pere = cpn;
        if (ln -> succ != NULL) {
            cpln -> succ = malloc(sizeof(liste_noeud));
            assert(cpln -> succ != NULL);
            cpln = cpln -> succ;
            cpln -> no = NULL;
            cpln -> succ = NULL;
        }
        ln = ln -> succ;
    }
    return cpn;
}

void cp(noeud *n, char *chem1, char *chem2){
    noeud *depart = n;
    cd(&depart, chem1, true);
    char *c;
    noeud *fin = verifChem2(n, depart, chem2, &c);
    liste_chemin *lc = buildChemin(chem2);
    verifNom(fin,c);
    noeud *ncp = copyNoeud(depart);
    strncpy(ncp -> nom, c, strlen(c));
    *(ncp -> nom + strlen(c)) = '\0';
    liste_noeud *ln = malloc(sizeof(liste_noeud));
    ln -> no = ncp;
    ln -> succ = fin -> fils;
    fin -> fils = ln; 
    ncp -> pere = fin;
    free(c);
    destroyListeChemin(lc);
}


void mv(noeud *n,char *chem1, char *chem2){
    noeud *depart = n;
    cd(&depart, chem1, true);
    char *c;
    noeud *fin = verifChem2(n, depart, chem2, &c);
    if (depart != fin) {
        assert(!verifCheminActuel(n,chem1) && "Le programme est placé dans le chemin à supprimer");
    }
    strncpy(depart -> nom, c, strlen(c));
    *(depart -> nom + strlen(c)) = '\0';
    free(c);
    if (depart == fin) return;
    supprimeFilsMv(depart);
    liste_noeud *new = malloc(sizeof(liste_noeud));
    new -> succ = fin -> fils;
    new -> no = depart;
    fin -> fils = new;   
    depart -> pere = fin;

}
