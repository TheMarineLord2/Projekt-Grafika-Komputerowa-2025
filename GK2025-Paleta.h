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
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
void paletaDedykowana();
void paletaNarzucona6();
SDL_Color z6Kdo24K(Uint8 kolor6bit);
int dodajKolor8(SDL_Color kolor);
#endif // GK2025_PALETA_H_INCLUDED
