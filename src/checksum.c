#include <stdio.h>
#include <stdlib.h> // Nécessaire pour malloc et free

/*
 * Fonction : calculer_checksum
 * Description : Calcule une empreinte numérique simple (somme ASCII modulo 10000)
 * pour vérifier l'intégrité du message.
 * Paramètre : char message[] - Le texte dont on veut calculer la signature.
 * Retour : int - Un code entre 0 et 9999.
 */
int calculer_checksum(char message[]) {
    int i = 0;                  // Indice de parcours
    int somme = 0;              // Cumul des valeurs ASCII

    while (message[i] != '\0') {
        somme = somme + (int)message[i];
        i++;
    }

    // On utilise un modulo 10000 pour obtenir un code à 4 chiffres maximum
    return somme % 10000;
}

/*
 * Fonction : signer_message
 * Description : Calcule le checksum et l'ajoute physiquement à la fin du message
 * chiffré sous la forme d'un séparateur '#' suivi de 4 chiffres.
 * Exemple : "MONMESSAGE" -> "MONMESSAGE#1234"
 */
void signer_message(char crypte[]) {
    int signature = calculer_checksum(crypte); // Calcul du code
    int taille = 0;                            // Position de la fin de chaîne

    // Trouver la fin du message chiffré
    while (crypte[taille] != '\0') {
        taille++;
    }

    // Ajout du séparateur
    crypte[taille] = '#';
    
    // Conversion manuelle de l'entier en caractères
    // On décompose le nombre de 0 à 9999
    crypte[taille + 1] = (signature / 1000) + '0';         // Milliers
    crypte[taille + 2] = ((signature / 100) % 10) + '0';    // Centaines
    crypte[taille + 3] = ((signature / 10) % 10) + '0';     // Dizaines
    crypte[taille + 4] = (signature % 10) + '0';            // Unités
    crypte[taille + 5] = '\0';                             // Nouvelle fin de chaîne
}

/*
 * Fonction : verifier_integrite
 * Description : Sépare le message de sa signature, recalcule le checksum du message
 * et le compare à la signature fournie.
 * Retour : 1 si valide, 0 si corrompu.
 */
int verifier_integrite(char message_signe[]) {
    // MODIFICATION : On utilise un pointeur pour une allocation dynamique
    char *message_pur = NULL;      
    int i = 0, j = 0;
    int sep_pos = -1;           // Position du caractère '#'

    // 1. Chercher le dernier '#'
    while (message_signe[i] != '\0') {
        if (message_signe[i] == '#') {
            sep_pos = i;
        }
        i++;
    }

    if (sep_pos == -1) return 0; // Pas de signature trouvée

    // 2. Extraire le message pur avec malloc pour éviter le Segmentation Fault
    message_pur = malloc((sep_pos + 1) * sizeof(char));
    if (message_pur == NULL) return 0;

    for (j = 0; j < sep_pos; j++) {
        message_pur[j] = message_signe[j];
    }
    message_pur[j] = '\0';

    // 3. Recalculer le checksum du message pur
    int checksum_calcule = calculer_checksum(message_pur);

    // 4. Extraire et convertir la signature numérique reçue
    int signature_recue = 0;
    signature_recue += (message_signe[sep_pos + 1] - '0') * 1000;
    signature_recue += (message_signe[sep_pos + 2] - '0') * 100;
    signature_recue += (message_signe[sep_pos + 3] - '0') * 10;
    signature_recue += (message_signe[sep_pos + 4] - '0');

    // Libération de la mémoire allouée pour le message temporaire
    free(message_pur);

    // 5. Comparaison finale
    if (checksum_calcule == signature_recue) {
        return 1; // Succès : l'intégrité est garantie
    } else {
        return 0; // Erreur : le message a été modifié
    }
}