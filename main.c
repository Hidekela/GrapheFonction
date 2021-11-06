/*
*******************************************************************************

            -------------------      main.c      -------------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Création: 05/09/2021
            Dernier modification: 05/09/2021
            ________________________________________________________

*******************************************************************************

  Fonction principale, utilise les fonctions nécessaires au programme entiers

_______________________________________________________________________________
*******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include "constantes.h"
#include "fonctions_utiles.h"
#include "fonctions_graphes.h"

int main(int argc, char *argv[])
{
    //Ecran principal
    SDL_Surface *ecranEntier = NULL;

    //Ce qui concerne le repere
    SDL_Surface *axeX = NULL, *axeY = NULL, *echelle = NULL, *abscisse = NULL, *ordonnee = NULL;
    TTF_Font *arial = NULL;

    /*
            Dans le cas où il n'y a pas de paramètres on charge les nuages et fonction par défaut
    */
    //Exemple de nuages de points
    point pointsParticuliers[] = {{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8}};
    //Considérer une fonction polynomiale tel que 1er éléments a_0, ... , nè éléments a_n
    double fonction[] = {0,0,0.0125};
    //Message (par défaut ou si il y a erreur alors on l'utilise)
    char message[] = "Affichage des nuages de points et fonction par défault:\n\nLes points particuliers = (1,1),(2,2),(3,3),(4,4),(5,5),(6,6),(7,7),(8,8)\nLa fonction = 0,0,0.0125 ou 0.0125x² + 0x + 0\n\nPour spécifier une fonction ou un point, faire comme ceci:\nstart GrapheFonction.exe /point (1,1) /fonction 1,-2,0.125 /fonction 6 /point (12,0)";

    //Prévention en cas d'erreur
    BOOL SansErreur = TRUE;

    SDL_Init(SDL_INIT_VIDEO);

    TTF_Init();

    ecranEntier = EcranPrincipal(ecranEntier);

    arial = TTF_OpenFont("arial.ttf", FONT_SIZE);

    Repere(ecranEntier,axeX,axeY,echelle,abscisse,ordonnee,arial);

    if(argc > 1)
    {
        SansErreur = TraitementParLigneDeCommande(ecranEntier,argc,argv);
    }
    else
    {
        TraceDeCourbe(ecranEntier,fonction,2);
        NuageDePoint(ecranEntier,pointsParticuliers,8);
        fprintf(stdout,"%s",message);
    }

    SDL_Flip(ecranEntier);

    Attendre();

    TTF_CloseFont(arial);
    TTF_Quit();

    //On libère les repères
    SDL_FreeSurface(axeX);
    SDL_FreeSurface(axeY);
    SDL_FreeSurface(echelle);
    SDL_FreeSurface(abscisse);
    SDL_FreeSurface(ordonnee);

    SDL_Quit();

    if(SansErreur == FALSE)
    {
        OuvreMessageErreur(argv[0]);
    }

    return EXIT_SUCCESS;
}
