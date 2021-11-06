/*
*******************************************************************************

            -------------      fonctions_graphes.h      -------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Cr�ation: 05/09/2021
            Dernier modification: 05/09/2021
            ________________________________________________________

*******************************************************************************

                Prototypes des fonctions dans fonctions_graphes.c

_______________________________________________________________________________
*******************************************************************************
*/
#ifndef FONCTIONS_GRAPHES_H_INCLUDED
#define FONCTIONS_GRAPHES_H_INCLUDED

#include <SDL_ttf.h>

//Tra�age du r�p�re orthonorm�
void Repere(SDL_Surface *ecranEntier, SDL_Surface *axeX, SDL_Surface *axeY, SDL_Surface *echelle, SDL_Surface *x, SDL_Surface *y, TTF_Font *police);

//Tra�age des nuages de points
void NuageDePoint(SDL_Surface *ecranEntier, point pointsParticuliers[], int nombreDePointsParticuliers);

//Tra�age de l'allure des fonctions
void TraceDeCourbe(SDL_Surface *ecranEntier, double fonction[], int degree);

#endif // FONCTIONS_GRAPHES_H_INCLUDED
