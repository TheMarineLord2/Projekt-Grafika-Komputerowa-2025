#include "paleta_kolorow.h"

void czyscPalete();

void paletaMediantCut() {
    ileKubelkow = 0;
    ileKolorow = 0;
    czyscPalete();
    SDL_Color kolor;
    int numer = 0;
    int indeks = 0;

    for (int y=0; y<wysokosc/2; y++) {
        kolor = getPixel(x, y);
        obrazekK[numer] = {kolor.r, kolor.g kolor.b};
        setPixel(x + szerokosc/2, y, obrazekK[numer].g , obrazekK[numer].b);    
        numer++;
    }

    
}