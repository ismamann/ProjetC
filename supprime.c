#include "verif.h"
#include "structure.h"
#include "stdlib.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "parcours.h"


void destroyListeChemin(liste_chemin *lc) {
    if (lc != NULL) {
        destroyListeChemin(lc -> suiv);
        free(lc -> chemin);
        free(lc);
    }
} 


void destroyFils(liste_noeud *ln){
    if(ln != NULL){
        destroyFils(ln -> succ);
    }
    free(ln);
}


void destroySousArbre(noeud *n) {
    if (n != NULL) {
        liste_noeud *ln = n -> fils;
        while(ln != NULL) {
            destroySousArbre(ln -> no);
            ln = ln -> succ;
        }      
        destroyFils(n -> fils);
        free(n);
    }
}


void supprimeFilsMv(noeud *depart){
 if(depart -> pere -> fils -> no == depart){
        liste_noeud *temp = depart -> pere -> fils;
        depart -> pere -> fils = depart -> pere -> fils -> succ;
        free(temp);
    } else {
        liste_noeud *pereln = depart -> pere -> fils;
        while (pereln -> succ != NULL){
            if(pereln -> succ -> no == depart){
                liste_noeud *temp = pereln -> succ;
                pereln -> succ = pereln -> succ -> succ;
                free(temp);
                break;
            }
            pereln = pereln -> succ;
        }
    }
}


void rm (noeud *n, char *chem){
    assert(!verifCheminActuel(n,chem) && "Le programme est placé dans le chemin à supprimer");
    noeud *n1 = n;
    cd(&n1,chem,true);
    liste_noeud *lf = n1 -> pere -> fils;
    if (lf -> no == n1) {
        liste_noeud *temp = lf;
        n1 -> pere -> fils = lf -> succ;
        free(temp);
    } else {
        while(lf -> succ != NULL){
            if(lf -> succ -> no == n1){
                liste_noeud *temp = lf -> succ;
                lf -> succ = lf -> succ -> succ;
                free(temp);
                break;
            }
            lf = lf -> succ;
        }
    }
    destroySousArbre(n1);
}