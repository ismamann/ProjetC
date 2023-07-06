Groupe 33 :
Bao Thinh DIEP
Ismaël DRICHE

Tout fonctionne correctement :

- ls : affiche ligne par ligne les fils existant.
- pwd : affiche le chemin.
- print : affiche toute l'arborescence
- cd :
        - cd : retour à la racine
        - cd .. : retour au père
        - cd chem : déplace au chemin
        - erreur : le chemin n'existe pas
- mkdir : creer le dossier
- touch : creer le fichier
        - erreur (pour mkdir et touch) : non existant et nom mal formé
- rm : supprime le sous arbre et le noeud à supprimer
        - erreur : le programme est dans l'arborescence à supprimer et le chemin n'existe pas.
- cp : copie le noeud et le sous arbre et le renomme vers le chemin donné.
        - erreur : nom existant, chemin n'existe ou se termine par '/'
- mv : déplace le neoud et le sous arbre et le renomme vers le chemin donné.
        - erreur : les mêmes que cp et rm.
