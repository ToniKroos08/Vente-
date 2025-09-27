include <stdio.h>

int main() {
    FILE *f = fopen("Hist_Ventes.dat", "a"); // ouvrir pour écrire à la fin
    if (f == NULL) {
        printf("Erreur d'ouverture.\n");
        return 1;
    }

    fprintf(f, "Texte ajouté dans le fichier.\n"); // écriture
    fclose(f);

    return 0;
}
