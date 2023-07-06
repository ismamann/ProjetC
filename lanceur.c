#include "structure.h"
#include "copie.h"
#include "build.h"
#include "parcours.h"
#include "supprime.h"
#include "verif.h"
#include "affiche.h"
#include <stdio.h>
#include "parseur.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Ce programme attend un fichier en paramètre mais lui vous en avez donné %d\n.", argc - 1);
    } else {
        FILE* f = fopen(argv[1], "r"); 
        if (f == NULL) perror("Fichier Inexistant");
        lecture(f);
        int k = fclose(f);
        if (k != 0) perror("Problème à la fermeture du fichier.");
    }
}