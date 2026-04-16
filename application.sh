#!/bin/sh

# On compile tous les fichiers .c du dossier src
# -Werror ne bloquera plus si on a bien supprimé les variables inutiles
gcc -Wall -Wextra -Werror -std=c11 ./src/*.c -o ./application

# On vérifie si le fichier "application" a bien été créé
if [ -f ./application ]; then
    echo "Compilation réussie. Lancement..."
    ./application
else
    echo "La compilation a échoué. Vérifiez les erreurs ci-dessus."
fi