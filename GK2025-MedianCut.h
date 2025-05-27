// metody do algorytmu kwantyzacji (MedianCut)
#ifndef GK2025_MEDIANCUT_H_INCLUDED
#define GK2025_MEDIANCUT_H_INCLUDED

#include <SDL2/SDL.h>

void paletaMedianCutBW();
void MedianCutBW(int start, int koniec, int iteracja);
void paletaMedianCutBW_6bit();
int znajdzSasiadaBW(Uint8 wartosc);
int znajdzSasiadaBW_6bit_64odcienieSzarego(Uint8 wartosc);
void sortujKubelekBW(int start, int koniec);

#endif // GK2025_MEDIANCUT_H_INCLUDED
