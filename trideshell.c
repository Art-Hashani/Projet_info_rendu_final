#include <stdio.h>
#include <stdlib.h>

void triShell(int tableau[], int taille, FILE *fichier) {
    // Calcul des écarts pour le tri de Shell
    for (int ecart = taille / 2; ecart > 0; ecart /= 2) {
        for (int i = ecart; i < taille; i++) {
            int temp = tableau[i];
            int j;
            for (j = i; j >= ecart && tableau[j - ecart] > temp; j -= ecart) {
                tableau[j] = tableau[j - ecart];
            }
            tableau[j] = temp;

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

    triShell(values, n, file);

    fclose(file);
    free(values);
    return 0;
}
