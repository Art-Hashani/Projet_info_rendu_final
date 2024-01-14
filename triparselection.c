#include <stdio.h>
#include <stdlib.h>

void triSelection(int tableau[], int taille, FILE *fichier) {
    int minIdx;

    for (int i = 0; i < taille - 1; i++) {
        minIdx = i;

        for (int j = i + 1; j < taille; j++) {
            if (tableau[j] < tableau[minIdx]) {
                minIdx = j;
            }
        }

        // Échanger les éléments si nécessaire
        if (minIdx != i) {
            int temp = tableau[i];
            tableau[i] = tableau[minIdx];
            tableau[minIdx] = temp;

            // Enregistrer l'étape du tri dans le fichier
            for (int k = 0; k < taille; k++) {
                fprintf(fichier, "%d ", tableau[k]);
            }
            fprintf(fichier, "\n");

            // Affichage de l'étape du tri à des fins de visualisation
            for (int k = 0; k < taille; k++) {
                printf("%d ", tableau[k]);
            }
            printf("\n");
        }
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

    

    triSelection(values, n, file);

    fclose(file);
    free(values);

    return 0;
}
