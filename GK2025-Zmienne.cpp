// zmienne globalne
#include "GK2025-Zmienne.h"

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

SDL_Color paleta8[szerokosc*wysokosc];
int ileKolorow8 = 0;
SDL_Color paleta6[szerokosc*wysokosc];
int ileKolorow6 = 0;

int ileKubelkow = 0;
Uint8 obrazekS[320*200];
SDL_Color obrazekK[320*200];

int sqr_size = 10;

// palety maksymalnej liczby odcieni
// pamietac o wielkosci palet
SDL_Color paleta8k[256];
SDL_Color paleta8s[256];
SDL_Color paleta6k[64];
SDL_Color paleta6s[64];

int ileKubelkow = 0;
Uint8 obrazekS[320*200];
SDL_Color obrazekK[320*200];

// tablicaBledow ma dwie wartosci, zeby byc przygotowana na przyjmowanie odchylen
// na plus i na minus od rysowanej wartosci
// [0] - nastepny kolor intenstywniej [1], nastepny kolor lzej
SDL_Color tablicaBledow[szerokosc/2][wysokosc/2][2];
// wartosci do obliczenia propagowania bledow
double siedem16 = 7/16;
double trzy16 = 3/16;
double piec16 = 5/16;
double jedna16 = 1/16;
