#ifndef VERIF_H
#define VERIF_H
#include "structure.h"

extern void verifNom(noeud *, char*);
extern noeud *verifFils(char *, liste_noeud *, bool);
extern bool verifCheminActuel(noeud *, char *);
extern noeud *verifChem2(noeud *, noeud *, char *, char **);

#endif