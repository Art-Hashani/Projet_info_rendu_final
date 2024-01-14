#include <stdio.h>
#include <stdlib.h>

void fusion(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Crée des tableaux temporaires
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copie les données dans les tableaux temporaires L[] et R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Fusionne les tableaux temporaires L[] et R[] en arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copie les éléments restants de L[], s'il y en a
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copie les éléments restants de R[], s'il y en a
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Libère la mémoire des tableaux temporaires
    free(L);
    free(R);
}

void triFusionNonRecursif(int arr[], int n,FILE *fichier) {
    int taille_actuelle, l;

    // Taille de sous-tableau de 1 à n/2
    for (taille_actuelle = 1; taille_actuelle <= n - 1; taille_actuelle = 2 * taille_actuelle) {
        // Fusionne les sous-tableaux de taille_actuelle
        for (l = 0; l < n - 1; l += 2 * taille_actuelle) {
            int m = l + taille_actuelle - 1;
            int r = (l + 2 * taille_actuelle - 1 < n - 1) ? (l + 2 * taille_actuelle - 1) : (n - 1);

            // Fusionne les sous-tableaux arr[l..m] et arr[m+1..r]
            fusion(arr, l, m, r);

            // Affiche le tableau à chaque étape
            for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
            for (int i = 0; i < n; i++) {
                fprintf(fichier,"%d ", arr[i]);
            }
            fprintf(fichier,"\n");
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
    triFusionNonRecursif(values,n, file);
    fclose(file);
    free(values);   
    return 0;
}