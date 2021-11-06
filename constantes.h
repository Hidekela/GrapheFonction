/*
*******************************************************************************

            -------------        constantes.h          -------------

*******************************************************************************
______________________________ Auteur: Hidekela _______________________________

            Cr�ation: 05/09/2021
            Dernier modification: 05/09/2021
            ________________________________________________________

*******************************************************************************

           Des constantes et types de variables personnalis�es utiles

_______________________________________________________________________________
*******************************************************************************
*/
#ifndef CONSTANTE_H_INCLUDED
#define CONSTANTE_H_INCLUDED

#define SCREENWIDTH 810
#define SCREENHEIGHT 610
#define RANG 4 //unit�s de la num�ration pour l'�chelle, exemple: 2 pour les dizaines
#define ECHELLE 20
#define SAUT 1 //saut de valeur sur l'�chelle
#define DIST_ORIG 20
#define X_0 DIST_ORIG
#define Y_0 SCREENHEIGHT - DIST_ORIG
#define FONT_SIZE ECHELLE/2

enum BOOL
{
    FALSE, TRUE
};
typedef enum BOOL BOOL;

struct point
{
    double x;
    double y;
};
typedef struct point point;

#endif // CONSTANTE_H_INCLUDED
