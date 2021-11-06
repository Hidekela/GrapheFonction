# Graphe Fonction

Un programme qui montre les graphes d'une(plusieurs) fonction(s) polynomiale(s)

## Pré-requis

* [gcc](https://gcc.gnu.org/install/binaries.html) ou autre compilateur du langage C(IDE)
* [SDL 1.2.15](https://sourceforge.net/projects/libsdl/files/SDL/1.2.15/)
* [SDL-ttf 2.0.11](https://www.libsdl.org/projects/SDL_ttf/release-1.2.html)
* [SDL-image 1.2.12](https://www.libsdl.org/projects/SDL_image/release-1.2.html)
* arial.ttf

## Installation

Compiler avec des IDE comme CodeBlocks est facile. Par contre, si vous n'êtes pas sur windows et que vous utilisez gcc, executez cette commande:
``windres.exe -J rc -O coff -i ressources.rc -o ressource.res``
Puis
``gcc *.c -o GrapheFonction ressources.res -I"chemin/des/headers/de/SDL" -L "chemin/des/libs/de/SDL" -s -lSDLmain -lSDL_ttf -lSDL``
Remarque:
    - remplacer _chemin/des/headers/de/SDL_ par le chemin des headers (SDL.h,SDL_ttf)
    - remplacer _chemin/des/libs/de/SDL_ par le chemin des librairies (libSDLmain.a, SDL_ttf.lib)
    - si vous êtes sur windows, ajoutez _-lmingw32_ avant -lSDLmain et _-mwindows_ à la fin du commande

## Démarrage

Après compilation, lancez le programme dans le terminal ou cmd avec les paramètres:
    - /point (a,b)
    - /fonction d,c,b,a
en changeant a,b,... par des nombres

_exemple:_ ``start GrapheFonction /point (1,1) /fonction 1,-2,0.125 /fonction 6 /point (12,0)``

## Auteur

**Hidekela**
