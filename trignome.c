#include <stdio.h>
#include <stdlib.h>

void triGnome(int tableau[], int taille, FILE *fichier) {
    int index = 0;

    while (index < taille) {
        if (index == 0 || tableau[index] >= tableau[index - 1]) {
            index++;
        } else {
            // Échanger les éléments si nécessaire
            int temp = tableau[index];
            tableau[index] = tableau[index - 1];
            tableau[index - 1] = temp;

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

            index--;
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
    printf("Étapes du tri Gnome :\n");

    triGnome(values, n, file);

    fclose(file);
    free(values);
    return 0;
}
