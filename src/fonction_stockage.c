#include <stdio.h>   
#include <stdlib.h>  

/*
 * Fonction ecrire_fichier
 * Écrit une chaîne de caractères dans un fichier texte.
 * Retourne 1 si tout s'est bien passé, 0 sinon.
 */
int ecrire_fichier(const char *nom_fichier, const char *texte)
{
    // Vérifie que le nom du fichier n'est pas NULL
    // et que le texte à écrire n'est pas NULL
    if (nom_fichier == NULL || texte == NULL)
    {
        // Message d'erreur si un des paramètres est invalide
        printf("Erreur : aucun fichier ou aucun texte\n");
        return 0; // Échec
    }

    // Déclare un pointeur de type FILE pour manipuler le fichier
    FILE *f = NULL;

    // Ouvre (ou crée) le fichier en mode écriture ("w")
    // Attention : écrase le fichier s'il existe déjà
    f = fopen(nom_fichier, "w");

    // Vérifie si l'ouverture du fichier a échoué
    if (f == NULL)
    {
        // Message d'erreur si le fichier n'a pas pu être ouvert
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nom_fichier);
        return 0; // Échec
    }

    // Écrit le texte dans le fichier suivi d'un retour à la ligne
    fprintf(f, "%s\n", texte);

    // Ferme le fichier pour libérer les ressources
    fclose(f);

    // Indique que l'écriture s'est bien déroulée
    return 1; // Succès
}

