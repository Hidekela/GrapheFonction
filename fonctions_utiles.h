/*
*******************************************************************************

            -------------      fonctions_utiles.h      -------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Création: 05/09/2021
            Dernier modification: 05/09/2021
            ________________________________________________________

*******************************************************************************

                Prototypes des fonctions dans fonctions_utiles.c

_______________________________________________________________________________
*******************************************************************************
*/
#ifndef FONCTIONS_UTILES_H_INCLUDED
#define FONCTIONS_UTILES_H_INCLUDED



//      -----------     Pour SDL      -----------

//Création de la fenêtre
SDL_Surface* EcranPrincipal(SDL_Surface *ecranEntier);

//Mets en pause le programme pour pouvoir visualiser la courbe
void Attendre();

//Traçage par pixel, fonction tirée dans la doc de SDL
void SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);



//      --- Traitement de chaine de caractère ---

//Convertis une chaine de caractère en une liste de double
int StringVersTabDbl(char *chaine, int longueurChaine, double tableauDouble[]);

//Coupe une chaine de caractère au bout d'un caractère spécifié (inclu)
int strcutback(char *chaineACoupe, char dernierCaractere);



//      -------- Quelques fonctionnalités --------

//Ouvre automatiquement le fichier stderr.txt
void OuvreMessageErreur(char *pathDuProgramme);

//Traitement des paramètres lorsque le programme est lancé avec des paramètres
BOOL TraitementParLigneDeCommande(SDL_Surface *ecranEntier, int argc, char *argv[]);



#endif // FONCTIONS_UTILES_H_INCLUDED
