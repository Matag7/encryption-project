#include <stdio.h>

/*
 * Fonction : afficher_en_tete
 * Description : Affiche le bandeau stylisé du projet.
 */
void afficher_en_tete() {
    printf("\033[1;36m"); // Cyan
    printf("==================================================\n");
    printf("||                                              ||\n");
    printf("||        PROJET : CHIFFREMENT VIGENERE         ||\n");
    printf("||                GROUPE E02                    ||\n");
    printf("||                                              ||\n");
    printf("==================================================\n");
    printf("\033[0m"); 
}

/*
 * Fonction : afficher_menu
 * Description : Affiche les options du menu principal.
 */
void afficher_menu() {
    printf("\n\033[1;33m--- MENU PRINCIPAL ---\033[0m\n");
    printf("1. Generer une cle aleatoire\n");
    printf("2. Chiffrer un message\n");
    printf("3. Dechiffrer un message\n");
    printf("4. Sauvegarder dans un fichier\n");
    printf("5. Lire un fichier texte\n");
    printf("6. Saisir une cle manuellement\n");
    printf("0. Quitter le programme\n");
    printf("\nVotre choix : ");
}