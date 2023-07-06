#ifndef SUPPRIME_H
#define SUPPRIME_H

#include "structure.h"

extern void destroyListeChemin(liste_chemin *);
extern void destroyFils(liste_noeud *);
extern void destroySousArbre(noeud *);
extern void supprimeFilsMv(noeud *);
extern void rm (noeud *, char *);

#endif