/*------------------------------------------------------------------------*/
/* FCHIER:                          vente.h                               */
/*AUTEUR:                           JEAN David Kehl                       */    
/*DATE DE CREATIION:                26/09/2025                            */  
/*DATE DE MODIFICATION:             27/09/2025                            */ 
/*DESCRIPTION:                      fichier contenant les nouveaux types de
                                    données, les prototypes, les structures 
                                    de données et les constantes          */    
/*------------------------------------------------------------------------*/ 

// structure vente
typedef struct {
    int id_vente;
    int id_prod;
    char dat_vente[11]; // format "JJ/MM/AAAA"
    int qte_vendue;
    float prix_unit;
    float prix_total;
} Vente;
