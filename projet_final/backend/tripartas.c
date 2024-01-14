#include <stdio.h>
#include <stdlib.h>

void afficherTableau(int tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        printf("%d ", tableau[i]);
    }
    printf("\n");
}

void echanger(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void entasser(int tableau[], int taille, int indice, FILE *fichier) {
    int plusGrand = indice;
    int gauche = 2 * indice + 1;
    int droite = 2 * indice + 2;

    // Trouver le plus grand élément parmi le nœud et ses enfants
    if (gauche < taille && tableau[gauche] > tableau[plusGrand]) {
        plusGrand = gauche;
    }

    if (droite < taille && tableau[droite] > tableau[plusGrand]) {
        plusGrand = droite;
    }

    // Si le plus grand n'est pas la racine, échanger et récursivement entasser
    if (plusGrand != indice) {
        echanger(&tableau[indice], &tableau[plusGrand]);

        // Enregistrer l'étape du tri dans le fichier après chaque entassement
        

        // Réorganiser le tas pour exclure l'élément extrait
        entasser(tableau, taille, plusGrand, fichier);
    }
}

void triParTas(int tableau[], int taille, FILE *fichier) {
    // Construire le tas (réorganiser le tableau)
    for (int i = taille / 2 - 1; i >= 0; i--) {
        entasser(tableau, taille, i, fichier);
    }

    // Extraire un par un les éléments du tas
    for (int i = taille - 1; i > 0; i--) {
        // Échanger la racine actuelle avec la dernière feuille
        echanger(&tableau[0], &tableau[i]);


        // Réorganiser le tas pour exclure l'élément extrait
        entasser(tableau, i, 0, fichier);
         for (int k = 0; k < taille; k++) {
                printf("%d ", tableau[k]);
                }
            printf("\n");
        for (int j = 0; j < taille; j++) {
            fprintf(fichier, "%d ", tableau[j]);
        }
        fprintf(fichier, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez fournir les valeurs à trier.\n");
        return 1;
    }

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        printf("Impossible d'ouvrir le fichier de sortie.\n");
        return 1;
    }

    int n = argc - 1;
    int *values = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    
    afficherTableau(values, n);

    // Enregistrer l'étape initiale dans le fichier
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");

    triParTas(values, n, file);

    fclose(file);
    free(values);
    return 0;
}
