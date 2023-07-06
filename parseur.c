#include "parseur.h"


bool avanceEspace(FILE *f) {
    int k;
    while((k = fgetc(f)) != EOF && k == ' ') {
        if ((k = fgetc(f)) != EOF && k != ' ') break;
    }
    if (k == EOF) return false;
    fseek(f, -1, SEEK_CUR);
    return true;
}

bool avanceSautDeLigne(FILE *f) {
    int k;
    bool b = false;
    while((k = fgetc(f)) != EOF && k == '\n') {
        b = avanceEspace(f);
    }
    if (!b) return false;
    fseek(f, -1, SEEK_CUR);
    return true;
} 

void remplirChar(FILE *f, size_t l, char *c) {
    fseek(f, -1, SEEK_CUR);
    for (size_t i = 0; i < l; ++i) {
        *(c+i) = fgetc(f);
    }
    *(c+l) = '\0';
    avanceEspace(f);
}

void commande0(char *c, noeud **n){
    if(strcmp(c,"cd") == 0){
        cd(n, "", false);
        return;
    } 
    if(strcmp(c,"ls") == 0) {
        ls(*n); 
        puts("");
        return ;
    }
    if(strcmp(c,"pwd") == 0){
        pwd(*n);
        puts("");
        return;
    }
    if(strcmp(c,"print") == 0)  {
        print((*(n)) -> racine, 0);
        puts("");
    } else {
        printf("Commande %s incorrecte\n", c);
    }
}

void commande1(char *c, char *arg1, noeud **n){
    if(strcmp(c,"cd") == 0){
        cd(n,arg1, false);
        return;
    } 
    if(strcmp(c,"mkdir") == 0){
      mkdir(*n,arg1);
      return;
    }
    if(strcmp(c,"touch") == 0){
        touch(*n,arg1);
        return;
    }
    if(strcmp(c,"rm") == 0){
        rm(*n,arg1);
    } else {
        printf("Commande %s incorrecte\n", c);
    }
}

void commande2(char *c, char *arg1, char *arg2, noeud **n){
    if(strcmp(c,"cp") == 0){
        cp(*n,arg1,arg2);
        return;
    }
    if(strcmp(c,"mv") == 0){
        mv(*n,arg1,arg2);
    } else {
        printf("Commande %s incorrecte\n", c);
    }
}


int nbArgsLigne(FILE *f) {
    int occ = 0;
    size_t nbIter = 0;
    int c;
    fseek(f, -1, SEEK_CUR);
    while((c = fgetc(f)) != EOF && c != '\n') {
        if (c == ' ' ){
            if ((c = fgetc(f)) != EOF) {
                if (c != ' ' && c != '\n') {
                    ++occ;
                }
                fseek(f, -1, SEEK_CUR);
            }
        }
        ++nbIter;
    } 
    fseek(f, -nbIter, SEEK_CUR);
    
    return occ;
}


size_t taille (FILE *f){
    int c;
    size_t taille = 0;
    fseek(f, -1, SEEK_CUR);
    c = fgetc(f);
    fseek(f, -1, SEEK_CUR);
    if (c == ' ') avanceEspace(f);
    else if (c == '\n') avanceSautDeLigne(f);
    while ((c = fgetc(f)) != EOF && c != ' ') {
        if (c == '\n') break;
        ++taille;
    }
    fseek(f, -taille, SEEK_CUR);
    return taille;
}

void lecture (FILE *f){
    int c;
    char *commande;
    char *arg1;
    char *arg2;
    int nbArgs = 0;
    size_t t = 0;
    noeud *n = buildRacine();
    noeud *pgrm = n;
    c = fgetc(f);
    if (c != EOF && c == '\n') {
        avanceSautDeLigne(f);
    } else if (c != EOF && c == ' ') {
        avanceEspace(f);
        avanceSautDeLigne(f);
    }
    else fseek(f, -1, SEEK_CUR);
    while((c = fgetc(f))!=EOF){
        if (c != '\n') nbArgs = nbArgsLigne(f);
            switch(nbArgs) {
                case 0 : 
                    t = taille(f);
                    commande = malloc((t+1) * sizeof(char));
                    assert(commande != NULL);
                    remplirChar(f,t,commande);
                    commande0(commande, &pgrm);
                    free(commande);
                    puts("");
                    break;
                case 1 : 
                    t = taille(f);
                    commande = malloc((t+1) * sizeof(char));
                    assert(commande != NULL);
                    remplirChar(f,t,commande);
                    t = taille(f);
                    arg1 = malloc((t+1) * sizeof(char));
                    assert(arg1 != NULL);
                    remplirChar(f,t,arg1);
                    commande1(commande, arg1, &pgrm);
                    free(commande);
                    free(arg1);
                    break;
                case 2 : 
                    t = taille(f);
                    commande = malloc((t+1) * sizeof(char));
                    assert(commande != NULL);
                    remplirChar(f,t,commande);
                    t = taille(f);
                    arg1 = malloc((t+1) * sizeof(char));
                    assert(arg1 != NULL);
                    remplirChar(f,t,arg1);
                    t = taille(f);
                    arg2 = malloc((t+1) * sizeof(char));
                    assert(arg2 != NULL);
                    remplirChar(f,t,arg2);
                    commande2(commande, arg1, arg2, &pgrm);
                    free(commande);
                    free(arg1);
                    free(arg2);
                    break;
            }
            if (!avanceSautDeLigne(f)) break;
           avanceEspace(f);
    }
    destroySousArbre(n);
}