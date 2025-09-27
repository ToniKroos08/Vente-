#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char nom[30];
    float prix;
} Produit;

int main() {
    Produit p = {1, "Clavier", 29.99};

    FILE *f = fopen("Hist_Ventes.dat", "ab"); // 'a' pour ajout, 'b' pour binaire
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 1;
    }

    fwrite(&p, sizeof(Produit), 1, f); // écriture binaire d'une structure
    fclose(f);

    return 0;
}
