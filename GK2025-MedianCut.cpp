// metody do algorytmu kwantyzacji (MedianCut)
#include "GK2025-MedianCut.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"
#include "GK2025-Paleta.h"

using namespace std;


void paletaMedianCutBW(){
    ileKubelkow = 0;
    ileKolorow8 = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary = 0;
    int numer = 0;
    int indeks = 0;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            szary = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            obrazekS[numer] = szary;
            setPixel(x+szerokosc/2, y, szary, szary, szary);
            numer++;
        }
    }
    MedianCutBW(0, numer-1, 3);

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            szary = getPixel(x + szerokosc/2, y).r;
            indeks = znajdzSasiadaBW(szary);
            setPixel(x, y + wysokosc/2, paleta8s[indeks].r, paleta8s[indeks].g, paleta8s[indeks].b);
        }
    }
    narysujPalete3b(0, 310, paleta8s);

    SDL_UpdateWindowSurface(window);

    numer = 0;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            szary = obrazekS[numer];
            setPixel(x+szerokosc/2,y+wysokosc/2,szary,szary,szary);
            numer++;
        }
    }
    SDL_UpdateWindowSurface(window);

}

void paletaMedianCutBW_6bit(){
    ileKubelkow = 0;
    ileKolorow6 = 0;
    czyscPalete();
    SDL_Color kolor;
    int szary = 0;
    int numer = 0;
    int indeks = 0;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            kolor = getPixel(x,y);
            szary = 0.299*kolor.r + 0.587*kolor.g + 0.114*kolor.b;
            obrazekS[numer] = szary;
            setPixel(x+szerokosc/2, y, szary, szary, szary);
            numer++;
        }
    }

    //algorytm generuje 64 odcienie szarosci
    MedianCutBW(0, numer-1, 6);

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            szary = getPixel(x + szerokosc/2, y).r;
            indeks = znajdzSasiadaBW_6bit_64odcienieSzarego(szary);
            setPixel(x, y + wysokosc/2, paleta6s[indeks].r, paleta6s[indeks].g, paleta6s[indeks].b);
        }
    }
    narysujPalete_6bit_64odcienie_szarego(0, wysokosc/2, paleta6s);

    SDL_UpdateWindowSurface(window);

    numer = 0;

    for(int y=0; y<wysokosc/2; y++){
        for(int x=0; x<szerokosc/2; x++){
            szary = obrazekS[numer];
            setPixel(x+szerokosc/2,y+wysokosc/2,szary,szary,szary);
            numer++;
        }
    }
    SDL_UpdateWindowSurface(window);

}




void MedianCutBW(int start, int koniec, int iteracja){

    if(iteracja > 0){

        for(int i=0; i<iteracja; i++) cout << " ";
        cout << "start: " << start<<", koniec: "<<koniec<<", iteracja:"<<iteracja<<endl;
        if(iteracja>0){
            for(int i=0; i<iteracja; i++) cout<<" ";
            cout<<"Dzielimy kubelek na poziomie "<<iteracja<<endl;

            sortujKubelekBW(start, koniec);
            int srodek = (start+koniec+1)/2;

            MedianCutBW(start, srodek-1, iteracja-1);
            MedianCutBW(srodek, koniec, iteracja-1);
        }
    }else{
        int sumaBW = 0;
        for(int p=start; p<=koniec; p++){
            sumaBW += obrazekS[p];
        }
        Uint8 noweBW = sumaBW / (koniec+1-start);
        SDL_Color nowyKolor = {noweBW, noweBW, noweBW};
        paleta6s[ileKubelkow] = nowyKolor;

        cout << "Kubelek "<<ileKubelkow;
        cout<<"(s:"<<start<<", k:"<<koniec<<", e:"<<(koniec+1-start)<<")";
        cout<<endl;
        cout<<"Kolor "<<ileKubelkow<<": ("<<(int)nowyKolor.r<<",";
        cout<<(int)nowyKolor.g<<","<<(int)nowyKolor.b<<")"<<endl;
        ileKubelkow++;

    }

}

void sortujKubelekBW(int start, int koniec){
    int minimum;
    for(int p=start; p<= koniec; p++){
        minimum = p;
        for(int i=p; i<=koniec; i++){
            if(obrazekS[i] < obrazekS[minimum])
                minimum = i;
        }
        swap(obrazekS[p], obrazekS[minimum]);
    }
}


int znajdzSasiadaBW(Uint8 wartosc){
    int minimum = 999;
    int indexMinimum = 0;

    int odleglosc = 0;

    for(int i=0; i<8; i++){
        odleglosc = abs(wartosc - paleta8s[i].r);
        if(odleglosc < minimum){
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}

int znajdzSasiadaBW_6bit_64odcienieSzarego(Uint8 wartosc){
    int minimum = 999;
    int indexMinimum = 0;

    int odleglosc = 0;

    for(int i=0; i<64; i++){
        odleglosc = abs(wartosc - paleta6s[i].r);
        if(odleglosc < minimum){
            minimum = odleglosc;
            indexMinimum = i;
        }
    }
    return indexMinimum;
}

