#include <stdio.h>
#include <stdlib.h>

void triCocktail(int tableau[], int taille, FILE *fichier) {
    int debut = 0;
    int fin = taille - 1;
    int swap = 1;

    while (swap) {
        swap = 0;

        // Passage de gauche à droite
        for (int i = debut; i < fin; i++) {
            if (tableau[i] > tableau[i + 1]) {
                // Échanger les éléments si l'élément courant est plus grand que l'élément suivant
                int temp = tableau[i];
                tableau[i] = tableau[i + 1];
                tableau[i + 1] = temp;
                swap = 1;

                // Enregistrer l'étape du tri dans le fichier
                for (int j = 0; j < taille; j++) {
                    fprintf(fichier, "%d ", tableau[j]);
                }
                fprintf(fichier, "\n");

                // Affichage de l'étape du tri à des fins de visualisation
                for (int k = 0; k < taille; k++) {
                    printf("%d ", tableau[k]);
                }
                printf("\n");
            }
        }

        // Si aucun échange n'a eu lieu à gauche, le tableau est trié
        if (!swap) {
            break;
        }

        swap = 0;

        // Passage de droite à gauche
        for (int i = fin - 1; i >= debut; i--) {
            if (tableau[i] > tableau[i + 1]) {
                // Échanger les éléments si l'élément courant est plus grand que l'élément suivant
                int temp = tableau[i];
                tableau[i] = tableau[i + 1];
                tableau[i + 1] = temp;
                swap = 1;

                // Enregistrer l'étape du tri dans le fichier
                for (int j = 0; j < taille; j++) {
                    fprintf(fichier, "%d ", tableau[j]);
                }
                fprintf(fichier, "\n");

                // Affichage de l'étape du tri à des fins de visualisation
                for (int k = 0; k < taille; k++) {
                    printf("%d ", tableau[k]);
                }
                printf("\n");
            }
        }

        debut++;
        fin--;
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
    for (int i = 0; i < n; i++) {
        fprintf(file, "%d ", values[i]);
    }
    fprintf(file, "\n");

    triCocktail(values, n, file);

    fclose(file);
    free(values);
    return 0;
}
