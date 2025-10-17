#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pour la date
int main(){
Vente v;
int choix;

// Constantes pour les noms de fichiers
#define HIST_VENTES_FILE "Hist_Ventes.dat"
#define PRODUITS_FILE "produits.dat"

int ins_vente(Vente v) {
    // 1. Ouverture du fichier produits.dat
    FILE *fp_prod = fopen(PRODUITS_FILE, "rb+"); // Ouverture en lecture/écriture binaire
    if (fp_prod == NULL) {
        perror("Erreur lors de l'ouverture du fichier produits.dat");
        return 0;
    }

    Produit p;
    int produit_trouve = 0;
    long position = 0;

    // 2. Parcourir le fichier pour trouver le produit
    while (fread(&p, sizeof(Produit), 1, fp_prod) == 1) {
        if (p.id_prod == v.id_prod) {
            produit_trouve = 1;
            break; // Produit trouvé
        }
        position = ftell(fp_prod); // Sauvegarde de la position pour le retour arrière
    }

    if (!produit_trouve) {
        printf("Erreur : Produit d'ID %d non trouvé dans le stock.\n", v.id_prod);
        fclose(fp_prod);
        return 0;
    }

    // 3. Vérifier la quantité disponible
    if (p.prod_qte < v.qte_vendue) {
        printf("Erreur : Stock insuffisant pour le produit %d (Stock: %d, Demandé: %d).\n", 
               p.id_prod, p.prod_qte, v.qte_vendue);
        fclose(fp_prod);
        return 0;
    }

    // 4. Mettre à jour la quantité et l'enregistrer dans le fichier produits.dat
    p.prod_qte -= v.qte_vendue;

    // Retourner à la position où l'enregistrement commence
    // On recule de la taille de la structure Produit par rapport à la position actuelle (après la lecture)
    fseek(fp_prod, -sizeof(Produit), SEEK_CUR);
    fwrite(&p, sizeof(Produit), 1, fp_prod);
    printf("Stock du produit %d mis à jour. Nouvelle quantité : %d.\n", id_prod, p.prod_qte);
    fclose(fp_prod);

    //5. Effectuer la vente
    v.prix_unit = p.prix_unit;
    v.prix_total = v.prix_unit * v.qte_vendue;
    generer_date_courante(v.date_vente);

    //6. Enregistrement de la vente dans Hist_vente.dat
    FILE *fp_vente = fopen(HIST_VENTES_FILE, "ab");
    if (fp_vente == NULL) {
        perror("Erreur d'ouverture de Hist_Ventes.dat");
        return 0;
    }

    if (fwrite(&v, sizeof(Vente), 1, fp_vente) != 1) {
        perror("Erreur d'écriture de la vente");
        fclose(fp_vente);
        return 0;
    }

    fclose(fp_vente);
    printf("Vente enregistrée avec succès (ID vente : %d).\n", v.id_vente);
    return 1;

}

void generer_date_courante(char* date_str) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    // Formatage : DD/MM/YYYY
    strftime(date_str, 11, "%d/%m/%Y", t);
}



    do {
        printf("\n=== MENU VENTE ===\n");
        printf("1. Effectuer une vente\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                // Saisie des infos de vente
                printf("ID vente : ");
                scanf("%d", &v.id_vente)

                printf("Quantité vendue : ");
                scanf("%d", &v.qte_vendue);

                if (ins_vente(v)) {
                    printf(" Vente effectuée avec succès.\n");
                } else {
                    printf(" Échec de la vente.\n");
                }
                break;
            case 0:
                printf("Fermeture du programme.\n");
                break;

            default:
                printf("Option invalide.\n");
        }
    } while (choix != 0);

    return 0;
}



