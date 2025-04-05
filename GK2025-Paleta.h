// funkcje do redukcji kolorów i tworzenia palet
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
void narysujPalete(int px, int py, SDL_Color pal8[]);
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2);
int dodajKolor(SDL_Color kolor);
void paletaDedykowana();
void paletaNarzucona6();
#endif // GK2025_PALETA_H_INCLUDED
