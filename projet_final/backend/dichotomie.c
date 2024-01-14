#include <stdio.h>
#include <stdlib.h>

// Fonction de tri par dichotomie
void dichotomySort(int arr[], int n, FILE *outputFile) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        // Effectuer la recherche dichotomique pour insérer la clé à la bonne position
        int left = 0;
        int right = i - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            if (arr[mid] < key) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Déplacer les éléments plus grands que la clé vers la droite
        while (j >= left) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[left] = key;

        // Afficher l'étape du tri à la console
        for (int k = 0; k < n; k++) {
            printf("%d ", arr[k]);
        }
        printf("\n");

        // Écrire l'étape du tri dans le fichier
        for (int k = 0; k < n; k++) {
            fprintf(outputFile, "%d ", arr[k]);
        }
        fprintf(outputFile, "\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Veuillez fournir les valeurs à trier.\n");
        return 1;
    }

    int n = argc - 1;
    int *values = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        values[i] = atoi(argv[i + 1]);
    }

    // Afficher les valeurs initiales à la console
    printf("Valeurs initiales :\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
    }
    printf("\n");

    // Ouvrir le fichier de sortie en mode écriture
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        return 1;
    }

    // Écrire les valeurs initiales dans le fichier
    for (int i = 0; i < n; i++) {
        fprintf(outputFile, "%d ", values[i]);
    }
    fprintf(outputFile, "\n");

    

    // Appeler la fonction de tri en passant le fichier de sortie
    dichotomySort(values, n, outputFile);

    // Fermer le fichier de sortie
    fclose(outputFile);

    free(values);
    return 0;
}