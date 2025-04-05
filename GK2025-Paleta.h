#ifndef GK2025_KONWERSJE_H
#define GK2025_KONWERSJE_H

#include <SDL.h>
#include <cmath>
#include <iostream>

using namespace std;

// Narzucone wersje redukcji kolorów
void narzuconaV1();
void narzuconaV2();
void narzuconaV3();

// Konwersje między przestrzeniami kolorów
Uint8 z24Kdo8K(SDL_Color kolor);
SDL_Color z8Kdo24K(Uint8 kolor8bit);

Uint8 z24Kdo6K(SDL_Color kolor);
SDL_Color z6Kdo24K(Uint8 kolor6bit);

Uint8 z24Kdo6S(SDL_Color kolor);
SDL_Color z6Sdo24K(Uint8 kolor6bit);

// Palety i operacje paletowe
void paletaNarzucona8();
void paletaNarzucona6();
void narysujPalete(int px, int py, SDL_Color pal[]);
void paletaDedykowana8();

int sprawdzKolor8(SDL_Color kolor);
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor8(SDL_Color kolor);
int dodajKolor6(SDL_Color kolor);
void czyscPalete8();
void czyscPalete6();

#endif // GK2025_KONWERSJE_H
