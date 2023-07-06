#include "affiche.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void ls(noeud *n) {
    liste_noeud *n1 = n -> fils;
   while(n1 != NULL) {
    printf("%s\n", n1 -> no -> nom);
    n1 = n1 -> succ;
   }
}

void pwd(noeud *n) {
    if (n -> pere != n -> racine)  pwd(n -> pere);
    printf("/%s", n -> nom);
}

int nbFils(noeud *n){
    liste_noeud *n1 = n -> fils;
    int cpt = 0;
    while(n1!=NULL){
        ++cpt;
        n1 = n1 -> succ;
    }
    return cpt;
}

void print(noeud *n, int espace){
    for(int i = 0; i < espace ; ++i){
        printf("    ");
    }
    if(strlen(n-> nom) == 0){
        printf("Noeud / (D)");
    } else if(n -> est_dossier){
        printf("Noeud %s (D)",n->nom);
    } else {
        printf("Noeud %s (F)",n->nom);
    }
    if(strlen(n->nom)>0){
        if(strlen(n->pere->nom) == 0){
          printf(", pere : /");
        } else {
          printf(", pere : %s",n->pere->nom);
        }      
    }
        printf(",%d fils",nbFils(n));
    //printf("  addresse : %p", n);
    puts("");
    liste_noeud *n2 = n -> fils;
    while (n2 != NULL && n2 -> no != NULL)  {
        print(n2 -> no,espace + 1);
        n2 = n2 -> succ;
    }
    
}