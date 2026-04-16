#include <stdio.h>
#include <stdlib.h>

/* * Fonction : len
 * Description : Reproduit la fonction strlen sans string.h
 * Paramètres : phrase - Chaine de caractères dont il faut déterminer la longueur
 */

int len(const char* phrase){
    int len=0;
    while(phrase[len]!='\0'){
        len++;
    }
    return len;
}

/*
 * Fonction : visual
 * description : Affiche une barre de chargement représentant la progression du déchiffrement
 * Paramètres : plein - Avancement de la tâche
 */

void visual(int plein){
    // Utilisation de la boucle de l'ancienne version pour l'affichage complet
    while (plein <= 20){
        printf("\rProgression : [");
        for (int i=0; i<plein; i++){
            printf("#");
        }
        for (int j=20; j>=plein+1; j=j-1){
            printf("-");
        }
        printf("] %d%%", plein*5);
        plein+=1;
        fflush(stdout);
    }
}

/*
 * Fonction : dechiffrement
 * Description : Déchiffre le code vigénaire en utilisant la clé fournie
 * Paramètres : code - chaine de caractères à décoder
 * simplekey - clé à utiliser, non répétée.
 */

char* dechiffrement(char code[], char simplekey[]){

    int longueur_code = len(code);
    
    // Sécurité 1 : Si le code est vide, on s'arrête tout de suite
    if (longueur_code == 0) {
        char *vide = malloc(1);
        vide[0] = '\0';
        return vide;
    }

    char minus = 'a';
    char* key=malloc((len(code)+1)*sizeof(char));
    char *decode=malloc((len(code)+1)*sizeof(char));
    
    // Initialisation pour éviter les erreurs de lecture
    if (decode) decode[0] = '\0';

    int compteur_avancee=0;
    int decalage=0;
    int isMaj=0;    


    for (int i=0; i<len(code); i++){                //Ecriture de la clé en boucle
        if((code[i] >='a' && code[i]<='z')||(code[i]>='A' && code[i]<='Z')){
            key[i]=simplekey[(i-decalage)%len(simplekey)];
            key[i+1]='\0';
            if(key[i]>='A' && key[i]<='Z') key[i]=key[i]+32;

            key[i+1]='\0';
        }else{                  //Si le code à l'emplacement i contient un caractère spécial, la lecture de la clé est décalée pour permettre un décodage correct. 
            decalage+=1;
            key[i] = code[i]; // On garde le caractère spécial dans la clé pour l'alignement
            key[i+1] = '\0';
        }
    }


    char minuscule[26][26];         //Tableau 2D format vigénère
    
    for (int i = 0; i < 26; i++){       //remplissage de la première ligne avec des lettres minuscules
        minuscule[0][i] = minus;
        minus+=1;
    }


    for (int j = 1; j < 26; j++) {      //remplissage du reste du tableau en suivant l'exemple de la première ligne, avec un décalage pour chaque nouvelle ligne
        for (int i = 0; i < 26; i++) {
            minuscule[j][i] = 'a'+(i+j)%26;
        }

    }



    for(int k=0; code[k] != '\0'; k++){                         //k est utilisé comme index dans plusieurs chaines de caractères. Code[k] représente le caractère en cours de décodage
                                                                //key[k] est le caractère de la clé qui permet le décodage du caractère codé
        if((code[k] >='a' && code[k]<='z')||(code[k]>='A' && code[k]<='Z')){        //Cette condition vérifie que le caractère encodé est une lettre. 
                                                                //Si ce n'en est pas une, le caractère est ajouté à la chaine de caractères décodés pour conserver la ponctuation et les espaces.
            if(code[k]>='A' && code[k]<='Z'){                   //Ce bloc de code transforme les lettres majuscules encodées en lettre minuscules encodées
                code[k]=code[k]+32;
                isMaj=1;
            }

            for(int l=0; l<26; l++){                        //Ce bloc de code cherche la lettre décodée en utilisant la lettre codée (code[k]) et la lettre associée de la clé (key[k]
                if(key[k]==minuscule[l][0]){
                    for(int m=0; m<26; m++){            
                        if(code[k]==minuscule[l][m]){
                            int n = 0;

                            while(decode[n]!='\0'){         //Ce bloc de code cherche la dernière position de la chaine de caractères "decode" pour y ajouter la lettre décodée plus tard
                                n++;
                            }

                            if(isMaj==1){               //Ce bloc de code transforme la lettre décodée minuscule en majuscule si elle était encodée en majuscule.
                                decode[n] = minuscule[0][m]-32;
                                decode[n+1] = '\0';
                                isMaj=0;
                            }else{
                                decode[n]=minuscule[0][m];
                                decode[n+1]='\0';
                            }
                        }
                    }
                }
            }
        }else{
            int n=0;
            while(decode[n]!='\0'){
                n++;
            }
            decode[n]=code[k];
            decode[n+1]='\0';
        }
    }

    // Appel unique de la fonction visuelle qui contient sa propre boucle de 0 à 100%
    visual(compteur_avancee);

    printf("\nOpération terminée avec succès.\n");
    free(key);
    return decode;
}