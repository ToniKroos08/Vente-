#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // Pour la date

// Constantes pour les noms de fichiers
#define HIST_VENTES_FILE "Hist_Ventes.dat"
#define PRODUITS_FILE "produits.dat"

int mettre_a_jour_stock(int id_prod, int qte_vendue) {
    FILE *fp = fopen(PRODUITS_FILE, "rb+"); // Ouverture en lecture/écriture binaire
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier produits.dat");
        return 0;
    }

    Produit produit;
    int trouve = 0;
    long position = 0;

    // 1. Parcourir le fichier pour trouver le produit
    while (fread(&produit, sizeof(Produit), 1, fp) == 1) {
        if (produit.id_prod == id_prod) {
            trouve = 1;
            break; // Produit trouvé
        }
        position = ftell(fp); // Sauvegarde de la position pour le retour arrière
    }

    if (!trouve) {
        printf("Erreur : Produit d'ID %d non trouvé dans le stock.\n", id_prod);
        fclose(fp);
        return 0;
    }

    // 2. Vérifier la quantité disponible
    if (produit.prod_qte < qte_vendue) {
        printf("Erreur : Stock insuffisant pour le produit %d (Stock: %d, Demandé: %d).\n", 
               id_prod, produit.prod_qte, qte_vendue);
        fclose(fp);
        return 0;
    }

    // 3. Mettre à jour la quantité et l'enregistrer dans le fichier
    produit.prod_qte -= qte_vendue;

    // Retourner à la position où l'enregistrement commence
    // On recule de la taille de la structure Produit par rapport à la position actuelle (après la lecture)
    if (fseek(fp, -sizeof(Produit), SEEK_CUR) != 0) { 
        perror("Erreur lors du positionnement du curseur pour la mise à jour");
        fclose(fp);
        return 0;
    }

    // Écrire l'enregistrement mis à jour
    if (fwrite(&produit, sizeof(Produit), 1, fp) != 1) {
        perror("Erreur lors de l'écriture de la mise à jour du produit");
        fclose(fp);
        return 0;
    }

    printf("Stock du produit %d mis à jour. Nouvelle quantité : %d.\n", id_prod, produit.prod_qte);
    fclose(fp);
    return 1;
}



void generer_date_courante(char* date_str) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    // Formatage : DD/MM/YYYY
    strftime(date_str, 11, "%d/%m/%Y", t);
}




