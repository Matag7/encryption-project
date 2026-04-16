#include <stdio.h>
#include <stdlib.h>

// --- FONCTIONS UTILITAIRES (Remplacent string.h) ---

/**
 * Calcule la longueur d'une chaîne de caractères (équivalent strlen)
 */
int ma_longueur(const char *s) {
    int i = 0;
    while (s[i] != '\0') i++;
    return i;
}

/**
 * Copie une chaîne source dans une destination (équivalent strcpy)
 */
void ma_copie(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

/**
 * Vérifie si la clé ne contient que des lettres (A-Z ou a-z)
 */
int cle_est_valide(char cle[]) {
    if (cle[0] == '\0') return 0;
    for (int i = 0; cle[i] != '\0'; i++) {
        char c = cle[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
            return 0;
        }
    }
    return 1;
}

// --- PROTOTYPES DES FONCTIONS ---
void afficher_en_tete();
void afficher_menu();
char* chiffrer_vigenere_table(char clair[], char cle[]); 
char* dechiffrement(char code[], char simplekey[]);
void signer_message(char crypte[]);
int verifier_integrite(char message_signe[]);
void generer_cle_aleatoire(char cle[]);
int ecrire_fichier(const char *nom_fichier, const char *texte); //
void lecture_fichier(const char *nom_fichier); //

int main() {
    int choix = -1;
    char *message = NULL;
    char cle_globale[100] = ""; 
    char *resultat = NULL;        // Dernier message chiffré
    char *message_decode = NULL;  // Dernier message déchiffré

    printf("\033[H\033[J");

    while (choix != 0) {
        afficher_en_tete();
        afficher_menu();
        
        if (scanf("%d", &choix) != 1) {
            printf("\n\033[1;31m[!] Erreur : Entrez un chiffre.\033[0m\n");
            while (getchar() != '\n'); 
            continue;
        }
        getchar();

        switch (choix) {
            case 1: // GENERER CLE
                generer_cle_aleatoire(cle_globale);
                printf("\n\033[1;32m[+] Cle actuelle : %s\033[0m\n", cle_globale);
                break;

            case 2: // CHIFFRER
                {
                    char cle_temp[100] = "";
                    char choix_c;
                    
                    if (cle_globale[0] != '\0') {
                        printf("\nUtiliser la cle [%s] ? (o/n) : ", cle_globale);
                        scanf(" %c", &choix_c); getchar();
                        if (choix_c == 'o' || choix_c == 'O') {
                            ma_copie(cle_temp, cle_globale);
                        }
                    }

                    if (cle_temp[0] == '\0') {
                        int valide = 0;
                        while(!valide) {
                            printf("\nEntrez votre cle (Lettres uniquement) : ");
                            scanf("%[^\n]", cle_temp); getchar();
                            if (cle_est_valide(cle_temp)) {
                                valide = 1;
                                ma_copie(cle_globale, cle_temp);
                            } else {
                                printf("\033[1;31m[!] Erreur : La cle ne doit contenir que des lettres.\033[0m\n");
                            }
                        }
                    }

                    message = malloc(5000 * sizeof(char));
                    printf("\nMessage a chiffrer : ");
                    scanf("%[^\n]", message); getchar();
                    
                    if (resultat != NULL) free(resultat);
                    resultat = chiffrer_vigenere_table(message, cle_temp);
                    
                    if (resultat != NULL) {
                        signer_message(resultat);
                        printf("\n\033[1;32m[V] Message chiffre avec succès.\033[0m\n");
                        printf("\033[1;32m[OK] Resultat :\033[0m %s\n", resultat);
                    }
                    free(message);
                }
                break;

            case 3: // DECHIFFRER
                {
                    char cle_temp[100] = "";
                    char choix_c;
                    int avec_checksum;

                    printf("\nUtiliser la cle actuelle [%s] ? (o/n) : ", cle_globale[0] == '\0' ? "AUCUNE" : cle_globale);
                    scanf(" %c", &choix_c); getchar();

                    if (choix_c == 'n' || choix_c == 'N' || cle_globale[0] == '\0') {
                        int valide = 0;
                        while(!valide) {
                            printf("Entrez la cle de dechiffrement : ");
                            scanf("%[^\n]", cle_temp); getchar();
                            if(cle_est_valide(cle_temp)) valide = 1;
                            else printf("\033[1;31m[!] Erreur : Cle invalide.\033[0m\n");
                        }
                    } else {
                        ma_copie(cle_temp, cle_globale);
                    }

                    char *temp_saisie = malloc(5000 * sizeof(char));
                    printf("\nEntrez le texte a dechiffrer : ");
                    scanf("%[^\n]", temp_saisie); getchar();

                    printf("\nLe message a-t-il une signature #XXXX ? (1: Oui / 0: Non) : ");
                    scanf("%d", &avec_checksum); getchar();
                
                    if (avec_checksum) {
                        if (verifier_integrite(temp_saisie)) {
                            printf("\n\033[1;32m[V] Checksum valide.\033[0m\n");
                            int i = 0;
                            while(temp_saisie[i] != '#' && temp_saisie[i] != '\0') i++;
                            temp_saisie[i] = '\0'; 
                            if (message_decode) free(message_decode);
                            message_decode = dechiffrement(temp_saisie, cle_temp);
                        } else {
                            printf("\n\033[1;31m[X] ERREUR : Checksum invalide !\033[0m\n");
                        }
                    } else {
                        if (message_decode) free(message_decode);
                        message_decode = dechiffrement(temp_saisie, cle_temp);
                    }
                    
                    if (message_decode) printf("\n\033[1;36mMessage d'origine :\033[0m %s\n", message_decode);
                    free(temp_saisie);
                }
                break;

            case 4: // SAUVEGARDER
                {
                    int choix_s;
                    printf("\n1. Sauvegarder CHIFFRE\n2. Sauvegarder DECHIFFRE\nChoix : ");
                    scanf("%d", &choix_s); getchar();

                    if (choix_s == 1 && resultat) {
                        ecrire_fichier("donnees.txt", resultat); //
                        printf("\n[+] Chiffre sauvegarde.\n");
                    } else if (choix_s == 2 && message_decode) {
                        ecrire_fichier("donnees.txt", message_decode); //
                        printf("\n[+] Dechiffre sauvegarde.\n");
                    } else {
                        printf("\n[!] Rien a sauvegarder.\n");
                    }
                }
                break;

            case 5: // LIRE
                lecture_fichier("donnees.txt"); //
                break;

            case 0: // QUITTER
                if (resultat) free(resultat);
                if (message_decode) free(message_decode);
                return 0;
        }
        printf("\nAppuyez sur Entree..."); getchar();
        printf("\033[H\033[J");
    }
    return 0;
}