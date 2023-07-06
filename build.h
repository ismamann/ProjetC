#ifndef BUILD_H
#define BUILD_H
#include "structure.h"
#include <stdlib.h>
#include <stdbool.h>

extern liste_chemin *buildChemin(char *);
extern noeud *buildRacine();
extern noeud *build(bool, char *, noeud *, noeud*);
extern void mkdir(noeud *, char *);
extern void touch(noeud *, char *);

#endif
