// metody do algorytmu kwantyzacji (MedianCut)
#ifndef GK2025_MEDIANCUT_H_INCLUDED
#define GK2025_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>

void paletaMedianCutBW();
void MedianCutBW_6bit(int start, int koniec, int iteracja);
void MedianCutBW(int start, int koniec, int iteracja);
void paletaMedianCutBW_6bit();
int znajdzSasiadaBW(Uint8 wartosc);
int znajdzSasiadaBW_6bit_64odcienieSzarego(Uint8 wartosc);
int znajdzSasiada(SDL_Color kolor);
int znajdzSasiada_6bit(SDL_Color kolor);
void paletaMedianCut();
void paletaMedianCut_6bit();
void MedianCut(int start, int koniec, int iteracja);
void MedianCut_6bit(int start, int koniec, int iteracja);
void sortujKubelekBW(int start, int koniec);
void sortujKubelek(int start, int koniec, Uint8 sortowanie);
Uint8 najwiekszaRoznica(int start, int koniec);

#endif // GK2025_MEDIANCUT_H_INCLUDED
