#include <stdio.h>

/*
 * Fonction : generer_cle_aleatoire
 * Description : Génère une clé pseudo-aléatoire de 6 caractères en se basant sur 
 * l'heure de compilation du programme (__TIME__) et des calculs arithmétiques.
 * Paramètre : char cle[] - Le tableau de destination qui recevra la clé (doit avoir une taille d'au moins 7).
 */
void generer_cle_aleatoire(char cle[]) {
    const char *t = __TIME__;           // Chaîne contenant l'heure de compilation au format "HH:MM:SS"

    // Conversion des caractères de l'heure en entiers
    int h0 = t[0] - '0';                // Premier chiffre de l'heure
    int h1 = t[1] - '0';                // Second chiffre de l'heure
    int m0 = t[3] - '0';                // Premier chiffre des minutes
    int m1 = t[4] - '0';                // Second chiffre des minutes
    int s0 = t[6] - '0';                // Premier chiffre des secondes
    int s1 = t[7] - '0';                // Second chiffre des secondes

    // Construction d'un nombre entier à partir des chiffres du temps
    int heure = h0*100000 + h1*10000 + m0*1000 + m1*100 + s0*10 + s1;

    // Calcul de la graine (seed) par des opérations arithmétiques pour le pseudo-aléatoire
    int seed = (heure * (s1 + 3)) 
               - (h0 * h1 * 97) 
               + (m0 + 1) * (m1 + 7) * 53 
               - (s0 + 5) * (s1 + 11) * 29 
               + (heure / (h1 + 1)) 
               - (m1 * 112);

    printf("Seed = %d\n", seed);

    int tab_seed[6];                    // Tableau pour stocker chaque chiffre de la seed
    int temp = seed;                    // Variable temporaire pour décomposer la seed sans la perdre

    // Extraction des 6 derniers chiffres de la seed pour remplir le tableau
    for (int i = 5; i >= 0; i--) {
        tab_seed[i] = temp % 10;
        temp = temp / 10;
    }

    // Construction de la clé finale en mélangeant majuscules et minuscules
    cle[0] = tab_seed[0] + 'A';         // Premier caractère (Majuscule)
    cle[1] = tab_seed[1] + 'A';         // Deuxième caractère (Majuscule)
    cle[2] = tab_seed[2] + 'a';         // Troisième caractère (Minuscule)
    cle[3] = tab_seed[3] + 'A';         // Quatrième caractère (Majuscule)
    cle[4] = tab_seed[4] + 'A';         // Cinquième caractère (Majuscule)
    cle[5] = tab_seed[5] + 'a';         // Sixième caractère (Minuscule)
    cle[6] = '\0';                      // Caractère de fin de chaîne

    printf("Cle aleatoire = %s\n", cle);
}