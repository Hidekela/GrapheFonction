/*
*******************************************************************************

            -------------     fonctions_graphes.c      -------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Création: 05/09/2021
            Dernier modification: 05/09/2021
            ________________________________________________________

*******************************************************************************

                Tout ce qui concerne l'affichage et le traçage

_______________________________________________________________________________
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "constantes.h"
#include "fonctions_graphes.h"
#include "fonctions_utiles.h"

void Repere(SDL_Surface *ecranEntier, SDL_Surface *axeX, SDL_Surface *axeY, SDL_Surface *echelle, SDL_Surface *x, SDL_Surface *y, TTF_Font *police)
{
    int i,j;
    SDL_Rect position;
    position.x = X_0;
    SDL_Color blanc = {255,255,255};
    char valeur[RANG] = {0};

    //Abscisse
    axeX = SDL_CreateRGBSurface(SDL_HWSURFACE,SCREENWIDTH-DIST_ORIG,1,32,0,0,0,0);
    SDL_FillRect(axeX,NULL,SDL_MapRGB(ecranEntier->format,255,255,255));
    position.y = SCREENHEIGHT-DIST_ORIG;
    SDL_BlitSurface(axeX,NULL,ecranEntier,&position);

    //Ordonnée
    axeY = SDL_CreateRGBSurface(SDL_HWSURFACE,1,SCREENHEIGHT-DIST_ORIG,32,0,0,0,0);
    SDL_FillRect(axeY,NULL,SDL_MapRGB(ecranEntier->format,255,255,255));
    position.y = 0;
    SDL_BlitSurface(axeY,NULL,ecranEntier,&position);

    SDL_LockSurface(ecranEntier);
    //vecteur ordonnée
    SetPixel(ecranEntier,X_0 - 2,2,SDL_MapRGB(ecranEntier->format,255,255,255));
    SetPixel(ecranEntier,X_0 - 1,1,SDL_MapRGB(ecranEntier->format,255,255,255));
    SetPixel(ecranEntier,X_0 + 1,1,SDL_MapRGB(ecranEntier->format,255,255,255));
    SetPixel(ecranEntier,X_0 + 2,2,SDL_MapRGB(ecranEntier->format,255,255,255));
    //vecteur abscisse
    SetPixel(ecranEntier,SCREENWIDTH - 3,Y_0 - 2,SDL_MapRGB(ecranEntier->format,255,255,255));
    SetPixel(ecranEntier,SCREENWIDTH - 2,Y_0 - 1,SDL_MapRGB(ecranEntier->format,255,255,255));
    SetPixel(ecranEntier,SCREENWIDTH - 2,Y_0 + 1,SDL_MapRGB(ecranEntier->format,255,255,255));
    SetPixel(ecranEntier,SCREENWIDTH - 3,Y_0 + 2,SDL_MapRGB(ecranEntier->format,255,255,255));

    //échelle de 20px pour 1cm
    for(i=X_0;i<SCREENWIDTH-DIST_ORIG;i+=ECHELLE)
    {
        SetPixel(ecranEntier,i,Y_0 + 1,SDL_MapRGB(ecranEntier->format,255,255,255));
    }
    for(i=Y_0;i>DIST_ORIG;i-=ECHELLE)
    {
        SetPixel(ecranEntier,X_0 - 1,i,SDL_MapRGB(ecranEntier->format,255,255,255));
    }
    SDL_UnlockSurface(ecranEntier);

    //x et f(x)
    x = TTF_RenderText_Blended(police,"x",blanc);
    position.x = SCREENWIDTH - 10;
    position.y = Y_0+5;
    SDL_BlitSurface(x,NULL,ecranEntier,&position);
    y = TTF_RenderText_Blended(police,"f(x)",blanc);
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(y,NULL,ecranEntier,&position);

    //valeurs sur l'échelle
    position.y = Y_0+5;
    for(i=X_0-4,j=0;i<SCREENWIDTH-DIST_ORIG;i+=ECHELLE,j+=SAUT)
    {
        sprintf(valeur,"%d",j);
        echelle = TTF_RenderText_Blended(police,valeur,blanc);
        position.x = i;
        SDL_BlitSurface(echelle,NULL,ecranEntier,&position);
    }
    position.x = 0;
    for(i=Y_0-4,j=0;i>DIST_ORIG;i-=ECHELLE,j+=SAUT)
    {
        sprintf(valeur,"%d",j);
        echelle = TTF_RenderText_Blended(police,valeur,blanc);
        position.y = i;
        SDL_BlitSurface(echelle,NULL,ecranEntier,&position);
    }
}

void NuageDePoint(SDL_Surface *ecranEntier, point pointsParticuliers[], int nombreDePointsParticuliers)
{
    int i;
    double x, y;

    SDL_LockSurface(ecranEntier);
    for(i=0;i<nombreDePointsParticuliers;i++)
    {
        x = X_0 + pointsParticuliers[i].x*ECHELLE;
        y = Y_0 - pointsParticuliers[i].y*ECHELLE;

        if(x < (X_0+1) || x >= SCREENWIDTH-DIST_ORIG || y < 1 || y > Y_0)
        {
            SDL_UnlockSurface(ecranEntier);
            return;
        }

        SetPixel(ecranEntier,x-1,y,SDL_MapRGB(ecranEntier->format,255,100,100));
        SetPixel(ecranEntier,x+1,y,SDL_MapRGB(ecranEntier->format,255,100,100));
        SetPixel(ecranEntier,x,y,SDL_MapRGB(ecranEntier->format,255,100,100));
        SetPixel(ecranEntier,x,y+1,SDL_MapRGB(ecranEntier->format,255,100,100));
        SetPixel(ecranEntier,x,y-1,SDL_MapRGB(ecranEntier->format,255,100,100));
    }
    SDL_UnlockSurface(ecranEntier);
}

void TraceDeCourbe(SDL_Surface *ecranEntier, double fonction[], int degree)
{
    int i, j;
    double y, x;
    const int limit_x = SCREENWIDTH-DIST_ORIG;
    static int green = 0;//Pour différencier la couleur des fonctions si il y en a plusieurs
    Uint32 couleurFonction = SDL_MapRGB(ecranEntier->format,0,green,155);

    //Pour éviter le problème de pixel quand a_n > 1
    double yPrecedent = 0, diffY = -1;

    SDL_LockSurface(ecranEntier);
    for(x=X_0;x<limit_x;x++)
    {
        for(i=0,j=1,y=0;i<=degree;i++,j--)
        {
            y += floor(fonction[i]*pow(x - X_0,i)*pow(ECHELLE,j));
        }
//        y = log((x-X_0)/ECHELLE)*ECHELLE; //ou autre: exp, cos,...

        y = Y_0 - y;

        if(y < 0 || y > Y_0)
        {
            yPrecedent = 0;
            diffY = -1;
            continue;
        }

        SetPixel(ecranEntier,x,y,couleurFonction);

        //Réglage de traçage du pente
        if(diffY == -1)
        {
            yPrecedent = y;
            diffY++;
            continue;
        }

        diffY = fabs(y-yPrecedent)-1;
        if(diffY)
        {
            if(y-yPrecedent<0)
                for(i=yPrecedent-1;i>y;i--)
                {
                    SetPixel(ecranEntier,x,i,couleurFonction);
                }
            else
                for(i=yPrecedent+1;i<y;i++)
                {
                    SetPixel(ecranEntier,x,i,couleurFonction);
                }
            yPrecedent = y;
        }
    }
    SDL_UnlockSurface(ecranEntier);

    //On change la valeur de green et on s'assure qu'il soit entre 0 et 255
    green = green < 215 ? green + 41 : green + 41 - 255;//214 + 41 = 255

    return;
}
