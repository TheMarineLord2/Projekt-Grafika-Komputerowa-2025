// zmienne globalne
#include "GK2025-Zmienne.h"

SDL_Window* window = NULL;
SDL_Surface* screen = NULL;

SDL_Color paleta8[szerokosc*wysokosc];
int ileKolorow = 0;

SDL_Color paleta8k[256];
SDL_Color paleta8s[256];
// palety maksymalnej liczby odcieni
SDL_Color paleta6k[64];
SDL_Color paleta6s[64];
