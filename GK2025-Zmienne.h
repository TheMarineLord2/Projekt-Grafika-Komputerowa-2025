// zmienne globalne
#ifndef GK2025_ZMIENNE_H_INCLUDED
#define GK2025_ZMIENNE_H_INCLUDED

#include <SDL2/SDL.h>

#define szerokosc 640
#define wysokosc 400

#define tytul "GK2025 - Projekt - Zespol XX"

extern SDL_Window* window;
extern SDL_Surface* screen;

extern SDL_Color paleta8[szerokosc*wysokosc];


extern SDL_Color paleta8k[256];
extern SDL_Color paleta8s[256];

extern int ileKolorow6;
extern int ileKolorow8;
extern int sqr_size;

extern SDL_Color paleta6[szerokosc*wysokosc];
extern SDL_Color paleta8k[256];
extern SDL_Color paleta8s[256];
extern SDL_Color paleta6k[64];
extern SDL_Color paleta6s[64];

// tablicaBledow ma dwie wartosci, zeby byc przygotowana na przyjmowanie odchylen
// na plus i na minus od rysowanej wartosci
// [0] - nastepny kolor intenstywniej [1], nastepny kolor lzej
extern SDL_Color tablicaBledow[szerokosc/2][wysokosc/2][2];
// zmienne float do propagowania bledow
extern double siedem16;
extern double trzy16;
extern double piec16;
extern double jedna16;

#endif // GK2025_ZMIENNE_H_INCLUDED
