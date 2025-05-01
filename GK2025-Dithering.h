#ifndef GK2025_DITHERING_H_INCLUDED
#define GK2025_DITHERING_H_INCLUDED

#include "GK2025-Pliki.h"

extern void wyzerujTabliceBledow();
extern void propagujBlad(SDL_Color wartosciBledow[], int x, int y);
extern void obliczIPropagujBlad(SDL_Color oryginal, SDL_Color malowany, int x, int y);
extern SDL_Color uzyskajKolorPoprawionyOBlod(SDL_Color oryginalny, int x, int y);


#endif
