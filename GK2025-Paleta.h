// funkcje do redukcji kolor�w i tworzenia palet
#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
using namespace std;

void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
void paletaNarzucona();
//void narysujPalete(int px, int py, SDL_Color pal8[]);
void narysujPalete8bit(int px, int py, SDL_Color pal[]);
void narysujPalete6bit(int px, int py, SDL_Color pal[]);
// Kolory 24 bitowe są skanami ekranu, [r8 g8 b8]
// Kolory 8 i 6 bitowe są danymi wyjściowymi. Nasze -- ( r2 g2 b2 )/( Grey6 )

void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
void paletaNarzucona();

void czyscPalete8();
void czyscPalete6();

// funkcie przygotowane przez Doktora:
Uint8 z24Kdo8K(SDL_Color kolor);
SDL_Color z8Kdo24K(Uint8 kolor8bit);
// -- przygotowanie 6bitowego kolorowego do namalowaia
// -- przygotowanie 6bitowego szarego do namalowania
SDL_Color z6Kdo24K(Uint8 kolor6bit);
SDL_Color z6Sdo24K(Uint8 kolor6bit);
// -- przetłumaczenie pixela na 6kolorowy
// -- przetłumaczenie pixela na 6szary
Uint8 z24Kdo6K(SDL_Color kolor);
Uint8 z24Kdo6S(SDL_Color kolor);


void narysujPalete8bit(int px, int py, SDL_Color pal[]);
void narysujPalete6bit(int px, int py, SDL_Color pal[]);
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
int dodajKolor8(SDL_Color kolor);
int dodajKolor6(SDL_Color kolor);



// narysowanie narzuconej palety barw kolo
void paletaDedykowana();
void paletaNarzucona8();
void paletaNarzucona6();

#endif // GK2025_PALETA_H_INCLUDED
