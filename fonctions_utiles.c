/*
*******************************************************************************

            -------------      fonctions_utiles.c      -------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Création: 05/09/2021
            Dernier modification: 05/09/2021
            ________________________________________________________

*******************************************************************************

  Quelques fonctionnalité utiles et nécessaire au fonctionnement du programme

_______________________________________________________________________________
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_image.h>
#include "constantes.h"
#include "fonctions_utiles.h"
#include "fonctions_graphes.h"

SDL_Surface* EcranPrincipal(SDL_Surface *ecranEntier)
{
    SDL_WM_SetIcon(IMG_Load("Icone.png"),NULL);
    SDL_WM_SetCaption("Graphe de la courbe",NULL);
    ecranEntier = SDL_SetVideoMode(SCREENWIDTH,SCREENHEIGHT,32,SDL_HWSURFACE);
    if(ecranEntier == NULL)
    {
        fprintf(stderr,"Erreur : \n%s",SDL_GetError());
        exit(EXIT_FAILURE);
    }

    return ecranEntier;
}

void Attendre()
{
    int continuer = 1;
    SDL_Event event;
    while(continuer)
    {
        SDL_WaitEvent(&event);
        continuer = event.type == SDL_QUIT? 0 : 1 ;
    }
}

void SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    switch(bpp)
    {
        case 1:
            *p = pixel;
            break;
        case 2:
            *(Uint16 *)p = pixel;
            break;
        case 3:
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            {
                p[0] = (pixel >> 16) & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = pixel & 0xff;
            } else {
                p[0] = pixel & 0xff;
                p[1] = (pixel >> 8) & 0xff;
                p[2] = (pixel >> 16) & 0xff;
            }
            break;
        case 4:
            *(Uint32 *)p = pixel;
            break;
    }
}

int StringVersTabDbl(char *chaine, int longueurChaine, double tableauDouble[])
{
    //Prendre la taille de tableauDouble comme supérieur au nombre de virgules
    int i, j = 0, tailleTab = 0;
    if(chaine[0] == ',' || chaine[longueurChaine-1] == ',')
        return 0;
    for(i=1;i<longueurChaine;i++)
    {
        if(chaine[i] == ',')
        {
            sscanf(chaine,"%lf,%s",&tableauDouble[j++],chaine);
            if(chaine[0] == ',')//Si la nouvelle chaine commence par ',' alors on sort
                return 0;
            longueurChaine = longueurChaine - i - 1;
            i = 0;//À la fin du boucle i sera incrémenté en 1 et on revient à la condition initiale
        }
    }
    sscanf(chaine,"%lf",&tableauDouble[j++]);
    tailleTab = j;
    return tailleTab;
}

int strcutback(char *chaineACoupe, char dernierCaractere)
{
    int i, longueurChaine = strlen(chaineACoupe);
    for(i=longueurChaine-1;i>=0;i--)
    {
        if(chaineACoupe[i] == dernierCaractere)
        {
            chaineACoupe[++i] = '\0';
            return i;//Retourne la nouvelle longueur du chaine
        }
    }
    return 0;
}

void OuvreMessageErreur(char *pathDuProgramme)
{
    char chemin[100] = {0}, action[100] = {0};

    fprintf(stderr,"Les paramètres saisis ne sont pas corrects!\n");

    strcpy(chemin,pathDuProgramme);

    if(!strcutback(chemin,'\\'))
        return;

    sprintf(action,"start notepad %sstderr.txt",chemin);
    system(action);
}

BOOL TraitementParLigneDeCommande(SDL_Surface *ecranEntier, int argc, char *argv[])
{


    int i;
    //Les coordonnées saisis par l'utilisateur
    point pointSaisi[] = {{-1,-1}};
    //Les fonctions saisis par l'utilisateur
    double fonction[50] = {-1};
    int degree = -1;

    if(argc%2) // == 1 donc impaire alors on utilise les paramètres
    {
        for(i=1;i<argc;i++)
        {
            if(!strcmp(argv[i],"/point"))//Si elles sont les mêmes
            {
                sscanf(argv[++i],"(%lf,%lf)",&(pointSaisi[0].x),&(pointSaisi[0].y));
                if(pointSaisi[0].x < 0 || pointSaisi[0].y < 0)
                    return FALSE;

                NuageDePoint(ecranEntier,pointSaisi,1);

                //Réinitialiser les coordonnées en -1 pour s'assurer du saisi suivant
                pointSaisi[0].x = -1;
                pointSaisi[0].y = -1;
            }
            else if(!strcmp(argv[i],"/fonction"))//Si elles sont les mêmes
            {
                i++;
                degree = StringVersTabDbl(argv[i],strlen(argv[i]),fonction) - 1;
                if(degree<0)
                    return FALSE;

                TraceDeCourbe(ecranEntier,fonction,degree);

                //Réinitialiser le dégrée de la fonction en -1 pour s'assurer du saisi suivant
                degree = -1;
            }
        }
        return TRUE;
    }
    return FALSE;
}
