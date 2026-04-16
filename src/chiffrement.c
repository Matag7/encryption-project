#include <stdio.h>
#include <stdlib.h>

/*
 * Fonction : chiffrer_vigenere_table
 * Description : Chiffre un texte en utilisant le carré de Vigenère (table 26x26).
 * Paramètres : 
 * - clair : le message d'origine saisi par l'utilisateur.
 * - cle   : la clé de chiffrement (générée ou saisie).
 * Retour : Un pointeur (char*) vers le message chiffré alloué en mémoire.
 */
char* chiffrer_vigenere_table(char clair[], char cle[]) {
    char table[26][26]; 
    int i, j;
    int taille_msg = 0, taille_cle = 0, pos_cle = 0;

    // 1. Initialisation de la table (Alphabets décalés : César 0 à 25)
    for (i = 0; i < 26; i++) {
        for (j = 0; j < 26; j++) {
            table[i][j] = ((i + j) % 26) + 'A';
        }
    }

    // 2. Calcul manuel des longueurs (pour se passer de string.h)
    while (clair[taille_msg] != '\0') taille_msg++;
    while (cle[taille_cle] != '\0') taille_cle++;

    // SÉCURITÉ : Si la clé est vide, on ne peut pas faire de modulo (%) 
    // Cela évite l'erreur "Floating point exception".
    if (taille_cle == 0) return NULL;

    // --- ALLOCATION DYNAMIQUE ---
    // On réserve de la place en mémoire : taille du message + 10 octets 
    // de marge pour pouvoir ajouter la signature (#XXXX) plus tard.
    char* crypte = malloc((taille_msg + 10) * sizeof(char));
    if (crypte == NULL) return NULL; // Sécurité si la mémoire RAM est pleine

    // 3. Boucle principale de chiffrement caractère par caractère
    for (i = 0; i < taille_msg; i++) {
        char c = clair[i];

        // On ne chiffre que les lettres de l'alphabet
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            int est_min = (c >= 'a' && c <= 'z');
            
            // On trouve la colonne dans la table (0 pour A, 25 pour Z)
            int col = (est_min) ? c - 'a' : c - 'A';
            
            // On récupère la lettre correspondante de la clé (en boucle via le modulo)
            char c_cle = cle[pos_cle % taille_cle];
            
            // On trouve la ligne correspondante dans la table
            int lig = (c_cle >= 'a' && c_cle <= 'z') ? c_cle - 'a' : c_cle - 'A';

            // On récupère le caractère chiffré à l'intersection ligne/colonne
            char res = table[lig][col];
            
            // On applique la casse d'origine (minuscule ou majuscule)
            crypte[i] = (est_min) ? res + 32 : res;

            // On fait avancer la clé uniquement si on a traité une lettre
            pos_cle++; 
        } 
        else {
            // Si c'est un espace ou un chiffre, on le recopie tel quel
            crypte[i] = c;
        }
    }
    
    // On ferme la chaîne de caractères avec le caractère nul
    crypte[taille_msg] = '\0';

    // On renvoie l'adresse de la zone mémoire créée
    return crypte; 
}