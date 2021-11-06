/*
*******************************************************************************

            -------------      fonctions_utiles.h      -------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Cr�ation: 05/09/2021
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

//Cr�ation de la fen�tre
SDL_Surface* EcranPrincipal(SDL_Surface *ecranEntier);

//Mets en pause le programme pour pouvoir visualiser la courbe
void Attendre();

//Tra�age par pixel, fonction tir�e dans la doc de SDL
void SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);



//      --- Traitement de chaine de caract�re ---

//Convertis une chaine de caract�re en une liste de double
int StringVersTabDbl(char *chaine, int longueurChaine, double tableauDouble[]);

//Coupe une chaine de caract�re au bout d'un caract�re sp�cifi� (inclu)
int strcutback(char *chaineACoupe, char dernierCaractere);



//      -------- Quelques fonctionnalit�s --------

//Ouvre automatiquement le fichier stderr.txt
void OuvreMessageErreur(char *pathDuProgramme);

//Traitement des param�tres lorsque le programme est lanc� avec des param�tres
BOOL TraitementParLigneDeCommande(SDL_Surface *ecranEntier, int argc, char *argv[]);



#endif // FONCTIONS_UTILES_H_INCLUDED
