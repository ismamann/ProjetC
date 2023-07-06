#ifndef PARSEUR_H
#define PARSEUR_H

#include "structure.h"
#include "build.h"
#include "structure.h"
#include "copie.h"
#include "build.h"
#include "parcours.h"
#include "supprime.h"
#include "verif.h"
#include "affiche.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

extern bool avanceEspace(FILE *);
extern bool avanceSautDeLigne(FILE *);
extern void remplirChar(FILE *, size_t , char *);
extern void commande0(char *, noeud **);
extern void commande1(char *, char *, noeud **);
extern void commande2(char *, char *, char *, noeud **);
extern int nbArgsLigne(FILE *);
extern size_t taille (FILE *);
extern void lecture (FILE *);

#endif