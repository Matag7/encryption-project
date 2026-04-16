#include <stdio.h>  
#include <stdlib.h>  

/*
 * Fonction lecture_fichier
 * Lit un fichier texte ligne par ligne et affiche son contenu
 * Paramètre :
 *  - nom_fichier : chemin vers le fichier à lire
 */
void lecture_fichier(const char *nom_fichier)
{
    FILE *fichier;          // Pointeur vers le fichier
    char tab[1024];      // Tableau pour stocker chaque ligne lue

    /*
     * Ouverture du fichier en mode lecture ("r")
     * fopen retourne NULL si l'ouverture échoue
     */
    fichier = fopen(nom_fichier, "r");
    if (fichier == NULL)
    {
        // Message d'erreur si le fichier ne peut pas être ouvert
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    /*
     * Boucle de lecture :
     * fgets lit une ligne du fichier et la stocke dans tab
     * La lecture s'arrête quand fgets retourne NULL (fin de fichier)
     */
    while (fgets(tab, sizeof(tab), fichier) != NULL)
    {
        // Affiche la ligne lue dans le terminal
        printf("%s", tab);
    }

    /*
     * Fermeture du fichier
     * Toujours fermer un fichier ouvert pour éviter les fuites mémoire
     */
    fclose(fichier);
}
